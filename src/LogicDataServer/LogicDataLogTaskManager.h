#ifndef _LOGICDATALOGTASKMANAGER_H_
#define _LOGICDATALOGTASKMANAGER_H_

#include "TaskManager.h"

class CLogicDataLogTaskManager : public CTaskManager
{
public:
    bool Init();

    void UniqueAddExt(CConnectTask *task);
    void UniqueRemoveExt(CConnectTask *task);

private:
     CConnectTask* NewTcpTask(CListenTCPServer *);
};

#endif

