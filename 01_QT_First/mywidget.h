#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT    //Q_OBJECT宏   写了这个宏 就支持了 QT的信号和槽机制

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
};
#endif // MYWIDGET_H
