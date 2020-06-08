#include "LogicServer.h"
#include "Confile.h"
#include "LogicTaskManager.h"
#include "LogicService.h"
#include "DBConnectClient.h"
#include "LogDBConnectClient.h"
#include "Defs.h"
#include "parameters.h"
#include "TimeTick.h"
#include "LogicConnectClient.h"

/**
 * \brief 
 *
 * \param argc 
 * \param argv 
 * \return 
 */

uint32_t g_serverPort;
uint32_t g_connectLogicDataServerPort;
uint32_t g_connectLogDataServerPort;

bool InitSystemManagers();
bool ClearSystemManagers();

int main(int argc,char **argv)
{

    //eagle::global["LoggerLevel"] = "1";
    //eagle::global["daemon"] = "true";
    //eagle::global["ifname"] = "eth0";
    //eagle::global["LogPath"] = "./log/LogicServer/";
    //eagle::global["CmdQueueMax"] = "102400";
    //eagle::global["ServerName"] = "eagle";
    //eagle::global["ConfigPath"] = "./Config/";
    //eagle::global["LuaInit"] = "./LuaScript/Init.lua";
    //eagle::global["ServerParametersPath"] = "./Config/GameServerParameters.xml";
    //eagle::global["ConfigPath"] = "../../Config/";
    //eagle::global["LuaInit"] = "../../LuaScript/Init.lua";
    //eagle::global["ServerParametersPath"] = "../../Config/GameServerParameters.xml";
    //eagle::global["connectlogicdataserverPort"] = "17077";
    //eagle::global["connectlogicdataserverIP"] = "127.0.0.1";
    //eagle::global["connectlogiclogdataserverPort"] = "17078";
    //eagle::global["connectlogiclogdataserverIP"] = "127.0.0.1";
    //eagle::global["logiclistenserver"] = "18077";

#ifdef WIN32
    CConfigFile m_ConfigFile("../../Config/ZoneConfig.xml");
#else 
    CConfigFile m_ConfigFile("./Config/ZoneConfig.xml");
#endif

    if(false==m_ConfigFile.parse("Share"))
        return 0;
    if(false==m_ConfigFile.parse("LogicServer"))
        return 0;

    ENUM_LOG_LEVEL level = LOG_LEVEL_DEBUG;//LOG_LEVEL_DEBUG;LOG_LEVEL_TRACE;
    level = (ENUM_LOG_LEVEL)atoi(eagle::global["LoggerLevel"].c_str());
    eagle::g_logger.SetLevel(level);
    eagle::g_logger.SetConsole(true);

    //
    if(strlen(eagle::global["LogPath"].c_str()))
    {        
        eagle::g_logger.SetPath(eagle::global["LogPath"].c_str());
    }

    eagle::g_logger.Init();

    game::Init(eagle::global["ServerParametersPath"].c_str());
    game::InitGameGlobalParameters();

    g_serverId = atoi(eagle::global["ServerId"].c_str());
    g_serverPort = atoi(eagle::global["LogicServerTcpPort"].c_str());
    g_gameServerId = atoi(eagle::global["GameServerId"].c_str());
    g_connectLogicDataServerPort = atoi(eagle::global["ConnectLogicDataServerPort"].c_str());
    g_connectLogDataServerPort = atoi(eagle::global["ConnectLogicLogDataServerPort"].c_str());
    uint32_t connectProxyServerPort = atoi(eagle::global["ConnectProxyServerPort"].c_str());

    g_pServerImp = new CLogicServer(eagle::global["ServerName"].c_str());
    if (!g_pServerImp)
    {
        LOGE("LogicServer calling main... new g_pServerImp NULL!!!");
        goto Lable;
    }

	if (!InitSystemManagers())
	{
		LOGE("LogicServer calling main... InitSystemManagers ERROR!!!");
		goto Lable;
	}

    g_pServerImp->AddListenServer(new CListenTCPServer(new LogicTaskManager(), "LogicServerListenServer", g_serverPort));
    g_pServerImp->AddConnectClient(new CDBConnectClient("LogicServerConnectDBServer", eagle::global["ConnectLogicDataServerIP"].c_str(), g_connectLogicDataServerPort), false);
    g_pServerImp->AddConnectClient(new CLogDBConnectClient("LogicServerConnectDBLogServer", eagle::global["ConnectLogicLogDataServerIP"].c_str(), g_connectLogDataServerPort), false);
    g_pServerImp->AddConnectClient(new CLogicConnectClient("LogicServerConnectProxyServer", SERVER_TYPE_PROXY_SERVER, g_serverId, eagle::global["ConnectProxyServerIP"].c_str(), connectProxyServerPort), true);

    if (!g_pServerImp->Init())
    {
        LOGE("LogicServer calling main... g_pServerImp Init Error!!!");
        goto Lable;
    }

    LOGI("LogicServer Run SECCUSS !!!");
    g_pServerImp->Start();

Lable:
    if (g_pServerImp)
    {
        g_pServerImp->Close();
        SAFE_DELETE(g_pServerImp);
    }

    ClearSystemManagers();

    LOGI("LogicServer calling main... CLOSE !!!");

    return EXIT_SUCCESS;
}

bool InitSystemManagers()
{
    CImpServerTimeTick::instance()->SetDelayTime((uint64_t)game::paramNumbers["ServerUpdateDelay"]);

    return World::instance()->Init();
}

//
bool ClearSystemManagers()
{
    
    World::instance()->Clear();

    return true;
}

void SendToDB(void *ptr,const int nCmdLen)
{
    g_pServerImp->SendCmdToConnect(ptr, nCmdLen, SERVER_TYPE_LOGIC_DATA);

    return;
}

void SendToLogDB(void *ptr,const int nCmdLen)
{
    g_pServerImp->SendCmdToConnect(ptr, nCmdLen, SERVER_TYPE_LOG_DATA);

    return;
}

void SendToGateway(void *ptr,const int nCmdLen)
{
    g_pServerImp->SendCmdToServerTask(ptr, nCmdLen, SERVER_TYPE_LOGIC_GATEWAY);

    return;
}

void SendToFriendGuild(void *ptr, const int nCmdLen)
{
    g_pServerImp->SendCmdToConnect(ptr, nCmdLen, SERVER_TYPE_FRIENDGUILD_SERVER);

    return;
}


