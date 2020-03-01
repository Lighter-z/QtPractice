#include "serverwidget.h"
#include "ui_serverwidget.h"
#include <QFileDialog>

ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerWidget)
{
    ui->setupUi(this);

    tcp_server = new QTcpServer(this);
    tcp_server->listen(QHostAddress::Any,8888);
    setWindowTitle("服务器端口8888");

    ui->sendButton->setEnabled(false);
    ui->chooseButton->setEnabled(false);

    connect(tcp_server,&QTcpServer::newConnection,this,[=](){
        tcp_socket = tcp_server->nextPendingConnection();
        QString ip = tcp_socket->peerAddress().toString();
        qint16 port = tcp_socket->peerPort();
        ui->textEditRead->setText(QString("%1:%2").arg(ip).arg(port));


        //ui->sendButton->setEnabled(true);
        ui->chooseButton->setEnabled(true);

        connect(tcp_socket,&QTcpSocket::readyRead,[=](){
            QByteArray array = tcp_socket->readAll();
            if(QString(array) == "file done")
            {
                ui->textEditRead->append("文件发送完毕");
                file.close();

                tcp_socket->disconnectFromHost();
                tcp_socket->close();
            }

        });
    });

    connect(&timer,&QTimer::timeout,[=](){
        timer.stop();
        sendData();
    });
}

ServerWidget::~ServerWidget()
{
    delete ui;
}


void ServerWidget::on_chooseButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"open","../");
    if(filePath.isEmpty() == false)
    {
        fileSzie = 0;
        sendSize = 0;
        fileName.clear();

        QFileInfo info(filePath);
        fileName = info.fileName();
        fileSzie = info.size();


        file.setFileName(filePath);
        bool isOpen = file.open(QIODevice::ReadOnly);
        if(false == isOpen)
        {
            qDebug() << "以只读方式打开失败";
        }
        ui->textEditRead->append(filePath);
        ui->chooseButton->setEnabled(false);
        ui->sendButton->setEnabled(true);
    }
    else
    {
        qDebug() << "选择文件路径出错";
    }
}

void ServerWidget::on_sendButton_clicked()
{
    ui->sendButton->setEnabled(false);
    QString head = QString("%1##%2").arg(fileName).arg(fileSzie);
    qint64 len = tcp_socket->write(head.toUtf8());
    if(len > 0)
    {
        timer.start(20);
    }
    else
    {
        qDebug() << "头部信息发送失败";
        file.close();
        ui->sendButton->setEnabled(false);
        ui->chooseButton->setEnabled(true);
    }
}

void ServerWidget::sendData(void)
{
    qint64 len = 0;

    do{
        char buf[4 * 1024] = {0};
        len = 0;

        len = file.read(buf,sizeof(buf));
        len = tcp_socket->write(buf,len);

        sendSize += len;
    }while (len > 0);

//    if(sendSize == fileSzie)
//    {
//        ui->textEditRead->setText(QString("发送完毕"));
//        file.close();

//        tcp_socket->disconnectFromHost();
//        tcp_socket->close();
//    }
}
