#include "lab6.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    lab6 window;
    window.show();
    return app.exec();
}
