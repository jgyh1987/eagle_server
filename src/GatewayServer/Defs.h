//该文件不能被include在.H 文件中
#ifndef _DEFS_H_
#define _DEFS_H_

#include "Misc.h"
#include "Logger.h"
#include "Global.h"

namespace ClientMsg
{
    struct Message;
};

class CGatewayUdpServer;
extern CGatewayUdpServer *g_pUdpServer;
extern uint32_t g_serverPort;
extern uint32_t g_delayTime;

void SendToLogicServer(void *ptr, const uint32_t nCmdLen);
void SendToGameServer(void* ptr, const uint32_t nCmdLen, uint32_t serverid);
void UdpSendToClient(ClientMsg::Message *message, sockaddr *addr);
void SendToLoginServer(void *ptr, const uint32_t nCmdLen);

#endif

