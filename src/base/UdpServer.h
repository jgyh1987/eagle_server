#ifndef _UDPSERVER_H_
#define _UDPSERVER_H_

#include "Sys.h"
#include "Noncopyable.h"
#include "Thread.h"
#include "CmdQueue.h"
#include "SockStream.h"

namespace eagle
{

class CUdpServer : private CNoncopyable, public CConCmdQueue, public CThread
{
public:
    static const uint32_t T_MSEC;
    static const uint32_t MAX_WAITQUEUE;


    CUdpServer(const std::string &name, int port, const char* ip = "0.0.0.0", uint32_t onceDoMsgNum = 5000, uint32_t queuesize = 102400, CSockStream *stream = new CSockStream);
    virtual ~CUdpServer();

    bool Init();
    void Run();
    void Final();
    void SendFianl();
    bool doCmd();
    bool cmdMsgParse(void *, const uint32_t);
    //具体消息处理函数
    virtual bool CmdMsgParseImp(void *, const uint32_t, sockaddr*, int mask) = 0;

    bool SendCmd(const void *, uint32_t, struct sockaddr* addr, int mask);


private:
    void CloseInl();
    bool ListeningRecv(const unsigned char* ptr, ssize_t nCmdLen, const struct sockaddr* addr);
    bool ListeningSend();
    void UnAllocBufferForRecv(uv_buf_t* buf);

private:
    std::string m_strSvrName;
    int m_nPort;
    std::string m_strIP;
    int m_loopStatus;
    bool m_bIsClosed;

    uv_loop_t m_loop;
    uv_udp_t m_udp_handle;
    uv_async_t m_async_handle;

    CSockStream *m_stream;
    buffercmdqueue m_recvBuffer;

    uint32_t m_msgNum;
    uint32_t m_sendNum;

    bool m_bIsUserAskForClosed;

public:
    static void AllocBufferForRecv(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
    static void AfterRecv(uv_udp_t* handle, ssize_t nread, const uv_buf_t* buf, const struct sockaddr* addr, unsigned flags);
    static void AsyncCB(uv_async_t* handle);//async 
};

};

#endif

