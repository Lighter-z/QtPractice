#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QStringList>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->radioButtonMain,&QRadioButton::clicked,this,[=](){
        qDebug() << "选中男的";
    });
    //使用lambda表达式时，可以不写this
    //选中打印2  未选中打印0  半选中打印1
    //半打印 需要在ui界面中 勾选tristate
    connect(ui->checkBox,&QCheckBox::stateChanged,[=](int value){
        qDebug() << value ;
    });

    //利用listWidget写诗
//    QListWidgetItem * item = new QListWidgetItem("锄禾日当午");
//    //设置dui对齐方式
//    item->setTextAlignment(Qt::AlignHCenter);
//    ui->listWidget->addItem(item);

    QStringList list;
    //缺点：不能设置对齐方式
    list << "锄禾日当午" << "汗滴禾下土" << "谁知盘中餐";
    ui->listWidget->addItems(list);

}

Widget::~Widget()
{
    delete ui;
}

