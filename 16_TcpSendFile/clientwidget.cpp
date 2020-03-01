#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QHostAddress>
#include <QMessageBox>

clientwidget::clientwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientwidget)
{
    ui->setupUi(this);
    isStart = true;
    setWindowTitle("客户端");
    tcp_socket = new QTcpSocket(this);
    connect(tcp_socket,&QTcpSocket::readyRead,this,[=](){
        QByteArray buf = tcp_socket->readAll();
        if(isStart == true)
        {
            isStart = false;

            fileName = QString(buf).section("##",0,0);
            fileSize = QString(buf).section("##",1,1).toInt();
            recvSize = 0;

            file.setFileName(fileName);

            bool isOpen = file.open(QIODevice::WriteOnly);
            if(false == isOpen)
            {
                qDebug() << "Write Only Error";
                tcp_socket->disconnectFromHost();
                tcp_socket->close();
                return;
            }

            QString str = QString("接收的文件：[%1:%2]").arg(fileName).arg(fileSize/1024);
            QMessageBox::information(this,"文件信息",str);
        }
        else
        {
            qint64 len = file.write(buf);
            if(len > 0)
            {
                recvSize += len;
            }

            if(recvSize == fileSize)
            {
                tcp_socket->write("file done");
                QMessageBox::information(this, "完成", "文件接收完成");
                file.close();
                tcp_socket->disconnectFromHost();
                tcp_socket->close();
            }
        }
    });
}

clientwidget::~clientwidget()
{
    delete ui;
}

void clientwidget::on_connectButton_clicked()
{
    QString ip = ui->ipEdit->text();
    qint16 port = ui->portEdit->text().toInt();
    tcp_socket->connectToHost(QHostAddress(ip),port);
    isStart = true;
}
