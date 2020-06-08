#ifndef _PROXYTASKMANAGER_H_
#define _PROXYTASKMANAGER_H_

#include "ServerTaskManager.h"
#include "ProxyTask.h"

class CProxyTaskManager : public CServerTaskManager
{
public:
    CProxyTaskManager()
    {}
    bool Init();

protected:
    void UniqueAddExtImp(CServerTask *task);
    void UniqueRemoveExtImp(CServerTask *task);

private:
     CConnectTask* NewTcpTask(CListenTCPServer *);    
};



#endif

