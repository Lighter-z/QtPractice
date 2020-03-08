#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QThread>
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

private slots:

    void on_stratBtn_clicked();
    void dealSignal();

    void on_stopBtn_clicked();

signals:
    void statrThread();//启动子线程的信号

private:
    Ui::Widget *ui;

    MyThread * myT;
    QThread * thread;
};
#endif // WIDGET_H
