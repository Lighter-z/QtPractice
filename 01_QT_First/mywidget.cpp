#include "mywidget.h"
#include <QPushButton>
#include "mybutton.h"
//命名规范 快捷键
/*
类名  首字母大写 单词与单词之间首字母大写
变量、函数  首字母大写 单子与单子之间首字母大写

快捷键：
运行：  ctrl + r
编译：  ctrl + b
查找：  ctrl + f
帮助文档：  F1   按ESC 退出帮助文档
字体缩放： ctrl + 鼠标滚轮
自动对齐： ctrl + i
整行引用： ctrl + shift + ↑ 或 ↓
同名之间的.h .cpp切换：F4
注释：  ctrl + /

*/
MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)    //初始化列表 ：将参数传给父类 让父类进行初始化
{
    //按钮
    QPushButton * btn1 = new QPushButton;
    //show,用顶层方式弹出，不会在MyWidiget界面上显示，若想要在MyWidiget界面上显示，需要依赖于MyWidiget窗口
    btn1->show();
    //设置父亲，这样就可以在MyWidiget界面上显示
    btn1->setParent(this);
    //设置按钮文字
    btn1->setText("1111");  //将char * 隐式类型转换位QString
    btn1->move(100,100);

    //第二种创建按钮方式
    QPushButton * btn2 = new QPushButton("按钮2",this);
    //设置窗口大小
    resize(600,400);
    //移动按钮 设置坐标
    btn2->move(0,0);
    //设置按钮大小
    btn2->resize(50,50);

    //重置窗口标题
    setWindowTitle("QT第一个窗口");
    //设置固定窗口大小
    setFixedSize(600,500);

    //QT一定程度下简化了内存回收机制
    //关闭界面时候，会调用相应的析构函数
    MyButton *myButton = new MyButton;
    myButton->setParent(this);
    myButton->setText("我的按键");
    myButton->resize(70,70);
    myButton->move(300,300);

    //点击 我的按键 关闭窗口
    //参数1 信号的发送者，参数2 发送的信号，参数3 信号接收这，参数4 处理的槽函数
    connect(myButton,&MyButton::clicked,this,&MyWidget::close);
}

MyWidget::~MyWidget()
{
}

