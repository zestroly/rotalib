#include "ZSerialPort.h"
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>

#include <termios.h>



namespace A7 {

ZSerialPort::ZSerialPort(std::string dev):
  m_isAvaliable(false),m_DevName(dev),m_fd(0)
{

 m_isAvaliable =  openDev();


}

bool ZSerialPort::openDev()
{
  //test m_DevName is exist?

  //open
  m_fd = open(m_DevName.c_str(), O_RDWR |O_NOCTTY|O_NONBLOCK );
  if(m_fd < 0)
  {
    return false;
  }

  if(fcntl(m_fd, F_SETFL, 0) < 0)
  {
    printf("fcntl failed!\n");
  }

  struct termios options;
  tcgetattr(m_fd, &options);

  cfsetispeed(&options, B19200);
  cfsetospeed(&options, B19200);

  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~CSIZE;
  options.c_cflag |= CS8;
  options.c_cflag |= CLOCAL | CREAD;

  options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
  options.c_oflag &= ~OPOST;
  options.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON | IGNCR);

  options.c_cc[VTIME] = 0;
  options.c_cc[VMIN]= 0;

  tcsetattr(m_fd, TCSANOW, &options);

  tcflush(m_fd,TCIFLUSH);

  //config

  return true;
}

ZSerialPort::~ZSerialPort()
{
  closeDev();
}

bool ZSerialPort::closeDev()
{
  close(m_fd);

}

int ZSerialPort::readData(uint8_t* buff, int len)
{
  return read(m_fd, buff, len);

}

int ZSerialPort::writeData(uint8_t* buff, int len)
{
  return write(m_fd, buff, len);
}



int ZSerialPort::selectData(uint8_t* buff, int len, float timeout)
{
    int ret, count;
    fd_set rfs;
    FD_ZERO(&rfs);
    FD_SET(m_fd,&rfs);

    int sec = (int)timeout;
    int usec = (int)((timeout - sec)*1000*1000);

    struct timeval wtimeout;
    wtimeout.tv_sec  = sec;
    wtimeout.tv_usec = usec;

   // printf("set timeout:%d.%d\n", wtimeout.tv_sec, wtimeout.tv_usec);

    ret = select(m_fd+1, &rfs, NULL, NULL, &wtimeout);
    if(ret > 0 && FD_ISSET(m_fd, &rfs))
    {
      count = read(m_fd, buff, len);
      return count;
    }else{
    //  printf("select %s timeout,no recvice data\n",m_DevName.c_str());
      return -1;
    }
}

std::string ZSerialPort::ToHexString(uint8_t* buff, int len)
{
  std::string restring = "";
  for(int i = 0; i < len; i++)
  {
      char bufftem[5] = {0};
      sprintf(bufftem, "%02x ", buff[i]);
      restring += bufftem;
  }
  return restring;
}

void ZSerialPort::ToHexPrint(uint8_t* buff, int len)
{
    printf("(%d){ ", len);
    for(int i = 0; i < len; i++)
    {
        printf("%02x ", buff[i]);
    }
    printf("} ");
}




} //namespace
