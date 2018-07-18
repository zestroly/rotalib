#include "ZNetWorkBase.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

namespace A7 {

void ZNetWorkBase::eraseStr(std::string& str,std::string substr)
{
  size_t pos = 0;
  if( (pos=str.find(substr,0)) != std::string::npos)
  {
    str.erase(0, pos+substr.size());
  }
  while(str.find_first_not_of(" ") != 0)
    str.erase(0,str.find_first_not_of(" "));
  str.erase(str.find_last_not_of(" ") + 1);

}



ZNetWorkBase::ZNetWorkBase(std::string DevName)
  :m_DevName(DevName)
{
  std::ifstream fin("/opt/interfaces");
  std::string s;
  bool start = false;
  bool isStatic = false;
  while(std::getline(fin, s))
  {
    if(!s.empty()) //去掉前空格
    {
      s.erase(0,s.find_first_not_of(" "));
      s.erase(0,s.find_first_not_of("\t"));
    }


    if(start == false)
    {
        if((s.find_first_of("auto",0) == 0) && (s.find(m_DevName, 0) != std::string::npos))
          start = true;
        m_dom.push_back(s);

        continue;

    }else{
      if(s.find("auto") != std::string::npos)
      {
        m_dom.push_back("\n");
        start =false;
        m_dom.push_back(s);
        continue;
      }

      if(s.find_first_of("iface", 0) == 0 && s.find(m_DevName, 0) != std::string::npos)
      {//iface ethx inet xxx
        s.erase(0,s.find("inet ",0)+5);
        s.erase(0,s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ") + 1);
        if(s == "static")
        {
          m_networkinfo.mothod = STATIC;
          isStatic = true;
        }
        else
          m_networkinfo.mothod = DHCP;
        continue;
      }

      if(isStatic == true)
      {
        size_t pos = 0;
        if( (pos = s.find("address", 0)) != std::string::npos) {
          eraseStr(s, "address");
          m_networkinfo.ipaddress = s;
          continue;
        }else if( (pos = s.find("netmask", 0)) != std::string::npos) {
          eraseStr(s, "netmask");
          m_networkinfo.subnetmask = s;
        }else if( (pos = s.find("gateway", 0)) != std::string::npos) {
          eraseStr(s, "gateway");
          m_networkinfo.gateway = s;
        }else if( (pos = s.find("dns-nameservers", 0)) != std::string::npos) {
          eraseStr(s, "dns-nameservers");
          m_networkinfo.dns = s;
        }
      }


    }
  }
}

void ZNetWorkBase::setNetWork(TNetWorkInfo network)
{
  m_devdom.clear();
  m_devdom.push_back("auto lo");
  m_devdom.push_back("iface lo inet loopback");
  m_devdom.push_back(" ");
  std::string autoethx = "auto " + m_DevName;
  m_devdom.push_back(autoethx);
  if(network.mothod == DHCP)
  {
    std::string iface = "iface " + m_DevName + " inet dhcp";
    m_devdom.push_back(iface);
  }else{
      std::string iface = "iface " + m_DevName + " inet static";
      m_devdom.push_back(iface);

      if(network.ipaddress !="")
          m_devdom.push_back(std::string("address ")+network.ipaddress);
    //  else
     //     m_devdom.push_back(std::string("address ")+m_networkinfo.ipaddress);

      if(network.subnetmask !="")
          m_devdom.push_back(std::string("netmask ")+network.subnetmask);
     // else
      //    m_devdom.push_back(std::string("netmask ")+m_networkinfo.subnetmask);

      if(network.gateway !="")
          m_devdom.push_back(std::string("gateway ")+network.gateway);
     // else
     //     m_devdom.push_back(std::string("gateway ")+m_networkinfo.gateway);

      if(network.dns !="")
          m_devdom.push_back(std::string("dns-nameservers ")+network.dns);
     // else
      //    m_devdom.push_back(std::string("dns-nameservers ")+m_networkinfo.dns);

  }

  std::list<std::string>::iterator iter;
  for(iter = m_dom.begin(); iter != m_dom.end();iter++)
  {
      if(*iter == autoethx)
          break;
  }

  //  m_dom.splice(++iter ,m_devdom);

  std::ofstream fou("/opt/interfaces");
  for (auto val : m_devdom)
  {
      fou<<val<<std::endl;
  }
  fou.flush();

}

void ZNetWorkBase::getNetWork(TNetWorkInfo& network)
{
    network = m_networkinfo;
}


ZNetWorkBase::~ZNetWorkBase()
{
    m_devdom.clear();
    m_dom.clear();

}




}
