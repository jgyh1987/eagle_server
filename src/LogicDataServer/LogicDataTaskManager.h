#ifndef _LOGICDATATASKMANAGER_H_
#define _LOGICDATATASKMANAGER_H_

#include "ServerTaskManager.h"

class CLogicDataTaskManager : public CServerTaskManager
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

