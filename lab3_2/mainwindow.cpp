#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gpio_control.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    pm.scaledToHeight(10);
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::LED_Switching1()
{
    count++;
    printf("%d\n",count);
    ui->LED1_pic->setPixmap(pm);
    ui->LED1_pic->setScaledContents(true);
    ui->LED2_pic->setPixmap(pm);
    ui->LED2_pic->setScaledContents(true);
    ui->LED3_pic->setPixmap(clearPm);
    ui->LED4_pic->setPixmap(clearPm);
    ui->LED1->setCheckState(Qt::Checked);
    ui->LED2->setCheckState(Qt::Checked);
    ui->LED3->setCheckState(Qt::Unchecked);
    ui->LED4->setCheckState(Qt::Unchecked);
    gpio_control(396, "on");
    gpio_control(255, "on");
    gpio_control(428, "off");
    gpio_control(427, "off");


}
void MainWindow::LED_Switching2()
{
    count++;
    printf("%d\n",count);
    ui->LED1_pic->setPixmap(clearPm);
    ui->LED2_pic->setPixmap(clearPm);
    ui->LED3_pic->setPixmap(pm);
    ui->LED3_pic->setScaledContents(true);
    ui->LED4_pic->setPixmap(pm);
    ui->LED4_pic->setScaledContents(true);
    ui->LED1->setCheckState(Qt::Unchecked);
    ui->LED2->setCheckState(Qt::Unchecked);
    ui->LED3->setCheckState(Qt::Checked);
    ui->LED4->setCheckState(Qt::Checked);
    gpio_control(396, "off");
    gpio_control(255, "off");
    gpio_control(428, "on");
    gpio_control(427, "on");

}



void MainWindow::on_LEDShining_clicked()
{


    if(ui->LED1->isChecked()){
            //ui->LED1_pic->setText("Shining!");
        ui->LED1_pic->setPixmap(pm);
        ui->LED1_pic->setScaledContents(true);
        gpio_control(396, "on");
    }
    else{
        ui->LED1_pic->setPixmap(clearPm);
        gpio_control(396, "off");
    }
    if(ui->LED2->isChecked() == true){
            //ui->LED2_pic->setText("Shining!");
            ui->LED2_pic->setPixmap(pm);
            ui->LED2_pic->setScaledContents(true);
            gpio_control(255, "on");
    }
    else{
        ui->LED2_pic->setPixmap(clearPm);
        gpio_control(255, "off");
    }
    if(ui->LED3->isChecked() == true){
            //ui->LED3_pic->setText("Shining!");
            ui->LED3_pic->setPixmap(pm);
            ui->LED3_pic->setScaledContents(true);
            gpio_control(428, "on");
    }
    else{
        ui->LED3_pic->setPixmap(clearPm);
        gpio_control(428, "off");
    }
    if(ui->LED4->isChecked() == true){
            //ui->LED4_pic->setText("Shining!");
            ui->LED4_pic->setPixmap(pm);
            ui->LED4_pic->setScaledContents(true);
            gpio_control(427, "on");
    }
    else{
        ui->LED4_pic->setPixmap(clearPm);
        gpio_control(427, "off");
    }
}

void MainWindow::on_LEDSwitchingOn_clicked()
{
    connect(timer1, SIGNAL(timeout()), this, SLOT(LED_Switching1()));
    timer1->start(1000*ui->spinBox->value()*0.01);
    connect(timer2, SIGNAL(timeout()), this, SLOT(LED_Switching2()));
    timer2->start(2000*ui->spinBox->value()*0.01);
}

void MainWindow::on_LEDSwitchingOff_clicked()
{
    timer1->stop();
    timer2->stop();
    ui->LED1_pic->setPixmap(clearPm);
    ui->LED2_pic->setPixmap(clearPm);
    ui->LED3_pic->setPixmap(clearPm);
    ui->LED4_pic->setPixmap(clearPm);
    ui->LED1->setCheckState(Qt::Unchecked);
    ui->LED2->setCheckState(Qt::Unchecked);
    ui->LED3->setCheckState(Qt::Unchecked);
    ui->LED4->setCheckState(Qt::Unchecked);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->spinBox->setValue(value);
    ui->progressBar->setValue(value);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->progressBar->setValue(arg1);
    ui->horizontalSlider->setValue(arg1);
}
