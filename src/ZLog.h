#ifndef ZLOG_H
#define ZLOG_H

#define Zlog(fmt, para...)    do \
    { \
        time_t t = time(NULL);  \
        struct tm *tmm = localtime(&t); \
        fprintf(stdout,"[%d-%02d-%02d %02d:%02d:%02d][%s][%s:%d] " fmt "\n",tmm->tm_year+1900,tmm->tm_mon+1,tmm->tm_mday,tmm->tm_hour,tmm->tm_min,tmm->tm_sec,__FUNCTION__,__FILE__,__LINE__,##para); \
        fflush(stdout); \
    } while(0)

#endif // ZLOG_H
