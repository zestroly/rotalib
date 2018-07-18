#include "ZBluetooth.h"
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/hidp.h>
#include <bluetooth/l2cap.h>
#include "ZLog.h"
#include <time.h>

namespace A7 {

ZBluetooth::ZBluetooth()
{
  _bt_dev_id = hci_get_route(NULL);
  if(_bt_dev_id < 0)
  {
    Zlog("error hci_get_route");
    return;
  }

  _btsock = hci_open_dev(_bt_dev_id);
  if(_btsock < 0)
  {
    Zlog("error hci_open_dev");
    return;
  }
}

ZBluetooth::~ZBluetooth()
{

}

void ZBluetooth::scan(std::map<std::string,std::string>& Devs)
{
  Zlog("scan start >");
  Devs.clear();
  inquiry_info * ii = new inquiry_info[255];
  if(_bt_dev_id >= 0)
  {
      int num_rsp = hci_inquiry(_bt_dev_id, 8, 255, NULL,&ii ,IREQ_CACHE_FLUSH);
      char addr[19];
      char name[100];
      for(int i = 0; i < num_rsp; i++)
      {
          memset(addr, 0, sizeof(addr));
          memset(name, 0, sizeof(name));

          ba2str(&ii[i].bdaddr, addr);
          hci_read_remote_name(_btsock, &ii[i].bdaddr,sizeof(name), name, 0);
          //Zlog("%s %s ",addr ,name);
          Devs.insert(std::pair<std::string,std::string> (addr, name) );
      }

  }
  delete[] ii;
  Zlog(" < scan end");
}

}
