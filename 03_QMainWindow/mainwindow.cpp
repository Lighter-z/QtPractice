#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(600,400);
//1、菜单栏  只能有一个
    QMenuBar * bar1 = menuBar();
    //将cai'dan'lan 放入窗口中
    this->setMenuBar(bar1);
    //创建菜单
    QMenu * fileMenu = bar1->addMenu("文件");
    QMenu * editMenu = bar1->addMenu("编辑");

    //添加菜单项
    QAction * newAction = fileMenu->addAction("新建");
    QAction * openAction = fileMenu->addAction("打开");
    //添加分割线
    fileMenu->addSeparator();
    QMenu * openMenu = fileMenu->addMenu("打开所在文件夹");

//2、工具栏  可以有多个
    QToolBar * toolBar1 = new QToolBar(this);
    //设置默认停靠范围
    addToolBar(Qt::TopToolBarArea,toolBar1);
    //只允许左右停靠
    toolBar1->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);
    //设置浮动  关闭
    toolBar1->setFloatable(false);
    //设置移动（总开关）
    //toolBar1->setMovable(false);

    //工具栏添加菜单项
    toolBar1->addAction(newAction);
    toolBar1->addSeparator();
    toolBar1->addAction(openAction);
    toolBar1->resize(10,10);


//3、状态栏  只能有一个
    QStatusBar * stBar = statusBar();
    setStatusBar(stBar);
    QLabel * label1 = new QLabel("提示信息",this);
    stBar->addWidget(label1);
    QLabel * label2 = new QLabel("右侧添加提示信息",this);
    stBar->addPermanentWidget(label2);

//4、核心部件  只能由一个
    QTextEdit *textEdit = new QTextEdit;  //wen'ben'bian'ji'kuang文本编辑框
    setCentralWidget(textEdit);

//5、铆接部件  浮动窗口 可以有多个
    QDockWidget * dock = new QDockWidget;
    addDockWidget(Qt::BottomDockWidgetArea,dock);
    dock->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);


}

MainWindow::~MainWindow()
{
}

