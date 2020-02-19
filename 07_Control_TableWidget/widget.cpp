#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QStringList list;
    list << "姓名" << "性别" << "年龄";
    //设置标题头大小
    ui->tableWidget->setColumnCount(list.size());
    //设置标题头内容
    ui->tableWidget->setHorizontalHeaderLabels(list);
    //设置有几行
    ui->tableWidget->setRowCount(5);
    //准备数据
    QStringList nameList;
    nameList << "亚瑟" << "妲己" << "安其拉" << "东皇太一" << "李白";
    QStringList sexList;
    sexList << "男" << "女" << "女" << "男" << "男";
    for (int i = 0;i < 5;i++) {
        int col = 0;
        //添加名字
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(nameList[i]));
        //添加性别
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(sexList[i]));
        //添加年龄
        //int 转 QString
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(QString::number(i+18)));
    }
    //点击按钮  增加 赵云
    connect(ui->addButton,&QPushButton::clicked,this,[=](){
        bool isEmpty = ui->tableWidget->findItems("赵云",Qt::MatchExactly).empty();
        if(isEmpty){
            //添加到第0行
            ui->tableWidget->insertRow(0);
            ui->tableWidget->setItem(0,0,new QTableWidgetItem("赵云"));
            ui->tableWidget->setItem(0,1,new QTableWidgetItem("男"));
            ui->tableWidget->setItem(0,2,new QTableWidgetItem(QString::number(20)));
        }
        else{
            QMessageBox::warning(this,"警告","已经有了");
        }
    });

    //点击按钮 删除 赵云
    connect(ui->deleteButton,&QPushButton::clicked,[=](){
        bool isEmpty = ui->tableWidget->findItems("赵云",Qt::MatchExactly).empty();
        if(isEmpty){
            QMessageBox::warning(this,"警告","赵云没有了");
        }
        else{
            int row = ui->tableWidget->findItems("赵云",Qt::MatchExactly).first()->row();
            ui->tableWidget->removeRow(row);
        }
    });
}

Widget::~Widget()
{
    delete ui;
}

