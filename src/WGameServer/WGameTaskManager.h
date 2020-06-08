#ifndef _WGAME_TASKMANAGER_H_
#define _WGAME_TASKMANAGER_H_

#include "ServerTaskManager.h"

class CWGameTaskManager : public CServerTaskManager
{
public:
    CWGameTaskManager()
    {}
    bool Init();

protected:
    void UniqueAddExtImp(CServerTask *task);
    void UniqueRemoveExtImp(CServerTask *task);

private:
     CConnectTask* NewTcpTask(CListenTCPServer *);    
};



#endif

