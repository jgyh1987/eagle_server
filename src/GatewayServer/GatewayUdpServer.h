#ifndef _GATEWAYUDPSERVER_H_
#define _GATEWAYUDPSERVER_H_

#include "UdpServer.h"
#include "ClientMsg.h"
#include "./proto/msg_net.pb.h"
#include "./proto/package_net.pb.h"

class CGatewayUdpServer : public CUdpServer
{
public:
    CGatewayUdpServer(const std::string &name, int port, const char* ip = "0.0.0.0", uint32_t onceDoMsgNum = 50000, uint32_t queuesize = 102400)
        :CUdpServer(name, port, ip, onceDoMsgNum, queuesize)
    {
    }

    bool CmdMsgParseImp(void *, const uint32_t, sockaddr *, int mask);

    bool SendClientMsg(ClientMsg::Message *message, sockaddr *addr);
    bool SendClientMsg(::google::protobuf::Message *message, int id, sockaddr *addr, uint32_t mask);

private:

};

#endif
