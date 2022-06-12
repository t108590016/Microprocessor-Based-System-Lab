#include "mainwindow.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    /*
    Ui ui=w.getUI();
    if(ui->LED1->isChecked() == true)
        gpio_control(396, "on");
    else
        gpio_control(396, "off");
    if(ui->LED2->isChecked() == true)
        gpio_control(255, "on");
    else
        gpio_control(255, "off");
    if(ui->LED3->isChecked() == true)
        gpio_control(428, "on");
    else
        gpio_control(428, "off");
    if(ui->LED4->isChecked() == true)
        gpio_control(427, "on");
    else
        gpio_control(427, "off");
    */
    return a.exec();
}
