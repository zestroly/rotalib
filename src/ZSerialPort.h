#ifndef ZSERIALPORT_H
#define ZSERIALPORT_H


#include <iostream>
#include <stdint.h>

namespace A7 {


class ZSerialPort
{
    public:
        enum BaudRateType
        {
            BAUD50,                //POSIX ONLY
            BAUD75,                //POSIX ONLY
            BAUD110,
            BAUD134,               //POSIX ONLY
            BAUD150,               //POSIX ONLY
            BAUD200,               //POSIX ONLY
            BAUD300,
            BAUD600,
            BAUD1200,
            BAUD1800,              //POSIX ONLY
            BAUD2400,
            BAUD4800,
            BAUD9600,
            BAUD14400,             //WINDOWS ONLY
            BAUD19200,
            BAUD38400,
            BAUD56000,             //WINDOWS ONLY
            BAUD57600,
            BAUD76800,             //POSIX ONLY
            BAUD115200,
            BAUD128000,            //WINDOWS ONLY
            BAUD256000             //WINDOWS ONLY
        };

        enum DataBitsType
        {
            DATA_5,
            DATA_6,
            DATA_7,
            DATA_8
        };

        enum ParityType
        {
            PAR_NONE,
            PAR_ODD,
            PAR_EVEN,
            PAR_MARK,               //WINDOWS ONLY
            PAR_SPACE
        };

        enum StopBitsType
        {
            STOP_1,
            STOP_1_5,               //WINDOWS ONLY
            STOP_2
        };

        enum FlowType
        {
            FLOW_OFF,
            FLOW_HARDWARE,
            FLOW_XONXOFF
        };

        struct TPortSettings
        {
            BaudRateType BaudRate;
            DataBitsType DataBits;
            ParityType   Parity;
            StopBitsType StopBits;
            FlowType     FlowControl;
            long         Timeout_Millisec;
        };

    public:
        ZSerialPort(std::string dev);
        ZSerialPort(TPortSettings& portsettings);

        ~ZSerialPort();
        bool openDev();
        bool closeDev();

        void flush();
        int readData(uint8_t* buff, int len);
        int writeData(uint8_t* buff, int len);

        int selectData(uint8_t* buff, int len, float timeout);

        void setPortName(const std::string & name);
        std::string PortName();

        void setBaudRate(BaudRateType);
        BaudRateType BaudRate();

        void setDataBits(DataBitsType);
        DataBitsType DataBits();

        void setParity(ParityType);
        ParityType Parity();

        void setStopBits(StopBitsType);
        StopBitsType StopBits();

        void setFlowControl(FlowType);
        FlowType FlowControl();

        void setTimeout(long);

        static std::string ToHexString(uint8_t* buff, int len);
        static void ToHexPrint(uint8_t* buff, int len);

    private:
        bool m_isAvaliable;
        int  m_fd;
        std::string m_DevName;
        TPortSettings portsettings;

};

}
#endif // ZSERIALPORT_H
