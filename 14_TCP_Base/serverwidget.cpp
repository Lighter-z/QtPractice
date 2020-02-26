#include "serverwidget.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
    setWindowTitle("服务器,端口：8888");

    tcp_server = NULL;
    tcp_socket = NULL;

    //简历监听套接字  指定父类对象让其自动回收空间
    tcp_server = new QTcpServer(this);

    tcp_server->listen(QHostAddress::Any,8888);

    connect(tcp_server,&QTcpServer::newConnection,[=](){
        //取出建立好的套接字
        tcp_socket = tcp_server->nextPendingConnection();
        //获取ip和端口号
        QString ip = tcp_socket->peerAddress().toString();
        qint16 port = tcp_socket->peerPort();

        QString str = QString("%1:%2").arg(ip).arg(port);
        ui->textEditRead->setText(str);

        connect(tcp_socket,&QTcpSocket::readyRead,[=](){
            //从通信套接字中取出内容
            QByteArray array = tcp_socket->readAll();
            //append是在后面追加  setText会把之前的清空
            ui->textEditRead->append(array);
        });
    });


}

ServerWidget::~ServerWidget()
{
    delete ui;
}


void ServerWidget::on_closeBtn_clicked()
{
    if(tcp_socket == NULL)
    {
        this->close();
        return;
    }
    //主动和客户端断开连接
    tcp_socket->disconnectFromHost();
    tcp_socket->close();
    tcp_socket = NULL;
}

void ServerWidget::on_sendBtn_clicked()
{
    if(tcp_socket == NULL)
    {
        return;
    }

    QString str = ui->textEditWrite->toPlainText();
    tcp_socket->write(str.toUtf8().data());
}
