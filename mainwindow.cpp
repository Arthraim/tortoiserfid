#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
    connect(ui->btn_Exit, SIGNAL(clicked()), qApp,  SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_Initialize_clicked()
{
    uchar code[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    uchar money[4] = {0x00,0x00,0x00,0x01};
    _RFIDfunction.initPurse(code, money);
    if(_RFIDfunction.isInitPurse() == true)
        printf("initPurse OK!\n");
    else
        printf("initPurse failed!\n");
}

void MainWindow::on_btn_GetMoney_clicked()
{
    uchar code[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    int money = _RFIDfunction.getMoney(code);
    if(money = -1)
        ui->lineEdit_GetMoney->setText("Check Account fail!");
    else
        ui->lineEdit_GetMoney->setText("Fuck you");
}

void MainWindow::on_btn_AddMoney_clicked()
{

}

void MainWindow::on_btn_CutMoney_clicked()
{

}
