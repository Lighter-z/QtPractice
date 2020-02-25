#include "dialoglist.h"
#include "ui_dialoglist.h"

#include <QToolButton>
#include <QMessageBox>
#include "widget.h"

DialogList::DialogList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogList)
{
    ui->setupUi(this);
    //设置标题
    setWindowTitle("MySelfQQ");
    //设置图标
    //QPixmap 会自动转换为 QIcon 类型
//    setWindowIcon(QPixmap(":/images/qq.png"));
    setWindowIcon(QIcon(":/images/qq.png"));

    QList<QString>nameList;
    nameList << "忆梦" << "北京出版人" << "Cherry" << "淡然" << "娇娇"
             << "水落" << "清末" << "无语";
    QStringList iconNaleList;
    iconNaleList << "ymrl" << "qq" << "Cherry" << "dr" << "jj"
                 << "lswh" << "qmnn" << "spqy";
    QVector<QToolButton *> vToolBtn;
    for(int i = 0; i < nameList.size(); i++)
    {
        //设置头像
        QToolButton * btn = new QToolButton;
        //设置名字
        btn->setText(nameList[i]);
        //设置头像
        QString str = QString(":/images/%1.png").arg(iconNaleList.at(i));
        btn->setIcon(QPixmap(str));
        //设置头像大小  设置为和图片一样大
        btn->setIconSize(QPixmap(str).size());
        //设置为透明风格
        btn->setAutoRaise(true);
        //设置文字和图片一起显示
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        //加载到 垂直布局中
        ui->vLayout->addWidget(btn);
        //保存在容器中 方便后面操作
        vToolBtn.push_back(btn);
        //对话框 是否打开标志位初始化
        isShow.push_back(false);
    }

    //对 对话框添加信号和槽
    for(int i = 0; i < nameList.size(); i++)
    {
        connect(vToolBtn[i],&QToolButton::clicked,[=]{
            if(isShow[i])
            {
                QString str = QString("%1窗口已经打开").arg(vToolBtn[i]->text());
                QMessageBox::warning(this,"警告",str,QMessageBox::Ok);
                return;
            }
            isShow[i] = true;
            //弹出对话框
            //构造时候 告诉对话框他的名字   参数1 顶层弹出方式（当主页面关闭 对话框也会关闭） 参数2 窗口名字
            Widget * widget = new Widget(0,vToolBtn[i]->text());
            //设置标题
            widget->setWindowTitle(vToolBtn[i]->text());
            //设置图片
            widget->setWindowIcon(vToolBtn[i]->icon());
            //显示
            widget->show();

            connect(widget,&Widget::closeWidget,[=](){
                //关闭
                isShow[i] = false;
            });
        });

    }

}

DialogList::~DialogList()
{
    delete ui;
}
