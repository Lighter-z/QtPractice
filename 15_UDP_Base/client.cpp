#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    udp_socket = new QUdpSocket(this);
    connect(udp_socket, &QUdpSocket::readyRead, this, &Client::dealMsg);
}

void Client::dealMsg()
{
    //读取对方发送的内容
    char buf[1024] = {0};
    QHostAddress cliAddr; //对方地址
    quint16 port;    //对方端口
    qint64 len = udp_socket->readDatagram(buf, sizeof(buf), &cliAddr, &port);
    if(len > 0)
    {
        //格式化 [192.68.2.2:8888]aaaa
        QString str = QString("[%1:%2] %3")
                .arg(cliAddr.toString())
                .arg(port)
                .arg(buf);
        //给编辑区设置内容
        ui->textEditRead->setText(str);
    }
}

Client::~Client()
{
    delete ui;
}

void Client::on_sendButton_clicked()
{
    QString ip = ui->lineEditIp->text();
    qint16 port = ui->lineEditPort->text().toInt();

    QString str = ui->textEditWrite->toPlainText();

    udp_socket->writeDatagram(str.toUtf8(),QHostAddress(ip),port);
}
