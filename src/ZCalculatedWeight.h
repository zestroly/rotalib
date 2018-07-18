#ifndef ZCALCULATEDWEIGHT_H
#define ZCALCULATEDWEIGHT_H

#include <iostream>
#include <thread>
#include <mutex>

#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>
#include <string.h>
#include <stdint.h>

#include "ZSerialPort.h"

namespace A7 {

class ZCalculatedWeight
{
  public:
    enum TProtocol{
      PROTOCOL_TSC = 0, //键宇tsc秤协议
      PROTOCOL_ROTA1,   //容大协议1
      PROTOCOL_ROTA2,   //容大协议2
    };

    struct TWeightInfo{
        float OutWeight;      //净重
        float OutTare;        //皮重
        bool isCrossMaxValue; //向上越界
        bool isCrossMinValue; //向下越界
        bool isStabilize;     //稳定
        bool isOnZero;        //零点
        TProtocol protocol;   //协议
        bool isAvaliable;     //判断数据是否可用
        int  PacketRate;      //包接收速率
        struct timeval timestamp;  //时间戳
    };

    struct TWeightPacket{
        uint8_t* buffsrc;
        int      bufflen;
        TWeightInfo info;
    };

    typedef void FRawData(TWeightPacket& , void*);

    ZCalculatedWeight(FRawData callback=NULL, void* pdata=NULL);
    ~ZCalculatedWeight();
    void GetInfo(TWeightInfo &info);  //获取重量
    bool SetModuleProtocol(TProtocol protocol);   //协议设置
    void SetTareWeight();       //去皮
    void SetZeroWeight();       //归零

    int writeData(uint8_t* buff, int len);


    void decodeProtocol(uint8_t* buff, int len, TWeightInfo& info);
    void paramPacket(uint8_t* buff, int len);
    static void LoopCatchWeight(ZCalculatedWeight *pCalculateWeight);

  private:
    ZSerialPort* m_SerialPort;
    std::thread* m_Thread;
    std::mutex   m_Mutex;
    bool m_isExit;
    bool m_isAvaliable;

    FRawData* m_callback;
    void * m_callback_param;

    TWeightInfo m_WeightInfo;
    struct timeval m_timestamp;  //时间戳
    int m_PacketRate;
    int m_PacketRateCount;
};

}

#endif // ZCALCULATEDWEIGHT_H
