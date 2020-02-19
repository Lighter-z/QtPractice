#include "widget.h"
#include "ui_widget.h"
#include <QMovie>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->BtnTab,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->BtnScrol,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(1);
    });

    connect(ui->BtnToolBox,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(2);
    });

    ui->comboBox_2->addItem("代码创建");
    ui->comboBox_2->addItem("che");

    connect(ui->pushButton_7,&QPushButton::clicked,[=](){
        ui->comboBox->setCurrentText("ui界面创建");
    });

    connect(ui->pushButton_8,&QPushButton::clicked,[=](){
        ui->comboBox_2->setCurrentIndex(1);
    });

    ui->label->setPixmap(QPixmap(":/img/1.jpg"));

    QMovie * mov = new QMovie(":/img/2.gif");
    ui->label_2->setMovie(mov);
    mov->start();
}

Widget::~Widget()
{
    delete ui;
}

