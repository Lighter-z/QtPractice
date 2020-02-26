#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QHostAddress>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    tcp_socket = NULL;

    setWindowTitle("客户端");

    tcp_socket = new QTcpSocket(this);

    connect(tcp_socket,&QTcpSocket::connected,this,[=](){
        ui->readEdit->setText(QString("成功连接"));
        //这个  连接 放在里面或外面都行 因为上面已经有了tcp_socket
        connect(tcp_socket,&QTcpSocket::readyRead,this,[=](){
            QByteArray array = tcp_socket->readAll();
            //append是在后面追加  setText会把之前内容清空
            ui->readEdit->append(array);
        });
    });
    //放在外面
//    connect(tcp_socket,&QTcpSocket::readyRead,this,[=](){
//        QByteArray array = tcp_socket->readAll();
//        //append是在后面追加  setText会把之前内容清空
//        ui->readEdit->append(array);
//    });
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_connectBtn_clicked()
{
    QString ip = ui->ip_Edit->text();
    qint16 port = ui->port_Edit->text().toInt();
    tcp_socket->connectToHost(QHostAddress(ip),port);
}

void ClientWidget::on_sendBtn_clicked()
{

    QString str = ui->writeEdit->toPlainText();
    tcp_socket->write(str.toUtf8().data());

}

void ClientWidget::on_closeBtn_clicked()
{
    //主动和对方断开连接
    tcp_socket->disconnectFromHost();
    tcp_socket->close();
}
