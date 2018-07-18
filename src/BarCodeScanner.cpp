#include "BarCodeScanner.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

#define SCANNER_DEV "/dev/input/event2"

static int8_t MapKey[29] =
{
00,// KEY_RESERVED	    0
00,// KEY_ESC		    1
49,// KEY_1			2
50,// KEY_2			3
51,// KEY_3			4
52,// KEY_4			5
53,// KEY_5			6
54,// KEY_6			7
55,// KEY_7			8
56,// KEY_8			9
57,// KEY_9			10
48,// KEY_0			11
00,// KEY_MINUS		12
00,// KEY_EQUAL		13
00,// KEY_BACKSPACE	14
00,// KEY_TAB		    15
00,// KEY_Q			16
00,// KEY_W			17
00,// KEY_E			18
00,// KEY_R			19
00,// KEY_T			20
00,// KEY_Y			21
00,// KEY_U			22
00,// KEY_I			23
00,// KEY_O			24
00,// KEY_P			25
00,// KEY_LEFTBRACE	26
00,// KEY_RIGHTBRACE	27
13// KEY_ENTER		28
};





BarCodeScanner::BarCodeScanner():m_fd(0),m_available(false)
{
    openDev();
}


BarCodeScanner::~BarCodeScanner()
{
    closeDev();
}

void BarCodeScanner::Scanne()
{
    struct input_event buff;
    while(1)
    {
        read(m_fd, &buff, sizeof(struct input_event));
        if(buff.value == 1)
        {
            printf("%c", MapKey[buff.code]);
            fflush(stdout);
        }


    }


}


bool BarCodeScanner::openDev()
{
    m_fd = open(SCANNER_DEV, O_RDONLY);
    if( m_fd < 0)
    {
        m_available = false;
        return false;
    }
    m_available = true;
    return true;
}

bool BarCodeScanner::closeDev()
{
    if (m_fd > 0)
    {
        close(m_fd);
    }
    m_available = false;
    return true;
}
