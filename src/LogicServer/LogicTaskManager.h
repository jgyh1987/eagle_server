#ifndef _LOGICTASKMANAGER_H_
#define _LOGICTASKMANAGER_H_

#include "ServerTaskManager.h"

class LogicTaskManager : public CServerTaskManager
{
public:
    bool Init();

protected:
    void UniqueAddExtImp(CServerTask *task);
    void UniqueRemoveExtImp(CServerTask *task);

private:
     CConnectTask* NewTcpTask(CListenTCPServer *);
};

#endif

