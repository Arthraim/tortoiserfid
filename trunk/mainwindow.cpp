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
    // 1、发送初始化钱包的请求
    uchar code[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    uchar money[4] = {0x00,0x00,0x00,0x01}; // 初始化为1元
    if(_RFIDfunction.initPurse(code, money) == true)
        printf("RFIDfunction::initPurse OK! (Sending initialize purse ask succeeded!)\n");
    else
        printf("RFIDfunction::initPurse failed! (Sending initialize purse ask failed!)\n");

    // 2、检查是否初始化成功
    if(_RFIDfunction.isInitPurse() == true)
        printf("RFIDfunction::isInitPurse OK! (Initialize Purse succeeded!)\n");
    else
        printf("RFIDfunction::isInitPurse failed! (Initialize Purse failed!)\n");
    printf("\n");
}

void MainWindow::on_btn_GetMoney_clicked()
{
    // 1、发送getMoney的请求
    uchar code[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    if(_RFIDfunction.getMoney(code) == true)
        printf("RFIDfunction::getMoney OK! (Sending get money ask succeeded!)\n");
    else
        printf("RFIDfunction::getMoney failed! (Sending get money ask failed!)\n");

    // 2、检查是否得到money
    int money = _RFIDfunction.isGetMoney();
    if(money == -1) // -1为RFIDfunction::isGetMoney错误时返回的代码
    {
        ui->lineEdit_GetMoney->setText("Check Account fail!");
        printf("RFIDfunction::isGetMoney failed!\n");
    }
    else
    {
        ui->lineEdit_GetMoney->setText(QString::number(money));
        printf("RFIDfunction::isGetMoney OK!\n");
        printf("The money is [%d].\n", money);
    }
    printf("\n");
}

void MainWindow::on_btn_AddMoney_clicked()
{
    // 1、从lineEdit_AddMoney中读出数字
    bool ok;
    int intMoney = ui->lineEdit_AddMoney->text().toInt(&ok, 10); // 转换为int
    if(ok == true) // 如果转换成功
    {
        printf("Get int from lineEdit_AddMoney OK!\n");
        printf("The money is [%d].\n", intMoney);
    }
    else
    {
        printf("Get int from lineEdit_AddMoney failed!\n");
        ui->lineEdit_AddMoney->setText("Invaild Content!");
        return; // 失败就直接返回
    }

    // 2、将读出的int转为hex
    uchar money[4] = {0x00,0x00,0x00,0x01};
    // 转换的代码之后要记得添加阿阿阿阿阿阿阿！！！！！！！！！！！！！！！！！！！！！

    // 3、调用类中充值的方法
    uchar code[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    if(_RFIDfunction.addMoney(code, money) == true)
        printf("RFIDfunction::addMoney OK! (Sending Add money ask succeeded!)\n");
    else
        printf("RFIDfunction::addMoney failed! (Sending Add money ask failed!)\n");

    // 4、检查充值后的反馈
    if(_RFIDfunction.isAddMoney() == true)
        printf("RFIDfunction::isAddMoney OK! (Add money succeeded!)\n");
    else
        printf("RFIDfunction::addMoney failed! (Add money failed!)\n");

    printf("\n");
}

void MainWindow::on_btn_CutMoney_clicked()
{
    // 1、从lineEdit_CutMoney中读出数字
    bool ok;
    int intMoney = ui->lineEdit_CutMoney->text().toInt(&ok, 10); // 转换为int
    if(ok == true) // 如果转换成功
    {
        printf("Get int from lineEdit_CutMoney OK!\n");
        printf("The money is [%d].\n", intMoney);
    }
    else
    {
        printf("Get int from lineEdit_CutMoney failed!\n");
        ui->lineEdit_CutMoney->setText("Invaild Content!");
        return; // 失败就直接返回
    }

    // 2、将读出的int转为hex
    uchar money[4] = {0x00,0x00,0x00,0x01};
    // 转换的代码之后要记得添加阿阿阿阿阿阿阿！！！！！！！！！！！！！！！！！！！！！

    // 3、调用类中扣款的方法
    uchar code[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    if(_RFIDfunction.cutMoney(code, money) == true)
        printf("RFIDfunction::lineEdit_AddMoney OK! (Sending cut money ask succeeded!)\n");
    else
        printf("RFIDfunction::lineEdit_AddMoney failed! (Sending cut money ask failed!)\n");

    // 4、检查扣款后的反馈
    if(_RFIDfunction.isCutMoney() == true)
        printf("RFIDfunction::isCutMoney OK! (Cut money succeeded!)\n");
    else
        printf("RFIDfunction::isCutMoney failed! (Cut money failed!)\n");

    printf("\n");
}
