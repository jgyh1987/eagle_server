#include "LogicTaskManager.h"
#include "LogicTask.h"
#include "World.h"
#include "Defs.h"

class CallbackGetPlayerRemoveTask : public CEntryCallback<LogicPlayer>
{
public:
    bool exec(LogicPlayer* player)
    {
        if (task)
            player->SetGateServer(task->GetServerId());
        else
            player->SetGateServer(0);

        return true;
    }

    CServerTask *task;
};

CConnectTask* LogicTaskManager::NewTcpTask(CListenTCPServer *listenServer)
{
    return new CLogicTask(listenServer);
}


bool LogicTaskManager::Init()
{

    return true;
}

void LogicTaskManager::UniqueAddExtImp(CServerTask *task)
{

    return;
}

void LogicTaskManager::UniqueRemoveExtImp(CServerTask *task)
{
    CallbackGetPlayerRemoveTask playerupdate;
    playerupdate.task = task;
    PlayerManager::instance()->ExecEveryPlayer(playerupdate);

    return;
}

