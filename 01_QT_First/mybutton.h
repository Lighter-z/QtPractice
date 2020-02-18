#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = nullptr);    //explicit防止构造的隐式类型转换
    ~MyButton();
signals:

};

#endif // MYBUTTON_H
