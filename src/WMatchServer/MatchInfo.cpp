#include "MatchInfo.h"
#include "WorldCommand.h"
#include "WMatchService.h"
#include "WMatchTask.h"
#include "WMatchManager.h"
#include "MatchTeam.h"

//MatchInfo
MatchInfo::~MatchInfo()
{
    for (auto v : m_teams)
    {
        SAFE_DELETE(v);
    }
}

void MatchInfo::ClearWFightDungeonConnectInfo()
{
    m_wDungeonBaseInfo.Clear();

    return;
}

void MatchInfo::MatchRemoveMatchTeam()
{
    for (auto v : m_teams)
    {
        v->MatchRemoveMatchTeam();
    }

    return;
}

void MatchInfo::AddFightTeam(FightTeam **team)
{
    for (uint32_t i = 0; i < m_teams.size(); ++i)
    {
        if (m_teams[i] == NULL)
        {
            m_teams[i] = *team;
            m_teams[i]->SetMatch(this);
            *team = NULL;
        }
    }

    return;
}


