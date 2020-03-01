#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    udp_sockeet = new QUdpSocket(this);
    //绑定
    udp_sockeet->bind(QHostAddress::AnyIPv4,8888);
    //加入某个组播 组播地址是D类
    udp_sockeet->joinMulticastGroup(QHostAddress("224.0.0.2"));
    //当对方发送数据过来 自动触发readMessage   这里也可以用lambda表达式
    connect(udp_sockeet,&QUdpSocket::readyRead,this,&Widget::readMessage);
}

void Widget::readMessage()
{
    //读取发送的内容
    char buf[1024] = {0};
    //发送端ip地址
    QHostAddress cliAddr;
    //发送端端口号
    quint16 port;
    //数据长度
    qint64 len = udp_sockeet->readDatagram(buf,sizeof(buf),&cliAddr,&port);

    if(len > 0)
    {
        //格式化
        QString str = QString("[%1:%2] %3").arg(cliAddr.toString()).arg(port).arg(buf);
        ///给编辑区设置内容
        ui->textEditRead->setText(str);
    }
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_sendButton_clicked()
{
    //先获取对方的IP和端口
    QString ip = ui->lineEditIp->text();
    qint16 port = ui->lineEditPort->text().toInt();
    //获取编辑区内容
    QString str = ui->textEditWrite->toPlainText();
    //给指定的IP发送数据
    udp_sockeet->writeDatagram(str.toUtf8(),QHostAddress(ip),port);
}
