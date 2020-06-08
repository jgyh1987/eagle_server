#ifndef _CENTRALTASKMANAGER_H_
#define _CENTRALTASKMANAGER_H_

#include "ServerTaskManager.h"
#include "CentralTask.h"

class CCentralTaskManager : public CServerTaskManager
{
public:
    CCentralTaskManager()
    {}
    bool Init();

protected:
    void UniqueAddExtImp(CServerTask *task);
    void UniqueRemoveExtImp(CServerTask *task);

private:
     CConnectTask* NewTcpTask(CListenTCPServer *);    
};



#endif

