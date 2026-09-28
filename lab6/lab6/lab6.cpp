#include "lab6.h"
#include "WidgetPanel.h"

#include <QVBoxLayout>

lab6::lab6(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    auto* layout = new QVBoxLayout(ui.centralWidget);
    layout->addWidget(new WidgetPanel);
    resize(800, 560);
}

lab6::~lab6()
{}
