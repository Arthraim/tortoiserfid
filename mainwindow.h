#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QThread>
#include "RFIDfunction.h"

namespace Ui
{
    class MainWindowClass;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindowClass *ui;
    RFIDfunction _RFIDfunction;
    uint _inputNum;

    void ShowNumber();

private slots:
    void on_btn_C_clicked();
    void on_btn_CE_clicked();
    void on_btn_0_clicked();
    void on_btn_9_clicked();
    void on_btn_8_clicked();
    void on_btn_7_clicked();
    void on_btn_6_clicked();
    void on_btn_5_clicked();
    void on_btn_4_clicked();
    void on_btn_3_clicked();
    void on_btn_2_clicked();
    void on_btn_1_clicked();
    void on_btn_GetType_clicked();
    void on_btn_CutMoney_clicked();
    void on_btn_AddMoney_clicked();
    void on_btn_GetMoney_clicked();
    void on_btn_Initialize_clicked();
};

#endif // MAINWINDOW_H
