#include "WMatchServer.h"
#include "Confile.h"
#include "ConnectClient.h"
#include "TimeTick.h"
#include "Defs.h"
#include "WMatchService.h"
#include "WMatchTaskManager.h"
#include "ToolsFun.h"
#include "World.h"
#include "WMatchManager.h"
#include "CentralConnectClient.h"


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
    if (false == m_ConfigFile.parse("WMatchServer"))
        return 0;

    ENUM_LOG_LEVEL level = LOG_LEVEL_DEBUG;//LOG_LEVEL_DEBUG;LOG_LEVEL_TRACE;
    level = (ENUM_LOG_LEVEL)atoi(eagle::global["LoggerLevel"].c_str());
    eagle::g_logger.SetLevel(level);
    eagle::g_logger.SetConsole(atoi(eagle::global["isConsole"].c_str()) > 0);

    g_serverId = atoi(eagle::global["ServerId"].c_str());

    //
    if(strlen(eagle::global["LogPath"].c_str()))
    {        
        eagle::g_logger.SetPath(eagle::global["LogPath"].c_str());
    }

    eagle::g_logger.Init();
    game::Init(eagle::global["ServerParametersPath"].c_str());
    game::InitGameGlobalParameters();

    g_serverPort = atoi(eagle::global["WMatchServerTcpPort"].c_str());
    uint32_t centralServerPort = atoi(eagle::global["ConnectCentralServerPort"].c_str());

    g_pServerImp = new CWMatchServer(eagle::global["ServerName"].c_str());
    if (!ServerImp())
    {
        LOGE("CWMatchServer calling main... new g_pServerImp NULL!!!");
        goto Lable;
    }

	if (!InitSystemManagers())
	{
		LOGE("CWMatchServer calling main... InitSystemManagers ERROR!!!");
		goto Lable;
	}

    ServerImp()->AddConnectClient(new CCentralConnectClient("CentralConnectClient", eagle::global["ConnectCentralServerIP"].c_str(), centralServerPort));
    ServerImp()->AddListenServer(new CListenTCPServer(new CWMatchTaskManager(), "WMatchServerListenTcpServer", g_serverPort));

    if (!ServerImp()->Init())
    {
        LOGE("CWMatchServer calling main... g_pServerImp Init Error!!!");
        goto Lable;
    }

    LOGI("CWMatchServer Run SECCUSS !!!");
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


    return true;
}

bool ClearSystemManagers()
{

    return true;
}


