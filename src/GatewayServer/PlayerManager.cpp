#include "PlayerManager.h"
#include "GatewayPlayer.h"
#include "GatewayConnectClient.h"
#include "TimeTick.h"
#include "LogicGateCommand.h"
#include "Defs.h"
#include "GatewayService.h"

GatewayPlayer* PlayerManager::GetPlayerByID(uint64_t id)
{
    return(GatewayPlayer*) GetObjectByID(id);
}

GatewayPlayer* PlayerManager::GetPlayerByTempID(uint64_t tempid)
{
    return(GatewayPlayer*) GetObjectByTempID(tempid);
}

bool PlayerManager::AddPlayer(GatewayPlayer* player)
{
    return AddObject(player);
}

void PlayerManager::RemovePlayer(GatewayPlayer* &player, bool notifyLogic)
{
    if (notifyLogic)
    {
        ServerImp()->NotifyPlayerLeave(player->Id());
    }

    player->LeaveWorld();

    RemoveObject(player);
    SAFE_DELETE(player);
}

bool PlayerManager::ExecEveryPlayer(CEntryCallback<GatewayPlayer>& execPlayer)
{
    return ExecEveryEntry(execPlayer);
}

void PlayerManager::SendAllPlayer(void *ptr, uint32_t len)
{
    typedef  CObjectTempID::iter my_iter;
    for (my_iter it = CObjectTempID::ets.begin(); it != CObjectTempID::ets.end(); ++it)
    {
        ((GatewayPlayer *)it->second)->SendCmd(ptr, len);
    }
    return ;
}

int PlayerManager::Size()const
{
    return CObjectManager<GatewayPlayer, CObjectTempID, CObjectID>::Size();
}

void PlayerManager::AddKcpPlayer(uint32_t id, GatewayPlayer *player)
{
    m_kcpPlayer[id] = player;

    return;
}

void PlayerManager::RemoveKcpPlayer(uint32_t id)
{
    std::map<uint32_t, GatewayPlayer *>::iterator itr = m_kcpPlayer.find(id);
    if (itr != m_kcpPlayer.end())
        m_kcpPlayer.erase(itr);

    return;
}

GatewayPlayer *PlayerManager::FindKcpPlayer(uint32_t id)
{
    std::map<uint32_t, GatewayPlayer *>::iterator itr = m_kcpPlayer.find(id);
    if (itr != m_kcpPlayer.end())
        return itr->second;

    return NULL;
}



