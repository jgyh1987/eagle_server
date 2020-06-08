#ifndef _WMATCH_TASKMANAGER_H_
#define _WMATCH_TASKMANAGER_H_

#include "ServerTaskManager.h"

class CWMatchTask;

class CWMatchTaskManager : public CServerTaskManager
{
public:
    bool Init();

    void UniqueAddExtImp(CServerTask *task);
    void UniqueRemoveExtImp(CServerTask *task);

private:
     CConnectTask* NewTcpTask(CListenTCPServer *);

};


#endif

