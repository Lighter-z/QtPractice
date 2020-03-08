#include "mythread.h"
#include <QDebug>

MyThread::MyThread(QObject *parent) : QObject(parent)
{
    isStop = false;
}

//线程处理函数内部不允许处理图形界面
void MyThread::myTimeOut()
{
    while(!isStop)
    {
        QThread::sleep(1);
        emit mySignal();
        qDebug() << "子线程 " << QThread::currentThread();
    }
}

void MyThread::setFlag(bool flag)
{
    isStop = flag;
}
