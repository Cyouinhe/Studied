#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    currentStyleSheet = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "文件对话框", "C:", "图片文件(*.png *.jpg);;文本文件(*.txt)");
    qDebug()<<"文件名称："<<fileName;
}


void MainWindow::on_actionOpen_3_triggered()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok)
    {
        ui->label->setFont(font);
    }
    else{
        qDebug()<<"没有选择字体";
    }
}

void MainWindow::on_actionOpen_2_triggered()
{
    QColor color = QColorDialog::getColor(Qt::red, this, "选择字体颜色", QColorDialog::ShowAlphaChannel);
    if(color.isValid())
    {
        QString newStyle = QString("color:%1;").arg(color.name());
        currentStyleSheet += newStyle;
        ui->label->setStyleSheet(currentStyleSheet);
        qDebug()<<"字体颜色为："<<color.name();
        qDebug()<<currentStyleSheet;
    }
    else{
        qDebug()<<"取消选择颜色";
    }

}

void MainWindow::on_action_B_triggered()
{
    QColor color = QColorDialog::getColor(Qt::red, this, "选择字体颜色", QColorDialog::ShowAlphaChannel);
    if(color.isValid())
    {
        QString newStyle = QString("background-color:%1;").arg(color.name());
        currentStyleSheet += newStyle;
        ui->label->setStyleSheet(currentStyleSheet);
        qDebug()<<"背景颜色为："<<color.name();
        qDebug()<<currentStyleSheet;
    }
    else{
        qDebug()<<"取消选择颜色";
    }
}
