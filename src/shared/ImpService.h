#ifndef _IMPSERVICE_H_
#define _IMPSERVICE_H_

#include "BaseService.h"
#include "ListenServer.h"
#include "ServerConnect.h"
#include "ServerTask.h"

class CImpServer : public CBaseServer
{
public:
    CImpServer(uint32_t serverTypeMax, const std::string &name);
    ~CImpServer();

    bool Init();

    bool Verify();
    bool CallBack();

    //
    bool Start();
    void Close();

//virtual
public:
    virtual void Update(){}
    virtual void UpdateSec(){}
    virtual void Update5Sec(){}
    virtual void UpdateMin(){}
    virtual void Update5Min(){}
    virtual void Update30Min(){}
    virtual void UpdateHour(){}
    virtual void Update24(){}

    virtual void TickLongWarn(uint32_t t);

//not tread safe , only call by this object Update or before Start
public:
    void UpdateListenServer();
    void UpdateConnect();

    uint32_t AddTimeThread(CThread *);

    uint32_t AddListenServer(CListenTCPServer *);
    uint32_t AddListenClinetServer(CListenTCPServer *);
    uint32_t AddServerTask(CServerTask *, bool cover = false);
    uint32_t RemoveServerTask(CServerTask *);
    CServerTask *GetServerTask(uint32_t serverType, uint32_t serverId);
    std::map<uint32_t, CServerTask *> *GetServerTaskByType(uint32_t serverType);
    void SendCmdToServerTask(void *pCmd, uint32_t size, uint32_t serverType, uint32_t serverId = 0);
    
    uint32_t AddConnectClient(CServerConnectClient *, bool isReConnect = true);
    uint32_t DynamicAddConnectClient(CServerConnectClient *, bool isReConnect = true);
    CServerConnectClient *GetConnectClient(uint32_t serverType, uint32_t serverId);
    std::map<uint32_t, CServerConnectClient *> *GetServerConnectByType(uint32_t serverType);
    uint32_t RemoveConnectClient(CServerConnectClient *);
    //serverId 0 notify all of serverType
    void SendCmdToConnect(void *pCmd, uint32_t size, uint32_t serverType, uint32_t serverId = 0);

    inline void Lock()
    {
        m_mImpServerLock.Lock();
    }
    inline void UnLock()
    {
        m_mImpServerLock.UnLock();    
    }
    inline CMutex *GetMutex()
    {
        return &m_mImpServerLock;
    }
    static void SetUpdateTime(uint32_t updateTime)
    {
        m_updateTime = updateTime;
        return;
    }
    inline static uint32_t UpdateTime()
    {
        return m_updateTime;
    }

protected:
    std::vector<CListenTCPServer *> m_listenServers;
    std::vector<CListenTCPServer *> m_listenClientServers;
    std::vector<CThread *> m_timeThreads;
    std::vector< std::map<uint32_t, CServerConnectClient *> > m_connectClients;
    std::vector< std::map<uint32_t, CServerTask *> > m_serverTasks;

    CMutex m_mImpServerLock;                        /// 

    static uint32_t m_updateTime;
};

extern CImpServer *g_pServerImp;
extern uint32_t g_serverId;

#endif

