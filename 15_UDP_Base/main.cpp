#include "widget.h"
#include "client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    Client c;
    c.show();
    w.show();
    return a.exec();
}
