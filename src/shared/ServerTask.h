#ifndef _SERVERTASK_H_
#define _SERVERTASK_H_

#include "ConnectTask.h"
#include "NullCmd.h"

enum SERVER_RETURN_TYPE
{
    SERVER_REPEAT_REGIST = 2,    //服务器重复注册
    SERVER_TYPE_ERROR = 3,        //服务器类型错误
    SERVER_INIT_ERROR = 4,        //服务器初始化错误
    SERVER_TASK_NOT_HAVE = 5,        //服务器连接不存在
};

class CServerTask : public CConnectTask
{
public:
    CServerTask(CListenTCPServer *listenServer)
        :CConnectTask(listenServer)
    {
    }

    ~CServerTask();

    void Clear();
	void UpdateServerInfo(Cmd::ServerInfo *info);

//tools fun
public:
    inline uint32_t GetServerType(){return m_serverInfo.serverType;}
    inline uint32_t GetServerId(){return m_serverInfo.serverId;}
    inline uint32_t GetServerPort(){return m_serverInfo.port;}
    inline const char *GetServerIp(){return m_serverInfo.serverIP;}
    inline const char *GetServerName(){return m_serverInfo.serverName;}
    inline Cmd::ServerInfo *GetServerInfo(){return &m_serverInfo;}

protected:
    Cmd::ServerInfo m_serverInfo;
};

#endif
