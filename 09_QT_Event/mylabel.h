#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>


class myLabel : public QLabel
{
    Q_OBJECT
public:
    explicit myLabel(QWidget *parent = nullptr);

    //捕获事件
    //鼠标进入
    void enterEvent(QEvent *);
    //鼠标离开
    void leaveEvent(QEvent *);

    //鼠标移动
    void mouseMoveEvent(QMouseEvent *ev);
    //鼠标按下
    void mousePressEvent(QMouseEvent *ev);
    //鼠标释放
    void mouseReleaseEvent(QMouseEvent *ev);

    //event一般做事件分发，不做拦截使用
    bool event(QEvent * e);

signals:

};

#endif // MYLABEL_H
