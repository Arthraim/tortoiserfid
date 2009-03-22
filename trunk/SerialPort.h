#ifndef SERIALPORT_H
#define SERIALPORT_H

#include     <stdio.h>      /*标准输入输出定义*/
#include     <stdlib.h>     /*标准函数库定义*/
#include     <unistd.h>     /*Unix标准函数定义*/
#include     <sys/types.h>  /**/
#include     <sys/stat.h>   /**/
#include     <fcntl.h>      /*文件控制定义*/
#include     <termios.h>    /*PPSIX终端控制定义*/
#include     <errno.h>      /*错误号定义*/

#define FALSE  -1
#define TRUE   0

#define uchar unsigned char

class SerialPort
{
private:
    int speed_arr[];
    int name_arr[];

public:
    // 构造方法
    SerialPort();

    // 设置串口通信速率
    void set_speed(int fd, int speed);

    // 设置串口数据位，停止位和效验位
    int set_Parity(int fd,int databits,int stopbits,int parity);

    // 打开串口
    int OpenDev(char *Dev);

    // 发送数据
    int PortSend(uchar *sbuf);

    // 接受数据
    int PortReceive(uchar *rbuf);
};

#endif // SERIALPORT_H
