#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->pushButton,&QPushButton::clicked,[=](){
        //点击按钮 选取文件
        QString path = QFileDialog::getOpenFileName(this,"打开文件","C:\\Users\\OMEN\\Desktop");
        if(path.isEmpty()){
            QMessageBox::warning(this,"警告","打开失败");
        }
        else{
//            ui->lineEdit->setText(path);
            //QFile  默认支持UTF-8格式
//            QFile file(path);
            //QIODevice：只要是IO设备都可以通过它打开 例如 文件 磁盘
//            /*file.open(QIODevice::ReadOnly);*/
            //QFileDevice  只能打开文件设备
//            file.open(QFileDevice::ReadOnly);

//            QByteArray array;
//            array = file.readAll();

//            ui->textEdit->setText(array);
//            file.close();

//------------------
//            ui->lineEdit->setText(path);
//            QFile file(path);
//            //写的方式打开 在文档后面追加内容
//            file.open(QIODevice::Append | QIODevice::ReadOnly);
//            file.open(QIODevice::ReadOnly);

//            QByteArray array;
//            array = file.readAll();
//            ui->textEdit->setText(array);
//            //必须关闭  才能进行后续写的操作
//            file.close();

//            //WriteOnly是把之前的覆盖掉 写
//            //Append是在后面追加写
//            file.open(QIODevice::Append);
//            file.write("9999");

//            file.close();


//------------------QFileInfo--------查看文件信息
            QFileInfo info(path);
            qDebug() << info.path();
            qDebug() << info.fileName();
            qDebug() << info.size();
            qDebug() << info.suffix();
            //创建日期
            qDebug() << info.created().toString("yyyy-MM-dd  hh:mm:ss");
            //修改日期
            qDebug() << info.lastModified().toString("yyyy/MM/dd  hh:mm:ss");

        }
    });

//------------------QFile--------文本流
//    QFile file("aaa.txt");
//    file.open(QFileDevice::WriteOnly);
//    QTextStream stream(&file);
//    stream << QString("Hello world") << 1111;
//    file.close();

//    file.open(QFileDevice::ReadOnly);
//    QString str;
//    /*stream >> str;*/  //读取到空格就结束
//    str = stream.readAll();
//    qDebug() << str;
//    file.close();

//------------------QFile--------数据流
    QFile file("bbbbb.txt");
    file.open(QFileDevice::WriteOnly);
    QDataStream stream(&file);
    stream << QString("hwllo world" ) << 132456;
    file.close();

    file.open(QFileDevice::ReadOnly);
    QString str;
    int num;
    stream >> str >> num;
    qDebug() << str;
    qDebug() << num;
    file.close();

}

Widget::~Widget()
{
    delete ui;
}

