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

void MainWindow::on_actionOpen_2_triggered()
{
    QColor color = QColorDialog::getColor(Qt::red, this, "颜色对话框", QColorDialog::ShowAlphaChannel);
    qDebug()<<"color:"<<color;
    qDebug()<<"RGB值:"<<color.red()<<color.green()<<color.blue();
    qDebug()<<"十六进制:"<<color.name();
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
