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

void Widget::on_pushButton_3_clicked()
{
    QWizard wizard(this);
    wizard.setWindowTitle("向导对话框");
    wizard.addPage(createPage1());
    wizard.addPage(createPage2());
    wizard.addPage(createPage3());
    wizard.exec();
}

QWizardPage *Widget::createPage1()
{
    QWizardPage *page = new QWizardPage();
    page->setTitle("介绍");
    return page;
}
QWizardPage *Widget::createPage2()
{
    QWizardPage *page = new QWizardPage();
    page->setTitle("用户选择信息");
    return page;
}

QWizardPage *Widget::createPage3()
{
    QWizardPage *page = new QWizardPage();
    page->setTitle("结束");
    return page;
}


