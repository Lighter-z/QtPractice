#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //添加信息可以直接在.ui中添加  宏 = 0
    //也可以使用代码添加  宏= 1
#if 1
    //添加头
    ui->treeWidget->setHeaderLabels(QStringList()<<"代码添加1" << "代码添加2");
    //添加项目
    QTreeWidgetItem * liItem = new QTreeWidgetItem(QStringList()<<"智力");
    QTreeWidgetItem * minItem = new QTreeWidgetItem(QStringList()<<"敏捷");
    //添加顶层项目
    ui->treeWidget->addTopLevelItem(liItem);
    ui->treeWidget->addTopLevelItem(minItem);

    QStringList hero1;
    hero1 << "111" << "5555";
    QStringList hero2;
    hero2 << "222" << "6666";

    //追加子项目
    QTreeWidgetItem * zhi1 = new QTreeWidgetItem(hero1);
    liItem->addChild(zhi1);

    QTreeWidgetItem * min1 = new QTreeWidgetItem(hero2);
    minItem->addChild(min1);
#endif



}

Widget::~Widget()
{
    delete ui;
}

