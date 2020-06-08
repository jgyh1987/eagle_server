#include "Confile.h"
#include "LoginDataTaskManager.h"
#include "LoginDataService.h"
#include "SqlData.h"
#include "Defs.h"
#include "SdkUrlManager.h"
#include "HttpClient.h"
#include "QQSdk.h"

/**
 * \brief 主程序入口
 *
 * \param argc 参数个数
 * \param argv 参数列表
 * \return 运行结果
 */

uint32_t g_serverPort;

bool InitSystemManagers();
bool ClearSystemManagers();

int main(int argc,char **argv)
{

    //eagle::global["LoggerLevel"] = "1";
    //eagle::global["daemon"] = "true";
    //eagle::global["ifname"] = "eth0";
    //eagle::global["LogPath"] = "./log/LoginDataServer/";
    //eagle::global["CmdQueueMax"] = "102400";
    //eagle::global["dataDBName"] = "logindata";
    //eagle::global["dataDBUser"] = "root";
    //eagle::global["dataDBPasswd"] = "leshu111";
    //eagle::global["dataDBIP"] = "127.0.0.1";
    //eagle::global["dataDBPort"] = "3306";
    //eagle::global["logindataserver"] = "17087";

#ifdef WIN32
    CConfigFile m_ConfigFile("../../Config/ZoneConfig.xml");
#else 
    CConfigFile m_ConfigFile("./Config/ZoneConfig.xml");
#endif

    if (false == m_ConfigFile.parse("Share"))
        return 0;
    if (false == m_ConfigFile.parse("LoginDataServer"))
        return 0;

    ENUM_LOG_LEVEL level = LOG_LEVEL_DEBUG;//LOG_LEVEL_DEBUG;LOG_LEVEL_TRACE;
    level = (ENUM_LOG_LEVEL)atoi(eagle::global["LoggerLevel"].c_str());
    eagle::g_logger.SetLevel(level);
    eagle::g_logger.SetConsole(true);

    //设置写本地日志文件
    if (strlen(eagle::global["LogPath"].c_str()))
    {        
        eagle::g_logger.SetPath(eagle::global["LogPath"].c_str());
    }

    eagle::g_logger.Init();

    g_serverId = atoi(eagle::global["ServerId"].c_str());
    g_serverPort = atoi(eagle::global["LoginDataServerTcpPort"].c_str());

    if (!DataDBConnection::instance()->init(eagle::global["DataDBName"].c_str(), eagle::global["DataDBUser"].c_str(), eagle::global["DataDBPasswd"].c_str(), eagle::global["DataDBIP"].c_str(), atoi(eagle::global["DataDBPort"].c_str())))
    {
        LOGE("LoginDataServer mysql data server connect error");
        return false;
    }

        //   if(!LogDBConnection::instance()->init(eagle::global["dataLogDBName"].c_str(), eagle::global["dataDBUser"].c_str(), eagle::global["dataDBPasswd"].c_str(), eagle::global["dataDBIP"].c_str(), atoi(eagle::global["dataDBPort"].c_str())))
        //{
        //       LOGE("mysql log server connect error");
        //       return false;
        //}


    DataSsqls::init();

    g_pServerImp = new CLoginDataServer(eagle::global["ServerName"].c_str());
    if (!g_pServerImp)
    {
        LOGE("LoginDataServer calling main... new g_pServerImp NULL!!!");
        goto Lable;
    }

	if (!InitSystemManagers())
	{
		LOGE("LoginDataServer calling main... InitSystemManagers ERROR!!!");
		goto Lable;
	}

    g_pServerImp->AddListenServer(new CListenTCPServer(new CLoginDataTaskManager(), "LogiNDataServerListenServer", g_serverPort));

    if (!g_pServerImp->Init())
    {
        LOGE("LoginDataServer calling main... g_pServerImp Init Error!!!");
        goto Lable;
    }

    if (!CQQSdkManager::instance() || !CQQSdkManager::instance()->Init())
    {
        LOGE("LoginDataServer calling main... CQQSdkManager::instance()->Init ERROR");
        goto Lable;
    }
    
    CQQSdkManager::instance()->Start();
    LOGI("LoginDataServer Run SECCUSS !!!");

    g_pServerImp->Start();

Lable:
    CQQSdkManager::instance()->Close();

    if (g_pServerImp)
    {
        g_pServerImp->Close();
        SAFE_DELETE(g_pServerImp);
    }

    ClearSystemManagers();

    LOGI("LoginDataServer calling main... CLOSE !!!");

    return EXIT_SUCCESS;
}

bool InitSystemManagers()
{
    CSDKUrlListManager::instance()->Init((char *)eagle::global["LoginServerConfig"].c_str());

    return true;
}

bool ClearSystemManagers()
{

    return true;
}

void SendToLoginServer(void *ptr, const uint32_t nCmdLen)
{
    g_pServerImp->SendCmdToServerTask(ptr, nCmdLen, SERVER_TYPE_LOGIN_SERVER);

    return;
}

