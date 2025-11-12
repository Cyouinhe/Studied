#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
#include<QColorDialog>
#include<QFileDialog>
#include<QFontDialog>
#include<QInputDialog>

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

void Widget::on_pushButton_7_clicked()
{
    QColor color = QColorDialog::getColor(Qt::red, this, "颜色对话框", QColorDialog::ShowAlphaChannel);
    qDebug()<<"color:"<<color;
    qDebug()<<"RGB值:"<<color.red()<<color.green()<<color.blue();
    qDebug()<<"十六进制:"<<color.name();


}

void Widget::on_pushButton_6_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "文件对话框", "C:", "图片文件(*.png *.jpg);;文本文件(*.txt)");
    qDebug()<<"文件名称："<<fileName;
}

void Widget::on_pushButton_clicked()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok)
    {
        ui->pushButton->setFont(font);
    }
    else{
        qDebug()<<"没有选择字体";
    }
}

void Widget::on_pushButton_5_clicked()
{
    bool ok;
    QString name = QInputDialog::getText(this, "输入对话框", "请输入用户名：", QLineEdit::Normal, "admin", &ok);
    if(ok)
    {
        qDebug()<<"用户名："<<name;
    }
    int intNum = QInputDialog::getInt(this, "整数输入对话框", "请输入 -1000 到 1000 之间的数值", 100, -1000, 1000, 10, &ok);
    if(ok)
    {
        qDebug()<<"整数值："<<intNum;
    }
    double doubleNum = QInputDialog::getDouble(this, "浮点数输入对话框", "请输入 -1000 到 1000 之间的数值", 0.00, -1000, 1000, 2, &ok);
    if(ok)
    {
        qDebug()<<"浮点数值：" <<doubleNum;
    }
    QStringList items;
    items<<"条目1"<<"条目2";
    QString item = QInputDialog::getItem(this, "条目输入对话框", "请选择或输入一个条目", items, 0, true, &ok);
    if(ok)
    {
        qDebug()<<"item:"<<item;
    }
}
