#ifndef _SERVERCONNECT_H_
#define _SERVERCONNECT_H_

#include "ConnectClient.h"

class CServerConnectClient : public CConnectClient
{
public:
    CServerConnectClient(const std::string &name, const uint32_t serverType, const uint32_t serverId, const std::string &ip = "127.0.0.1",const unsigned short port = 44444, uint32_t queuesize = 102400)
        :CConnectClient(name, ip, port, queuesize)
    {
        GetServerType() = serverType;
        GetServerId() = serverId;

        m_isInit = false;
    }

    void CallBackConnectSuccess();
    void CallBackConnectError();
    inline bool IsInit() { return m_isInit; }

protected:
    virtual void CallBackConnectSuccessImp() = 0;
    virtual void CallBackConnectErrorImp() = 0;

    bool m_isInit;
};

#endif
