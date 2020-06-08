#ifndef _LISTENSERVER_H_
#define _LISTENSERVER_H_

#include "Sys.h"
#include "Noncopyable.h"
#include "Thread.h"
#include "ConnectTask.h"
#include "TaskManager.h"

namespace eagle
{

typedef std::list<CConnectTask *> CConnectTaskContainer;
typedef CConnectTaskContainer::iterator CConnectTask_IT;

class CReadyConnectTaskThread;
class CCRecycleConnectTaskThread;
class CRunConnectTaskThread;

class CListenTCPServer :private CNoncopyable , public CThread
{
public:
    static const uint32_t T_MSEC;
    static const uint32_t MAX_WAITQUEUE;


    CListenTCPServer(CTaskManager *ptaskmanager, const std::string &name, int port, const char* ip = "0.0.0.0", int threadNum = 4);
    virtual ~CListenTCPServer();

    bool Init();
    void Run();
    void Final();
    void SendFianl();

    bool UniqueAdd(CConnectTask *task);
    bool UniqueRemove(CConnectTask *task);

    bool AddReady(CConnectTask*task);
    bool AddRun(CConnectTask*task);
    bool AddRecycle(CConnectTask*task);
    void RecycleMalloc(CConnectTask*task);
    void SendAsyncToAllRunThread();

    uv_loop_t* GetLoop();
    uv_async_t* GetAsync_t();

    inline CTaskManager *GetTaskManager(){return m_pTaskManager;}
protected:
    //int Accept(struct sockaddr_in *addr);
    uint32_t GetAvailaClientID();
    inline CThread* GetTaskThreadByID(int id);

    CRunConnectTaskThread *AddNewCRunConnectTaskThread();

protected:
    //static void AfterServerClose(uv_handle_t* handle);
    //static void DeleteTcpHandle(uv_handle_t* handle);//delete handle after close client
    //static void RecycleTcpHandle(uv_handle_t* handle);//recycle handle after close client
    static void AcceptConnection(uv_stream_t* server, int status);
    //static void SubClientClosed(int clientid, void* userdata); //AcceptClient close cb
    static void AsyncCB(uv_async_t* handle);//async 

private:
    void CloseInl();
    bool Bind();
    bool Listen();

private:
    std::string m_strSvrName;
    int m_nPort;
    std::string m_strIP;

    uv_loop_t m_loop;
    uv_tcp_t m_tcp_handle;
    uv_async_t m_async_handle;
    bool m_bIsClosed;
    bool m_bIsUserAskForClosed;
    int m_loopStatus;

    CReadyConnectTaskThread * m_readyThread;
    CCRecycleConnectTaskThread * m_recycleThread;
    CThreadGroup m_taskThreads;
    int m_nThreadsNum;
    CTaskManager *m_pTaskManager;

    uint32_t s_id;
};

class CConnectTaskQueue
{
public:
    CConnectTaskQueue():m_size(0){}
    virtual ~CConnectTaskQueue(){}
    inline void Add(CConnectTask*task);

protected:
    inline void CheckQueue();
    virtual void AddToTasks(CConnectTask*task)=0;
    unsigned int m_size;

    typedef std::deque<CConnectTask *> taskcontainer;
    taskcontainer m_queue;
    taskcontainer m_temp_queue;
    CMutex m_lock;
};

class CConnectTaskThread : public CThread, public CConnectTaskQueue
{
protected:
    CListenTCPServer *m_parentServer;
    CConnectTaskContainer m_tasks;
    CConnectTaskContainer::size_type m_taskCount;
    CMutex m_mutexSendAsync;

    virtual void AddToTasks(CConnectTask* task);    

public:
    //CConnectTaskContainer::size_type connPerThread;
    CConnectTaskThread(CListenTCPServer *parentServer, const std::string &name=std::string("CConnectTaskThread"))
        :CThread(name), m_parentServer(parentServer)
    {

    }
    virtual ~CConnectTaskThread()
    {
        
    }

    virtual void Remove(CConnectTask* task);
    virtual void Remove(CConnectTask_IT it);

    const CConnectTaskContainer::size_type size() const 
    {
        return m_taskCount + m_size;
    }
};

//CRunConnectTaskThread
class CRunConnectTaskThread : public CConnectTaskThread
{
private:    
    uv_loop_t m_loop;
    int m_loopStatus;
    uv_async_t m_async_handle;
    CMutex m_tcpSocksMutex;
    std::list<uv_tcp_t *> m_tcpSocks;
    bool m_bIsClosed;
    bool m_bIsUserAskForClosed;

public:
    CRunConnectTaskThread(CListenTCPServer *parentServer, const std::string &name=std::string("CRunConnectTaskThread"));
    ~CRunConnectTaskThread()
    {
        CloseInl();
        uv_loop_close(&m_loop);
    }

    bool Init();
    void Run();
    void Final();
    void SendFianl();
    void AddToTasks(CConnectTask* task);

    void SendAsync();
    uv_tcp_t* GetTcpSock();
    uv_async_t* GetAsync_t();

public:
    static void AsyncCB(uv_async_t* handle);//async 

protected:
    void CloseInl();

};

};

#endif

