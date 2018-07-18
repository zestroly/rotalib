#include "ZWifiMananger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fstream>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <linux/wireless.h>
#include <limits.h>
#include <sys/ioctl.h>

#include "ZLog.h"
#include "ZSystemIO.h"
#include <jsoncpp/json/json.h>

namespace A7 {

ZWifiMananger::ZWifiMananger()
  :m_ErrorNo(WIFI_NOERROR)
{
    signal(SIGCHLD,SIG_IGN);

    m_currentSSID = "";
    m_currentPassword = "";
    m_currentEncryp = ENCRYP_NONE;
}

ZWifiMananger::~ZWifiMananger()
{
  m_wifilist.clear();
}


void ZWifiMananger::WifiON()
{
    std::string result;
    getCommandLine("ip link set wlan0 up", result);

    struct stat st;
    memset(&st, 0, sizeof(struct stat));
    if(stat("/run/wpa_supplicant/wlan0", &st) != 0)
    {
        wpa_supplicant_run("wlan0");
        getCommandLine("udhcpc -i wlan0", result);
    }

    m_wifilistmutex.lock();
    m_wifilist.clear();
    m_wifilistmutex.unlock();
    setErrorStatus(WIFI_NOERROR);
}


void ZWifiMananger::WifiOFF()
{
    std::string result;
    //OFF udhcpc
    std::list<std::string> pidlist;
    ZSystemIO::getProgressPid("udhcpc", pidlist);
    for(auto pid: pidlist)
    {
      ZSystemIO::killProgressByPid(std::stoi(pid));
    }

    wpa_supplicant_stop();

    getCommandLine("ip link set wlan0 down", result);

    setErrorStatus(WIFI_NOERROR);
}

void ZWifiMananger::setWifi(TStatus status)
{
  if(status == ON)
  {
    Zlog("Wifi ON");
    WifiON();
  }else{
    Zlog("Wifi OFF");
    WifiOFF();
  }

}

ZWifiMananger::TStatus ZWifiMananger::getWifi()
{
    struct stat st;
    memset(&st, 0, sizeof(struct stat));
    if(stat("/run/wpa_supplicant/wlan0", &st) != 0)
      return OFF;
    else
      return ON;
}

void ZWifiMananger::setErrorStatus(TErrorNo no)
{
    m_ErrorNo = no;
}

ZWifiMananger::TErrorNo ZWifiMananger::getErrorStatus()
{
  return m_ErrorNo;
}




void ZWifiMananger::Wifi_setting(std::string ssid, std::string passwork)
{
    if(!wpa_cli_scan_r(m_wifilist))
        return;

    for(auto wifi : m_wifilist)
    {
        if (wifi.ssid == ssid) //查找ip
        {
            m_currentWifiMutex.lock();
            m_currentWifi.ssid = ssid;
            m_currentWifi.password = passwork;
            m_currentWifi.encryp = wifi.encryp;
           // m_currentWifi.type = wifi.type;
            m_currentWifiMutex.unlock();

            //保存配置文件
            wpa_supplicant_conf_save();

            //重新加载配置文件
            wpa_cli_reconf();

            //查看网络状态
            int count  = 0;
            while(count++ < 5)
            {
                sleep(1);
                if(wpa_cli_status())
                {
                    //SCANNING
                    //ASSOCIATING
                    //INACTIVE
                    //COMPLETED
                    //DISCONNECTED
                   // if(m_currentWifi.wpa_state =="COMPLETED")
                    {
                        Wifi_dhcp("wlan0");
                        break;
                    }
                }
            }
            break;
        }
     //   std::cout<<wifi.bssid<<"|"<<wifi.encryp<<"|"<<wifi.flag<<"|"<<wifi.frequency<<"|"
      //  <<wifi.password<<"|"<<wifi.signal<<"|"<<wifi.status<<"|"<<wifi.type<<"|"<<std::endl;
    }
}

bool ZWifiMananger::isPasswordValid(const std::string &password,const TEncryp& encryp)
{
  switch(encryp)
  {
      case ENCRYP_NONE:
          return true;
          break;
      case ENCRYP_WAP:
          if(password.size() <=63 && password.size() >=8)
              return true;
          break;
      case ENCRYP_WEP:
          if(password.size() <=5 && password.size() >=13)
              return true;
          break;
  }
  setErrorStatus(WIFI_PASSWORD_NO_VALID);
  return false;
}

bool ZWifiMananger::addWifiNode(const std::string& ssid,
                               const std::string& password,
                               const TEncryp& encryp)
{
    /*
  "wpa_cli -i wlan0 add_network"
  "wpa_cli -i wlan0 set_network 0 ssid '""'
  "wpa_cli -i wlan0 set_network 0 psk '""'
  "wpa_cli -i wlan0 enable_network 0"
  */
    int index = 0;
    if(wpa_cli_add_network(index))
    {
        std::string cmd;
        std::string result;
        std::string indexstr=std::to_string(index);

        cmd = "wpa_cli -i wlan0 set_network " + indexstr +" ssid "+"\'\""+ssid+"\"\'";
        getCommandLine(cmd, result);
        Zlog("cmd:[%s]", cmd.c_str());
        if(result.find("OK", 0) == std::string::npos)
            return false;

        switch (encryp)
        {
            case ENCRYP_NONE:
                cmd = "wpa_cli -i wlan0 set_network " + indexstr +" key_mgnt NONE";
                getCommandLine(cmd, result);
                Zlog("cmd:[%s]", cmd.c_str());

                cmd = "wpa_cli -i wlan0 select_network " + indexstr;
                getCommandLine(cmd, result);
                Zlog("cmd:[%s]", cmd.c_str());

                cmd = "wpa_cli -i wlan0 enable_network " + indexstr;
                getCommandLine(cmd, result);
                Zlog("cmd:[%s]", cmd.c_str());
                break;
            case ENCRYP_WAP:
                cmd = "wpa_cli -i wlan0 set_network " + indexstr +" psk "+"\'\""+password+"\"\'";
                getCommandLine(cmd, result);
                Zlog("cmd:[%s]", cmd.c_str());

                cmd = "wpa_cli -i wlan0 select_network " + indexstr;
                getCommandLine(cmd, result);
                Zlog("cmd:[%s]", cmd.c_str());

                cmd = "wpa_cli -i wlan0 enable_network " + indexstr;
                getCommandLine(cmd, result);
                Zlog("cmd:[%s]", cmd.c_str());
                break;
            case ENCRYP_WEP:
                cmd = "wpa_cli -i wlan0 set_network " + indexstr +" key_mgnt NONE";
                getCommandLine(cmd, result);
                Zlog("cmd:[%s]", cmd.c_str());

                cmd = "wpa_cli -i wlan0 set_network " + indexstr +" wep_key0 "+"\'\""+password+"\"\'";
                getCommandLine(cmd, result);
                Zlog("cmd:[%s]", cmd.c_str());

                cmd = "wpa_cli -i wlan0 select_network " + indexstr;
                getCommandLine(cmd, result);
                Zlog("cmd:[%s]", cmd.c_str());

                cmd = "wpa_cli -i wlan0 enable_network " + indexstr;
                getCommandLine(cmd, result);
                Zlog("cmd:[%s]", cmd.c_str());
                break;
        }
        return true;
    }else{
      return false;
    }
}



bool ZWifiMananger::wpa_cli_add_network(int& index)
{
    std::string result;
    getCommandLine("wpa_cli -i wlan0 add_network ", result);
    if(result != "") {
        if(result.size() > 4)
            return "";

        size_t n = result.find_first_of('\n', 0);
        if(n != std::string::npos)
            result.erase(n);
        index= std::stoi(result);
        return true;
    }
    else
        return false;
}


bool ZWifiMananger::connectWifi(const std::string ssid,
                                const std::string password,
                                const TEncryp encryp)
{

    m_currentSSID = ssid;
    m_currentPassword = password;
    m_currentEncryp = encryp;

    if(!isPasswordValid(password, encryp))
        return false;


    std::list<A7::ZWifiMananger::TApNode> Aplist;
    if(!wpa_cli_list_network(Aplist))
        return false;

    for(auto ap: Aplist)
    {
        if(ap.ssid == ssid)
        {
            //已经存在，修改已经存在的
            if(ap.flag == "[CURRENT]")//已连接上
                Zlog("已经连接至此ssid上");
            else{
                removeWifiNode(ap.index);
                addWifiNode(ssid, password, encryp);
            }
            goto SET_DEV_SUCCESS;
        }
    }
    //未配置过，添加新的选项
    addWifiNode(ssid, password, encryp);
SET_DEV_SUCCESS:
    Aplist.clear();
    setErrorStatus(WIFI_NOERROR);
}


bool ZWifiMananger::saveWifiToConfigFile(const std::string ssid,const std::string password,const TEncryp encryp)
{
    if(ssid == "")
        return false;

    if(!isPasswordValid(password, encryp))
    {
      Zlog("密码长度错误");
      return false;
    }

    std::string filePath="/opt/wifi.json";
    Json::Value wifiRoot;
    std::ifstream wifi_ifs;

    wifi_ifs.open(filePath);
    if(wifi_ifs.is_open())
    {
        Json::Reader reader;
        if(reader.parse(wifi_ifs, wifiRoot))
        {
            Zlog("ok");
            wifi_ifs.close();
        }else{
            wifi_ifs.close();
            Zlog("error");
        }

        int sz = wifiRoot.size();
        bool isFind = false;
        for(int i = 0; i < sz; i++)
        {
            if(wifiRoot[i]["ssid"].asString() == ssid)
            { //已有相同ssid ，修改ssid 内容
                wifiRoot[i]["password"] = Json::Value(password);
                wifiRoot[i]["encrpy"] = Json::Value(EncrypTostring(encryp));
                isFind = true;
            }
        }

        if(isFind != true)
        {
            Json::Value partner;
            partner["ssid"]=Json::Value(ssid);
            partner["password"]=Json::Value(password);
            partner["encrpy"]=Json::Value(EncrypTostring(encryp));
            wifiRoot.append(partner);
        }
    }else{
        Zlog("no wifi.json file, create /opt/wifi.sh");
        Json::Value partner;
        partner["ssid"]=Json::Value(ssid);
        partner["password"]=Json::Value(password);
        partner["encrpy"]=Json::Value(EncrypTostring(encryp));
        wifiRoot.append(partner);
    }

    std::ofstream os;
    os.open("/opt/wifi.json");
    os << wifiRoot.toStyledString();
    os.close();
    wifiRoot.clear();
    return true;
}

bool ZWifiMananger::wifi_json_To_Wpa_supplicant_conf()
{
  std::string filePath="/opt/wifi.json";
  Json::Value wifiRoot;
  std::ifstream wifi_ifs;

  wifi_ifs.open(filePath);
  if(wifi_ifs.is_open())
  {
      Json::Reader reader;
      if(reader.parse(wifi_ifs, wifiRoot))
      {
          wifi_ifs.close();
          std::ofstream osconf;
          osconf.open("/opt/wpa_supplicant.conf");
          osconf << "";

          osconf<<"ctrl_interface=/var/run/wpa_supplicant\n";
          osconf<<"ctrl_interface_group=0\n";
          osconf<<"ap_scan=1\n\n";

          int sz = wifiRoot.size();
          for(int i = 0; i < sz; i++)
          {
              osconf<<"network={\n";
              osconf<<"\tssid=\""<<wifiRoot[i]["ssid"].asString()<<"\"\n";
              if(wifiRoot[i]["encrpy"].asString() =="NONE") {
                  osconf<<"\tkey_mgmt=NONE\n";
                  osconf<<"\tpriority=5\n";
              }else if(wifiRoot[i]["encrpy"].asString() =="WEP"){
                  osconf<<"\tkey_mgmt=NONE\n";
                  osconf<<"\twep_key0="<<wifiRoot[i]["password"].asString()<<"\n";
                  osconf<<"\twep_tx_keyidx=0\n";
                  osconf<<"\tpriority=5\n";
                  osconf<<"\tauth_alg=SHARED\n";
              }else if(wifiRoot[i]["encrpy"].asString() =="WPA"){
                  osconf<<"\tpsk=\""<<wifiRoot[i]["password"].asString()<<"\"\n";
              }
              osconf<<"}\n\n";
          }
          osconf.close();
      }
  }
  return true;
}



bool ZWifiMananger::deleteWifiConfigBySSID(const std::string ssid)
{
    if(ssid == "")
        return false;

    return true;
}

bool ZWifiMananger::reloadWifiFromConfigFile()
{

    return true;
}

bool ZWifiMananger::removeWifiNode(const int& index)
{
    Zlog("remove network %d", index);
    std::string result;
    std::string cmd;
    cmd = "wpa_cli -i wlan0 disable  " + std::to_string(index);
    getCommandLine(cmd, result);
    cmd = "wpa_cli -i wlan0 remove_network  " + std::to_string(index);
    getCommandLine(cmd, result);
    return true;
}

void ZWifiMananger::WifiScaning(std::list<TWifi>& wifis)
{
    Zlog("Wifi Scanning");
    wifis.clear();
    TStatus status = getWifi();
    if(status == OFF)
    {
        Zlog("Wifi is OFF");
        setErrorStatus(WIFI_DEV_OFF);
    }

    int i=0;
    while(1)
    {

      wpa_cli_scan_r(wifis);
      if(i++ >5)
        break;
      if(wifis.size() > 0)
        break;
      sleep(1);
    }
}


std::list<ZWifiMananger::TWifi>& ZWifiMananger::WifiScaning()
{
    Zlog("Wifi Scanning");
    m_wifilistmutex.lock();
    WifiScaning(m_wifilist);
    m_wifilistmutex.unlock();
    return m_wifilist;
}

std::string ZWifiMananger::WifiStatus()
{
    Zlog("Wifi status");
    TStatus status = getWifi();
    if(status == OFF)
    {
        Zlog("Wifi is OFF");
        setErrorStatus(WIFI_DEV_OFF);
        return "";
    }

    FILE *pfile = popen("wpa_cli -iwlan0 status", "r");
    if (!pfile)
        return "";

    char line[256];
    char key[100];
    char value[100];
    while(fgets(line, sizeof(line), pfile) != NULL)
    {
        sscanf(line, "%[^=]=%s", key, value);

        if(std::string("wpa_state") == std::string(key)) {
            pclose(pfile);
            return value;
        }
    }
    pclose(pfile);
    return "";
}


void ZWifiMananger::Wifi_dhcp(std::string iface)
{
    std::string result;
    getCommandLine("udhcpc -i wlan0", result);
    Zlog("%s",result.c_str());
}


void ZWifiMananger::getCommandLine(const std::string& command, std::string& result)
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
    for(i = 0; fgets(tmp, 200, file) != NULL;i++)
    {
        result += tmp;
    }

    delete[] tmp;
    pclose(file);
}

bool ZWifiMananger::wpa_cli_isOk()
{
    std::string result;
    getCommandLine("wpa_cli -iwlan0 scan", result);
    if(result.find("OK", 0) != std::string::npos)
        return true;
    else
        return false;
}

bool ZWifiMananger::wpa_cli_reconf()
{
    //  if(!wpa_cli_isOk())
    //  {
    //      Zlog("wpa_cli not available!");
    //      return false;
    //  }

    int timerOut = 0;
    while(!wpa_cli_isOk())
    {
        Zlog("check ... %d!", timerOut);
        if(++timerOut > 5)
            break;
        sleep(1);
    }
    if(timerOut > 5)
    {
        Zlog("Check wpa_cli failed!");
        return false;
    }

    std::string result;
    getCommandLine("wpa_cli -iwlan0 reconf", result);
    if(result.find("OK", 0) != std::string::npos)
        return true;
    else
        return false;
}


bool ZWifiMananger::wpa_cli_status()
{
    bool ret = false;
    int timerOut = 0;
    while(!wpa_cli_isOk())
    {
        Zlog("check ... %d!", timerOut);
        if(++timerOut > 5)
            break;
        sleep(1);
    }
    if(timerOut > 5)
    {
        Zlog("Check wpa_cli failed!");
        return false;
    }

    FILE *pfile = popen("wpa_cli -iwlan0 status", "r");
    if (!pfile)
        return false;

    char line[256];
    char key[100];
    char value[100];
    while(fgets(line, sizeof(line), pfile) != NULL)
    {
        sscanf(line, "%[^=]=%s", key, value);

        if(std::string("wpa_state") == std::string(key)) {
            m_currentWifiMutex.lock();
            //   m_currentWifi.wpa_state = value;
            m_currentWifiMutex.unlock();
            ret = true;
        }
        /* else if(std::string("bssid") == std::string(key)) {
            m_currentWifi.bssid = value;
        } else if(std::string("ssid") == std::string(key)) {
            m_currentWifi.ssid = value;
        }
        */
    }
    pclose(pfile);
    return ret;
}

bool ZWifiMananger::wpa_supplicant_conf_save()
{
    m_currentWifiMutex.lock();
    std::string ssid = m_currentWifi.ssid;
    std::string password = m_currentWifi.password;
    std::string encypt = "";//m_currentWifi.encryp;
    std::string type ="";// m_currentWifi.type;
    m_currentWifiMutex.unlock();

    FILE* fp=fopen("/opt/wpa_supplicant.conf", "wb");
    if(!fp)
    {
        Zlog("Can't open wpa_supplicant.conf!");
        return false;
    }
    fprintf(fp, "ctrl_interface=/var/run/wpa_supplicant\n");
    fprintf(fp, "ctrl_interface_group=0\n");
    fprintf(fp, "ap_scan=1\n\n");

    if("NO" == encypt){
        fprintf(fp, "network={\n"
                    "\tssid=%s\n"
                    "\tkey_mgmt=NONE\n"
                    "\tpriority=5\n"
                    "}\n", ssid.c_str());
    }else if("WEP" == type ) {
        fprintf(fp, "network={\n"
                    "\tssid=\"%s\"\n"
                    "\tkey_mgmt=NONE\n"
                    "\twep_key0=%s\n"
                    "\twep_tx_keyidx=0\n"
                    "\tpriority=5\n"
                    "\tauth_alg=SHARED\n"
                    "}\n",
                ssid.c_str(), password.c_str());
    }else if("WPA" == type) {
        fprintf(fp, "network={\n"
                    "\tssid=\"%s\"\n"
                    "\tpsk=\"%s\"\n"
                    "}\n",
                ssid.c_str(), password.c_str());
    }
    fclose(fp);
}



bool ZWifiMananger::wpa_cli_scan_r(std::list<TWifi>& wifis)
{
    wifis.clear();
    if(!wait_ok())
      return false;

    FILE *pfile = popen("wpa_cli -iwlan0 scan_r", "r");
    if (!pfile){
        setErrorStatus(WIFI_POPEN_FAILED);
        return false;
    }

    char Line[256];
    fgets(Line, sizeof(Line), pfile);

    char bssid[100];
    char frequency[100];
    char signallevel[100];
    char flag[100];
    char ssid[100];
    while(fgets(Line, sizeof(Line), pfile) != NULL)
    {
        sscanf(Line, "%s\t%s\t%s\t%s\t%s\n", bssid, frequency, signallevel, flag, ssid);

        TWifi wifi;
        wifi.ssid = ssid;

        if(strstr(flag, "WPA"))
            wifi.encryp = ENCRYP_WAP;
        else if(strstr(flag, "WEP"))
            wifi.encryp = ENCRYP_WEP;
        else
            wifi.encryp = ENCRYP_NONE;

        wifi.password = "";
        wifi.bssid = bssid;
        wifi.frequency = frequency;
        wifi.signal = signallevel;
        wifis.push_back(wifi);
        Zlog("|%s|\t|%s|\t|%s|\t|%s|\t|%s|\n", bssid, frequency, signallevel, flag, ssid);
    }
    pclose(pfile);

    setErrorStatus(WIFI_NOERROR);
    return true;
}

std::string ZWifiMananger::EncrypTostring(const TEncryp& encryp)
{
    switch(encryp)
    {
        case ENCRYP_NONE:
            return "NONE";
        case ENCRYP_WEP:
            return "WEP";
        case ENCRYP_WAP:
            return "WPA";
    }
    return "";
}


bool ZWifiMananger::wait_ok()
{
    int timerOut = 0;
    while(!wpa_cli_isOk())
    {
        Zlog("wait wpa_cli_scan ok...");
        if(++timerOut > 5)
            break;
        sleep(1);
    }

    if(timerOut > 5)
    {
        Zlog("[error]wait timeout!");
        setErrorStatus(WIFI_DEV_LIST_NETWORK_TIMEOUT);
        return false;
    }
    return true;
}

bool ZWifiMananger::wpa_cli_list_network(std::list<TApNode>& Aps)
{
    if(!wait_ok())
        return false;

    FILE *pfile = popen("wpa_cli -iwlan0 list_network", "r");
    if (!pfile){
        setErrorStatus(WIFI_POPEN_FAILED);
        return false;
    }

    char Line[256];
    fgets(Line, sizeof(Line), pfile);

    char networkid[64];
    char ssid[100];
    char bssid[100];
    char flag[64];

    Aps.clear();
    while(fgets(Line, sizeof(Line), pfile) != NULL)
    {
        sscanf(Line, "%s\t%s\t%s\t%s\n",networkid, ssid, bssid, flag);
        TApNode ap;
        ap.index = std::stoi(networkid);
        ap.ssid = ssid;
        ap.bssid = bssid;
        ap.flag = flag;
        Zlog("list network |%s| |%s| |%s| |%s|",networkid, ssid, bssid, flag);
        Aps.push_back(ap);
    }
    pclose(pfile);
    setErrorStatus(WIFI_NOERROR);
    return true;
}



void ZWifiMananger::iw_dev_wlan0_link()
{
    std::string result;
    getCommandLine("iw dev wlan0 link", result);

    Zlog("%s", result.c_str());
    if(result.find("Not connected", 0) != std::string::npos)
    {
        Zlog("%s", "未连接");
    }else{
        Zlog("%s", "已连接");
    }

}

void ZWifiMananger::iw_dev_wlan0_scan()
{
    std::string result;
    getCommandLine("iw dev wlan0 scan | grep SSID", result);
    Zlog("%s", result.c_str());
}

void ZWifiMananger::wpa_supplicant_stop()
{
    std::string path = "/run/wpa_supplicant/wlan0";
    struct stat st;
    memset(&st, 0, sizeof(struct stat));
    if(stat(path.c_str(), &st ) != 0)
    {
        Zlog("wpa_supplicant not runing on");
        return;
    }
    wpa_socket_cmd(path,"DISCONNECT");
    sleep(1);
    wpa_socket_cmd(path,"TERMINATE");


}

void ZWifiMananger::wpa_supplicant_run(std::string iface)
{

    pid_t pid;
    pid = fork();
    std::string ifn = "-i"+iface;

    if(pid == -1)
    {
        return;
    }else if(pid > 0) {
        /* parent */
        return;
    }else{
        /*  childen */
        if(execlp("wpa_supplicant", "wpa_supplicant",
                  "-Dnl80211",ifn.c_str(), "-c/opt/wpa_supplicant.conf","-B", NULL) == -1)
        {
            Zlog("connect error!");
        }
    }
    return;
}

void ZWifiMananger::wpa_socket_cmd(std::string path, std::string cmd)
{
    int fd;
    struct sockaddr_un sa;
    size_t len;

    int ret;
    memset(&sa, 0, sizeof(struct sockaddr_un));

    fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(fd < 0)
    {
        Zlog("error open fd\n");
        return;
    }

    sa.sun_family = AF_UNIX;
    snprintf(sa.sun_path, sizeof(sa.sun_path), "%s", path.c_str());

    len = sizeof(struct sockaddr_un);
    if(connect(fd, (const struct sockaddr*)&sa, len) == -1 )
    {
        Zlog("%s",path.c_str());
        close(fd);
    }

    len = strlen(cmd.c_str());
    if( (ret = send(fd, cmd.c_str(), len, 0)) != len)
    {
        Zlog("%s",cmd.c_str());
    }
    close(fd);
}

bool ZWifiMananger::wpa_socket_wireless_status(std::string iface)
{
    int sock_fd;
    int ret = 0;
    struct iwreq iwr;
    struct iw_statistics stats;

    if (iface == "")
    {
        Zlog("iface is NULL");
        return false;
    }

    /* make socket fd */
    if ((sock_fd = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
    {
        Zlog("socket err");
        return false;
    }

    memset(&iwr, 0, sizeof(iwr));
    memset(&stats, 0, sizeof(stats));
    iwr.u.data.pointer = (caddr_t) &stats; /* result value */
    iwr.u.data.length = sizeof(stats);
    iwr.u.data.flags = 1; /* clear updated flag */

    /* ifname is reqired */
    strncpy(iwr.ifr_ifrn.ifrn_name, iface.c_str(), IFNAMSIZ - 1);

    /* get SIOCGIWSTATS */
    if (ioctl(sock_fd, SIOCGIWSTATS, &iwr) < 0)
    {
        Zlog("No Such Device %s",iface.c_str());
        close(sock_fd);
        return false;
    }
    ret = stats.status;
    close(sock_fd);
    return ret?true:false;
}



}
