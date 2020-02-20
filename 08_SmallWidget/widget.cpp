#include "widget.h"
#include "ui_widget.h"
#include "smallwidget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->getBtn,&QPushButton::clicked,[=](){
        qDebug() << ui->widget->getValue();
    });

    connect(ui->setBtn,&QPushButton::clicked,[=](){
        ui->widget->setValue(50);
    });

}

Widget::~Widget()
{
    delete ui;
}

