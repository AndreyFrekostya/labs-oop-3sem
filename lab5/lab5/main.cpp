#include "lab5.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    HelloWidget widget;
    widget.show();
    return app.exec();
}
