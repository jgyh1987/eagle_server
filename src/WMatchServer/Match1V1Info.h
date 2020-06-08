#ifndef _MATCH_1V1_INFO_H_
#define _MATCH_1V1_INFO_H_

#include "WorldObject.h"
#include "TimeTick.h"
#include "CommonType.h"
#include "MatchInfo.h"

class MatchSoloInfo : public MatchInfo
{
public:

    MatchSoloInfo()
    {
        m_baseInfo.matchType = OBJECT_DUNGEON_SOLO;
    }
    ~MatchSoloInfo();

    uint32_t Type() { return OBJECT_DUNGEON_SOLO; }
    bool IsType(uint32_t type) { return OBJECT_DUNGEON_SOLO == type; }

    uint32_t SendCreateFightReq() { return SUCCESS; }
    void MatchCallback(Cmd::t_World_Create_Fight_Res *recv);

public:
    uint64_t m_dungeonId;
    WorldPlayerInfo m_player;
};

class Match1V1Info : public MatchInfo
{
public:

    Match1V1Info();
    ~Match1V1Info(){}

    uint32_t Type() { return OBJECT_DUNGEON_1V1; }
    bool IsType(uint32_t type) { return OBJECT_DUNGEON_1V1 == type; }

    uint32_t SendCreateFightReq();
    void MatchCallback(Cmd::t_World_Create_Fight_Res *recv);
};

class Match3V3Info : public MatchInfo
{
public:

    Match3V3Info();
    ~Match3V3Info() {}

    uint32_t Type() { return OBJECT_DUNGEON_3V3; }
    bool IsType(uint32_t type) { return OBJECT_DUNGEON_3V3 == type; }

    uint32_t SendCreateFightReq();
    void MatchCallback(Cmd::t_World_Create_Fight_Res *recv);

private:
    
};


#endif

 