#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //通过ui寻找控件
//    ui->actionNew->setIcon(QIcon("F:/1.Work/1.Study/BASE/QT/QtPractice/04_Source/picture/file1.png"));

    //添加资源到项目文件中
    //使用资源文件 ": + 前缀名 + 文件名"
    ui->actionNew->setIcon(QIcon(":/picture/file1.png"));
    ui->actionOpen->setIcon(QIcon(":/picture/open.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

