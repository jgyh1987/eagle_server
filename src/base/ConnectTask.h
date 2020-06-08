#ifndef _CONNECTTASK_H_
#define _CONNECTTASK_H_

#include "Sys.h"
#include "Noncopyable.h"
#include "Eagle_Time.h"
#include "CmdQueue.h"
#include "SockStream.h"

namespace eagle
{

class CListenTCPServer;
class CRunConnectTaskThread;

enum CONNECT_TASK_CLOSE_STATUS
{
    CONNECT_TASK_CLOSE_STATUS_NONE = 0,
    CONNECT_TASK_CLOSE_STATUS_NEED_CLOSE = 1,
    CONNECT_TASK_CLOSE_STATUS_CLOSEING = 2,
    CONNECT_TASK_CLOSE_STATUS_CLOSED = 3,
};

/* 
 *  \brief 定义一个任务类，是连接线程池的工作单元
 * */
class CConnectTask: private CNoncopyable, public CConCmdQueue
{
public:
    enum TerminateMethod
    {
        terminate_no,           // 没有结束任务
        terminate_active,       // 客户端主动断开连接，主要是由于服务器端检测到套接口关闭或者套接口异常
        terminate_passive,      // 服务器端主动断开连接
    };

    CConnectTask(CListenTCPServer *, uint32_t onceDoMsgNum = 500, uint32_t queuesize = 102400, CSockStream *stream = new CSockStream());
    virtual ~CConnectTask();

    inline uv_tcp_t* TcpHandle()
    {
        return m_tcpHandle;
    }
    inline void SetTcpHandle(uv_tcp_t *tcpHandle)
    {
        m_tcpHandle = tcpHandle;
        return;
    }

    void SetClientID(uint32_t clientid)
    {
        m_nClientID = clientid;
        
        return;
    }
    uint32_t GetClientID()
    {
        return m_nClientID;
    }

    void SetRunTaskThread(CRunConnectTaskThread *);
    CRunConnectTaskThread * GetRunTaskThread()
    {
        return m_taskServer;
    }

    void SetCListenTCPServer(CListenTCPServer *listenServer)
    {
        m_listenServer = listenServer;
        m_nIsClosed = CONNECT_TASK_CLOSE_STATUS_NONE;
        
        return ;
    }

    inline CSockStream* GetStream();

    bool cmdMsgParse(void *,const uint32_t){return true;}

    virtual bool SendCmd(const void *, uint32_t);
    virtual bool ListeningRecv(const unsigned char*, ssize_t);
    virtual bool ListeningSend();

    bool Close(bool bRemove = false);
    void SetNeedClose()
    {
        if (CONNECT_TASK_CLOSE_STATUS_NONE == m_nIsClosed)
            m_nIsClosed = CONNECT_TASK_CLOSE_STATUS_NEED_CLOSE;
    }
    int CloseStatus(){return m_nIsClosed;}
    virtual void Clear();

    static void AfterClientClose(uv_handle_t* handle);
    static void AllocBufferForRecv(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
    static void AfterRecv(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf);
    static void AfterSend(uv_write_t* req, int status);
protected:
    CMutex m_tcp_mutex;
    CSockStream *m_stream;
    uv_tcp_t *m_tcpHandle;
    buffercmdqueue m_recvBuffer;

    CRunConnectTaskThread* m_taskServer;//connect task server
    CListenTCPServer *m_listenServer;
    uint32_t m_nClientID;

    int m_nIsClosed;
    volatile bool m_buffered;
};

class CClientConnectTask : public CConnectTask
{
public:
    CClientConnectTask(CListenTCPServer *listenServer, uint32_t onceDoMsgNum = 500, uint32_t queuesize = 1024)
        :CConnectTask(listenServer, queuesize)
    {
    }

    bool SendCmd(const void *, uint32_t);
    bool ListeningRecv(const unsigned char*, ssize_t);

};

class CWebSockConnectTask : public CConnectTask
{
public:
    CWebSockConnectTask(CListenTCPServer *listenServer, uint32_t onceDoMsgNum = 500, uint32_t queuesize = 1024)
        :CConnectTask(listenServer, queuesize)
    {
        m_isUpgrade = false;
    }

    virtual bool SendCmd(const void *, uint32_t);
    virtual bool ListeningRecv(const unsigned char*, ssize_t);
    virtual void Clear();

    virtual void UpgradeHttp(char*);
    inline void UpdateHttpToWS() { m_isUpgrade = true; }

    static void UpgradeWSAfterSend(uv_write_t* req, int status);


private:
    bool m_isUpgrade;

};



};

#endif
