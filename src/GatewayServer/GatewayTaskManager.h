#ifndef _GATEWAYTASKMANAGER_H_
#define _GATEWAYTASKMANAGER_H_

#include "ClientTaskManager.h"

class GatewayTaskManager : public CClientTaskManager
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

