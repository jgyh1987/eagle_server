#ifndef _MATCH_MANAGER_H_
#define _MATCH_MANAGER_H_

#include "Sys.h"
#include "Singleton.h"
#include "WorldCommand.h"
#include "Unit.h"
#include "MatchInfo.h"
#include "MatchTeam.h"
#include "ServerCommand.h"

class CWMatchTask;
class MatchInfo;
class MatchTeam;
class FightTeam;

class WGateServerInfo
{
public:
    Cmd::ServerInfoEx info;

    WGateServerInfo(Cmd::ServerInfoEx *_info)
    {
        info = *_info;
    }

};

class WFightServerInfo
{
public:
    Cmd::ServerInfoEx info;

    WFightServerInfo(Cmd::ServerInfoEx *_info)
    {
        info = *_info;
    }

};

class WMatchManager : public CSingleton<WMatchManager>
{
public:

    WMatchManager();

    void Update1Sec();


    void NotifyMatchError(uint32_t errorType, WorldPlayerInfo *playerinfo, MatchInfo *matchinfo, CWMatchTask *task = NULL);
    void NotifyMatchError(uint32_t errorType, WorldPlayerInfo *playerinfo, uint32_t count, MatchInfo *matchinfo, CWMatchTask *task = NULL);

    //world cmd logic
    void Match(Cmd::t_World_Match_Req *recv, CWMatchTask *task);

    //world cmd wfight
    void CreateFightBack(Cmd::t_World_Create_Fight_Res *recv);

public:
    void AddPlayer(MatchTeam *, WorldPlayerInfo *playerinfo);
    void RemovePlayer(WorldPlayerInfo &playerinfo);

    void AddWGateServer(Cmd::ServerInfoEx *);
    void AddWFightServer(Cmd::ServerInfoEx *);
    WGateServerInfo *GetWGateServer();
    WFightServerInfo *GetWFightServer();
    WGateServerInfo *FindWGateServerById(uint32_t id);
    WFightServerInfo *FindWFightServerById(uint32_t id);


    void AddMatch(MatchInfo *);
    void RemoveMatch(MatchInfo *);
    void AddMatchTeam(MatchTeam *);
    void RemoveMatchTeam(MatchTeam *);

private:
    
    MatchTeam *PlayerHaveMatch(WorldPlayerInfo *);
    MatchInfo *FindMatchByUid(MatchBaseInfo &info);

    //主线
    void MatchSolo(Cmd::t_World_Match_Req *recv, CWMatchTask *task);

    //1v1 Match
    void Match1V1(Cmd::t_World_Match_Req *recv, CWMatchTask *task);
    void Update1V1();

    //3v3 Match
    void Match3V3(Cmd::t_World_Match_Req *recv, CWMatchTask *task);
    void Update3V3();
    void Check3V3MatchTeam3Player(FightTeam *, FightTeam *, MatchTeam *);
    void Check3V3MatchTeamXPlayer(FightTeam *, FightTeam *, MatchTeam *);

private:
    std::map< uint32_t, std::map<uint64_t, MatchTeam *> > m_playerMatchs;

    //
    std::map< uint32_t, std::map<uint64_t, MatchTeam *> > m_matchTeams;
    std::map<uint64_t, MatchInfo *> m_matchs;

    std::map<uint32_t, WGateServerInfo *> m_gateServer;
    std::map<uint32_t, WFightServerInfo *> m_fightServer;
};

#endif

 