//该文件不能被include在.H 文件中
#ifndef _DEFS_H_
#define _DEFS_H_

#include "Misc.h"
#include "Logger.h"
#include "Global.h"
#include "CommonType.h"

#define LOGINSERVER_CONNECT_MAXTIME 30000

extern char g_sdkstr[SDK_TYPE_MAX][MAX_ACCOUNT_LENGHT];

namespace ClientMsg
{
    struct Message;
};

void SendToDB(void *ptr,const int nCmdLen);
void SendToUdpClient(ClientMsg::Message *message, sockaddr *addr);

#endif

