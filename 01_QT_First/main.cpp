#include "mywidget.h"

#include <QApplication>

//argc命令行便令数量    argv命令行变量数组
int main(int argc, char *argv[])
{
    //应用程序对象 a   QT中  有且只有一个应用程序对象
    QApplication a(argc, argv);
    MyWidget w;
    //窗口默认是不会弹出的   如果想要弹出，调用show方法
    w.show();
    //a.exec()进入消息循环机制    避免程序一闪而过
    return a.exec();
}
