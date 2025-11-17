#include "widget.h"
#include "ui_widget.h"
#include <QInputDialog>
#include <QDebug>

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
    QString name = QInputDialog::getText(this, "用户名输入对话框", "请输入用户名：", QLineEdit::Normal, "admin", &ok);
    if(ok){
        qDebug()<<"用户名："<<name;
    }
}

void Widget::on_pushButton_2_clicked()
{
    int intNum = QInputDialog::getInt(this, "整数输入对话框", "请输入-1000到1000的整数：", 100, -1000, 1000, 10, &ok);
    if(ok){
        qDebug()<<"整数值："<<intNum;
    }
}

void Widget::on_pushButton_3_clicked()
{
    double doubleNum = QInputDialog::getDouble(this, "浮点数输入对话框", "请输入-1000到1000的浮点数：", 100.00, -1000, 1000, 10, &ok);
    if(ok){
        qDebug()<<"浮点数值："<<doubleNum;
    }
}

void Widget::on_pushButton_4_clicked()
{
    QStringList items;
    items<<"条目1"<<"条目2";
    QString itemsNum = QInputDialog::getItem(this, "条目输入对话框", "请选择条目：", items, 0, false, &ok);
    if(ok)
    {
        qDebug()<<"条目值："<<itemsNum;
    }
}
