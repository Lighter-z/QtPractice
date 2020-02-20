#include "mylabel.h"
#include <QDebug>
#include <QMouseEvent>

myLabel::myLabel(QWidget *parent) : QLabel(parent)
{
    //设置鼠标追踪
    //不设置 默认使flase值
    //设置追踪后，不需要按下鼠标 也会显示鼠标移动
    this->setMouseTracking(true);

}

void myLabel::enterEvent(QEvent *)
{
    qDebug() << "鼠标进入";
}

void myLabel::leaveEvent(QEvent *)
{
    qDebug() << "鼠标离开";
}

void myLabel::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons() & Qt::LeftButton){
        qDebug() << "鼠标左键移动";
    }
    else if(ev->buttons() & Qt::RightButton) {
        qDebug() << "鼠标右键移动";
    }
    //只要有按键按下移动 就会触发
    qDebug() << "鼠标移动，无法判断是哪个键";
}

void myLabel::mousePressEvent(QMouseEvent *ev)
{
    QString str = QString("鼠标按下了！！！ x = %1, y = %2").arg(ev->x()).arg(ev->y());
    qDebug() << str;
}

void myLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    //鼠标按下时 打印
    QString str = QString("鼠标释放了！！！ x = %1, y = %2").arg(ev->x()).arg(ev->y());
    if(ev->button() == Qt::LeftButton) {
        qDebug() << str;
    }
}
