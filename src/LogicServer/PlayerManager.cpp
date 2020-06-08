#include "PlayerManager.h"

LogicPlayer* PlayerManager::GetPlayerByID(uint64_t id)
{
    return(LogicPlayer*) GetObjectByID(id);
}

LogicPlayer* PlayerManager::GetPlayerByTempID(uint64_t tempid)
{
    return(LogicPlayer*) GetObjectByTempID(tempid);
}

LogicPlayer* PlayerManager::GetPlayerByName(const std::string& name)
{
    return(LogicPlayer*) GetObjectByName(name);
}

LogicPlayer* PlayerManager::GetPlayerByAccount(const std::string& account)
{
    return(LogicPlayer*) GetObjectBySession(account);
}

bool PlayerManager::AddPlayer(LogicPlayer* player)
{
    return AddObject(player);
}

void PlayerManager::RemovePlayer(LogicPlayer* player)
{
    RemoveObject(player);
}

bool PlayerManager::ExecEveryPlayer(CEntryCallback<LogicPlayer>& execPlayer)
{
    return ExecEveryEntry(execPlayer);
}

int PlayerManager::Size()const
{
    return CObjectManager<LogicPlayer, CObjectTempID, CObjectID, CObjectSession, CObjectName>::Size();
}

LogicPlayer* PlayerManager::GetFirstPlayer() const
{
    if (CObjectTempID::ets.size())
        return(LogicPlayer*) CObjectTempID::ets.begin()->second;
    return NULL;
}

