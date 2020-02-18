#include "student.h"

Student::Student(QObject *parent) : QObject(parent)
{

}

void Student::tryEat()
{
    qDebug() << "学生请老师吃饭";
}

void Student::tryEat(QString foodName){
//    qDebug() << "学生请老师吃饭，老师吃" << foodName;   //  打印效果： 学生请老师吃饭，老师吃 "宫保鸡丁"

    //QString 转为 char *   先转为 QBytearray类型  再转为 char *
    qDebug() << "学生请老师吃饭，老师吃" << foodName.toUtf8().data();   //  打印效果： 学学生请老师吃饭，老师吃 宫保鸡丁
}
