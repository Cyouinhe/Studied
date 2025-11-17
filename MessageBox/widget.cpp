#include "widget.h"
#include "ui_widget.h"
#include<QMessageBox>
#include<QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    int ret1 = QMessageBox::question(this, "问题对话框", "你了解Qt吗？", QMessageBox::Yes, QMessageBox::No);
    if(ret1 == QMessageBox::Yes)
    {
        qDebug()<<"问题！";
    }
    int ret2 = QMessageBox::information(this, "提示对话框", "这是Qt书籍！", QMessageBox::Ok);
    if(ret2 == QMessageBox::Ok)
    {
        qDebug()<<"提示！";
    }
    int ret3 = QMessageBox::warning(this, "警告对话框", "不能提前结束！", QMessageBox::Abort);
    if(ret2 == QMessageBox::Abort)
    {
        qDebug()<<"警告！";
    }
    int ret4 = QMessageBox::critical(this, "严重错误对话框", "发现一个严重错误！现在要关闭所有文件！", QMessageBox::YesAll);
    if(ret2 == QMessageBox::YesAll)
    {
        qDebug()<<"错误！";
    }
    QMessageBox::about(this, "关于对话框", "Qt对话框实例");
}
