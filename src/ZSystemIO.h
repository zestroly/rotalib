#ifndef ZSYSTEMIO_H
#define ZSYSTEMIO_H
#include <iostream>
#include <list>
#include <sys/types.h>

namespace A7 {


class ZSystemIO
{
  public:
    ZSystemIO();
    ~ZSystemIO();
    static void getProgressPid(std::string progress, std::list<std::string>& pidlist);
    static void getCommandLines(std::string command, std::string& result);
    static void killProgressByPid(pid_t pid);
    static void SplitString(const std::string& src, std::list<std::string>& l, const std::string& c);
};

}
#endif // ZSYSTEMIO_H
