#include "mywidget.h"
#include <QPushButton>

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

*/
MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)    //初始化列表 ：将参数传给父类 让父类进行初始化
{
    //按钮

}

MyWidget::~MyWidget()
{
}

