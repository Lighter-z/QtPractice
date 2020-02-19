#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDialog>
#include <QMessageBox>
#include <QColorDialog>
#include <QColor>
#include <QFileDialog>
#include <QString>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionNew,&QAction::triggered,this,[=](){
        qDebug() << "弹出对话框";
        //对话框有两种
        //1、模态对话框（弹出对话框时，不能对其他操作）
        //2、非模态对话框（弹出对话框时，还可以对其他进行操作）

        //1、模态
//        QDialog dlg1(this);
//        dlg1.resize(200,100);  //设置对话框大小
//        dlg1.exec();  //阻塞

        //2、非模态
//        QDialog dlg2(this);   //建立在栈上，随着函数结束，这个对象也会被释放
//        dlg2.resize(200,100);
//        dlg2.show();

//        QDialog * dlg2 = new QDialog(this);    //建立在堆上
//        dlg2->resize(100,200);
//        dlg2->show();

//        //如果想要关闭小对话框时候，释放这个对象，则需要设置属性
//        dlg2->setAttribute(Qt::WA_DeleteOnClose);

        //标准对话框
        //1、错误对话框
//        QMessageBox::critical(this,"错误！","critical");
        //2、信息对话框
//        QMessageBox::information(this,"信息","infor");
        //3、询问对话框
//        QMessageBox::question(this,"问题","question");

        //参数1、父亲 2、标题 3、提示内容 4、按键类型 5、关联回车按键
//        QMessageBox::question(this,"问题","question",QMessageBox::Save | QMessageBox::Cancel,QMessageBox::Cancel);

//        if(QMessageBox::Yes == QMessageBox::question(this,"问题","question")) {
//            qDebug() << "Yes";
//        }else {
//            qDebug() << "No";
//        }

        //4、警告对话框
//        QMessageBox::warning(this,"警告","waring",QMessageBox::Ok,QMessageBox::Ok);

        //文件
        QFileDialog::getSaveFileName();

    });

    connect(ui->actionOpen,&QAction::triggered,this,[=](){
        //选择文件或者目录
//        QFileDialog::getOpenFileName();
        //默认是打开所有文件类型
        QString path = QFileDialog::getOpenFileName(this,"打开文件","F:\\1.Work\\1.Study\\BASE","*.txt*.png");
        qDebug() << path;
    });

    connect(ui->actionColorOpen,&QAction::triggered,this,[=](){
        //颜色对话框
        QColor color = QColorDialog::getColor(QColor(255,0,0));
        qDebug() << color;
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

