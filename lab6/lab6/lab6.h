#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab6.h"

class lab6 : public QMainWindow
{
    Q_OBJECT

public:
    lab6(QWidget *parent = nullptr);
    ~lab6();

private:
    Ui::lab6Class ui;
};

