//该文件不能被include在.H 文件中
#ifndef _DEFS_H_
#define _DEFS_H_

#include "Misc.h"
#include "Logger.h"
#include "Global.h"

extern uint32_t g_serverPort;
class CMatchConnectClient;
extern CMatchConnectClient *g_matchConn;

#endif
