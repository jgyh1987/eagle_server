#ifndef _LOGICLOGDATATASK_H_
#define _LOGICLOGDATATASK_H_

#include "ServerTask.h"
#include "LogicDataCommand.h"
#include "ConstructInPlace.h"

class CLogicDataLogTask : public CServerTask
{
public:
    CLogicDataLogTask(CListenTCPServer *listenServer)
        :CServerTask(listenServer)
    {
    }

    bool cmdMsgParse(void *,const uint32_t);

private:
    bool DBServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);

    bool DBLogicPlayerInfoMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);
    bool DBRecvLog(Cmd::t_SendCmdToData_LogInfo *);

private:

};


#endif
