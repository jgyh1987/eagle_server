#include "WMatchManager.h"
#include "TimeTick.h"
#include "Defs.h"
#include "WMatchService.h"
#include "WMatchTask.h"
#include "World.h"
#include "Match1V1Info.h"
#include "MatchTeam.h"

//WMatchManager
WMatchManager::WMatchManager()
{
    
}

void WMatchManager::Update1Sec()
{
    Update1V1();

    Update3V3();

    for (auto itr = m_matchs.begin(); itr != m_matchs.end();)
    {
        if (CImpServerTimeTick::currentTime.sec() > itr->second->m_time)
        {
            Cmd::t_World_Create_Fight_Res send;
            send.ret = WORLD_MATCH_CREATE_ERROR;
            itr->second->MatchCallback(&send);
            SAFE_DELETE(itr->second);
            m_matchs.erase(itr++);
        }
        else
        {
            ++itr;
        }
    }

    return;
}

void WMatchManager::Update1V1()
{
    auto itr = m_matchTeams.find(OBJECT_DUNGEON_1V1);
    if (itr == m_matchTeams.end())
    {
        return;
    }

    std::list<Match1V1Info *> matchlist;

    FightTeam *fightTeam1 = new FightTeam();
    FightTeam *fightTeam2 = new FightTeam();
    if (!fightTeam1 || !fightTeam2)
    {
        SAFE_DELETE(fightTeam1);
        SAFE_DELETE(fightTeam2);

        return;
    }

    for (auto itr1 = itr->second.begin(); itr1 != itr->second.end(); ++itr)
    {
        if (!fightTeam1->PlayerCount())
        {
            fightTeam1->AddMatchTeam(itr1->second);
        }
        else if (!fightTeam2->PlayerCount())
        {
            fightTeam2->AddMatchTeam(itr1->second);
        }
        
        if (fightTeam2->PlayerCount() == 1 && fightTeam1->PlayerCount() == 1)
        {
            Match1V1Info *matchInfo = new Match1V1Info();
            if (matchInfo)
            {
                matchInfo->AddFightTeam(&fightTeam1);
                matchInfo->AddFightTeam(&fightTeam2);
                matchlist.push_back(matchInfo);

                fightTeam1 = new FightTeam();
                fightTeam2 = new FightTeam();
                if (!fightTeam1 || !fightTeam2)
                {
                    SAFE_DELETE(fightTeam1);
                    SAFE_DELETE(fightTeam2);

                    break;
                }
            }
        }
    }

    fightTeam1->ClearMatchTeam();
    fightTeam2->ClearMatchTeam();
    SAFE_DELETE(fightTeam1);
    SAFE_DELETE(fightTeam2);

    for (auto v : matchlist)
    {
        v->MatchRemoveMatchTeam();

        if (SUCCESS != v->SendCreateFightReq())
        {
            SAFE_DELETE(v);
        }
    }

    return;
}

void WMatchManager::Update3V3()
{
    auto itr = m_matchTeams.find(OBJECT_DUNGEON_3V3);
    if (itr == m_matchTeams.end())
    {
        return;
    }

    FightTeam *fightTeam1 = new FightTeam();
    FightTeam *fightTeam2 = new FightTeam();
    if (!fightTeam1 || !fightTeam2)
    {
        SAFE_DELETE(fightTeam1);
        SAFE_DELETE(fightTeam2);

        return;
    }

    std::list<Match3V3Info *> matchlist;

    FightTeam *fightTeam = fightTeam1;
    for (auto itr1 = itr->second.begin(); itr1 != itr->second.end(); ++itr1)
    {
        if (itr1->second->PlayerCount() == 3)
        {
            Check3V3MatchTeam3Player(fightTeam1, fightTeam2, itr1->second);
        }
        else
        { 
            Check3V3MatchTeamXPlayer(fightTeam1, fightTeam2, itr1->second);
        }

        if (fightTeam2->PlayerCount() == 3 && fightTeam1->PlayerCount() == 3)
        {
            Match3V3Info *matchInfo = new Match3V3Info();
            if (matchInfo)
            {
                matchInfo->AddFightTeam(&fightTeam1);
                matchInfo->AddFightTeam(&fightTeam2);
                matchlist.push_back(matchInfo);

                fightTeam1 = new FightTeam();
                fightTeam2 = new FightTeam();
                if (!fightTeam1 || !fightTeam2)
                {
                    SAFE_DELETE(fightTeam1);
                    SAFE_DELETE(fightTeam2);

                    break;
                }
            }
        }
    }

    fightTeam1->ClearMatchTeam();
    fightTeam2->ClearMatchTeam();
    SAFE_DELETE(fightTeam1);
    SAFE_DELETE(fightTeam2);

    for (auto v : matchlist)
    {
        v->MatchRemoveMatchTeam();

        if (SUCCESS != v->SendCreateFightReq())
        {
            SAFE_DELETE(v);
        }
    }    

    return;
}

void WMatchManager::Check3V3MatchTeam3Player(FightTeam *fightTeam1, FightTeam *fightTeam2, MatchTeam *matchTeam)
{
    if (fightTeam1->PlayerCount() == 0)
    {
        fightTeam1->AddMatchTeam(matchTeam);

        return;
    }

    if (fightTeam2->PlayerCount() == 0)
    {
        fightTeam2->AddMatchTeam(matchTeam);

        return;
    }

    if (fightTeam2->PlayerCount() != 3 && fightTeam1->PlayerCount() == 3)
    {
        fightTeam2->ClearMatchTeam();
        fightTeam2->AddMatchTeam(matchTeam);

        return;
    }

    if (fightTeam1->PlayerCount() != 3 && fightTeam2->PlayerCount() == 3)
    {
        fightTeam1->ClearMatchTeam();
        fightTeam1->AddMatchTeam(matchTeam);

        return;
    }

    return;
}

void WMatchManager::Check3V3MatchTeamXPlayer(FightTeam *fightTeam1, FightTeam *fightTeam2, MatchTeam *matchTeam)
{
    if (fightTeam1->PlayerCount() == 0)
    {
        fightTeam1->AddMatchTeam(matchTeam);

        return;
    }

    if (fightTeam2->PlayerCount() == 0)
    {
        fightTeam2->AddMatchTeam(matchTeam);

        return;
    }

    if (fightTeam1->PlayerCount() + matchTeam ->PlayerCount() == 3)
    {
        fightTeam1->AddMatchTeam(matchTeam);

        return;
    }

    if (fightTeam2->PlayerCount() + matchTeam->PlayerCount() == 3)
    {
        fightTeam2->AddMatchTeam(matchTeam);

        return;
    }

    if (fightTeam1->PlayerCount() + matchTeam->PlayerCount() <= 3)
    {
        fightTeam1->AddMatchTeam(matchTeam);

        return;
    }

    if (fightTeam2->PlayerCount() + matchTeam->PlayerCount() <= 3)
    {
        fightTeam2->AddMatchTeam(matchTeam);

        return;
    }

    return;
}

void WMatchManager::Match(Cmd::t_World_Match_Req *recv, CWMatchTask *task)
{    
    switch (recv->matchType)
    {
    case OBJECT_DUNGEON_SOLO:
    {
        return MatchSolo(recv, task);
    }
    break;
    case OBJECT_DUNGEON_1V1:
        {
        return Match1V1(recv, task);
        }
        break;
    case OBJECT_DUNGEON_3V3:
        {
        return Match3V3(recv, task);
        }
        break;
    default:
        break;
    }

    return;
}

void WMatchManager::CreateFightBack(Cmd::t_World_Create_Fight_Res *recv)
{
    MatchInfo *matchinfo = FindMatchByUid(recv->matchInfo);
    if (!matchinfo)
    {
        return;
    }

    matchinfo->MatchCallback(recv);
    RemoveMatch(matchinfo);

    return;
}

void WMatchManager::AddMatch(MatchInfo *info)
{
    m_matchs[info->Uid()] = info;

    return;
}

void WMatchManager::RemoveMatch(MatchInfo *info)
{
    auto itr = m_matchs.find(info->Uid());
    if (itr != m_matchs.end())
    {
        SAFE_DELETE(itr->second);
        m_matchs.erase(itr);
    }

    return;
}

void WMatchManager::AddMatchTeam(MatchTeam *team)
{
    m_matchTeams[team->MatchType()][team->Uid()] = team;

    return;
}

void WMatchManager::RemoveMatchTeam(MatchTeam *team)
{
    auto itr = m_matchTeams.find(team->MatchType());
    if (itr != m_matchTeams.end())
    {
        auto itr1 = itr->second.find(team->Uid());
        if (itr1 != itr->second.end())
            itr->second.erase(itr1);
    }

    return;
}

void WMatchManager::AddPlayer(MatchTeam *team, WorldPlayerInfo *playerinfo)
{
    m_playerMatchs[playerinfo->gameServerId][playerinfo->playerId] = team;

    return;
}

void WMatchManager::RemovePlayer(WorldPlayerInfo &playerinfo)
{
    auto itr = m_playerMatchs.find(playerinfo.gameServerId);
    if (itr != m_playerMatchs.end())
    {
        auto itr1 = itr->second.find(playerinfo.playerId);
        if (itr1 != itr->second.end())
        {
            itr->second.erase(itr1);
        }
    }

    return;
}

void WMatchManager::AddWGateServer(Cmd::ServerInfoEx *info)
{
    auto itr = m_gateServer.find(info->serverId);
    if (itr != m_gateServer.end())
    {
        itr->second->info = *info;
    }
    else
        m_gateServer[info->serverId] = new WGateServerInfo(info);

    return;
}

void WMatchManager::AddWFightServer(Cmd::ServerInfoEx *info)
{
    auto itr = m_fightServer.find(info->serverId);
    if (itr != m_fightServer.end())
    {
        itr->second->info = *info;
    }
    else
        m_fightServer[info->serverId] = new WFightServerInfo(info);

    return;
}

WGateServerInfo *WMatchManager::GetWGateServer()
{
    for (auto &itr : m_gateServer)
    {
        return itr.second;
    }

    return 0;
}

WFightServerInfo *WMatchManager::GetWFightServer()
{
    for (auto &itr : m_fightServer)
    {
        return itr.second;
    }

    return 0;
}

WGateServerInfo *WMatchManager::FindWGateServerById(uint32_t id)
{
    auto itr = m_gateServer.find(id);
    if (itr != m_gateServer.end())
    {
        return itr->second;
    }

    return NULL;
}

WFightServerInfo *WMatchManager::FindWFightServerById(uint32_t id)
{
    auto itr = m_fightServer.find(id);
    if (itr != m_fightServer.end())
    {
        return itr->second;
    }

    return NULL;
}

MatchTeam *WMatchManager::PlayerHaveMatch(WorldPlayerInfo *info)
{
    auto itr = m_playerMatchs.find(info->gameServerId);
    if (itr != m_playerMatchs.end())
    {
        auto itr1 = itr->second.find(info->playerId);
        if (itr1 != itr->second.end())
        {
            return itr1->second;        
        }
    }

    return NULL;
}

MatchInfo *WMatchManager::FindMatchByUid(MatchBaseInfo &info)
{
    auto itr = m_matchs.find(info.matchUid);
    if (itr != m_matchs.end())
    {
        return itr->second;
    }

    return NULL;
}

void WMatchManager::NotifyMatchError(uint32_t errorType, WorldPlayerInfo *playerinfo, MatchInfo *matchinfo, CWMatchTask *task)
{
    Cmd::t_World_Match_Res send;
    send.ret = errorType;
    send.playerInfo = *playerinfo;

    ServerImp()->ProxySendCmd(&send, sizeof(send), SERVER_TYPE_LOGIC_SERVER, playerinfo->logicServerId, task);

    return;
}

void WMatchManager::NotifyMatchError(uint32_t errorType, WorldPlayerInfo *playerinfo, uint32_t count, MatchInfo *matchinfo, CWMatchTask *task)
{
    for (uint32_t i = 0; i < count; ++i)
    {
        NotifyMatchError(errorType, &playerinfo[i], matchinfo, task);
    }

    return;
}

void WMatchManager::MatchSolo(Cmd::t_World_Match_Req *recv, CWMatchTask *task)
{
    WorldPlayerInfo *infos = (WorldPlayerInfo *)recv->data;

    WGateServerInfo *gateInfo = WMatchManager::instance()->GetWGateServer();
    WFightServerInfo *fightInfo = WMatchManager::instance()->GetWFightServer();
    if (!gateInfo || !fightInfo)
    {
        return NotifyMatchError(WORLD_FIGHT_SERVER_ERROR, infos, NULL, task);
    }

    MatchSoloInfo *match = new MatchSoloInfo();
    WMatchManager::instance()->AddMatch(match);

    match->m_player = *infos;

    match->m_dungeonId = recv->dungeonId;

    memcpy(match->m_wDungeonBaseInfo.ip, gateInfo->info.serverIP, sizeof(match->m_wDungeonBaseInfo.ip));
    match->m_wDungeonBaseInfo.tcpPort = gateInfo->info.port;
    match->m_wDungeonBaseInfo.udpPort = gateInfo->info.gameServerId;

    match->m_wDungeonBaseInfo.wServerId = fightInfo->info.serverId;


    Cmd::t_World_Create_Fight_Req *cmd;
    World::instance()->ServerCmdBuffer(cmd);
    cmd->matchInfo = match->m_baseInfo;
    cmd->dungeonId = recv->dungeonId;
    uint8_t *ptr = cmd->data;
    uint32_t length = sizeof(WorldPlayerInfo);
    memcpy(ptr, infos, length);
    cmd->len = length;
    cmd->playerCount = 1;

    ServerImp()->ProxySendCmd(cmd, cmd->Size(), SERVER_TYPE_WGAME_SERVER, match->m_wDungeonBaseInfo.wServerId);


}

void WMatchManager::Match1V1(Cmd::t_World_Match_Req *recv, CWMatchTask *task)
{
    WorldPlayerInfo *infos = (WorldPlayerInfo *)recv->data;

    MatchTeam *team = PlayerHaveMatch(infos);
    if (team)
    {
        return NotifyMatchError(WORLD_MATCH_EXIST, infos, NULL, task);
    }

    team = new MatchTeam(recv->matchType);
    if (team->AddPlayer(*infos))
        AddMatchTeam(team);
    else
    {
        NotifyMatchError(WORLD_MATCH_CREATE_ERROR, infos, NULL, task);
        SAFE_DELETE(team);
    }
        
    
    return;
}

void WMatchManager::Match3V3(Cmd::t_World_Match_Req *recv, CWMatchTask *task)
{
    WorldPlayerInfo *infos = (WorldPlayerInfo *)recv->data;

    MatchTeam *team = new MatchTeam(recv->matchType);
    for (uint32_t i = 0; i < recv->count; ++i)
    {
        if (!team->AddPlayer(infos[i]))
        {
            SAFE_DELETE(team);
            return NotifyMatchError(WORLD_MATCH_CREATE_ERROR, &infos[0], NULL, task);
        }

        MatchTeam *oldTeam = PlayerHaveMatch(&infos[i]);
        if (oldTeam)
        {
            SAFE_DELETE(team);
            return NotifyMatchError(WORLD_TEAMER_HAVE_MATCH, &infos[0], NULL, task);
        }
    }

    AddMatchTeam(team);

    return;
}



