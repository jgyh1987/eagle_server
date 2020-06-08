#ifndef _WGATE_CLIENT_TASKMANAGER_H_
#define _WGATE_CLIENT_TASKMANAGER_H_

#include "ClientTaskManager.h"

class CWGateClientTaskManager : public CClientTaskManager
{
public:
    bool Init();

    void UniqueAddExtImp(CClientTask *task);
    void UniqueRemoveExtImp(CClientTask *task);

private:
     CConnectTask* NewTcpTask(CListenTCPServer *);

};

#endif

