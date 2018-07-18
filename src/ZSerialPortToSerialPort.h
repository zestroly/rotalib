#ifndef ZSERIALPORTTOSERIALPORT_H
#define ZSERIALPORTTOSERIALPORT_H

#include "ZSerialPort.h"
#include <thread>

namespace A7 {


class ZSerialPortToSerialPort
{
  public:
    ZSerialPortToSerialPort(std::string dest, std::string src);
    ~ZSerialPortToSerialPort();
    static void selectSrc(ZSerialPortToSerialPort*);
    static void selectDest(ZSerialPortToSerialPort*);

  private:
    ZSerialPort *m_DestPort;
    ZSerialPort *m_SrcPort;
    bool m_isAvaliable;
    bool m_isExit;
    std::thread* m_ThreadSrc;
    std::thread* m_ThreadDest;

};

}

#endif // ZSERIALPORTTOSERIALPORT_H
