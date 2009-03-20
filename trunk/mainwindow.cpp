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
}

void MainWindow::on_btn_GetMoney_clicked()
{

}

void MainWindow::on_btn_AddMoney_clicked()
{

}

void MainWindow::on_btn_CutMoney_clicked()
{

}
