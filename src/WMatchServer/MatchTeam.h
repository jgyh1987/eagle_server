#ifndef _TEAM_H_
#define _TEAM_H_

#include "Sys.h"
#include "PlayerInfo.h"
#include "CObject.h"
#include "WMatchManager.h"
#include "WorldCommand.h"

class MatchInfo;
class FightTeam;

class MatchTeam : public CObjectBase
{
public:
    MatchTeam(uint32_t matchType)
        :CObjectBase(GetObjectUid()), m_matchType(matchType)
    {
        m_time = CImpServerTimeTick::currentTime.sec();
        m_begin = false;
        m_del = false;
    }

    ~MatchTeam();

    bool AddPlayer(WorldPlayerInfo &info);
    inline uint32_t PlayerCount() { return (uint32_t)m_players.size(); }
    inline void SetFightTeam(FightTeam *team) { m_fightTeam = team; }
    inline FightTeam *GetFightTeam() { return m_fightTeam; }
    inline std::vector<WorldPlayerInfo> &GetPlayers() { return m_players; }
    inline uint32_t MatchType() { return m_matchType; }

    void Serialize(uint8_t *ptr, uint32_t &len, uint32_t &count);
    void NotifyError(uint32_t error, MatchInfo *info);
    void SendMatchRes(Cmd::t_World_Match_Res *cmd, uint32_t len);

private:
    std::vector<WorldPlayerInfo> m_players;
    FightTeam *m_fightTeam;
    uint64_t m_time;
    bool m_begin;
    bool m_del;
    uint32_t m_matchType;
};

class FightTeam
{
public:
    FightTeam()
    {

    }

    ~FightTeam();

    void AddMatchTeam(MatchTeam *team);
    void RemoveMatchTeam(MatchTeam *team);
    void ClearMatchTeam();
    uint32_t PlayerCount();
    void MatchRemoveMatchTeam();

    inline std::vector<MatchTeam *> &GetTeams() { return m_teams; }
    inline void SetMatch(MatchInfo *match) 
    {
        m_match = match; 
    }
    inline MatchInfo *GetMatch() { return m_match; }

    void Serialize(uint8_t *ptr, uint32_t &len, uint32_t &count);
    void NotifyError(uint32_t error, MatchInfo *info);
    void SendMatchRes(Cmd::t_World_Match_Res *cmd, uint32_t len);

private:

    std::vector<MatchTeam *> m_teams;
    MatchInfo *m_match;
};

#endif


