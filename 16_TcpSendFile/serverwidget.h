#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class ServerWidget; }
QT_END_NAMESPACE

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    ServerWidget(QWidget *parent = nullptr);
    ~ServerWidget();

private slots:
    void on_chooseButton_clicked();

    void on_sendButton_clicked();

private:
    Ui::ServerWidget *ui;
    QTcpServer * tcp_server;
    QTcpSocket * tcp_socket;

    QFile file;
    QString fileName;
    qint64 fileSzie;
    qint64 sendSize;
    QTimer timer;

    void sendData(void);

};
#endif // SERVERWIDGET_H
