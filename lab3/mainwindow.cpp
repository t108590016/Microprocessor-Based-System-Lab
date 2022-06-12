#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    if(count == (ui->timeEdit->text().toInt())*3+1){
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
    else{
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
    }


}
void MainWindow::LED_Switching2()
{
    count++;
    printf("%d, %d\n",count, ui->timeEdit->text().toInt());
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

}

void MainWindow::on_LEDShining_clicked()
{


    if(ui->LED1->isChecked()){
            //ui->LED1_pic->setText("Shining!");
        ui->LED1_pic->setPixmap(pm);
        ui->LED1_pic->setScaledContents(true);
    }
    else{
        ui->LED1_pic->setPixmap(clearPm);
    }
    if(ui->LED2->isChecked() == true){
            //ui->LED2_pic->setText("Shining!");
            ui->LED2_pic->setPixmap(pm);
            ui->LED2_pic->setScaledContents(true);
    }
    else{
        ui->LED2_pic->setPixmap(clearPm);
    }
    if(ui->LED3->isChecked() == true){
            //ui->LED3_pic->setText("Shining!");
            ui->LED3_pic->setPixmap(pm);
            ui->LED3_pic->setScaledContents(true);
    }
    else{
        ui->LED3_pic->setPixmap(clearPm);
    }
    if(ui->LED4->isChecked() == true){
            //ui->LED4_pic->setText("Shining!");
            ui->LED4_pic->setPixmap(pm);
            ui->LED4_pic->setScaledContents(true);
    }
    else{
        ui->LED4_pic->setPixmap(clearPm);
    }
}

void MainWindow::on_LEDSwitching_clicked()
{
    connect(timer1, SIGNAL(timeout()), this, SLOT(LED_Switching1()));
    timer1->start(1000);
    connect(timer2, SIGNAL(timeout()), this, SLOT(LED_Switching2()));
    timer2->start(2000);
}
