#ifndef RFIDFUNCTION_H
#define RFIDFUNCTION_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
//#include "SerialPort.h"
#include "posix_qextserialport.h"

#define uchar unsigned char
using namespace std;

class RFIDfunction
{
public:

    // 构造方法
    RFIDfunction();

    // 检查是否初始化成功
    bool isInitPurse();

    // 检查是否获得余额成功（成功，buff为金额值）
    int isGetMoney();

    // 检查是否充钱成功
    bool isAddMoney();

    // 检查是否扣钱成功
    bool isCutMoney();

    // 初始化钱包
    bool initPurse(uchar *code, uchar *money);

    // 读取money
    bool getMoney(uchar *code);

    // 充钱
    bool addMoney(uchar *code, uchar *money);

    // 扣钱
    bool cutMoney(uchar *code, uchar *money);

    // 发送前加上AA
    // 此方法需要去掉第一组AABB的处理！！！！
    void SendCheck_AA(unsigned char *SendBuf);

    // 删除AA后面的00
    void RecieveCheck_AA(unsigned char *RecieveBuf);

    // 转hex为字符串
    std::string  hex2char( int len, char*income );

private:

    // 串口通信类
    //SerialPort _SerialPort;
    Posix_QextSerialPort _SerialPort;

    // 串口发送
    bool Send(uchar*msg);

    // 串口接受
    bool Recieve(uchar*msg);

};


#endif  //RFIDFUNCTION_H
