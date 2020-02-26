#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class ServerWidget; }
QT_END_NAMESPACE

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    ServerWidget(QWidget *parent = nullptr);
    ~ServerWidget();

private:
    Ui::ServerWidget *ui;

public:
    QTcpServer * tcp_server;
    QTcpSocket * tcp_socket;
private slots:
    void on_closeBtn_clicked();

    void on_sendBtn_clicked();


};
#endif // SERVERWIDGET_H
