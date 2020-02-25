#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    enum MsgType{
        Msg,
        UsrEnter,
        UsrLeft
    };
public:
    Widget(QWidget *parent, QString name);
    ~Widget();

private:
    Ui::Widget *ui;
signals:
    //关闭窗口信号
    void closeWidget();
public:
    //实现虚函数  关闭事件
    void closeEvent(QCloseEvent *event);
public:
    void sendMsg(MsgType type);
    void usrEnter(QString name);
    void usrLeft(QString name, QString time);
    QString getUsr();
    QString getMsg();
private:
    QUdpSocket * udpSocket;
    qint16 port;
    QString uName;
    void ReceiveMsg();
};
#endif // WIDGET_H
