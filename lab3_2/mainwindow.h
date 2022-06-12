#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPixmap>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    int count=0;
    QTimer *timer1 = new QTimer(this);
    QTimer *timer2 = new QTimer(this);
    QPixmap pm = QPixmap("light.png");
    QPixmap clearPm;
    ~MainWindow();

private slots:
    void on_LEDShining_clicked();
    void on_LEDSwitchingOn_clicked();
    void LED_Switching1();
    void LED_Switching2();
    void on_LEDSwitchingOff_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
