
#include "ZSerialPort.h"
#include <stdio.h>
#include <unistd.h>


int main(int argc, char** argv)
{
    A7::ZSerialPort SerialPort("/dev/ttymxc1");

    uint8_t wbuff[4]={0x02, 0x43, 0x03, 0x0D};

    SerialPort.writeData(wbuff, sizeof(wbuff));

    uint8_t buff[1024];
    while(1)
    {
        int len = SerialPort.readData(buff, sizeof(buff));
        if(len >0)
        {

            printf("%d [ ", len);
            for(int i = 0; i < len; i++)
            {
                printf("%02x ", buff[i]);
            }
            printf("]\n");
        }
    }



    sleep(1000);


    return 0;
}
