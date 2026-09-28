#include "lab5.h"

#include <QApplication>
#include <QLabel>
#include <QPushButton>

HelloWidget::HelloWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Hello World");
    setGeometry(100, 100, 300, 150);

    label = new QLabel("Hello World", this);
    label->setGeometry(10, 10, 280, 60);
    label->setAlignment(Qt::AlignCenter);

    exitButton = new QPushButton("Exit", this);
    exitButton->setGeometry(100, 90, 100, 40);

    connect(exitButton, &QPushButton::clicked, qApp, &QApplication::quit);
}
