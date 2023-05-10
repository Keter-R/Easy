#include "MainWidget.h"
#include <QtWidgets/QApplication>
#include "Protocol.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.show();
    return a.exec();
}
