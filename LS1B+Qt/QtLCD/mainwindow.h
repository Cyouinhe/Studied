#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnOpen_clicked();          // 打开串口
    void on_btnSend_clicked();          // 发送数据
    void readSerialData();              // 读取串口数据
    void on_btnRefresh_clicked();       // 刷新串口列表

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;                // 串口对象
    bool isSerialOpen;                  // 串口状态标记
};

#endif // MAINWINDOW_H
