#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
