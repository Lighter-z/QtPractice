#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //自定义类对象  分配空间 不能指定父类对象
    myT = new myThread();
    //创建子线程
    thread = new QThread(this);
    //把自定义类模块添加到子线程
    myT->moveToThread(thread);
    //子线程开始   但是没有启动线程处理函数
    thread->start();
    //线程处理函数 必须通过 signal-slot 方式调用
    connect(ui->pushButton,&QPushButton::clicked,myT,&myThread::drawImage);

    connect(myT,&myThread::updateImage,this,&Widget::getImage);
    //关闭窗口
    connect(this,&Widget::destroyed,this,[=](){
        //退出子线程
        thread->quit();
        //回收资源
        thread->wait();
        //删除自定义类对象
        delete myT;
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::getImage(QImage temp)
{
    image = temp;
    update();  //更新窗口 间接调用paintEvent函数
}

//重写 paintEvent 函数
void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);//创建画家 指定绘图设备为窗口
    p.drawImage(50,50,image);

}

