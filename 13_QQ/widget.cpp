#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDateTime>
#include <QColorDialog>
#include <QFileDialog>

Widget::Widget(QWidget *parent, QString name)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //初始化操作
    udpSocket = new QUdpSocket(this);
    //获取用户名
    uName = name;
    //设置端口号
    this->port = 9999;

    //绑定端口  绑定模式：共享地址 断线重连
    udpSocket->bind(this->port,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    //发送新用户进入
    sendMsg(UsrEnter);
    //点击发送按钮 发送消息
    connect(ui->sendBtn,&QPushButton::clicked,[=](){
        sendMsg(Msg);
    });
    //监听别然发送的消息
    connect(udpSocket,&QUdpSocket::readyRead,this,&Widget::ReceiveMsg);
    //点击退出 关闭窗口
    connect(ui->exitBtn,&QPushButton::clicked,[=](){
        this->close();
    });

    //辅助功能
    //设置字体
    connect(ui->fontCbx,&QFontComboBox::currentFontChanged,[=](const QFont &font){
        ui->msgTextEdit->setCurrentFont(font);
        ui->msgTextEdit->setFocus();
    });
    //设置字号
    void(QComboBox:: * combosingal)(const QString & text) = &QComboBox::currentIndexChanged;
    connect(ui->sizeCbx,combosingal,[=](const QString & text){
        ui->msgTextEdit->setFontPointSize(text.toDouble());
        ui->msgTextEdit->setFocus();
    });
    //设置加粗
    connect(ui->boldTBtn,&QToolButton::clicked,[=](bool isCheck){
        if(isCheck)
        {
            ui->msgTextEdit->setFontWeight(QFont::Bold);
        }
        else
        {
            ui->msgTextEdit->setFontWeight(QFont::Normal);
        }
    });
    //倾斜
    connect(ui->italicTBtn,&QToolButton::clicked,[=](bool isCheck){
        ui->msgTextEdit->setFontItalic(isCheck);
    });
    //下划线
    connect(ui->underlineTBtn,&QToolButton::clicked,[=](bool isCheck){
        ui->msgTextEdit->setFontUnderline(isCheck);
    });
    //颜色
    connect(ui->colorTBtn,&QToolButton::clicked,[=](){
        QColor color = QColorDialog::getColor(Qt::red);
        ui->msgTextEdit->setTextColor(color);
    });
    //清空聊天记录
    connect(ui->clearTBtn,&QToolButton::clicked,[=](){
        ui->msgBrowser->clear();
    });
    //保存聊天记录
    connect(ui->saveTBtn,&QToolButton::clicked,[=](){
        if(ui->msgBrowser->document()->isEmpty())
        {
            QMessageBox::warning(this,"警告","内容不能为空");
            return;
        }
        else
        {
            QString path = QFileDialog::getSaveFileName(this,"保存记录","聊天记录","(*.txt)");
            QFile file(path);
            //打开模式 加 换行
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream stream(&file);
            stream << ui->msgBrowser->toPlainText();
            file.close();
        }
    });

}

QString Widget::getUsr()
{
    return this->uName;
}

QString Widget::getMsg()
{
    QString str = ui->msgTextEdit->toHtml();
    ui->msgTextEdit->clear();
    ui->msgTextEdit->setFocus();
    return str;
}

void Widget::usrEnter(QString name)
{
    //查询右侧TableWidget是否有这个用户
    bool isEmpty = ui->usrTableWidget->findItems(name,Qt::MatchExactly).isEmpty();
    if(isEmpty)
    {
        QTableWidgetItem * usr = new QTableWidgetItem(name);
        //插入行
        ui->usrTableWidget->insertRow(0);
        ui->usrTableWidget->setItem(0,0,usr);
        //追加聊天记录
        ui->msgBrowser->setTextColor(Qt::gray);
        ui->msgBrowser->append(QString("%1 上线了").arg(name));
        //更新在线人数
        ui->usrNumLbl->setText(QString("在线用户 %1 人").arg(ui->usrTableWidget->rowCount()));
        //把自身信息 广播出去
        sendMsg(UsrEnter);
    }
}

void Widget::usrLeft(QString name, QString time)
{
    bool isEmpty = ui->usrTableWidget->findItems(name,Qt::MatchExactly).isEmpty();
    if(!isEmpty)
    {
        int row = ui->usrTableWidget->findItems(name,Qt::MatchExactly).first()->row();
        ui->usrTableWidget->removeRow(row);

        ui->msgBrowser->setTextColor(Qt::gray);
        ui->msgBrowser->append(QString("%1 于 %2 离开").arg(name).arg(time));
        ui->usrNumLbl->setText(QString("在线用户：%1人").arg(ui->usrTableWidget->rowCount()));

    }
}

//广播udp消息
void Widget::sendMsg(MsgType type)
{
    //发送的消息分为三种类型
    //第一段 类型  第二段 用户名 第三段 具体内容
    QByteArray array;
    QDataStream stream(&array,QIODevice::WriteOnly);
    //把第一段 第二段数据添加到 数据流中
    stream << type << getUsr();
    switch(type)
    {
    case Msg:  //普通消息发送
        //如果编辑框为空
        if(ui->msgTextEdit->toPlainText() == "")
        {
            QMessageBox::warning(this,"警告","发送内容不能为空");
            return;
        }
        //把第三段信息加入数据流中
        stream << getMsg();
        break;
    case UsrLeft:  //新用户进入消息
        break;
    case UsrEnter:  //用户离开消息
        break;
    default:
        break;

    }
    //书写报文  广播发送
    udpSocket->writeDatagram(array,QHostAddress::Broadcast,port);
}

//接收UDP信息
void Widget::ReceiveMsg()
{
    //拿到数据报文
    //获取长度
    qint16 size = udpSocket->pendingDatagramSize();
    QByteArray array = QByteArray(size,0);
    udpSocket->readDatagram(array.data(),size);
    //解析数据
    //第一段  类型  第二段 用户名 第三段 内容
    QDataStream stream(&array,QIODevice::ReadOnly);

    int msg_type;  //读取到类型
    QString usr_name;
    QString msg;

    //获取时间
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    stream >> msg_type;
    switch(msg_type)
    {
    case Msg:
        stream >> usr_name >> msg;
        //追加聊天记录 用户名 和 时间
        ui->msgBrowser->setTextColor(Qt::blue);
        ui->msgBrowser->append("[" + usr_name + "]" + time);
        ui->msgBrowser->append(msg);
        break;
    case UsrEnter:
        stream >> usr_name;
        usrEnter(usr_name);
        break;
    case UsrLeft:
        stream >> usr_name;
        usrLeft(usr_name,time);
        break;
    default:
        break;
    }
}

void Widget::closeEvent(QCloseEvent *event)
{
    emit this->closeWidget();
    sendMsg(UsrLeft);

    //断开套接字
    //关闭
    udpSocket->close();
    //销毁
    udpSocket->destroyed();

    //其他的事件交给父类处理
    QWidget::closeEvent(event);
}

Widget::~Widget()
{
    delete ui;
}

