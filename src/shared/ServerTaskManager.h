#ifndef _SERVERTASKMANAGER_H_
#define _SERVERTASKMANAGER_H_

#include "TaskManager.h"
#include "ServerTask.h"

class CServerTaskManager : public CTaskManager
{
public:
    void UniqueAddExt(CConnectTask *task);
    void UniqueRemoveExt(CConnectTask *task);

protected:
    virtual void UniqueAddExtImp(CServerTask *task) = 0;
    virtual void UniqueRemoveExtImp(CServerTask *task) = 0;
};

#endif

