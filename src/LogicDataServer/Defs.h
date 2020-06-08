#ifndef _DEFS_H_
#define _DEFS_H_

#include "Misc.h"
#include "Global.h"
#include "Logger.h"
#include "DelayDBConnection.h"
#include "DataDBConnection.h"
#include "LogDBConnection.h"

#define MYSQLPP_SSQLS_NO_STATICS
#include "SqlData.h"

void SendToLogicServer(void *ptr, const uint32_t nCmdLen);

#endif

