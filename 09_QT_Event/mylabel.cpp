#include "mylabel.h"
#include <QDebug>
#include <QMouseEvent>

myLabel::myLabel(QWidget *parent) : QLabel(parent)
{
    //设置鼠标追踪
    //不设置 默认使flase值
    //设置追踪后，不需要按下鼠标 也会显示鼠标移动
    //this->setMouseTracking(true);

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

bool myLabel::event(QEvent * e)
{
    //通常event事件不做拦截 只负责下发
    //这里测试 返回true 的动能  拦截MouseButtonPress  由用户处理 不再下发
    //上面的 void myLabel::mouseReleaseEvent(QMouseEvent *ev) 不会再调用
    if(e->type() == QEvent::MouseButtonPress) {
        QMouseEvent * ev = static_cast<QMouseEvent *>(e);
        QString str = QString("Event   鼠标按下  x = %1  y = %2").arg(ev->x()).arg(ev->y());
        qDebug() << str;
        //这里 鼠标按下事件 被event 拦截了
        //只有鼠标按下 由自己处理 返回true
        return true;
    }
    //其他事件继续下发 由父亲处理
    return QLabel::event(e);
}
