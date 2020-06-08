#ifndef _GATEWAYWSTASKMANAGER_H_
#define _GATEWAYWSTASKMANAGER_H_

#include "ClientTaskManager.h"

class GatewayWSTaskManager : public CClientTaskManager
{
public:
    bool Init();

protected:
    void UniqueAddExtImp(CClientTask *task){}
    void UniqueRemoveExtImp(CClientTask *task);

private:
     CConnectTask* NewTcpTask(CListenTCPServer *);
};

#endif

