#include "RFIDfunction.h"

// 构造方法
RFIDfunction::RFIDfunction()
{
    //_SerialPort = new SerialPort();
}

// 检查是否初始化成功
bool RFIDfunction::isInitPurse()
{
    uchar *buff;
    if(Recieve(buff) == false)
        return false;
    if(buff[2] == 0x02 && buff[3] == 0xdc)
        return false;
    else if(buff[2] == 0x02 && buff[3] == 0x23)
        return true;
    else
        return false;
}

// 检查是否获得余额成功（成功，buff为金额值）
int RFIDfunction::isGetMoney()
{
    int _money; // 返回的钱数量
    uchar *buff;
    if(Recieve(buff) == false)
        return false;
    uchar money[4];
    if(buff[2] == 0x02 && buff[3] == 0xdb)
        return -1; // －1表示失败
    else if(buff[2] == 0x06 && buff[3] == 0x24)
    {
        money[0] = buff[4];
        money[1] = buff[5];
        money[2] = buff[6];
        money[3] = buff[7];
    }
    //把money转为int并且返回！！！！
    return _money;
}

// 检查是否充钱成功
bool RFIDfunction::isAddMoney()
{
    uchar *buff;
    if(Recieve(buff) == false)
        return false;
    if(buff[2] == 0x02 && buff[3] == 0xda)
        return false;
    else if(buff[2] == 0x02 && buff[3] == 0x24)
        return true;
    else
        return false;
}

// 检查是否扣钱成功
bool RFIDfunction::isCutMoney()
{
    uchar *buff;
    if(Recieve(buff) == false)
        return false;
    if(buff[2] == 0x02 && buff[3] == 0xd9)
        return false;
    else if(buff[2] == 0x02 && buff[3] == 0x26)
        return true;
    else
        return false;
}

// 初始化钱包
bool RFIDfunction::initPurse(uchar *code, uchar *money)
{
    uchar *msg = new uchar[17];
    msg[0] = 0xaa;
    msg[1] = 0xbb;
    msg[2] = 0x0e;
    msg[3] = 0x23;
    msg[4] = 0x00;
    msg[5] = 0x03; //块号
    msg[6] = code[0];
    msg[7] = code[1];
    msg[8] = code[2];
    msg[9] = code[3];
    msg[10] = code[4];
    msg[11] = code[5];
    msg[12] = money[0];
    msg[13] = money[1];
    msg[14] = money[2];
    msg[15] = money[3];
    msg[16] = 0x24;
    
    bool flag = false;
    flag = Send(msg);
    return flag;
}

// 读取money
bool RFIDfunction::getMoney(uchar *code)
{
    uchar *msg = new uchar[13];
    msg[0] = 0xaa;
    msg[1] = 0xbb;
    msg[2] = 0x0a;
    msg[3] = 0x24;
    msg[4] = 0x00;
    msg[5] = 0x03; //块号
    msg[6] = code[0];
    msg[7] = code[1];
    msg[8] = code[2];
    msg[9] = code[3];
    msg[10] = code[4];
    msg[11] = code[5];
    msg[12] = 0x27;
    
    bool flag = false;
    flag = Send(msg);
    return flag;
}

// 充钱
bool RFIDfunction::addMoney(uchar *code, uchar *money)
{
    uchar *msg = new uchar[17];
    msg[0] = 0xaa;
    msg[1] = 0xbb;
    msg[2] = 0x0e;
    msg[3] = 0x25;
    msg[4] = 0x00;
    msg[5] = 0x03; //块号
    msg[6] = code[0];
    msg[7] = code[1];
    msg[8] = code[2];
    msg[9] = code[3];
    msg[10] = code[4];
    msg[11] = code[5];
    msg[12] = money[0];
    msg[13] = money[1];
    msg[14] = money[2];
    msg[15] = money[3];
    msg[16] = 0x22;
    
    bool flag = false;
    flag = Send(msg);
    return flag;
}

// 扣钱
bool RFIDfunction::cutMoney(uchar *code, uchar *money)
{
    uchar *msg = new uchar[17];
    msg[0] = 0xaa;
    msg[1] = 0xbb;
    msg[2] = 0x0e;
    msg[3] = 0x26;
    msg[4] = 0x00;
    msg[5] = 0x03; //块号
    msg[6] = code[0];
    msg[7] = code[1];
    msg[8] = code[2];
    msg[9] = code[3];
    msg[10] = code[4];
    msg[11] = code[5];
    msg[12] = money[0];
    msg[13] = money[1];
    msg[14] = money[2];
    msg[15] = money[3];
    msg[16] = 0x21;
    
    bool flag = false;
    flag = Send(msg);
    return flag;
}

// 发送前加上AA
void RFIDfunction::SendCheck_AA(unsigned char *SendBuf)
 {
    unsigned char i;
    unsigned char  buffer[1000];
    //for(i=1;i<SendBuf[0];i++) // i=0则为包括AABB的AA
    int length = sizeof(SendBuf);
    for(i=1; i < length; i++)
    {
        if(SendBuf[i]==0xAA)
        {
            memcpy(buffer,&SendBuf[i+1],SendBuf[0]-i);
            SendBuf[i+1]=0x00;
            memcpy(&SendBuf[i+2],buffer,SendBuf[0]-i);
        }
    }
    printf("SendCheck_AA is  OK\n");
 }

// 删除AA后面的00
void RFIDfunction::RecieveCheck_AA(unsigned char *ReceiveBuf)
{
    unsigned char i;
    unsigned char  buffer[1000];
    //for(i=1;i<RecieveBuf[0];i++)
    int length = sizeof(ReceiveBuf);
    for(i=1; i < length; i++)
    {
        if(ReceiveBuf[i]==0x00 && ReceiveBuf[i-1]==0xAA)            //changed  for  test
        {
            memcpy(buffer,&ReceiveBuf[i+1],ReceiveBuf[0]-i);
            memcpy(&ReceiveBuf[i],buffer,ReceiveBuf[0]-i);
        }
    }
    printf("RecieveCheck_AA is  OK\n");
}

// 转hex为字符串
std::string RFIDfunction::hex2char( int len, char*income )
{
    static const char hexval[16] = { '0', '1', '2', '3',
                                     '4', '5', '6', '7',
                                     '8', '9', 'a', 'b',
                                     'c', 'd', 'e', 'f' };
    unsigned max_cols = 16;
    std::ostringstream buf;

    for (int i = 0; i < len;)
    {
        for (unsigned col = 0; col < max_cols; ++col)
        {
            if (i < len)
            {
                buf << hexval[ ( (income[i] >> 4) & 0xF ) ]
                    << hexval[ ( income[i] & 0x0F ) ];
                ++i;
            }
        }
    }
    return buf.str();
}

// 串口发送
bool RFIDfunction::Send(uchar*msg)
{
    SendCheck_AA(msg);
    //串口通信的发送代码！！！
    //发送msg
    /*
    if (_SerialPort.PortSend(msg) == 0)
    {
        printf("SerialProt::ProtSend OK!");
        return true;
    }
    else
    {
        printf("SerialProt::ProtSend failed!");
        return false;
    }*/
    if (_SerialPort.write((const char*)msg))
    {
        printf("SerialProt::ProtSend OK!");
        return true;
    }
    else
    {
        printf("SerialProt::ProtSend failed!");
        return false;
    }
    return false;
}


// 串口接受
bool RFIDfunction::Recieve(uchar*msg)
{        
    //串口通信的接受代码！！！
    //得到的记作msg
    /*
    if (_SerialPort.PortReceive(msg) == 0)
    {
        printf("SerialProt::ProtSend OK!");
        return true;
    }
    else
    {
        printf("SerialProt::ProtSend failed!");
        return false;
    }
    */
    if (_SerialPort.read((char*)msg,17))
    {
        printf("SerialProt::ProtSend OK!");
        return true;
    }
    else
    {
        printf("SerialProt::ProtSend failed!");
        return false;
    }
    RecieveCheck_AA(msg);
    return false;
}
