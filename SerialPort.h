#ifndef SERIALPORT_H
#define SERIALPORT_H

#include     <stdio.h>      /*��׼�����������*/
#include     <stdlib.h>     /*��׼�����ⶨ��*/
#include     <unistd.h>     /*Unix��׼��������*/
#include     <sys/types.h>  /**/
#include     <sys/stat.h>   /**/
#include     <fcntl.h>      /*�ļ����ƶ���*/
#include     <termios.h>    /*PPSIX�ն˿��ƶ���*/
#include     <errno.h>      /*����Ŷ���*/

#define FALSE  -1
#define TRUE   0

#define uchar unsigned char

class SerialPort
{
private:
    int speed_arr[];
    int name_arr[];

public:
    // ���췽��
    SerialPort();

    // ���ô���ͨ������
    void set_speed(int fd, int speed);

    // ���ô�������λ��ֹͣλ��Ч��λ
    int set_Parity(int fd,int databits,int stopbits,int parity);

    // �򿪴���
    int OpenDev(char *Dev);
};

#endif // SERIALPORT_H
