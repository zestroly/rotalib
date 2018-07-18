#ifndef ZBLUETOOTH_H
#define ZBLUETOOTH_H

#include <map>
#include <iostream>

namespace A7 {


class ZBluetooth
{
  public:
    ZBluetooth();
    ~ZBluetooth();
    void scan(std::map<std::string,std::string>& Devs);
    void connect(std::string mac);

  private:
    int _bt_dev_id;
    int _btsock;

};

}

#endif // ZBLUETOOTH_H
