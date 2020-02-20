#include "smallwidget.h"
#include "ui_smallwidget.h"
#include <QSpinBox>

SmallWidget::SmallWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmallWidget)
{
    ui->setupUi(this);

    //数字连接滑块
    //QSpinBox:: * signal  指明函数指针的作用域在QSpinBox下
    void(QSpinBox:: * spinSignal)(int) = &QSpinBox::valueChanged;
    connect(ui->spinBox,spinSignal,ui->horizontalSlider,&QSlider::setValue);
    //滑块连接数字
    connect(ui->horizontalSlider,&QSlider::valueChanged,ui->spinBox,&QSpinBox::setValue);
}

void SmallWidget::setValue(int value)
{
    ui->spinBox->setValue(value);
}

int SmallWidget::getValue()
{
    return ui->spinBox->value();
}

SmallWidget::~SmallWidget()
{
    delete ui;
}
