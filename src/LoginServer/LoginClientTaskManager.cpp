#include "LoginClientTaskManager.h"
#include "LoginClientTask.h"
#include "LogicLoginCommand.h"
#include "LoginService.h"
#include "CObject.h"
#include "TimeTick.h"

CConnectTask* LoginClientTaskManager::NewTcpTask(CListenTCPServer *listenServer)
{
    return new CLoginClientTask(listenServer);
}


bool LoginClientTaskManager::Init()
{

    return true;
}

void LoginClientTaskManager::UniqueAddExtImp(CClientTask *task)
{
    ((CLoginClientTask *)task)->SetConnectTime(CImpServerTimeTick::currentTime.msec());
    GetServerImp()->AddClientTask((CLoginClientTask *)task);

    return;
}

void LoginClientTaskManager::UniqueRemoveExtImp(CClientTask *task)
{
    GetServerImp()->RemoveClientTask(((CLoginClientTask *)task));

    return ;
}

