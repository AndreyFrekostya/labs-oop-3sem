#pragma once

#include <QWidget>

class QLabel;
class QPushButton;

class HelloWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HelloWidget(QWidget *parent = nullptr);

private:
    QLabel *label;
    QPushButton *exitButton;
};
