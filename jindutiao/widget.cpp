#include "widget.h"
#include "ui_widget.h"
#include <QProgressDialog>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    errorDialog = new QErrorMessage(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QProgressDialog dialog("文件复制进度", "取消", 0, 50000, this);
    dialog.setWindowTitle("进度对话框");
    dialog.show();
    for(int i = 0; i < 50000; i++)
    {
        dialog.setValue(i);
        QCoreApplication::processEvents();
        if(dialog.wasCanceled())
        {
            qDebug()<<"取消！";
            break;
        }
    }
    if(dialog.value() >= 49000)
        qDebug()<<"复制结束！";

}

void Widget::on_pushButton_2_clicked()
{
    errorDialog->setWindowTitle("错误消息对话框");
    errorDialog->showMessage("错误！");
}
