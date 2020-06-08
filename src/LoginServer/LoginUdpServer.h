#ifndef _LOGINUDPSERVER_H_
#define _LOGINUDPSERVER_H_

#include "UdpServer.h"
#include "ClientMsg.h"

class CLoginUdpServer : public CUdpServer
{
public:
    CLoginUdpServer(const std::string &name, int port, const char* ip = "0.0.0.0", uint32_t queuesize = 102400)
        :CUdpServer(name, port, ip, queuesize)
    {
        m_clientMsgId = 0;
    }

    bool CmdMsgParseImp(void *, const uint32_t, sockaddr *, int mask);

    bool SendClientMsg(ClientMsg::Message *message, sockaddr *addr);

private:
    uint64_t m_clientMsgId;
};

#endif
