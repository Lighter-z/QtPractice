#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include "teacher.h"
#include "student.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void classIsOver();

    Teacher * zt;
    Student * st;
};
#endif // WIDGET_H
