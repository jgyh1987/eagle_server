#ifndef _MATCH_INFO_H_
#define _MATCH_INFO_H_

#include "WorldObject.h"
#include "TimeTick.h"
#include "PlayerInfo.h"
#include "WorldCommand.h"

#define CREATE_FIGHT_CALLBACK_TIMEOUT 300

class FightTeam;

class MatchInfo : public UnitObject
{
public:
    MatchInfo()
        :UnitObject(GetObjectUid())
    {
        m_baseInfo.matchUid = Uid();
        m_baseInfo.matchType = OBJECT_DUNGEON;
        m_time = CImpServerTimeTick::currentTime.sec() + CREATE_FIGHT_CALLBACK_TIMEOUT;
    }
    ~MatchInfo();

    uint32_t Type() { return OBJECT_DUNGEON; }
    bool IsType(uint32_t type) { return OBJECT_DUNGEON == type; }

    inline MatchBaseInfo *GetMatchBaseInfo() { return &m_baseInfo; }
    inline uint32_t GetMatchType() { return m_baseInfo.matchType; }

    void ClearWFightDungeonConnectInfo();
    void MatchRemoveMatchTeam();
    virtual void AddFightTeam(FightTeam **);
    virtual uint32_t SendCreateFightReq() = 0;
    virtual void MatchCallback(Cmd::t_World_Create_Fight_Res *recv) = 0;

public:
    WDungeonBaseInfo m_wDungeonBaseInfo;
    MatchBaseInfo m_baseInfo;
    std::vector<FightTeam *> m_teams;
    uint64_t m_time;
};


#endif

 