//该文件不能被include在.H 文件中
#ifndef _DEFS_H_
#define _DEFS_H_

#include "Misc.h"
#include "Logger.h"
#include "Global.h"
#include "ToolsFun.h"
#include "parameters.h"
#include "World.h"
#include "ECS_Bag.h"
#include "ECS_Mail.h"
#include "ECS_Quest.h"
#include "ECS_Counter.h"
#include "WGameWorld.h"

extern uint32_t g_serverPort;

void SendToDB(void* ptr, const int nCmdLen, uint32_t dbserverId);

#endif

