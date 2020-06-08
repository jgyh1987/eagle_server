#ifndef _DEFS_H_
#define _DEFS_H_

#include "Misc.h"
#include "Logger.h"
#include "Global.h"
#include "LogicDataManager.h"
#include "World.h"
#include "SysLogInfo.h"
#include "Random.h"
#include "ECS_Bag.h"
#include "ECS_Mail.h"
#include "ECS_Counter.h"

extern uint32_t g_serverPort;
extern uint32_t g_connectLogicDataServerPort;
extern uint32_t g_connectLogDataServerPort;

void SendToDB(void *ptr,const int nCmdLen);
void SendToLogDB(void *ptr,const int nCmdLen);
void SendToGateway(void *ptr,const int nCmdLen);
void SendToFriendGuild(void *ptr, const int nCmdLen);

#endif

