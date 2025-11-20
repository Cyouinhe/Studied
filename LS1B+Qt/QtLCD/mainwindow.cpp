#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    isSerialOpen(false)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);

    // 初始化串口参数选项
    // 波特率
    ui->cbbBaud->addItems(QStringList() << "4800" << "9600" << "19200" << "38400"
                                        << "57600" << "115200" << "230400");
    ui->cbbBaud->setCurrentText("115200");

    // 数据位
    ui->cbbDataBits->addItems(QStringList() << "5" << "6" << "7" << "8");
    ui->cbbDataBits->setCurrentText("8");

    // 停止位
    ui->cbbStopBits->addItems(QStringList() << "1" << "1.5" << "2");
    ui->cbbStopBits->setCurrentText("1");

    // 校验位
    ui->cbbParity->addItems(QStringList() << "None" << "Even" << "Odd" << "Space" << "Mark");
    ui->cbbParity->setCurrentText("None");

    // 刷新串口列表
    on_btnRefresh_clicked();

    // 连接串口读取信号槽
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readSerialData);
}

MainWindow::~MainWindow()
{
    if(serial->isOpen())
        serial->close();
    delete ui;
}

// 刷新串口列表
void MainWindow::on_btnRefresh_clicked()
{
    ui->cbbPort->clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->cbbPort->addItem(info.portName() + " - " + info.description());
    }
}

// 打开/关闭串口
void MainWindow::on_btnOpen_clicked()
{
    if(!isSerialOpen)
    {
        // 获取串口名称
        QString portName = ui->cbbPort->currentText().split(" - ").first();
        serial->setPortName(portName);

        // 设置波特率
        qint32 baudRate = ui->cbbBaud->currentText().toInt();
        serial->setBaudRate(baudRate);

        // 设置数据位
        switch(ui->cbbDataBits->currentText().toInt())
        {
            case 5: serial->setDataBits(QSerialPort::Data5); break;
            case 6: serial->setDataBits(QSerialPort::Data6); break;
            case 7: serial->setDataBits(QSerialPort::Data7); break;
            case 8: serial->setDataBits(QSerialPort::Data8); break;
            default: serial->setDataBits(QSerialPort::Data8);
        }

        // 设置停止位
        if(ui->cbbStopBits->currentText() == "1")
            serial->setStopBits(QSerialPort::OneStop);
        else if(ui->cbbStopBits->currentText() == "1.5")
            serial->setStopBits(QSerialPort::OneAndHalfStop);
        else if(ui->cbbStopBits->currentText() == "2")
            serial->setStopBits(QSerialPort::TwoStop);

        // 设置校验位
        if(ui->cbbParity->currentText() == "None")
            serial->setParity(QSerialPort::NoParity);
        else if(ui->cbbParity->currentText() == "Even")
            serial->setParity(QSerialPort::EvenParity);
        else if(ui->cbbParity->currentText() == "Odd")
            serial->setParity(QSerialPort::OddParity);
        else if(ui->cbbParity->currentText() == "Space")
            serial->setParity(QSerialPort::SpaceParity);
        else if(ui->cbbParity->currentText() == "Mark")
            serial->setParity(QSerialPort::MarkParity);

        // 设置流控
        serial->setFlowControl(QSerialPort::NoFlowControl);

        // 打开串口
        if(serial->open(QIODevice::ReadWrite))
        {
            isSerialOpen = true;
            ui->btnOpen->setText("关闭串口");
            ui->cbbPort->setEnabled(false);
            ui->cbbBaud->setEnabled(false);
            ui->cbbDataBits->setEnabled(false);
            ui->cbbStopBits->setEnabled(false);
            ui->cbbParity->setEnabled(false);
            ui->btnRefresh->setEnabled(false);
            QMessageBox::information(this, "成功", "串口打开成功！");
        }
        else
        {
            QMessageBox::critical(this, "失败", "串口打开失败：" + serial->errorString());
        }
    }
    else
    {
        // 关闭串口
        serial->close();
        isSerialOpen = false;
        ui->btnOpen->setText("打开串口");
        ui->cbbPort->setEnabled(true);
        ui->cbbBaud->setEnabled(true);
        ui->cbbDataBits->setEnabled(true);
        ui->cbbStopBits->setEnabled(true);
        ui->cbbParity->setEnabled(true);
        ui->btnRefresh->setEnabled(true);
    }
}

// 发送数据
void MainWindow::on_btnSend_clicked()
{
    if(!isSerialOpen)
    {
        QMessageBox::warning(this, "警告", "请先打开串口！");
        return;
    }

    QString sendData = ui->txtSend->text().trimmed();
    if(sendData.isEmpty())
    {
        QMessageBox::warning(this, "警告", "发送数据不能为空！");
        return;
    }

    // 发送数据（添加回车换行符与嵌入式程序匹配）
    QByteArray sendBytes = sendData.toUtf8();
    qint64 bytesWritten = serial->write(sendBytes);

    if(bytesWritten == -1)
    {
        QMessageBox::critical(this, "失败", "数据发送失败！");
    }
    else
    {
        ui->txtRecv->append("[发送]：" + sendData);
        ui->txtSend->clear();
    }
}

// 读取串口数据
void MainWindow::readSerialData()
{
    QByteArray recvData = serial->readAll();
    if(!recvData.isEmpty())
    {
        QString recvStr = QString::fromUtf8(recvData);
        ui->txtRecv->append("[接收]：" + recvStr);
    }
}
