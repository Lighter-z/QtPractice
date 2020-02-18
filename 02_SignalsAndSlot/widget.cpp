#include "widget.h"

/*
需求：做两个类  Teacher类  Student类
下课后，老师Teacher  zt  会发出一个信号   饿了
学生响应信号  Student  st  处理信号的槽函数  请客吃饭
*/

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    zt = new Teacher(this);
    st = new Student(this);

    //连接  老师和学生
    //connect(zt,&Teacher::Hungry,st,&Student::tryEat);
    //由于添加了有参的信号和槽函数 所以不能再使用上述写法  因为不知道指向的是无参函数还是有参函数

    //调用有参
    void(Teacher:: * teacherFood)(QString) = &Teacher::Hungry;
    void(Student:: * studentFood)(QString) = &Student::tryEat;
    connect(zt,teacherFood,st,studentFood);

    classIsOver();

    QPushButton * btn = new QPushButton;
    btn->setParent(this);
    btn->setText("下课");
    btn->resize(50,50);
    btn->move(10,10);

//信号和槽的扩展：
//1、信号可以连接信号
//2、信号和槽可以断开
//3、一个信号可以触发多个槽函数
//4、多个信号可以连接一个槽函数
//5、信号和槽的参数必须一一对应
    //（参数个数不一定一一对应，信号的参数个数可以多于槽函数的参数个数，反之不可以，但是类型必须一一对应）

    //按键触发 学生请老师吃饭
    //无参
    void(Teacher:: * noTeacherFood)(void) = &Teacher::Hungry;
    void(Student:: * noStudentFood)(void) = &Student::tryEat;
//1、信号可以连接信号
    //信号连接信号  clicked信号连接Hungry信号 当clicked触发时，Hungry也会触发
    connect(btn,&QPushButton::clicked,zt,noTeacherFood);
    connect(zt,noTeacherFood,st,noStudentFood);

    //断开信号和信号槽
//2、信号和槽可以断开
//    disconnect(zt,noTeacherFood,st,noStudentFood);

//3、一个信号可以触发多个槽函数
    connect(btn,&QPushButton::clicked,this,&Widget::close);
//4、多个信号可以连接一个槽函数
    QPushButton * btn2 = new QPushButton("按键2",this);
    connect(btn2,&QPushButton::clicked,this,&Widget::close);

//lambda表达式
    //= 值传递  可以使用lambda所在作用范围内所有可见的局部变量
    [=](){
        btn2->setText("4444");
    }();

    //& 引用传递  可以使用lambda所在作用范围内所有可见的局部变量
    [&](){
        btn2->setText("4444");
    }();

    //btn  内部只能调用btn的  调用其他报错
    [btn](){
        //btn2->setText("4444");  //报错
        btn->setText("下课[]");
    }();

    //mutable关键字  用于修改值传递的 变量 进行修改
    QPushButton * myBtn1 = new QPushButton("myBtn1",this);
    QPushButton * myBtn2 = new QPushButton("myBtn2",this);
    myBtn2->move(100,100);
    myBtn1->move(130,130);

    int m = 10;
    connect(myBtn1,&QPushButton::clicked,this,[=]()mutable{
        m = 100;
        qDebug() << "m = " << m;
    });

    connect(myBtn2,&QPushButton::clicked,this,[=](){
        qDebug() << "m = " << m;
    });

    //返回值
    int ret = []()->int{return 8000;}();
    qDebug() << ret ;

    QPushButton * myBtn3 = new QPushButton("myBtn3",this);
    myBtn3->move(70,70);
    //使用最频繁的就是 [=](){}
    connect(myBtn3,&QPushButton::clicked,this,[=](){
        myBtn3->setText("myBtn3333");
    });

    //做信号连接时  默认内部变量会进行锁状态！！！  只读状态 如果进行写操作 程序会挂掉
//    connect(myBtn3,&QPushButton::clicked,this,[&](){
//        myBtn3->setText("myBtn3333");
//    });

    //无参按钮调用  有参 请客吃饭
    connect(myBtn3,&QPushButton::clicked,this,[=]{
        zt->Hungry("----宫保鸡丁");
    });

    connect(myBtn3,&QPushButton::clicked,this,[=]{
        this->close();
    });


}

Widget::~Widget()
{
}

void Widget::classIsOver(){
    //触发 hungry 信号
    //触发自定义信号关键字 emit
    emit zt->Hungry();
    emit zt->Hungry("宫保鸡丁");
}


