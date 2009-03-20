#ifndef RFIDFUNCTION_H
#define RFIDFUNCTION_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#define uchar unsigned char
using namespace std;

class RFIDfunction
{
public:

    // 检查是否初始化成功
    bool isInitPurse(uchar *buff);

    // 检查是否获得余额成功（成功，buff为金额值）
    bool isGetMoney(uchar *buff);

    // 检查是否充钱成功
    bool isAddMoney(uchar *buff);

    // 检查是否扣钱成功
    bool isCutMoney(uchar *buff);

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
    void  SendCheck_AA(unsigned char *SendBuf);

    // 删除AA后面的00
    void RecieveCheck_AA(unsigned char *RecieveBuf);

    // 转hex为字符串
    std::string  hex2char( int len, char*income );

private:

    // 串口发送
    void Send(uchar*msg);

    // 串口接受
    void Recieve(uchar*msg);

};


#endif  //RFIDFUNCTION_H
