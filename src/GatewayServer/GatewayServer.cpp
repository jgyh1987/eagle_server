#include "GatewayServer.h"
#include "Confile.h"
#include "GatewayTaskManager.h"
#include "TimeTick.h"
#include "GatewayUdpServer.h"
#include "GatewayService.h"
#include "GatewayConnectClient.h"
#include "Defs.h"
#include "parameters.h"
#include "ImpService.h"
#include "LogicDataManager.h"
#include "GatewayWSTaskManager.h"
#include "GameBaseTask.h"
#include "GatewayPlayer.h"

/**
 * \brief 主程序入口
 *
 * \param argc 参数个数
 * \param argv 参数列表
 * \return 运行结果
 */

CGatewayUdpServer *g_pUdpServer = NULL;
uint32_t g_serverPort;
uint32_t g_delayTime;

bool InitSystemManagers();
bool ClearSystemManagers();
int UdpOutput(const char* buf, int len, ikcpcb* kcp, void* user);

int main(int argc,char **argv)
{

    //eagle::global["LoggerLevel"] = "1";
    //eagle::global["daemon"] = "true";
    //eagle::global["ifname"] = "eth0";
    //eagle::global["LogPath"] = "./log/GatewayServer/";
    //eagle::global["CmdQueueMax"] = "1024";
    //eagle::global["ServerName"] = "eagle";
    //eagle::global["gatelistenserver"] = "18067";
    //eagle::global["gatelistenUdpserver"] = "18068";
    //eagle::global["connectlogicserverPort"] = "18077";
    //eagle::global["connectlogicserverIP"] = "127.0.0.1";
    //eagle::global["connectloginserverPort"] = "18087";
    //eagle::global["connectloginserverIP"] = "127.0.0.1";
    //eagle::global["connectchatserverPort"] = "18057";
    //eagle::global["connectchatserverIP"] = "127.0.0.1";
    //eagle::global["connectPTserverPort"] = "7777";
    //eagle::global["connectPTserverIP"] = "192.168.1.209";

	KcpPlayer::m_udpOutPut = UdpOutput;

#ifdef WIN32
    CConfigFile m_ConfigFile("../../Config/ZoneConfig.xml");
#else 
    CConfigFile m_ConfigFile("./Config/ZoneConfig.xml");
#endif

    if (false == m_ConfigFile.parse("Share"))
        return 0;
    if (false == m_ConfigFile.parse("GateServer"))
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

    game::Init(eagle::global["ServerParametersPath"].c_str());

    g_serverId = atoi(eagle::global["ServerId"].c_str());
    g_serverPort = atoi(eagle::global["GateServerTcpPort"].c_str());
    g_gameServerId = atoi(eagle::global["GameServerId"].c_str());
    g_delayTime = (uint32_t)game::paramNumbers["ServerUpdateDelay"];
    uint32_t connectLogicServerPort = atoi(eagle::global["ConnectLogicServerPort"].c_str());
    uint32_t connectLoginServerPort = atoi(eagle::global["ConnectLoginServerPort"].c_str());
    uint32_t gateServerUdpPort = atoi(eagle::global["GateServerUdpPort"].c_str());
	uint32_t connectCentralServerPort = atoi(eagle::global["ConnectCentralServerPort"].c_str());

    g_pServerImp = new CGatewayServer(eagle::global["ServerName"].c_str());
    if (!g_pServerImp)
    {
        LOGE("GateServer calling main... new g_pServerImp NULL!!!");
        goto Lable;
    }

	if (!InitSystemManagers())
	{
		LOGE("GateServer calling main... InitSystemManagers ERROR!!!");
		goto Lable;
	}

    g_pServerImp->AddListenClinetServer(new CListenTCPServer(new GatewayTaskManager(), "GateServerListenClient", g_serverPort));
    g_pServerImp->AddListenClinetServer(new CListenTCPServer(new GatewayWSTaskManager(), "GateServerListenWSClient", 1314));
    g_pServerImp->AddConnectClient(new CGatewayConnectClient(SERVER_TYPE_LOGIC_SERVER, g_serverId, "GateServerConnectLogicServer", eagle::global["ConnectLogicServerIP"].c_str(), connectLogicServerPort));
    g_pServerImp->AddConnectClient(new CGatewayConnectClient(SERVER_TYPE_LOGIN_SERVER, 0, "GateServerConnectLoginServer", eagle::global["ConnectLoginServerIP"].c_str(), connectLoginServerPort));
	g_pServerImp->AddConnectClient(new CGatewayConnectClient(SERVER_TYPE_CENTRAL_SERVER, g_serverId, "CWGameConnectCentralClient", eagle::global["ConnectCentralServerIP"].c_str(), connectCentralServerPort));

    g_pUdpServer = new CGatewayUdpServer("GatewayUdpServer", gateServerUdpPort);
    if (g_pUdpServer && g_pUdpServer->Init())
    {
        LOGFMTD("GatewayServer CGatewayUdpServer  %p", g_pUdpServer);    
    }
    else
    {
        LOGE("GatewayServer calling main... CGatewayUdpServer NULL");
        goto Lable;
    }
        
    if (!g_pServerImp->Init())
    {
        LOGE("GatewayServer calling main... g_pServerImp Init Error!!!");
        goto Lable;
    }

    g_pUdpServer->Start();

    LOGI("GatewayServer Run SECCUSS !!!");
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

    LOGI("GatewayServer calling main... CLOSE");

    return EXIT_SUCCESS;
}

bool InitSystemManagers()
{
    //if (!LogicDataManager::instance()->Init(eagle::global["ConfigPath"]))
    //    return false;

    //if (!SceneManager::instance()->Init(0))
    //    return false;

    //InitPlayer();

    return true;
}

bool ClearSystemManagers()
{

    return true;
}

void SendToLogicServer(void *ptr, const uint32_t nCmdLen)
{
    g_pServerImp->SendCmdToConnect(ptr, nCmdLen, SERVER_TYPE_LOGIC_SERVER);

    return;
}

void SendToGameServer(void* ptr, const uint32_t nCmdLen, uint32_t serverid)
{
	g_pServerImp->SendCmdToConnect(ptr, nCmdLen, SERVER_TYPE_WGAME_SERVER, serverid);

	return;
}

void UdpSendToClient(ClientMsg::Message *message, sockaddr *addr)
{
    g_pUdpServer->SendClientMsg(message, addr);

    return;
}

void SendToLoginServer(void *ptr, const uint32_t nCmdLen)
{
    g_pServerImp->SendCmdToConnect(ptr, nCmdLen, SERVER_TYPE_LOGIN_SERVER);

    return;
}

int UdpOutput(const char* buf, int len, ikcpcb* kcp, void* user)
{
	GatewayPlayer* player = (GatewayPlayer*)user;
	g_pUdpServer->SendCmd(buf, len, player->GetUdpAddr(), player->GetKcpId());

	LOGD("UdpOutput name = " << player->Account() << " mask = " << player->GetKcpId());

	//for (uint32_t i = 0; i < len; ++i)
	//{
	//    uint8_t a = buf[i];
	//    LOGD((uint32_t)a);
	//}

	return 0;
}

