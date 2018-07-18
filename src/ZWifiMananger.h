#ifndef ZWIFIMANANGER_H
#define ZWIFIMANANGER_H

#include <iostream>
#include <list>
#include <mutex>

namespace A7 {

class ZWifiMananger
{
  public:
    enum TEncryp{
      ENCRYP_NONE =0,
      ENCRYP_WEP,
      ENCRYP_WAP
    };


    struct TWifi{
        TEncryp     encryp;
        std::string ssid;
        std::string password;
        std::string bssid;
        std::string signal;
        std::string frequency;
      //  std::string status;
     //   std::string wpa_state;
    };

    //using save  'wpa_cli -i wlan0 list_network'  message
    struct TApNode{
        int index;
        std::string ssid;
        std::string bssid;
        std::string flag;
    };

    enum TStatus{
      ON = 0,
      OFF
    };

    enum TErrorNo{
      WIFI_NOERROR = 0,  //无错误
      WIFI_DEV_OFF,  //设备已经关闭
      WIFI_DEV_SCAN_TIMEOUT, //扫描超时
      WIFI_POPEN_FAILED, //打开管道文件失败
      WIFI_DEV_LIST_NETWORK_TIMEOUT,  //列表节点超时
      WIFI_PASSWORD_NO_VALID,  //密码非法,长度
    };


    ZWifiMananger();
    ~ZWifiMananger();

    /* 功能：wifi开关
     * 输入参数：
     *      TStatus status, 设置状态，ON表示开， OFF表示关
     * 返回值：空
     * TErrorNo:
     *      WIFI_NOERROR
     */
    void setWifi(TStatus status);
    /* 功能:查询wifi开关状态
     * 输入参数:空
     * 返回值: 类型(TStatus)
     *      ON表示开， OFF表示关
     */
    TStatus getWifi(); //当前wifi状态, 运行 or 停止


    /* 功能:查询wifi热点状态
     * 输入参数:
     *      std::list<TWifi>& wifis ,用于存储查询的wifi 热点
     * 返回值: 空
     * TErrorNo:
     *      WIFI_NOERROR
     *      WIFI_DEV_OFF
     */
    void WifiScaning(std::list<TWifi>& wifis);

    /* 功能：查询当前wifi网络的状态
     * 输入参数： 空
     * 返回值:(std::string)
     *      "COMPLETED"  已经连接上
     *      "SCANNING"
     *      "ASSOCIATING"
     *      "4WAY_HANDSHAKE"
     *      "DISCONNECTED"
     *      "INACTIVE"
     */
    std::string WifiStatus(); //状态查询


    /* 功能:连接wifi热点
     * 输入参数:
     *  std::string ssid       ssid号
     *  std::string password   密码，有效长度跟flag关联
     *  TEncryp encryp
     *           ENCRYP_NONE  无密码
     *           ENCRYP_WEP   wep密码,password长度5-13个
     *           ENCRYP_WPA   wpa加密,password长度8-63个
     * 返回值：空
     *
     * TErrorNo:
     *      WIFI_NOERROR
     *      WIFI_PASSWORD_NO_VALID,  //密码非法,长度
     *      WIFI_DEV_LIST_NETWORK_TIMEOUT
     *
     * 注意：ssid中文无法设置，需要转化成16进制
     */
    bool connectWifi(const std::string ssid,const std::string password,const TEncryp encryp);

    //Wifi save ssid and password
    bool saveWifiToConfigFile(const std::string ssid,const std::string password,const TEncryp encryp);
    bool deleteWifiConfigBySSID(const std::string ssid);
    bool reloadWifiFromConfigFile();
    bool wifi_json_To_Wpa_supplicant_conf();

    std::string EncrypTostring(const TEncryp& encryp);

    //Error status
    void setErrorStatus(TErrorNo no);
    TErrorNo getErrorStatus();


  public:
    std::list<TWifi>& WifiScaning(); //扫描wifi
    bool isPasswordValid(const std::string &password,const TEncryp& encryp);
    bool addWifiNode(const std::string& ssid, const std::string& password, const TEncryp& encryp);
    bool removeWifiNode(const int& index);
    void WifiON();  //运行wifi
    void WifiOFF(); //停止wifi

    void Wifi_setting(std::string ssid, std::string passwork);
    void Wifi_dhcp(std::string iface);

    bool wait_ok();
    bool wpa_cli_isOk();
    bool wpa_cli_status();
    bool wpa_cli_reconf();
    bool wpa_cli_scan_r(std::list<TWifi>& wifis);
    bool wpa_cli_list_network(std::list<TApNode>& Aps);
    bool wpa_cli_add_network(int& index);


    void wpa_socket_cmd(std::string path, std::string cmd);
    void iw_dev_wlan0_scan();
    void iw_dev_wlan0_link();
    void wpa_supplicant_stop();
    void wpa_supplicant_run(std::string iface);
    bool wpa_supplicant_conf_save();
    bool wpa_socket_wireless_status(std::string iface);
  private:
    /*can't work*/

    void getCommandLine(const std::string& command, std::string& result);
    std::list<TWifi> m_wifilist;
    std::mutex m_wifilistmutex;

    TWifi m_currentWifi;
    std::mutex m_currentWifiMutex;
    TErrorNo m_ErrorNo;

    std::string m_currentSSID;
    std::string m_currentPassword;
    TEncryp     m_currentEncryp;
};

}
#endif // ZWIFIMANANGER_H
