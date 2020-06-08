#include "MatchTeam.h"
#include "WMatchManager.h"
#include "WMatchService.h"

//MatchTeam
MatchTeam::~MatchTeam()
{
    if (m_fightTeam)
    {
        m_fightTeam->RemoveMatchTeam(this);
    }

    for (auto &v : m_players)
    {
        WMatchManager::instance()->RemovePlayer(v);
    }
}

bool MatchTeam::AddPlayer(WorldPlayerInfo &info)
{
    bool have = false;
    for (uint32_t i = 0; i < m_players.size(); ++i)
    {
        if (m_players[i].gameServerId == info.gameServerId && m_players[i].playerId == info.playerId)
        {
            have = true;
            break;
        }
    }

    if (!have)
    {
        m_players.push_back(info);
        WMatchManager::instance()->AddPlayer(this, &info);

        return true;
    }

    return false;
}

void MatchTeam::Serialize(uint8_t *ptr, uint32_t &len, uint32_t &count)
{
    uint32_t length = sizeof(WorldPlayerInfo);
    for (auto &v : m_players)
    {
        memcpy(ptr, &v, length);
        len += length;
        ptr += length;
        ++count;
    }

    return;
}

void MatchTeam::NotifyError(uint32_t error, MatchInfo *info)
{
    for (auto &v : m_players)
    {
        WMatchManager::instance()->NotifyMatchError(error, &v, info);
    }

    return;
}

void MatchTeam::SendMatchRes(Cmd::t_World_Match_Res *cmd, uint32_t len)
{
    for (auto &v : m_players)
    {
        cmd->playerInfo.playerId = v.playerId;
        ServerImp()->ProxySendCmd(cmd, len, SERVER_TYPE_LOGIC_SERVER, v.logicServerId);
    }
    
    return;
}

//FightTeam
FightTeam::~FightTeam()
{
    for (auto v : m_teams)
    {
        v->SetFightTeam(NULL);
        SAFE_DELETE(v);
    }
}

void FightTeam::AddMatchTeam(MatchTeam *team)
{
    m_teams.push_back(team);
    team->SetFightTeam(this);

    return;
}

void FightTeam::RemoveMatchTeam(MatchTeam *team)
{
    for (auto itr = m_teams.begin(); itr != m_teams.end(); ++itr)
    {
        if ((*itr)->Uid() == team->Uid())
        {
            m_teams.erase(itr);
            break;
        }
    }

    team->SetFightTeam(NULL);

    return;
}

void FightTeam::ClearMatchTeam()
{
    for (auto itr = m_teams.begin(); itr != m_teams.end(); ++itr)
    {
        (*itr)->SetFightTeam(NULL);
    }

    m_teams.clear();

    return;
}

uint32_t FightTeam::PlayerCount()
{
    uint32_t count = 0;

    for (auto v : m_teams)
    {
        count += v->PlayerCount();
    }

    return count;
}

void FightTeam::MatchRemoveMatchTeam()
{
    for (auto v : m_teams)
    {
        WMatchManager::instance()->RemoveMatchTeam(v);
    }

    return;
}

void FightTeam::Serialize(uint8_t *ptr, uint32_t &len, uint32_t &count)
{
    for (auto v : m_teams)
    {
        uint32_t length = 0;
        v->Serialize(ptr, length, count);
        ptr += length;
        len += length;
    }

    return;
}

void FightTeam::NotifyError(uint32_t error, MatchInfo *info)
{
    for (auto v : m_teams)
    {
        v->NotifyError(error, info);
    }

    return;
}

void FightTeam::SendMatchRes(Cmd::t_World_Match_Res *cmd, uint32_t len)
{
    for (auto v : m_teams)
    {
        v->SendMatchRes(cmd, len);
    }

    return;
}
