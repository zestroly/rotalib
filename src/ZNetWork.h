#ifndef ZNETWORK_H
#define ZNETWORK_H

#include <iostream>
#include "ZNetWorkBase.h"

namespace A7 {


class ZNetWork
{
  public:
    ZNetWork(std::string DevName);
    ~ZNetWork();
    void setNetWork(ZNetWorkBase::TNetWorkInfo network);
    void getNetWork(ZNetWorkBase::TNetWorkInfo& network);
    void restartNetWork();

  private:
    std::string m_Dev;
};

}
#endif // ZNETWORK_H
