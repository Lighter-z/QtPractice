#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>

class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

signals:
    void mySignal();

public:
    void myTimeOut();  //线程处理函数
    void setFlag(bool flag = true);

private:
    bool isStop;  // isStop = false时 线程不关闭

};

#endif // MYTHREAD_H
