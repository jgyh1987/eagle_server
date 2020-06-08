#ifndef _DEFS_H_
#define _DEFS_H_

#include "Misc.h"
#include "Global.h"
#include "Logger.h"
#include "DataDBConnection.h"

#define MYSQLPP_SSQLS_NO_STATICS
#include "SqlData.h"

extern uint32_t g_serverPort;

void SendToLoginServer(void *ptr, const uint32_t nCmdLen);


#endif

