#include "WGameServer.h"
#include "Confile.h"
#include "ListenServer.h"
#include "ConnectClient.h"
#include "TimeTick.h"
#include "Defs.h"
#include "WGameService.h"
#include "WGameTaskManager.h"
#include "ToolsFun.h"
#include "World.h"
#include "WGameConnectClient.h"

/**
 * \brief 主程序入口
 *
 * \param argc 参数个数
 * \param argv 参数列表
 * \return 运行结果
 */

uint32_t g_serverPort = 0;

bool InitSystemManagers();
bool ClearSystemManagers();

int main(int argc,char **argv)
{
    //IgnoreSigPipe();

    //eagle::global["LoggerLevel"] = "1";
    //eagle::global["daemon"] = "true";
    //eagle::global["ifname"] = "eth0";
    //eagle::global["LogPath"] = "./log/ShareServer/";
    //eagle::global["CmdQueueMax"] = "102400";
    //eagle::global["chatserverTcpServer"] = "18057";
    //eagle::global["chatclientTcpServer"] = "18058";

#ifdef WIN32
    CConfigFile m_ConfigFile("../../Config/ZoneConfig.xml");
#else 
    CConfigFile m_ConfigFile("./Config/ZoneConfig.xml");
#endif

    if (false == m_ConfigFile.parse("Share"))
        return 0; 
    if (false == m_ConfigFile.parse("WGameServer"))
        return 0;

    ENUM_LOG_LEVEL level = LOG_LEVEL_DEBUG;//LOG_LEVEL_DEBUG;LOG_LEVEL_TRACE;
    level = (ENUM_LOG_LEVEL)atoi(eagle::global["LoggerLevel"].c_str());
    eagle::g_logger.SetLevel(level);
    eagle::g_logger.SetConsole(atoi(eagle::global["isConsole"].c_str()) > 0);

    g_serverId = atoi(eagle::global["ServerId"].c_str());
	g_gameServerId = eagle::global.GetInt("GameServerId");

    //
    if(strlen(eagle::global["LogPath"].c_str()))
    {        
        eagle::g_logger.SetPath(eagle::global["LogPath"].c_str());
    }

    eagle::g_logger.Init();

	game::Init(eagle::global["ServerParametersPath"].c_str());
	game::InitGameGlobalParameters();

    g_serverPort = atoi(eagle::global["WGameServerTcpPort"].c_str());
    uint32_t connectCentralServerPort = atoi(eagle::global["ConnectCentralServerPort"].c_str());

    ////
    g_pServerImp = new CWGameServer(eagle::global["ServerName"].c_str());
    if (!ServerImp())
    {
        LOGE("WGameServer calling main... new g_pServerImp NULL!!!");
        goto Lable;
    }

	InitSystemManagers();

	ServerImp()->UseDungeon(eagle::global.GetInt("UseDungeon") == 1);
    ServerImp()->AddListenServer(new CListenTCPServer(new CWGameTaskManager(), "WGameServerListenTcpServer", g_serverPort));
    ServerImp()->AddConnectClient(new CWGameConnectClient("CWGameConnectCentralClient", SERVER_TYPE_CENTRAL_SERVER, g_serverId, eagle::global["ConnectCentralServerIP"].c_str(), connectCentralServerPort));

    if (!ServerImp()->Init())
    {
        LOGE("WGameServer calling main... g_pServerImp Init Error!!!");
        goto Lable;
    }

    LOGI("WGameServer Run SECCUSS !!!");
    ServerImp()->Start();

Lable:
    if (ServerImp())
    {
        ServerImp()->Close();
        SAFE_DELETE(g_pServerImp);
    }

    ClearSystemManagers();

    LOGD("calling main... CLOSE");

    return EXIT_SUCCESS;
}

bool InitSystemManagers()
{
    if (!World::instance()->Init())
    {
        return false;
    }

    return true;
}

bool ClearSystemManagers()
{

    return true;
}

void SendToDB(void* ptr, const int nCmdLen, uint32_t dbserverId)
{
	ServerImp()->ProxySendCmd(ptr, nCmdLen, SERVER_TYPE_LOGIC_DATA, dbserverId);

	return;
}


