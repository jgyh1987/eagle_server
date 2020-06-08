#ifndef _CConnectClient_H_
#define _CConnectClient_H_

#include "Sys.h"
#include "Thread.h"
#include "CmdQueue.h"
#include "SockStream.h"
#include "Noncopyable.h"
#include "NullCmd.h"

namespace eagle
{
/* 
 *  \brief TCP客户端
 * 
 *  封装了一些TCP客户端的逻辑，比如建立连接等等，在实际应用中，需要派生这个类，并重载解析指令的函数msgParse
 * */
class CConnectClient : public CThread, public CConCmdQueue, private CNoncopyable
{
    public:
        /* 
         * \brief 构造函数，创建实例对象，初始化对象成员
         * \param name 名称
         * \param ip 地址
         * \param port 端口
         * \param compress 底层数据传输是否支持压缩
         * */
        CConnectClient(const std::string &name,const std::string &ip="127.0.0.1",const unsigned short port=80, uint32_t onceDoMsgNum = 500, uint32_t queuesize = 102400, CSockStream *stream = new CSockStream, const bool compress = false);

        virtual ~CConnectClient()
        {
            CloseInl();
            uv_loop_close(&m_loop);
        }

        bool Init();
        void Run();
        void Final();
        void SendFianl();

        bool Connect();
        bool Connect(const char *ip,const unsigned short port);
        bool StartReconnect();
        void StopReconnect();
        inline bool SetStartReconnect(){return StartReconnect();}
        inline uint32_t &GetServerType(){return m_serverInfo.serverType;}
        inline uint32_t &GetServerId(){return m_serverInfo.serverId;}
        inline uint32_t &GetServerPort(){return m_serverInfo.port;}
        inline char *GetServerIp(){return m_serverInfo.serverIP;}
        inline char *GetServerName(){return m_serverInfo.serverName;}
        inline Cmd::ServerInfo *GetServerInfo(){return &m_serverInfo;}

        /*
         * \brief 消息发送
         * */
        virtual bool SendCmd(const void *pstrCmd,const int nCmdLen);

        const unsigned int GetBufferSize()const; 

        bool doCmd();
        bool cmdMsgParse(void *,const uint32_t);

        // after connect success callback
        virtual void CallBackConnectSuccess(){}
        virtual void CallBackConnectError(){}
protected:
        virtual bool ListeningRecv(const unsigned char*, ssize_t);
        virtual bool ListeningSend();

private:
        virtual void CloseInl();

protected:
    enum
    {
        CONNECT_TIMEOUT,
        CONNECT_FINISH,
        CONNECT_ERROR,
        CONNECT_DIS,
    };

        uv_loop_t m_loop;
        uv_tcp_t *m_tcp_handle;
        uv_timer_t m_reconnect_timer;
        uv_async_t m_async_handle;
        uv_connect_t m_connect_req;

        CSockStream *m_stream;
        buffercmdqueue m_recvBuffer;

        Cmd::ServerInfo m_serverInfo;
        int64_t m_repeat_time;

        const bool m_bCompress;
        bool m_bIsClosed;
        bool m_bIsReconnect;
        uint32_t m_connectStatus;
        int m_loopStatus;
        volatile bool m_buffered;
        bool m_bIsUserAskForClosed;

public:
    static void AsyncCloseCB(uv_async_t* handle);//async close
    static void AfterConnect(uv_connect_t* handle, int status);
    static void ReconnectTimer(uv_timer_t* handle);
    static void AllocBufferForRecv(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
    static void AfterRecv(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf);
    static void AfterConnectClinetSend(uv_write_t* req, int status);
};

/* 
 *  \brief 带缓冲的TCP客户端连接
 * 
 * */
class CConnectBufferClient : public CConnectClient
{
    public:
        CConnectBufferClient(const std::string &name,const std::string &ip="127.0.0.1",const unsigned short port=80, uint32_t onceDoMsgNum = 500,const bool compress=false, const unsigned long usleep_time=50000L)
            :CConnectClient(name,ip,port,compress)
        {
            m_buffered = true;
            m_uSleepTime = 0;
        }
        void Close();

        void Run();
        void SetUsleepTime(const unsigned long utime);

protected:
        bool ListeningSend();
        void Sync();
        unsigned long m_uSleepTime;
};

};

#endif

