#ifndef _LOGINDATATASKMANAGER_H_
#define _LOGINDATATASKMANAGER_H_

#include "ServerTaskManager.h"

class CLoginDataTaskManager : public CServerTaskManager
{
public:
    bool Init();

protected:
    void UniqueAddExtImp(CServerTask *task);
    void UniqueRemoveExtImp(CServerTask *task);

private:
     CConnectTask* NewTcpTask(CListenTCPServer *);
};

#endif

