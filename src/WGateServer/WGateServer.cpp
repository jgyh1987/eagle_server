#include "WGateServer.h"
#include "Confile.h"
#include "ListenServer.h"
#include "ConnectClient.h"
#include "TimeTick.h"
#include "Defs.h"
#include "WGateService.h"
#include "WGateClientTaskManager.h"
#include "ToolsFun.h"
#include "World.h"
#include "WGateConnectClient.h"

/**
 * \brief 主程序入口
 *
 * \param argc 参数个数
 * \param argv 参数列表
 * \return 运行结果
 */

uint32_t g_serverPort = 0;
uint32_t g_serverUdpPort = 0;

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
    if (false == m_ConfigFile.parse("WGateServer"))
        return 0;

    ENUM_LOG_LEVEL level = LOG_LEVEL_DEBUG;//LOG_LEVEL_DEBUG;LOG_LEVEL_TRACE;
    level = (ENUM_LOG_LEVEL)atoi(eagle::global["LoggerLevel"].c_str());
    eagle::g_logger.SetLevel(level);
    eagle::g_logger.SetConsole(atoi(eagle::global["isConsole"].c_str()) > 0);

    //设置写本地日志文件
    if(strlen(eagle::global["LogPath"].c_str()))
    {        
        eagle::g_logger.SetPath(eagle::global["LogPath"].c_str());
    }

    eagle::g_logger.Init();

    g_serverId = atoi(eagle::global["ServerId"].c_str());
    g_serverPort = atoi(eagle::global["WGateServerTcpPort"].c_str());
    g_serverUdpPort = atoi(eagle::global["WGateServerUdpPort"].c_str());
    uint32_t centralServerPort = atoi(eagle::global["ConnectCentralServerPort"].c_str());

    ////
    g_pServerImp = new CWGateServer(eagle::global["ServerName"].c_str());
    if (!ServerImp())
    {
        LOGE("WGateServer calling main... new g_pServerImp NULL!!!");
        goto Lable;
    }

	InitSystemManagers();

    ServerImp()->AddListenClinetServer(new CListenTCPServer(new CWGateClientTaskManager(), "WGateServerListenTcpServer", g_serverPort));
    ServerImp()->AddConnectClient(new CWGateConnectClient("CCentralConnectClient", SERVER_TYPE_CENTRAL_SERVER, g_serverId, eagle::global["ConnectCentralServerIP"].c_str(), centralServerPort));

    if (!ServerImp()->Init())
    {
        LOGE("WGateServer calling main... g_pServerImp Init Error!!!");
        goto Lable;
    }

    LOGI("WGateServer Run SECCUSS !!!");
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


