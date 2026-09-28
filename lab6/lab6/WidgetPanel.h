#pragma once

#include <QHash>
#include <QList>
#include <QMetaObject>
#include <QPointer>
#include <QString>
#include <QWidget>

class QComboBox;
class QPlainTextEdit;
class QVBoxLayout;

// Панель с единой коллекцией виджетов (QLabel, QSlider, QScrollBar, QSpinBox).
// Виджеты добавляются кнопкой и НЕ соединяются автоматически:
// соединение выполняется отдельным методом connectAll().
class WidgetPanel : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetPanel(QWidget* parent = nullptr);

    // Создаёт виджет типа с номером typeIndex (см. таблицу типов в .cpp), кладёт в коллекцию.
    QWidget* addWidget(int typeIndex);

    // Соединяет напрямую (сигнал одного -> слот другого) все виджеты коллекции.
    // Возвращает число новых соединений. Повторный вызов дубликатов не создаёт.
    int connectAll();

    // Разрывает все соединения, созданные connectAll(). Возвращает их число.
    int disconnectAll();

    // Отладочная проверка: сверяет реальную таблицу соединений Qt (dumpObjectInfo)
    // с реестром, ищет дубликаты и "висячие" соединения. true - проблем нет.
    bool verifyConnections();

private:
    void pruneDeleted();
    void log(const QString& text);

    QList<QPointer<QWidget>> m_widgets;             // единая коллекция виджетов
    QHash<QString, QMetaObject::Connection> m_links; // реестр созданных соединений
    int m_serial = 0;

    QComboBox* m_typeBox = nullptr;
    QVBoxLayout* m_itemsLayout = nullptr;
    QPlainTextEdit* m_log = nullptr;
};
