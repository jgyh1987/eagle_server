#ifndef _CLIENTTASKMANAGER_H_
#define _CLIENTTASKMANAGER_H_

#include "TaskManager.h"
#include "ClientTask.h"

class CClientTaskManager : public CTaskManager
{
public:
    void UniqueAddExt(CConnectTask *task);
    void UniqueRemoveExt(CConnectTask *task);

protected:
    virtual void UniqueAddExtImp(CClientTask *task) = 0;
    virtual void UniqueRemoveExtImp(CClientTask *task) = 0;
};

#endif

