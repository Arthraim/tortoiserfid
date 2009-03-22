#include "SerialPort.h"

SerialPort::SerialPort()
{
    int speed_arr[] = { B38400, B19200, B9600, B4800, B2400, B1200, B300,
                B38400, B19200, B9600, B4800, B2400, B1200, B300, };
    int name_arr[] = {38400,  19200,  9600,  4800,  2400,  1200,  300,
                38400,  19200,  9600, 4800, 2400, 1200,  300, };
}

/**
*@brief  设置串口通信速率
*@param  fd     类型 int  打开串口的文件句柄
*@param  speed  类型 int  串口速度
*@return void*/
void SerialPort::set_speed(int fd, int speed)
{
    int   i;
    int   status;
    struct termios   Opt;
    tcgetattr(fd, &Opt);
    for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)
    {
        if  (speed == name_arr[i])
        {
            tcflush(fd, TCIOFLUSH);
            cfsetispeed(&Opt, speed_arr[i]);
            cfsetospeed(&Opt, speed_arr[i]);
            status = tcsetattr(fd, TCSANOW, &Opt);
            if  (status != 0)
                perror("tcsetattr fd1");
            return;
        }
        tcflush(fd,TCIOFLUSH);
    }
}

/**
*@brief   设置串口数据位，停止位和效验位
*@param  fd      类型  int  打开的串口文件句柄*
*@param  databits 类型  int  数据位   取值为 7 或者8*
*@param  stopbits 类型  int  停止位   取值为 1 或者2*
*@param  parity   类型  int  效验类型 取值为 N,E,O,,S
*/
int SerialPort::set_Parity(int fd,int databits,int stopbits,int parity)
{
    struct termios options;
    if  ( tcgetattr( fd,&options)  !=  0)
    {
        perror("SetupSerial 1");
        return(FALSE);
    }
    options.c_cflag &= ~CSIZE;
    switch (databits) // 设置数据位数
    {
    case 7: options.c_cflag |= CS7; break;
    case 8: options.c_cflag |= CS8; break;
    default:fprintf(stderr,"Unsupported data size\n");
            return (FALSE);
    }
    switch (parity)
    {
    case 'n':
    case 'N':
        options.c_cflag &= ~PARENB;   // Clear parity enable
        options.c_iflag &= ~INPCK;     // Enable parity checking
        break;
    case 'o':
    case 'O':
        options.c_cflag |= (PARODD | PARENB);  // 设置为奇效验
        options.c_iflag |= INPCK;             // Disnable parity checking
        break;
    case 'e':
    case 'E':
        options.c_cflag |= PARENB;     // Enable parity
        options.c_cflag &= ~PARODD;   // 转换为偶效验
        options.c_iflag |= INPCK;       // Disnable parity checking
        break;
    case 'S':
    case 's':  //as no parity
        options.c_cflag &= ~PARENB;
        options.c_cflag &= ~CSTOPB;
    break;
    default:
        fprintf(stderr,"Unsupported parity\n");
        return (FALSE);
    }
    // 设置停止位
    switch (stopbits)
    {
    case 1:
        options.c_cflag &= ~CSTOPB;
        break;
    case 2:
        options.c_cflag |= CSTOPB;
        break;
    default:
        fprintf(stderr,"Unsupported stop bits\n");
        return (FALSE);
    }
    // Set input parity option
    if (parity != 'n')
        options.c_iflag |= INPCK;
    options.c_cc[VTIME] = 150; // 15 seconds
    options.c_cc[VMIN] = 0;

    tcflush(fd,TCIFLUSH); // Update the options and do it NOW
    if (tcsetattr(fd,TCSANOW,&options) != 0)
    {
        perror("SetupSerial 3");
        return (FALSE);
    }
    return (TRUE);
 }

/**
*@breif 打开串口
*/
int SerialPort::OpenDev(char *Dev)
{
    int fd = open( Dev, O_RDWR );   // | O_NOCTTY | O_NDELAY
    if (-1 == fd)
    {   //设置数据位数
        perror("Can't Open Serial Port");
        return -1;
    }
    else
        return fd;
}

/**
*@bref 发送数据
*/
int SerialPort::PortSend(uchar *sbuf)
{
    int fd;
    int nwrite;
    /*
    char sbuf[5]; //待发送的内容
    sbuf[0] = 0xAA;
    sbuf[1] = 0xBB;
    sbuf[2] = 0x02;
    sbuf[3] = 0x19;
    sbuf[4] = 0x1b;
    */
    int length=sizeof(sbuf); //发送缓冲区数据宽度
    char *dev ="/dev/ttyS0";
    //char *dev ="/dev/s3c2410_serial0";/*arm的串口*/
    fd = OpenDev(dev);
    if (fd>0)
        set_speed(fd,19200);
    else
    {
        printf("Can't Open Serial Port!\n");
        return FALSE;
    }
    if (set_Parity(fd,8,1,'N')== FALSE)
    {
        printf("Set Parity Error\n");
        return FALSE;
    }

    nwrite=write(fd,sbuf,5);
    if(nwrite==-1)
    {
        perror("write");
    }
    printf("the number if char sent is %d\n",nwrite);

    //close(fd);
    return TRUE;
}

/**
*@bref 接受数据
*/
int SerialPort::PortReceive(uchar *rbuf)
{
    int fd;
    int nread;
    rbuf = new unsigned char[512];
    char *dev ="/dev/ttyS0";
    //char *dev ="/dev/s3c2410_serial0";/*arm的串口*/
    fd = OpenDev(dev);
    if (fd>0)
        set_speed(fd,19200);
    else
    {
        printf("Can't Open Serial Port!\n");
        return FALSE;
    }
    if (set_Parity(fd,8,1,'N')== FALSE)
    {
        printf("Set Parity Error\n");
        return FALSE;
    }
    while(1)
    {
        int nread=read(fd,rbuf,1);
        if(nread!=-1)
        {
            printf("%x\n",*rbuf);
        }
        else
        {
            printf("can not read data! ");
        }
    }
    //close(fd);
    return TRUE;
}


