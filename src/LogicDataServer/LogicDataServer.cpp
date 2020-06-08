#include "Confile.h"
#include "LogicDataTaskManager.h"
#include "LogicDataLogTaskManager.h"
#include "DelayTimeTick.h"
#include "LogTimeTick.h"
#include "LogicDataService.h"
#include "SqlData.h"
#include "Defs.h"
#include "DelaySaveCmdQueue.h"

/**
 * \brief 
 *
 * \param argc 
 * \param argv 
 * \return 
 */

DelaySaveCmdQueue g_delaySaveDBCmdQueue;
uint32_t g_gmIsOpen = 0;
uint32_t g_serverPort;
CListenTCPServer *g_pListenTcpLogServer = NULL;

bool InitSystemManagers();
bool ClearSystemManagers();

int main(int argc,char **argv)
{

    //eagle::global["LoggerLevel"] = "1";
    //eagle::global["daemon"] = "true";
    //eagle::global["ifname"] = "eth0";
    //eagle::global["LogPath"] = "./log/LogicDataServer/";
    //eagle::global["CmdQueueMax"] = "102400";
    //eagle::global["dataDBName"] = "logicdata";
    //eagle::global["dataDBUser"] = "root";
    //eagle::global["dataDBPasswd"] = "leshu111";
    //eagle::global["dataDBIP"] = "127.0.0.1";
    //eagle::global["dataDBPort"] = "3306";
    //eagle::global["dataLogDBName"] = "logdata";
    //eagle::global["logicdatalistenserver"] = "17077";
    //eagle::global["logiclogdatalistenserver"] = "17078";

#ifdef WIN32
    CConfigFile m_ConfigFile("../../Config/ZoneConfig.xml");
#else 
    CConfigFile m_ConfigFile("./Config/ZoneConfig.xml");
#endif

    if (false == m_ConfigFile.parse("Share"))
        return 0;
    if (false == m_ConfigFile.parse("LogicDataServer"))
        return 0;

    ENUM_LOG_LEVEL level = LOG_LEVEL_DEBUG;//LOG_LEVEL_DEBUG;LOG_LEVEL_TRACE;
    level = (ENUM_LOG_LEVEL)atoi(eagle::global["LoggerLevel"].c_str());
    eagle::g_logger.SetLevel(level);
    eagle::g_logger.SetConsole(true);

    //
    if (strlen(eagle::global["LogPath"].c_str()))
    {        
        eagle::g_logger.SetPath(eagle::global["LogPath"].c_str());
    }

    eagle::g_logger.Init();

    g_gmIsOpen = atoi(eagle::global["GMIsOpen"].c_str());
    g_serverId = atoi(eagle::global["ServerId"].c_str());
    g_serverPort = atoi(eagle::global["LogicDataServerTcpPort"].c_str());
    uint32_t logicLogDataServerTcpPort = atoi(eagle::global["LogicLogDataServerTcpPort"].c_str());
	uint32_t connectCentralServerPort = atoi(eagle::global["ConnectCentralServerPort"].c_str());
    CTaskManager *logServerTaskManager = NULL;

    if (!DataDBConnection::instance()->init(eagle::global["DataDBName"].c_str(), eagle::global["DataDBUser"].c_str(), eagle::global["DataDBPasswd"].c_str(), eagle::global["DataDBIP"].c_str(), atoi(eagle::global["DataDBPort"].c_str())))
    {
        LOGE("LogicDataServer mysql data server DataDBConnection connect error");
        return false;
    }

    //if (!DelayDBConnection::instance()->init(eagle::global["DataDBName"].c_str(), eagle::global["DataDBUser"].c_str(), eagle::global["DataDBPasswd"].c_str(), eagle::global["DataDBIP"].c_str(), atoi(eagle::global["DataDBPort"].c_str())))
    //{
 //       LOGE("LogicDataServer mysql data server DelayDBConnection connect error");
 //       return false;
 //   }

    if(!LogDBConnection::instance()->init(eagle::global["DataLogDBName"].c_str(), eagle::global["DataDBUser"].c_str(), eagle::global["DataDBPasswd"].c_str(), eagle::global["DataDBIP"].c_str(), atoi(eagle::global["DataDBPort"].c_str())))
    {
        LOGE("LogicDataServer mysql log server LogDBConnection connect error");
        return false;
    }

    DataSsqls::init();

    g_pServerImp = new CLogicDataServer(eagle::global["ServerName"].c_str());
    if (!g_pServerImp)
    {
        LOGE("LogicDataServer calling main... new g_pServerImp NULL!!!");
        goto Lable;
    }

	if (!InitSystemManagers())
	{
		LOGE("LogicDataServer calling main... InitSystemManagers ERROR!!!");
		goto Lable;
	}

    g_pServerImp->AddListenServer(new CListenTCPServer(new CLogicDataTaskManager(), "LogicDataServerListenServer", g_serverPort));

    if (!g_pServerImp->Init())
    {
        LOGE("LogicDataServer calling main... g_pServerImp Init Error!!!");
        goto Lable;
    }

    g_pListenTcpLogServer = new CListenTCPServer(new CLogicDataLogTaskManager(), "logicdatalogserver", logicLogDataServerTcpPort);
    logServerTaskManager = g_pListenTcpLogServer->GetTaskManager();
    if (g_pListenTcpLogServer && g_pListenTcpLogServer->Init())
    {
        LOGFMTD("LogicDataServer listenserver  %p", g_pListenTcpLogServer);    
    }
    else
    {
        LOGE("LogicDataServer calling main... g_pListenTcpLogServer NULL");
        goto Lable;
    }

    if (!CDelayTimeTick::instance() || !CDelayTimeTick::instance()->Init())
    {
        LOGE("LogicDataServer calling main... CDelayTimeTick::instance()->Init ERROR");
        goto Lable;
    }

    if (!CLogicDataLogTimeTick::instance() || !CLogicDataLogTimeTick::instance()->Init())
    {
        LOGE("LogicDataServer calling main... CLogicDataLogTimeTick::instance()->Init ERROR");
        goto Lable;
    }

    CDelayTimeTick::instance()->Start();
    CLogicDataLogTimeTick::instance()->Start();
    g_pListenTcpLogServer->Start();

    LOGI("LogicDataServer Run SECCUSS !!!");

    g_pServerImp->Start();
Lable:
    CLogicDataLogTimeTick::instance()->Close();
    CDelayTimeTick::instance()->Close();

    if (g_pServerImp)
    {
        g_pServerImp->Close();
        SAFE_DELETE(g_pServerImp);
    }

    if (g_pListenTcpLogServer)
    {
        g_pListenTcpLogServer->Close();
        SAFE_DELETE(g_pListenTcpLogServer);
    }

    if (logServerTaskManager)
    {
        logServerTaskManager->Close();
        SAFE_DELETE(logServerTaskManager);
    }

    ServerImp()->Close();

    ClearSystemManagers();

    LOGI("LogicDataServer calling main... CLOSE !!!");

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

void SendToLogicServer(void *ptr, const uint32_t nCmdLen)
{
    g_pServerImp->SendCmdToServerTask(ptr, nCmdLen, SERVER_TYPE_LOGIC_SERVER);

    return;
}


