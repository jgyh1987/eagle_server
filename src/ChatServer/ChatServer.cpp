#include "ChatServer.h"
#include "Confile.h"
#include "ChatServerTaskManager.h"
#include "ChatClientTaskManager.h"
#include "ChatService.h"
#include "Defs.h"

/**
 * \brief 主程序入口
 *
 * \param argc 参数个数
 * \param argv 参数列表
 * \return 运行结果
 */

uint32_t g_serverId = 0;
uint32_t g_serverPort = 18057;

bool InitSystemManagers();
bool ClearSystemManagers();

int main(int argc,char **argv)
{

	//eagle::global["LoggerLevel"] = "1";
	//eagle::global["daemon"] = "true";
	//eagle::global["ifname"] = "eth0";
	//eagle::global["LogPath"] = "./log/ChatServer/";
	//eagle::global["CmdQueueMax"] = "102400";
	//eagle::global["chatserverTcpServer"] = "18057";
	//eagle::global["chatclientTcpServer"] = "18058";

	CConfigFile m_ConfigFile("./Config/ZoneConfig.xml");
	if (false == m_ConfigFile.parse("Share"))
	    return 0;
	if (false == m_ConfigFile.parse("ChatServer"))
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
	g_serverPort = atoi(eagle::global["ChatServerTcpPort"].c_str());
	uint32_t clientTcpPort = atoi(eagle::global["ChatClientTcpPort"].c_str());

	if (!InitSystemManagers())
	{
		LOGE("ChatServer calling main... InitSystemManagers ERROR!!!");
		goto Lable;
	}

	g_pServerImp = new CChatServer(eagle::global["ServerName"].c_str());
	if (!g_pServerImp)
	{
		LOGE("ChatServer calling main... new g_pServerImp NULL!!!");
		goto Lable;
	}

	g_pServerImp->AddListenServer(new CListenTCPServer(new CChatServerTaskManager(), "ChatServerListenServer", g_serverPort));
	g_pServerImp->AddListenClinetServer(new CListenTCPServer(new CChatClientTaskManager(), "ChatServerListenClient", clientTcpPort));


	if (!g_pServerImp->Init())
	{
		LOGE("ChatServer calling main... g_pServerImp Init Error!!!");
		goto Lable;
	}

	LOGI("ChatServer Run SECCUSS !!!");
	g_pServerImp->Start();

Lable:
	if (g_pServerImp)
	{
		g_pServerImp->Close();
		SAFE_DELETE(g_pServerImp);
	}

	ClearSystemManagers();

	LOGI("ChatServer calling main... CLOSE !!!");

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


