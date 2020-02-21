#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    posX = 0;
    QTimer * timer = new QTimer(this);
    timer->start(1000);
    connect(timer,&QTimer::timeout,[=](){
        posX+=10;
        update();
    });



    connect(ui->pushButton,&QPushButton::clicked,[=](){
        posX+=100;
        //手动调用绘图事件
        update();
    });

    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        timer->stop();
    });

    connect(ui->pushButton_3,&QPushButton::clicked,[=](){
        timer->start();
    });

}

void Widget::paintEvent(QPaintEvent *)
{
#if 0  //初级设置
    //创建画家
    QPainter painter(this);
    //创建画笔
    QPen pen(QColor(0,255,0));
    //设置画笔宽度
    pen.setWidth(3);
    //设置画笔风格
    pen.setStyle(Qt::CustomDashLine);
    //让画家使用画笔
    painter.setPen(pen);

    //创建画刷
    QBrush brush(Qt::green);
    //设置画刷风格
    brush.setStyle(Qt::Dense4Pattern);
    //让画家使用画刷
    painter.setBrush(brush);

    //画线
    painter.drawLine(QPoint(0,0),QPoint(100,100));
    //画矩形
    painter.drawRect(10,10,50,50);
    //画圆
    painter.drawEllipse(QPoint(100,100),50,50);
    //画椭圆
    painter.drawEllipse(QPoint(200,150),80,50);
    //画字体
    painter.drawText(QRect(10,200,150,50),"好好学习");
#else  //高级设置
//    QPainter painter(this);
//    painter.drawEllipse(QPoint(100,100),50,50);
//    //抗锯齿
//    painter.setRenderHint(QPainter::Antialiasing);
//    painter.drawEllipse(QPoint(200,100),50,50);

//    painter.drawRect(QRect(300,80,50,50));
//    //移动画家
//    painter.translate(QPoint(350,0));
//    //保存状态
//    painter.save();
//    painter.drawRect(QRect(300,80,50,50));

//    painter.translate(QPoint(350,0));
//    //取出状态
//    painter.restore();
//    painter.drawRect(QRect(300,80,50,50));

    QPainter painter(this);
    //判断坐标是否出屏幕
    if(posX > this->width()){
        posX = 0;
    }
    //显示图片
    painter.drawPixmap(posX,100,QPixmap(":/image/1.png"));
#endif

}

Widget::~Widget()
{
    delete ui;
}

