#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //启动定时器

    //第一种使用方式
    //1000ms
    timerId1 = startTimer(2000);
    //5000ms
    timerId2 = startTimer(5000);

    //第二种使用方式
    QTimer * timer1 = new QTimer(this);
    //启动定时器对象
    connect(ui->startBtn,&QPushButton::clicked,[=](){
        timer1->start(500);
    });

    //每隔0.5s发送一个信号
    connect(timer1,&QTimer::timeout,this,[=](){
       static int num = 0;
        ui->label_4->setText(QString::number(num++));
    });

    connect(ui->stopBtn,&QPushButton::clicked,[=](){
        timer1->stop();
    });

    //1、给控件安装事件过滤器
    //参数this  通过父窗口给label安装事件过滤器
    ui->label->installEventFilter(this);
    //2、重写eventFilter事件

}

//事件过滤器
//被事件过滤器处理的事件 不会在下发给 event 进行处理
bool Widget::eventFilter(QObject * obj, QEvent * e)
{
    if(obj == ui->label) {
        if(e->type() == QEvent::MouseButtonPress){
            QMouseEvent * ev = static_cast<QMouseEvent *>(e);
            QString str = QString("事件过滤器  鼠标按下 x = %1，y = %2").arg(ev->x()).arg(ev->y());
            qDebug() << str;
            //鼠标按下 自己处理  返回 reture
            return true;
        }
    }
    //其他让父类处理
    return QWidget::eventFilter(obj,e);
}

void Widget::timerEvent(QTimerEvent * ev)
{
    static int num1 = 10;
    if(timerId1 == ev->timerId()) {
        ui->label_2->setText(QString::number(num1++));
    }

    static int num2 = 0;
    if(timerId2 == ev->timerId()) {
        ui->label_3->setText(QString::number(num2++));
    }
}

Widget::~Widget()
{
    delete ui;
}

