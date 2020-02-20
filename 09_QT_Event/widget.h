#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    bool eventFilter(QObject * obj, QEvent * e);
    ~Widget();

private:
    Ui::Widget *ui;

    //定时器事件
    void timerEvent(QTimerEvent * ev);
    int timerId1 = 0;
    int timerId2 = 0;
};
#endif // WIDGET_H
