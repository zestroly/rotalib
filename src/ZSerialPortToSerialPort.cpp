#include "ZSerialPortToSerialPort.h"

#include <iostream>

namespace A7 {

ZSerialPortToSerialPort::ZSerialPortToSerialPort
    (std::string dest, std::string src):
  m_DestPort(NULL), m_SrcPort(NULL),m_isAvaliable(true),m_isExit(false)
{
  m_SrcPort = new ZSerialPort(src.c_str());
  m_DestPort = new ZSerialPort(dest.c_str());

  m_ThreadSrc = new std::thread(selectSrc, this);
  m_ThreadDest = new std::thread(selectDest, this);
}

ZSerialPortToSerialPort::~ZSerialPortToSerialPort()
{
  m_isExit = true;
  m_ThreadDest->join();
  m_ThreadSrc->join();
  delete m_SrcPort;
  delete m_DestPort;
}


void ZSerialPortToSerialPort::selectSrc(ZSerialPortToSerialPort* pClass)
{
  uint8_t buff[100];
  int len;
  while(!pClass->m_isExit)
  {
    len = pClass->m_SrcPort->selectData(buff, sizeof(buff), 0.5);
    if(len > 0)
    {
      pClass->m_DestPort->writeData(buff, len);
    }
  }
}

void ZSerialPortToSerialPort::selectDest(ZSerialPortToSerialPort* pClass)
{
  uint8_t buff[100];
  int len;
   while(!pClass->m_isExit)
  {
    len = pClass->m_DestPort->selectData(buff, sizeof(buff), 0.5);
    if(len > 0)
    {
      pClass->m_SrcPort->writeData(buff, len);
    }
  }
}


}
