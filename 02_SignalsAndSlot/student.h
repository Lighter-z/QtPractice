#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>
#include <QDebug>

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(QObject *parent = nullptr);
    //自定义槽函数
    //高版本可以写在 public 下，或者全局函数  低版本卸载 public slots 下
    //返回值 void
    //槽函数需要声明 需要重载
    //槽函数也可以有参数  可以发生重载
    void tryEat();
    void tryEat(QString foodName);
signals:

};

#endif // STUDENT_H
