#include "Match1V1Info.h"
#include "WMatchManager.h"
#include "WMatchService.h"
#include "MatchTeam.h"
#include "World.h"

//MatchSoloInfo
MatchSoloInfo::~MatchSoloInfo()
{
    
}



void MatchSoloInfo::MatchCallback(Cmd::t_World_Create_Fight_Res *recv)
{
    Cmd::t_World_Match_Res send;
    send.ret = recv->ret;

    if (SUCCESS == recv->ret)
    {
        m_wDungeonBaseInfo.dungeonUid = recv->wdungeonInfo.dungeonUid;
        send.wdungeonInfo = m_wDungeonBaseInfo;
    }

    send.playerInfo.playerId = m_player.playerId;
    ServerImp()->ProxySendCmd(&send, sizeof(send), SERVER_TYPE_LOGIC_SERVER, m_player.logicServerId);

    return;
}

/////Match1V1Info///////////////////////////////////////////////////////////
Match1V1Info::Match1V1Info()
{
    m_baseInfo.matchType = OBJECT_DUNGEON_1V1;
    m_teams.resize(2, NULL);
}

uint32_t Match1V1Info::SendCreateFightReq()
{
    WGateServerInfo *gateInfo = WMatchManager::instance()->GetWGateServer();
    WFightServerInfo *fightInfo = WMatchManager::instance()->GetWFightServer();
    if (!gateInfo || !fightInfo)
    {
        for (auto v : m_teams)
        {
            v->NotifyError(WORLD_FIGHT_SERVER_ERROR, this);
        }

        return DEFAULT_ERROR;
    }

    memcpy(m_wDungeonBaseInfo.ip, gateInfo->info.serverIP, sizeof(m_wDungeonBaseInfo.ip));
    m_wDungeonBaseInfo.tcpPort = gateInfo->info.port;
    m_wDungeonBaseInfo.udpPort = gateInfo->info.gameServerId;

    m_wDungeonBaseInfo.wServerId = fightInfo->info.serverId;

    if (m_wDungeonBaseInfo.tcpPort && m_wDungeonBaseInfo.wServerId)
    {
        Cmd::t_World_Create_Fight_Req *cmd;
        World::instance()->ServerCmdBuffer(cmd);
        cmd->matchInfo = m_baseInfo;
        uint8_t *ptr = cmd->data;

        for (auto v : m_teams)
        {
            uint32_t length = 0;
            v->Serialize(ptr, length, cmd->playerCount);
            ptr += length;
            cmd->len += length;
        }

        ServerImp()->ProxySendCmd(cmd, cmd->Size(), SERVER_TYPE_WGAME_SERVER, m_wDungeonBaseInfo.wServerId);

        WMatchManager::instance()->AddMatch(this);

        return SUCCESS;
    }
    else
    {
        for (auto v : m_teams)
        {
            v->NotifyError(WORLD_FIGHT_SERVER_ERROR, this);
        }
    }

    return DEFAULT_ERROR;
}

void Match1V1Info::MatchCallback(Cmd::t_World_Create_Fight_Res *recv)
{
    Cmd::t_World_Match_Res send;
    send.ret = recv->ret;

    if (SUCCESS == recv->ret)
    {
        m_wDungeonBaseInfo.dungeonUid = recv->wdungeonInfo.dungeonUid;
        send.wdungeonInfo = m_wDungeonBaseInfo;
    }

    for (auto v : m_teams)
    {
        v->SendMatchRes(&send, sizeof(send));
    }

    return;
}


//////////Match3V3Info//////////////////////////////////////////////////////////////////

Match3V3Info::Match3V3Info()
{
    m_baseInfo.matchType = OBJECT_DUNGEON_3V3;
    m_teams.resize(2, NULL);
}

uint32_t Match3V3Info::SendCreateFightReq()
{
    WGateServerInfo *gateInfo = WMatchManager::instance()->GetWGateServer();
    WFightServerInfo *fightInfo = WMatchManager::instance()->GetWFightServer();
    if (!gateInfo || !fightInfo)
    {
        for (auto v : m_teams)
        {
            v->NotifyError(WORLD_FIGHT_SERVER_ERROR, this);
        }

        return DEFAULT_ERROR;
    }

    memcpy(m_wDungeonBaseInfo.ip, gateInfo->info.serverIP, sizeof(m_wDungeonBaseInfo.ip));
    m_wDungeonBaseInfo.tcpPort = gateInfo->info.port;
    m_wDungeonBaseInfo.udpPort = gateInfo->info.gameServerId;

    m_wDungeonBaseInfo.wServerId = fightInfo->info.serverId;

    if (m_wDungeonBaseInfo.tcpPort && m_wDungeonBaseInfo.wServerId)
    {
        Cmd::t_World_Create_Fight_Req *cmd;
        World::instance()->ServerCmdBuffer(cmd);
        cmd->matchInfo = m_baseInfo;
        uint8_t *ptr = cmd->data;

        for (auto v : m_teams)
        {
            uint32_t length = 0;
            v->Serialize(ptr, length, cmd->playerCount);
            ptr += length;
            cmd->len += length;
        }

        ServerImp()->ProxySendCmd(cmd, cmd->Size(), SERVER_TYPE_WGAME_SERVER, m_wDungeonBaseInfo.wServerId);

        WMatchManager::instance()->AddMatch(this);

        return SUCCESS;
    }
    else
    {
        for (auto v : m_teams)
        {
            v->NotifyError(WORLD_FIGHT_SERVER_ERROR, this);
        }
    }

    return DEFAULT_ERROR;
}

void Match3V3Info::MatchCallback(Cmd::t_World_Create_Fight_Res *recv)
{
    Cmd::t_World_Match_Res send;
    send.ret = recv->ret;

    if (SUCCESS == recv->ret)
    {
        m_wDungeonBaseInfo.dungeonUid = recv->wdungeonInfo.dungeonUid;
        send.wdungeonInfo = m_wDungeonBaseInfo;
    }

    for (auto v : m_teams)
    {
        v->SendMatchRes(&send, sizeof(send));
    }

    return;
}


