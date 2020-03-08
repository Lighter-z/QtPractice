#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //动态分配空间 不能指定父类对象
    myT = new MyThread;
    //创建子线程
    thread = new QThread(this);
    //把 自定义线程加入 子线程中
    myT->moveToThread(thread);

    connect(myT,&MyThread::mySignal,this,&Widget::dealSignal);

    qDebug() << "主线程 " << QThread::currentThread();

    //通过信号和槽的方式调用线程处理函数
    //线程处理函数内部不允许处理图形界面
    connect(this,&Widget::statrThread,myT,&MyThread::myTimeOut);

    connect(this,&Widget::destroyed,this,[=](){
        on_stopBtn_clicked();
        delete myT;
    });

    //connect() 第五个参数的作用 连接方式：默认，直接，队列
    //多线程时候才有意义
    //默认的时候：
    //  如果是单线程，默认使用直接方式
    //  如果是多线程，默认使用队列
    //队列：槽函数和接收者所在同一个线程
    //直接：槽函数和发送者在同一个线程
}

Widget::~Widget()
{
    delete ui;
}


void Widget::dealSignal()
{
    static int num = 0;
    num++;
    ui->lcdNumber->display(num);
}

void Widget::on_stratBtn_clicked()
{

    if(thread->isRunning() == true)
    {
        return;
    }

    //启动子线程 但没有启动线程处理函数
    thread->start();

    myT->setFlag(false);

    //不能直接调用
    //直接调用导致 线程处理函数和主线程是一个线程
//    myT->myTimeOut();

    //通过信号和槽的方式调用 线程处理函数
    emit statrThread();
}

void Widget::on_stopBtn_clicked()
{
    if(thread->isRunning() == false)
    {
        return;
    }
    myT->setFlag(true);
    thread->quit();
    thread->wait();
}
