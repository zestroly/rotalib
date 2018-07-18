#include "ZNetWork.h"

namespace A7 {

ZNetWork::ZNetWork(std::string DevName):
  m_Dev(DevName)
{

}

void ZNetWork::setNetWork(ZNetWorkBase::TNetWorkInfo network)
{
  system("wr cp /etc/network/interfaces /opt/interfaces ");
  ZNetWorkBase NW(m_Dev);
  NW.setNetWork(network);
  system("wr cp /opt/interfaces /etc/network/interfaces ");
}

void ZNetWork::getNetWork(ZNetWorkBase::TNetWorkInfo& network)
{
  system("wr cp /etc/network/interfaces /opt/interfaces ");
  ZNetWorkBase NW(m_Dev);
  NW.getNetWork(network);

}

void ZNetWork::restartNetWork()
{
  system("/etc/init.d/S40network restart");
}

ZNetWork::~ZNetWork()
{

}


}
