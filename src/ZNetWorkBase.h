#ifndef ZNETWORKBASE_H
#define ZNETWORKBASE_H

#include <iostream>
#include <list>

namespace A7 {


class ZNetWorkBase
{
  public:

    enum Method{
      DHCP,
      STATIC,
    };
    struct TNetWorkInfo{
        Method mothod;
        std::string ipaddress;
        std::string subnetmask;
        std::string gateway;
        std::string dns;
    };

    ZNetWorkBase(std::string DevName);
    ~ZNetWorkBase();

    void setNetWork(TNetWorkInfo network);
    void getNetWork(TNetWorkInfo& network);

    void eraseStr(std::string& str,std::string substr);
  private:
    std::string m_DevName;
    std::list<std::string> m_dom;
    std::list<std::string> m_devdom;
    TNetWorkInfo  m_networkinfo;

};

}

#endif // ZNETWORKBASE_H
