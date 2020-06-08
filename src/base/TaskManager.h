#ifndef _TASKMANAGER_H_
#define _TASKMANAGER_H_
/**
* \brief 服务器子连接管理器
*
*/
#include "Sys.h"
#include "Entry.h"
#include "Lock.h"
#include "ConnectTask.h"

namespace eagle
{

typedef std::list<CConnectTask *> recycletaskpool;
typedef std::map<uint32_t, CConnectTask*> activetaskpool;
class CListenTCPServer;

//BEFORE USE NEED CALL SetListenTCPServer
class CTaskManager : private CNoncopyable
{

public:

    /**
    * \brief 回调函数
    *
    */
    typedef CEntryCallback<CConnectTask> TaskCallback;

    CTaskManager();
    virtual ~CTaskManager();

    virtual bool Init();
    virtual bool Close();

    bool UniqueAdd(CConnectTask *task);
    bool UniqueRemove(CConnectTask *task);
    void ExecAll(TaskCallback *callback = NULL);
    //not thread safe
    virtual void UniqueAddExt(CConnectTask *task){}
    virtual void UniqueRemoveExt(CConnectTask *task){}
    
    CConnectTask* AllocConnectTask(CListenTCPServer *);
    void RecycleConnectTask(CConnectTask*);

    void SetListenTCPServer(CListenTCPServer *listenServer);

    virtual void SendMsgSync();

    void Lock();
    void UnLock();

    void SendAll(const void *, const uint32_t);
    
protected:
    virtual CConnectTask* NewTcpTask(CListenTCPServer *);

protected:

    recycletaskpool m_recyclePool;
    activetaskpool    m_activePool;
    CMutex m_mutex;
    CMutex m_recycleMutex;

    CListenTCPServer *m_listenServer;
};

};

#endif

