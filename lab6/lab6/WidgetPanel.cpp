#include "WidgetPanel.h"

#include <QComboBox>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QMetaMethod>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QSlider>
#include <QSpinBox>
#include <QVBoxLayout>

namespace
{
// Описание поддерживаемого класса. Тип объекта определяется по QMetaObject,
// а какие сигнал/слот использовать - берётся из этой же таблицы.
struct TypeInfo
{
    const QMetaObject* meta;
    const char* title;
    const char* signal;   // nullptr - виджет ничего не сообщает другим
    const char* slot;     // nullptr - виджет не принимает значение
    QWidget* (*create)();
};

QWidget* createLabel()
{
    auto* w = new QLabel;
    w->setNum(0);
    w->setAlignment(Qt::AlignCenter);
    w->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    return w;
}

QWidget* createSlider()
{
    auto* w = new QSlider(Qt::Horizontal);
    w->setRange(0, 100);
    return w;
}

QWidget* createScrollBar()
{
    auto* w = new QScrollBar(Qt::Horizontal);
    w->setRange(0, 100);
    return w;
}

QWidget* createSpinBox()
{
    auto* w = new QSpinBox;
    w->setRange(0, 100);
    return w;
}

const TypeInfo kTypes[] = {
    { &QLabel::staticMetaObject,     "QLabel",     nullptr,             "setNum(int)",   createLabel },
    { &QSlider::staticMetaObject,    "QSlider",    "valueChanged(int)", "setValue(int)", createSlider },
    { &QScrollBar::staticMetaObject, "QScrollBar", "valueChanged(int)", "setValue(int)", createScrollBar },
    { &QSpinBox::staticMetaObject,   "QSpinBox",   "valueChanged(int)", "setValue(int)", createSpinBox },
};

constexpr int kTypeCount = sizeof(kTypes) / sizeof(kTypes[0]);

// Определяет класс объекта по метаинформации (без cast-преобразований).
const TypeInfo* typeOf(const QObject* obj)
{
    const QMetaObject* mo = obj->metaObject();
    for (const TypeInfo& t : kTypes) {
        if (mo->inherits(t.meta))
            return &t;
    }
    return nullptr;
}

QString linkKey(const QString& sender, const char* signal, const QString& receiver, const char* slot)
{
    return QStringLiteral("%1.%2 -> %3.%4").arg(sender, signal, receiver, slot);
}

// Перехват вывода qDebug: dumpObjectInfo() печатает только через qDebug.
QStringList* g_sink = nullptr;

void sinkHandler(QtMsgType, const QMessageLogContext&, const QString& msg)
{
    if (g_sink)
        g_sink->append(msg);
}

QStringList dumpLines(const QObject* obj)
{
    QStringList lines;
    g_sink = &lines;
    const QtMessageHandler prev = qInstallMessageHandler(sinkHandler);
    obj->dumpObjectInfo();
    qInstallMessageHandler(prev);
    g_sink = nullptr;
    return lines;
}
} // namespace

WidgetPanel::WidgetPanel(QWidget* parent)
    : QWidget(parent)
{
    m_typeBox = new QComboBox;
    for (const TypeInfo& t : kTypes)
        m_typeBox->addItem(t.title);

    auto* addBtn = new QPushButton("Добавить");
    auto* connectBtn = new QPushButton("Соединить все");
    auto* disconnectBtn = new QPushButton("Разъединить все");
    auto* verifyBtn = new QPushButton("Проверить соединения");

    auto* bar = new QHBoxLayout;
    bar->addWidget(m_typeBox);
    bar->addWidget(addBtn);
    bar->addStretch();
    bar->addWidget(connectBtn);
    bar->addWidget(disconnectBtn);
    bar->addWidget(verifyBtn);

    auto* holder = new QWidget;
    m_itemsLayout = new QVBoxLayout(holder);
    m_itemsLayout->addStretch();
    auto* scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setWidget(holder);

    m_log = new QPlainTextEdit;
    m_log->setReadOnly(true);
    m_log->setMaximumHeight(140);

    auto* root = new QVBoxLayout(this);
    root->addLayout(bar);
    root->addWidget(scroll, 1);
    root->addWidget(m_log);

    connect(addBtn, &QPushButton::clicked, this, [this] { addWidget(m_typeBox->currentIndex()); });
    connect(connectBtn, &QPushButton::clicked, this, [this] { connectAll(); });
    connect(disconnectBtn, &QPushButton::clicked, this, [this] { disconnectAll(); });
    connect(verifyBtn, &QPushButton::clicked, this, [this] { verifyConnections(); });
}

void WidgetPanel::log(const QString& text)
{
    m_log->appendPlainText(text);
    qDebug().noquote() << text;
}

void WidgetPanel::pruneDeleted()
{
    m_widgets.removeIf([](const QPointer<QWidget>& w) { return w.isNull(); });
}

QWidget* WidgetPanel::addWidget(int typeIndex)
{
    if (typeIndex < 0 || typeIndex >= kTypeCount)
        return nullptr;

    const TypeInfo& type = kTypes[typeIndex];
    QWidget* w = type.create();
    w->setObjectName(QStringLiteral("%1_%2").arg(type.title).arg(++m_serial));

    m_itemsLayout->insertWidget(m_itemsLayout->count() - 1, w);
    m_widgets.append(w);

    log(QStringLiteral("+ %1 (соединений нет)").arg(w->objectName()));
    return w;
}

int WidgetPanel::connectAll()
{
    pruneDeleted();

    int created = 0;
    int skipped = 0;
    for (const QPointer<QWidget>& src : m_widgets) {
        const TypeInfo* srcType = typeOf(src.data());
        if (!srcType || !srcType->signal)
            continue;

        for (const QPointer<QWidget>& dst : m_widgets) {
            if (src == dst)
                continue;
            const TypeInfo* dstType = typeOf(dst.data());
            if (!dstType || !dstType->slot)
                continue;

            const QMetaObject* srcMeta = src->metaObject();
            const QMetaObject* dstMeta = dst->metaObject();
            const int signalIndex = srcMeta->indexOfSignal(srcType->signal);
            const int slotIndex = dstMeta->indexOfSlot(dstType->slot);
            if (signalIndex < 0 || slotIndex < 0)
                continue;

            const QString key = linkKey(src->objectName(), srcType->signal, dst->objectName(), dstType->slot);
            if (m_links.contains(key)) {
                ++skipped;
                continue;
            }

            // Прямое соединение сигнал -> слот, UniqueConnection - защита от дубликатов на стороне Qt.
            const QMetaObject::Connection c = QObject::connect(
                src.data(), srcMeta->method(signalIndex),
                dst.data(), dstMeta->method(slotIndex),
                Qt::UniqueConnection);
            if (!c) {
                log(QStringLiteral("! Qt отклонил соединение (дубликат вне реестра): %1").arg(key));
                continue;
            }
            m_links.insert(key, c);
            ++created;
        }
    }

    log(QStringLiteral("Соединено: новых %1, уже было %2, всего в реестре %3")
            .arg(created).arg(skipped).arg(m_links.size()));
    return created;
}

int WidgetPanel::disconnectAll()
{
    int n = 0;
    for (const QMetaObject::Connection& c : std::as_const(m_links)) {
        if (QObject::disconnect(c))
            ++n;
    }
    m_links.clear();

    log(QStringLiteral("Разъединено: %1").arg(n));
    return n;
}

bool WidgetPanel::verifyConnections()
{
    pruneDeleted();

    QHash<QString, QWidget*> live;
    for (const QPointer<QWidget>& w : m_widgets)
        live.insert(w->objectName(), w.data());

    // Реальные соединения из внутренней таблицы Qt: ключ -> сколько раз встретился.
    QHash<QString, int> actual;
    QStringList foreign;      // получатель вне коллекции
    int destroyedReceivers = 0;
    bool dumpWorks = true;

    for (QWidget* w : std::as_const(live)) {
        const TypeInfo* type = typeOf(w);
        if (!type || !type->signal)
            continue;

        const QStringList lines = dumpLines(w);
        if (lines.isEmpty()) {
            dumpWorks = false;
            break;
        }

        bool signalsOut = false;
        QString currentSignal;
        for (const QString& raw : lines) {
            const QString line = raw.trimmed();
            if (line == QLatin1String("SIGNALS OUT")) {
                signalsOut = true;
            } else if (line == QLatin1String("SIGNALS IN")) {
                signalsOut = false;
            } else if (!signalsOut) {
                continue;
            } else if (line.startsWith(QLatin1String("signal:"))) {
                currentSignal = line.mid(7).trimmed();
            } else if (currentSignal != QLatin1String(type->signal)) {
                continue;
            } else if (line.startsWith(QLatin1String("<destroyed receiver>"))) {
                ++destroyedReceivers;
            } else if (line.startsWith(QLatin1String("-->"))) {
                // "--> QLabel::QLabel_1 setNum(int)"
                const QString rest = line.mid(3).trimmed();
                const int space = rest.indexOf(QLatin1Char(' '));
                const QString target = rest.left(space);
                const QString slot = rest.mid(space + 1).trimmed();
                const QString receiver = target.mid(target.indexOf(QLatin1String("::")) + 2);
                if (!live.contains(receiver))
                    foreign.append(target);
                else
                    ++actual[linkKey(w->objectName(), type->signal, receiver, slot.toLatin1().constData())];
            }
        }
    }

    log(QStringLiteral("--- Проверка: виджетов %1, в реестре %2 соединений ---")
            .arg(live.size()).arg(m_links.size()));

    int duplicates = 0;
    int stray = 0;
    int stale = 0;

    if (!dumpWorks) {
        log(QStringLiteral("dumpObjectInfo() недоступен (release-сборка Qt): проверка только по реестру"));
    } else {
        for (auto it = actual.cbegin(); it != actual.cend(); ++it) {
            if (it.value() > 1) {
                ++duplicates;
                log(QStringLiteral("ДУБЛИКАТ x%1: %2").arg(it.value()).arg(it.key()));
            }
            if (!m_links.contains(it.key())) {
                ++stray;
                log(QStringLiteral("ЛИШНЕЕ (нет в реестре): %1").arg(it.key()));
            }
        }
        for (auto it = m_links.begin(); it != m_links.end();) {
            if (!actual.contains(it.key())) {
                ++stale;
                log(QStringLiteral("очищено (соединение уже разорвано Qt, виджет удалён): %1").arg(it.key()));
                it = m_links.erase(it);
            } else {
                ++it;
            }
        }
        for (const QString& f : std::as_const(foreign))
            log(QStringLiteral("ВИСЯЧЕЕ (получатель вне коллекции): %1").arg(f));
        if (destroyedReceivers > 0)
            log(QStringLiteral("ВИСЯЧЕЕ (уничтоженный получатель): %1").arg(destroyedReceivers));
    }

    const qsizetype dangling = foreign.size() + destroyedReceivers;
    const bool ok = duplicates == 0 && dangling == 0 && stray == 0;
    log(QStringLiteral("Найдено в Qt: %1 уникальных; дубликатов %2, висячих %3, лишних %4 -> %5")
            .arg(actual.size()).arg(duplicates).arg(dangling).arg(stray)
            .arg(ok ? QStringLiteral("OK") : QStringLiteral("ЕСТЬ ПРОБЛЕМЫ")));
    return ok;
}
