#include "ZSystemIO.h"
#include "ZLog.h"
#include <signal.h>

namespace A7 {

ZSystemIO::ZSystemIO()
{


}


void ZSystemIO::SplitString(const std::string& src, std::list<std::string>& l, const std::string& c)
{
    std::string::size_type pos1, pos2;
    pos2 = src.find(c);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        l.push_back(src.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = src.find(c, pos1);
    }
    if(pos1 != src.length())
        l.push_back(src.substr(pos1));
}

void ZSystemIO::killProgressByPid(pid_t pid)
{
  kill(pid, 9);
  Zlog("kill progress pid=%d", pid);
}

void ZSystemIO::getProgressPid(std::string progress, std::list<std::string>& pidlist)
{
  std::string cmd = "pidof " + progress;
  std::string result;
  getCommandLines(cmd, result);

  if(result == "")
    return;

  for(int i =0 ; i < result.size(); i++)
  {
    if(result[i] > '9' || result[i] < '0')
      result[i]=',';
  }

  SplitString(result, pidlist, ",");

#ifdef DEBUG
  for(auto l: pidlist)
  {
    std::cout<<"["<<l<<"]"<<std::endl;
  }
#endif

  Zlog("获取 %s pid [%s]",progress.c_str() , result.c_str());

}

void ZSystemIO::getCommandLines(std::string command, std::string& result)
{
    result = "";
    FILE* file = popen(command.c_str(), "r");
    if(!file)
    {
        Zlog("打开管道是失败!");
        return;
    }

    int i = 0;
    char* tmp = new char[256];
    for(i = 0; fgets(tmp, 200, file) > 0;i++)
    {
        result += tmp;
    }

    delete[] tmp;
    pclose(file);
}



}

