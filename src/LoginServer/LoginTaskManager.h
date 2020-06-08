#ifndef _LOGINTASKMANAGER_H_
#define _LOGINTASKMANAGER_H_

#include "ServerTaskManager.h"

class CLoginTask;

class LoginTaskManager : public CServerTaskManager
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

