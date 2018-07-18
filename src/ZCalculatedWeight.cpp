#include "ZCalculatedWeight.h"

namespace A7 {

ZCalculatedWeight::ZCalculatedWeight(FRawData callback, void* pdata):
  m_isExit(false),m_Thread(NULL),m_SerialPort(NULL),m_isAvaliable(true),
  m_callback(callback),m_callback_param(pdata),m_PacketRate(0),
  m_PacketRateCount(0)
{


  m_SerialPort = new ZSerialPort("/dev/ttymxc1");
  if( m_SerialPort == NULL)
  {
    m_isAvaliable = false;
    return;
  }

  m_Thread = new std::thread(LoopCatchWeight, this);
  if(m_Thread == NULL)
  {
    m_isAvaliable = false;
    return;
  }
}

int ZCalculatedWeight::writeData(uint8_t* buff, int len)
{
  return m_SerialPort->writeData(buff, len);
}


ZCalculatedWeight::~ZCalculatedWeight()
{
  if(m_Thread != NULL)
  {
    m_isExit = true;
    m_Thread->join();
    delete m_Thread;
    m_Thread = NULL;
  }

  if(m_SerialPort != NULL)
  {
    delete m_SerialPort;
    m_SerialPort = NULL;
  }

}

void ZCalculatedWeight::GetInfo(TWeightInfo& info)          //获取重量
{
  m_Mutex.lock();
  info = m_WeightInfo;
  m_Mutex.unlock();
}

bool ZCalculatedWeight::SetModuleProtocol(TProtocol protocol)   //协议设置
{
  uint8_t buff[4] = {0x02, 0x00, 0x03, 0x0D};
  switch (protocol)
  {
      case 0:
          buff[1] = 0x41;
          break;
      case 1:
          buff[1] = 0x42;
          break;
      case 2:
          buff[1] = 0x43;
          break;
      default:
          printf("no support this protocol\n");
          return false;
  }
  m_SerialPort->writeData(buff, 4);
  return true;
}

void ZCalculatedWeight::SetTareWeight()       //去皮
{
  uint8_t buff[4] = {0x02, 0x54, 0x03, 0x0D};
  m_SerialPort->writeData(buff, 4);

}

void ZCalculatedWeight::SetZeroWeight()       //归零
{
  uint8_t buff[4] = {0x02, 0x5A, 0x03, 0x0D};
  m_SerialPort->writeData(buff, 4);
}


void ZCalculatedWeight::decodeProtocol(uint8_t* buff, int len, TWeightInfo& info)
{
  uint8_t checksum = 0;

  if(buff[0]==0x02 && buff[9] == 0x03 && buff[11]== 0x0D)
  {
      //计算校验值
      for(int i = 1; i < 9 ;i++)
          checksum += buff[i];

      if(buff[10]==checksum)
      {//校验通过
          std::string weight;
          weight+=buff[1];
          weight+=buff[2];
          weight+=buff[3];
          weight+=buff[4];
          weight+=buff[5];
          weight+=buff[6];

          //tare
          std::string Tare;
          if(buff[12] == 0x54 && buff[18]== 0x0D)
          {
              Tare += buff[13];
              Tare += buff[14];
              Tare += buff[15];
              Tare += buff[16];
              Tare += buff[17];
          }

          float weight_f =  std::stof(weight);
          float tare_f    = std::stof(Tare);

          uint8_t Decimal = (buff[8]&0x07);
          for(int i = 0 ; i < Decimal; i++)
          {
            tare_f  /=10;
            weight_f /= 10;
          }

          info.OutWeight = weight_f;
          info.OutTare = tare_f;
          info.isCrossMaxValue = (buff[8]>>7)&0x01 ? true:false;
          info.isCrossMinValue = (buff[8]>>6)&0x01 ? true:false;
          info.isStabilize = (buff[8]>>4)&0x01 ? true:false;
          info.isOnZero = (buff[8]>>3)&0x01 ? true:false;
          info.isAvaliable = true;
          info.protocol = PROTOCOL_ROTA2;
      }
  }
}

void ZCalculatedWeight::paramPacket(uint8_t* buff, int len)
{
  TWeightPacket packet;
  packet.info.isAvaliable = false;
  packet.buffsrc = buff;
  packet.bufflen = len;

  gettimeofday(&packet.info.timestamp, NULL);
  if(packet.info.timestamp.tv_sec == m_timestamp.tv_sec) {
      m_PacketRateCount++;
  }else {
      m_PacketRate = m_PacketRateCount;
      m_PacketRateCount=0;
      m_timestamp = packet.info.timestamp;
  }

  decodeProtocol(buff, len, packet.info);

  packet.info.PacketRate = m_PacketRate;
  m_Mutex.lock();
  m_WeightInfo = packet.info;
  m_Mutex.unlock();

  if(m_callback != NULL)
      m_callback(packet, m_callback_param);

}

void ZCalculatedWeight::LoopCatchWeight(ZCalculatedWeight *pCalculateWeight)
{
    uint8_t buff[80];
    int  count;
    while(pCalculateWeight->m_isExit == false)
    {
        memset(buff, 0, sizeof(80));
        count = pCalculateWeight->m_SerialPort->selectData(buff, sizeof(buff),1);
        if(count > 0)
        {
            pCalculateWeight->paramPacket(buff, count);
        }
    }
}



}
