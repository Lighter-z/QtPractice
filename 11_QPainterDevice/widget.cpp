#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPicture>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //QPixmap 做绘图设备，对不同平台显示做了优化
    //设置画布大小
//    QPixmap pix(300,300);
    //设置背景色
//    pix.fill(Qt::white);
    //把画家添加在画布上
//    QPainter painter(&pix);

    //设置画笔颜色
//    painter.setPen(QPen(Qt::green));
    //画原
//    painter.drawEllipse(QPoint(150,150),100,100);
    //保存
//    pix.save("F:\\1.Work\\1.Study\\BASE\\QT\\QtPractice\\11_QPainterDevice\\pix.png");

    //QImage 做绘图设备  对像素级访问做了优化
//    QImage img(300,300,QImage::Format_RGB32);
//    img.fill(Qt::white);
//    QPainter painter(&img);

//    painter.setPen(QPen(Qt::red));
//    painter.drawEllipse(QPoint(150,150),100,100);
//    img.save("F:\\1.Work\\1.Study\\BASE\\QT\\QtPractice\\11_QPainterDevice\\img.png");



}

void Widget::paintEvent(QPaintEvent *event)
{
//    //QImage可修改 像素
//    QImage img;
//    img.load(":/1.png");

//    //把以下区域内的像素变为红色
//    for(int i = 0;i < 50;i++){
//        for(int j = 0;j < 50;j++){
//            QRgb value = qRgb(255,0,0);
//            img.setPixel(i,j,value);
//        }
//    }
//    QPainter painter(this);
//    painter.drawImage(QPoint(0,0),img);

    //QPicture  保存绘图动作
    QPicture pic;
    QPainter painter;
    //将图像绘制到QPicture中 并保存文件pic.zm
    painter.begin(&pic);
    painter.setPen(QPen(Qt::blue));
    painter.drawEllipse(QPoint(150,150),100,100);
    painter.end();
    pic.save("F:\\1.Work\\1.Study\\BASE\\QT\\QtPractice\\11_QPainterDevice\\pic.zm");

    //将保存的绘图动作重新绘制到设备上
    pic.load("F:\\1.Work\\1.Study\\BASE\\QT\\QtPractice\\11_QPainterDevice\\pic.zm");
    painter.begin(this);
    painter.drawPicture(0,0,pic);
    painter.end();
}

Widget::~Widget()
{
    delete ui;
}

