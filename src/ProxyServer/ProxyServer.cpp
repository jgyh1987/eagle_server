#include "ProxyServer.h"
#include "Confile.h"
#include "ProxyService.h"
#include "ProxyTaskManager.h"
#include "TransMap.h"
#include "TimeTick.h"
#include "Defs.h"
#include "ProxyConnectClient.h"

/**
 * \brief 主程序入口
 *
 * \param argc 参数个数
 * \param argv 参数列表
 * \return 运行结果
 */

uint32_t g_serverPort;
CMatchConnectClient *g_matchConn;

bool InitSystemManagers();
bool ClearSystemManagers();



int main(int argc,char **argv)
{

    //eagle::global["LoggerLevel"] = "1";
    //eagle::global["daemon"] = "true";
    //eagle::global["ifname"] = "eth0";
    //eagle::global["LogPath"] = "./log/LoginServer/";
    //eagle::global["CmdQueueMax"] = "102400";
    //eagle::global["ServerListRefTime"] = "300";
    //eagle::global["loginlistenserver"] = "18087";
    //eagle::global["loginlistenUdpserver"] = "18088";
    //eagle::global["connectlogindataserverPort"] = "17087";
    //eagle::global["connectlogindataserverIP"] = "127.0.0.1";

#ifdef WIN32
    CConfigFile m_ConfigFile("../../Config/ZoneConfig.xml");
#else 
    CConfigFile m_ConfigFile("./Config/ZoneConfig.xml");
#endif

    if (false == m_ConfigFile.parse("Share"))
        return 0;
    if (false == m_ConfigFile.parse("ProxyServer"))
        return 0;

    ENUM_LOG_LEVEL level = LOG_LEVEL_DEBUG;//LOG_LEVEL_DEBUG;LOG_LEVEL_TRACE;
    level = (ENUM_LOG_LEVEL)atoi(eagle::global["LoggerLevel"].c_str());
    eagle::g_logger.SetLevel(level);
    eagle::g_logger.SetConsole(true);

    //设置写本地日志文件
    if(strlen(eagle::global["LogPath"].c_str()))
    {        
        eagle::g_logger.SetPath(eagle::global["LogPath"].c_str());
    }

    eagle::g_logger.Init();

    g_serverId = atoi(eagle::global["ServerId"].c_str());
    g_serverPort = atoi(eagle::global["ProxyServerTcpPort"].c_str());
    uint32_t centralServerPort = atoi(eagle::global["ConnectCentralServerPort"].c_str());

    g_pServerImp = new CProxyServer(eagle::global["ServerName"].c_str());
    if (!g_pServerImp)
    {
        LOGE("ProxyServer calling main... new g_pServerImp NULL!!!");
        goto Lable;
    }

	if (!InitSystemManagers())
	{
		LOGE("ProxyServer calling main... InitSystemManagers ERROR!!!");
		goto Lable;
	}

    g_pServerImp->AddListenServer(new CListenTCPServer(new CProxyTaskManager(), "ProxyListenServer", g_serverPort));
    g_pServerImp->AddConnectClient(new CProxyConnectClient("ProxyServerConnectCentralServer", SERVER_TYPE_CENTRAL_SERVER, g_serverId, eagle::global["ConnectCentralServerIP"].c_str(), centralServerPort));

    if (!g_pServerImp->Init())
    {
        LOGE("ProxyServer main... g_pServerImp Init Error!!!");
        goto Lable;
    }

    LOGI("ProxyServer Run SECCUSS !!!");
    g_pServerImp->Start();

Lable:
    if (g_pServerImp)
    {
        g_pServerImp->Close();
        SAFE_DELETE(g_pServerImp);
    }

    ClearSystemManagers();

    LOGI("ProxyServer calling main...  CLOSE !!!");

    return EXIT_SUCCESS;
}

bool InitSystemManagers()
{

    return true;
}

bool ClearSystemManagers()
{

    return true;
}

