#include "LoginServer.h"
#include "Confile.h"
#include "LoginTaskManager.h"
#include "LoginClientTaskManager.h"
#include "DBConnectClient.h"
#include "LoginUdpServer.h"
#include "LoginService.h"
#include "Defs.h"
#include "AccountManager.h"
#include "ServeListManager.h"
#include "google/protobuf/message.h"

/**
 * \brief 主程序入口
 *
 * \param argc 参数个数
 * \param argv 参数列表
 * \return 运行结果
 */

CLoginUdpServer *g_pUdpServer = NULL;

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

    GOOGLE_PROTOBUF_VERIFY_VERSION;

#ifdef WIN32
    CConfigFile m_ConfigFile("../../Config/ZoneConfig.xml");
#else 
    CConfigFile m_ConfigFile("./Config/ZoneConfig.xml");
#endif

    if (false == m_ConfigFile.parse("Share"))
        return 0;
    if (false == m_ConfigFile.parse("LoginServer"))
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
    uint32_t connectLoginDataServerPort = atoi(eagle::global["ConnectLoginDataServerPort"].c_str());
    uint32_t loginserverUdpPort = atoi(eagle::global["LoginServerUdpPort"].c_str());
    uint32_t clientPort = atoi(eagle::global["LoginClientTcpPort"].c_str());
    uint32_t serverPort = atoi(eagle::global["LoginServerTcpPort"].c_str());

    g_pServerImp = new CLoginServer(eagle::global["ServerName"].c_str());
    if (!g_pServerImp)
    {
        LOGE("LoginServer calling main... new g_pServerImp NULL!!!");
        goto Lable;
    }

	if (!InitSystemManagers())
	{
		LOGE("LoginServer calling main... InitSystemManagers ERROR!!!");
		goto Lable;
	}

    g_pServerImp->AddListenServer(new CListenTCPServer(new LoginTaskManager(), "LoginServerListenServer", serverPort));
    g_pServerImp->AddListenClinetServer(new CListenTCPServer(new LoginClientTaskManager(), "LoginClientTaskManager", clientPort));
    g_pServerImp->AddConnectClient(new CDBConnectClient("LoginServerConnectDBServer", eagle::global["ConnectLoginDataServerIP"].c_str(), connectLoginDataServerPort), false);

    g_pUdpServer = new CLoginUdpServer("GatewayUdpServer", loginserverUdpPort);
    if (g_pUdpServer && g_pUdpServer->Init())
    {
        LOGFMTD("LoginServer CLoginServerUdpServer  %p", g_pUdpServer);    
    }
    else
    {
        LOGE("LoginServer calling main... CLoginServerUdpServer NULL");
        goto Lable;
    }

    if (!g_pServerImp->Init())
    {
        LOGE("LoginServer calling main... g_pServerImp Init Error!!!");
        goto Lable;
    }

    g_pUdpServer->Start();

    LOGI("LoginServer Run SECCUSS !!!");
    g_pServerImp->Start();

Lable:
    if (g_pServerImp)
    {
        g_pServerImp->Close();
        SAFE_DELETE(g_pServerImp);
    }

    if (g_pUdpServer)
    {
        g_pUdpServer->Close();
        SAFE_DELETE(g_pUdpServer);
    }

    ClearSystemManagers();

    LOGI("LoginServer calling main... CLOSE");

    return EXIT_SUCCESS;
}

bool InitSystemManagers()
{
    CServeListManager::instance()->Init();
    CAccountManager::instance()->Init();

    return true;
}

bool ClearSystemManagers()
{

    return true;
}

void SendToDB(void *ptr,const int nCmdLen)
{
    g_pServerImp->SendCmdToConnect(ptr, nCmdLen, SERVER_TYPE_LOGIN_DATA, 0);

    return;
}

void SendToUdpClient(ClientMsg::Message *message, sockaddr *addr)
{
    g_pUdpServer->SendClientMsg(message, addr);

    return;
}

