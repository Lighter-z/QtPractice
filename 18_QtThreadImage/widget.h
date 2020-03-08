#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QThread>
#include <QImage>
#include <QPainter>

#include "mythread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void getImage(QImage temp);
    void paintEvent(QPaintEvent *);

private:
    Ui::Widget *ui;

    QImage image;
    myThread * myT;
    QThread * thread;
};
#endif // WIDGET_H
