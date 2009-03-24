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

private slots:
    void on_btn_GetType_clicked();
    void on_btn_CutMoney_clicked();
    void on_btn_AddMoney_clicked();
    void on_btn_GetMoney_clicked();
    void on_btn_Initialize_clicked();
};

#endif // MAINWINDOW_H
