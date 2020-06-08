#include "OffLinePlayer.h"
#include "Defs.h"
#include "World.h"
#include "LogicPlayer.h"

void COffLinePLayerManager::AddOffPlayer(LogicPlayer *player)
{
    std::map<uint64_t, LogicPlayer *>::iterator itr = m_offPlayers.find(player->Id());
    if (itr != m_offPlayers.end())
    {
        World::instance()->FreePlayer(itr->second); 
        m_offPlayers.erase(itr);
    }

    m_offPlayers[player->Id()] = player;

    return;
}

void COffLinePLayerManager::RemoveOffPlayer(LogicPlayer *player)
{
    return RemoveOffPlayer(player->Id());
}

void COffLinePLayerManager::RemoveOffPlayer(uint64_t playerId)
{
    std::map<uint64_t, LogicPlayer *>::iterator itr = m_offPlayers.find(playerId);
    if (itr != m_offPlayers.end())
    {
        World::instance()->FreePlayer(itr->second); 
        m_offPlayers.erase(itr);
    }

    return;
}

LogicPlayer *COffLinePLayerManager::GetOffPlayerById(uint64_t id)
{
    std::map<uint64_t, LogicPlayer *>::iterator itr = m_offPlayers.find(id);
    if (itr != m_offPlayers.end())
        return itr->second;

    return NULL;
}

