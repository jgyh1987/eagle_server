#include "LogicPlayer.h"
#include "LogicService.h"
#include "World.h"
#include "Defs.h"
#include "LogicTask.h"
#include "ClientMsg.h"
#include "GM.h"
#include "ServerCommand.h"
#include "GameBaseTask.h"
#include "GameServerManager.h"

LogicPlayer::LogicPlayer(const PlayerInfoBase &playerInfo)
    :CIdNameSessionObject(playerInfo.playerId), EventManagerInterface(g_condition_to_event, EVENT_TYPE_MAX), m_playerInfo(playerInfo)
{
    m_id = playerInfo.playerId;
    m_session = playerInfo.account;
    m_name = playerInfo.account;

	m_playerInfo.playerUid = playerInfo.playerId;
}

LogicPlayer::~LogicPlayer()
{
    Clear();
}

void LogicPlayer::Clear()
{
	m_isAgent = false;
	m_playerInfo.Clear();
	m_roles.clear();
	SAFE_DELETE(m_role);

    return;
}

void LogicPlayer::SetGateServer(uint32_t gateServerId)
{
	if (gateServerId != m_playerInfo.gatewayServerId && m_playerInfo.gatewayServerId && gateServerId)
		KickPlayerOnline();

	m_playerInfo.gatewayServerId = gateServerId;
}

bool LogicPlayer::SendCmd(void* ptNull, uint32_t nCmdLen)
{
	if (!m_playerInfo.gatewayServerId)
		return false;

	ServerImp()->SendCmdToServerTask(ptNull, nCmdLen, SERVER_TYPE_LOGIC_GATEWAY, m_playerInfo.gatewayServerId);

	return true;
}

bool LogicPlayer::SendClientMsg(ClientMsg::Message* msg)
{
	if (!m_playerInfo.gatewayServerId)
		return false;

	return ServerImp()->SendClientMsg(msg, Uid(), m_playerInfo.gatewayServerId);
}

bool LogicPlayer::SendClientMsg(::google::protobuf::Message* message, int id)
{
	if (!m_playerInfo.gatewayServerId)
		return false;

	return ServerImp()->SendClientMsg(message, id, Uid(), m_playerInfo.gatewayServerId);
}

void LogicPlayer::NotifyClientError(uint32_t error)
{
	protocol::ErrorNotifyNet send;
	send.set_err(error);
	SendClientMsg(&send, protocol::sc_errorNotify);

	return;
}

void LogicPlayer::Update()
{
    if (!IsAgent())
        return ;

    return;
}

void LogicPlayer::UpdateSec()
{
    if (!IsAgent())
        return ;

    return;
}

void LogicPlayer::Update5Sec()
{
    if (!IsAgent())
        return ;

    return;
}

void LogicPlayer::UpdateMin()
{
    if (!IsAgent())
        return ;

    if (m_needSave)
    {
        Save();
    }


    return;
}

void LogicPlayer::UpdateHour()
{
    if (!IsAgent())
        return ;

    return;
}

void LogicPlayer::Update24()
{
    if (!IsAgent())
        return ;

    if (IsNextDay(m_playerInfo.lastOffTime))
    {
        m_counters.Refresh();

        
        m_playerInfo.lastOffTime = CImpServerTimeTick::currentTime.sec();
    }

    return;
}

bool LogicPlayer::FirstLogin()
{
    m_playerInfo.lastOffTime = CImpServerTimeTick::currentTime.sec();
    m_playerInfo.vipLevel = PLAYER_VIPLEVEL_DEFUAL;

    return true;
}

bool LogicPlayer::OnLogin()
{
    if (!m_playerInfo.lastOffTime)
    {
        FirstLogin();
    }

    //次日登录
    if (IsNextDay(m_playerInfo.lastOffTime))
    {
        m_counters.Refresh();

        m_playerInfo.lastOffTime = CImpServerTimeTick::currentTime.sec();
    }

    SetNeedSave(true);

    return true;
}

bool LogicPlayer::ReConnect()
{

    return true;
}

void LogicPlayer::NotifyLoginGame()
{
	ClientMsg::SelectLogicRes send;
	send.ret = SUCCESS;
	send.roleInfo.reserve(m_roles.size());
	for (uint32_t i = 0; i < m_roles.size(); ++i)
	{
		if (!m_roles[i].m_baseInfo.roleId)
			continue;
		Struct::RoleSimpleInfo info;
		info.jobId = m_roles[i].m_baseInfo.jobId;
		info.roleId = m_roles[i].m_baseInfo.roleId;

		send.roleInfo.push_back(info);
	}
	SendClientMsg(&send);

	return;
}

void LogicPlayer::SyncLoginMsg()
{
    
    return;
}

bool LogicPlayer::OnUnLogin()
{
    m_playerInfo.lastOffTime = CImpServerTimeTick::currentTime.sec();

    SetNeedSave(true);

    return true;
}

bool LogicPlayer::CanFree()
{
    if (AsyncMsg())
        return false;

    return true;
}

void LogicPlayer::KickPlayerOnline(uint32_t type)
{
    Cmd::t_Player_Kick_Notify send;
    send.ret = type;
    send.playerId = Id();
    SendCmd(&send, sizeof(send));

	if (type)
		World::instance()->AddRecoveryPlayer(this);

    return;
}

void LogicPlayer::EnterToWorld()
{
	EaglePos pos(m_role->GetRoleInfo()->pos);
	uint32_t serverId = GameServerManager::instance()->GetServerIdByMapId(m_role->GetRoleInfo()->mapId, pos);

	if (serverId)
	{
		Cmd::t_Enter_World_Req* send;
		World::instance()->ServerCmdBuffer(send);
		send->enterType = 1;
		SerializeWithEnter(send);
		ServerImp()->ProxySendCmd(send, send->Size(), SERVER_TYPE_WGAME_SERVER, serverId);

		m_isAgent = false;
	}
	else
		NotifyClientError(SCENE_SERVER_ERROR);

	//SerializeWorldPlayerInfo(send->data, send->len);

	//send->agent = 1;
	//SendCmd(send, send->Size());

	//Cmd::t_Role_Enter_Scene *send;
	//World::instance()->ServerCmdBuffer(send);
	//send->playerId = Id();
	////SerializeClientMainCityInfo(send->data, send->len);
	//SendCmd(send, send->Size());

	return;
}

void LogicPlayer::SerializeWithDB(Cmd::t_Data_Save_PlayerInfo_Req* send)
{
	m_playerInfo.lastOffTime = CImpServerTimeTick::currentTime.sec();
	send->playerinfo = m_playerInfo;

	uint8_t* buffer = send->data;
	uint32_t length = 0;

#define SERIALIZE_PLAYER_DATA(system)	\
    auto size = system.Serialize(buffer);	\
    BuffWriteMoveLen(buffer, length, size);
#include "PlayerData.inl"
#undef SERIALIZE_PLAYER_DATA

	send->allBinarrayLength = length;

    return;
}

bool LogicPlayer::UnSerializeWithDB(Cmd::t_Data_Get_PlayerInfo_Res* recv)
{
	//
	uint8_t* buffer = recv->data;
	uint32_t length = recv->playerDataLen;

	LOGD("LogicPlayer::UnSerialize Playerid = " << Id() << " length = " << length);

	do
	{

#define UNSERIALIZE_PLAYER_DATA(system)		\
    if (!length)								\
		break;								\
	{										\
		auto size = system.UnSerialize(buffer);	\
		BuffLoadMoveLen(buffer, length, size);	\
	}

#include "PlayerData.inl"
#undef UNSERIALIZE_PLAYER_DATA

	} while (false);

	if (recv->funType == 0)
	{
		m_isAgent = true;

		m_counters.Refresh();
	}

	length = recv->allBinarrayLength - recv->playerDataLen;

	if (!length)
		return true;

	UnSerializeRoleSimpleWithDB(recv->data + recv->playerDataLen, length);

	return true;
}

void LogicPlayer::SerializeWithEnter(Cmd::t_Enter_World_Req* send)
{
	//m_playerInfo.lastOffTime = CImpServerTimeTick::currentTime.sec();
	send->playerinfo = m_playerInfo;

	uint8_t* buffer = send->data;
	uint32_t length = 0;

#define SERIALIZE_PLAYER_DATA(system)	\
	{										\
		auto size = system.Serialize(buffer);	\
		BuffWriteMoveLen(buffer, length, size);	\
	}

#include "PlayerData.inl"
#undef SERIALIZE_PLAYER_DATA

	send->allBinarrayLength = send->playerDataLen = length;

	m_role->SerializeWithEnter(send);

	return;
}

void LogicPlayer::UnSerializeRoleSimpleWithDB(uint8_t* buffer, uint32_t length)
{
    BuffLoadInt(buffer, length, length);
    uint32_t count = 0;
    BuffLoadInt(buffer, length, count);

    m_roles.resize(count);
    for (uint32_t i = 0; i < count; ++i)
    {
        uint32_t roleLen = m_roles[i].UnSerializeWithDB(buffer);
        BuffLoadMoveLen(buffer, length, roleLen);
    }

    return;
}

void LogicPlayer::Save()
{
    if (!IsAgent())
        return;

    Cmd::t_Data_Save_PlayerInfo_Req *send;
    World::instance()->ServerCmdBuffer(send);

	send->serverId = g_serverId;
	send->serverType = SERVER_TYPE_LOGIC_SERVER;
	
    SerializeWithDB(send);

    SendToDB(send, send->Size());

    m_needSave = false;

    return ;
}

//Off Player Data CallBack
void LogicPlayer::OffPlayerDataCallBack(LogicPlayer *target, uint32_t funType)
{
    switch (funType)
    {
    case OFF_PLAYER_FUN_TYPE_JJC:
        {
        }
        break;
    default:
        break;
    }

    return;
}

Cmd::t_Data_Update_Item_Req *LogicPlayer::BeginUpdateItem()
{
    Cmd::t_Data_Update_Item_Req *send;
    World::instance()->ServerItemCmdBuffer(send);

    send->playerId = Id();
	if (m_role)
		send->roleId = m_role->RoleId();
    send->serverId = g_serverId;
    send->serverType = SERVER_TYPE_LOGIC_SERVER;

    return send;
}

void LogicPlayer::EndUpdateItem(Cmd::t_Data_Update_Item_Req *send, bool saveRole)
{
    SendToDB(send, send->Size());

    return;
}

bool LogicPlayer::InitRoleInfo(Cmd::t_Data_GetRoleInfo_Res *recv)
{
	SAFE_DELETE(m_role);
	m_role = new LogicRole(this);
    if (m_role && m_role->Init(recv))
        return true;

	SAFE_DELETE(m_role);

    return false;
}

//
//Login Msg
bool LogicPlayer::ParaseLoginMessage(BinaryReadStream &stream, uint32_t minorCmd)
{
    switch (minorCmd)
    {
        case ClientMsg::EnterWorldReq::MINOR_CMD:
        {
            if (AsyncMsg())
                return false;

            stream.Reset();
            ClientMsg::EnterWorldReq msg;
            if (msg.Unserialize(&stream) != 0)
            {
                LOGFMTE("ClientMsg::EnterMapReq msg Unserialize Error");
                return false;
            }

            auto curRole = HaveRole(msg.roleId);
            if (-1 == curRole)
            {
                LOGE("ClientMsg::EnterWorldReq not find role, account = " << Account() << " playerId = " << Id() << " roleId = " << msg.roleId);
                //
            
                ClientMsg::EnterWorldRes send;
                send.ret = NO_ROLEINFO;
                SendClientMsg(&send);
            }
            else
            {
                Cmd::t_Data_GetRoleInfo_Req send;
                send.playerId = Id();
                send.roleId = msg.roleId;
                SendToDB(&send, sizeof(send));
                SetAsyncMsg(true);
            }
        }
        break;
        case ClientMsg::DeleteRoleReq::MINOR_CMD:
        {
            stream.Reset();
            ClientMsg::DeleteRoleReq msg;
            if (msg.Unserialize(&stream) != 0)
            {
                LOGFMTE("ClientMsg::DeleteRoleReq msg Unserialize Error");
                return false;
            }

            //if (!GetRoleInfoByRoleId(msg.roleId))
            //{
            //    LOGE("Cmd::DeleteRoleRes not find role, roleId = "<<msg.roleId<<"account:"<<Account());

            //    //
            //    ClientMsg::DeleteRoleRes send;
            //    send.ret = NO_ROLEINFO;
            //    SendClientMsg(&send);
            //}
            //else
            //{
            //    //
            //    Cmd::t_Data_DeleteRole_Req send;
            //    send.roleId = msg.roleId;
            //    send.playerId = Id();
            //    SendToDB(&send, sizeof(send));
            //}
        }
        break;
        case ClientMsg::CreateRoleReq::MINOR_CMD:
        {
            stream.Reset();
            ClientMsg::CreateRoleReq msg;
            if (msg.Unserialize(&stream) != 0)
            {
                LOGFMTE("ClientMsg::CreateRoleReq msg Unserialize Error");
                return false;
            }
            return MessageCreateRole(msg);
        }
        break;
    default:
        break;
    }
    return true;
}

bool LogicPlayer::ParaseLoginMessage(protocol::PackageNet *data)
{
    switch (data->id())
    {
    case protocol::cs_createRole:
        {
            MessageCreateRole(data);
        }
        break;
    default:
        break;
    }


    return true;
}

//PlayerInfo Msg
#define ParasePlayerInfoMsgFunMax 200
typedef bool (*ParasePlayerInfoMsgFun)(BinaryReadStream &stream, LogicPlayer *player);
ParasePlayerInfoMsgFun g_parasePlayerInfoMsgFun[ParasePlayerInfoMsgFunMax] = {NULL};

bool RecvMailReq(BinaryReadStream &stream, LogicPlayer *player)
{
    stream.Reset();
    ClientMsg::RecvMailReq msg;
    if(msg.Unserialize(&stream) != 0)
        return false;
    //return MailManager::instance()->RecvMail(player, &msg);
    return true;
}


void InitParasePlayerInfoMsgFun()
{
    g_parasePlayerInfoMsgFun[ClientMsg::RecvMailReq::MINOR_CMD] = RecvMailReq;
    
    return;
}

bool LogicPlayer::ParasePlayerInfoMessage(BinaryReadStream &stream, uint32_t minorCmd)          
{
    if (!m_role)
    {

        return false;
    }
    
    if (minorCmd <= ParasePlayerInfoMsgFunMax && g_parasePlayerInfoMsgFun[minorCmd])
        return g_parasePlayerInfoMsgFun[minorCmd](stream, this);

    return false;
}

bool LogicPlayer::ParasePlayerInfoMessage(protocol::PackageNet *data)
{
    if (!m_role)
    {
        return false;
    }

    switch (data->id())
    {
    default:
        break;
    }


    return true;
}

//Chat Msg
bool LogicPlayer::ParaseChatMessage(BinaryReadStream &stream, uint32_t majorCmd)
{
    switch (majorCmd)
    {
    case  ClientMsg::GMCMDReq::MINOR_CMD:
    {
        stream.Reset();
        ClientMsg::GMCMDReq msg;
        if (msg.Unserialize(&stream) != 0)
            return false;

        if (m_playerInfo.authority)
        {
            std::string out;
            GMCommandManager::instance()->parse(msg.str, out);
        }

        return true;
    }
    break;
    case  ClientMsg::PMReq::MINOR_CMD:
    {
        stream.Reset();
        ClientMsg::PMReq msg;
        if (msg.Unserialize(&stream) != 0)
            return false;


        LogicPlayer *player = World::instance()->GetPlayerByID(msg.playerId);
        if (player)
        {
            ClientMsg::PMRes send;
            send.chaterName = Name();
            send.chatMessage = msg.chatMessage;
            send.playerId = Id();
            player->SendClientMsg(&send);
        }

        return true;
    }
    break;
    default:break;
    }

    return true;
}

bool LogicPlayer::ParaseChatMessage(protocol::PackageNet *data)
{
    switch (data->id())
    {
    case protocol::cs_GMCMD:
    {
        protocol::GMCMDReqNet stream;
        stream.ParseFromArray((void *)data->body().c_str(), (int)data->body().size());
        MessageGMCMD(stream.cmd());
    }
    break;
    default:
        break;
    }


    return true;
}

void LogicPlayer::MessageGMCMD(const std::string &cmd)
{
    protocol::GMCMDRspNet send;
    if (!m_playerInfo.authority)
    {
        protocol::GMCMDRspNet send;
        send.set_ret("NO_GM_AUTH_ERROR");
    }
    else 
    {
        std::string out;
        GMCommandManager::instance()->parse(cmd, out);
        send.set_ret(out);
    }

    SendClientMsg(&send, protocol::sc_GMCMD);

    return;
}

//World Msg
bool LogicPlayer::ParaseWorldMessage(BinaryReadStream &stream, uint32_t minorCmd)
{
    switch (minorCmd)
    {
    case ClientMsg::WorldMatchReq::MINOR_CMD:
    {
        stream.Reset();
        ClientMsg::WorldMatchReq msg;
        if (msg.Unserialize(&stream) != 0)
        {
            LOGFMTE("ClientMsg::WorldMatchReq msg Unserialize Error");
            return false;
        }


    }
    break;
    default:
        break;
    }

    return true;
}

//Friend Msg
bool LogicPlayer::ParaseFriendMessage(BinaryReadStream &stream, uint32_t minorCmd, uint8_t *ptr, uint32_t len)
{
    return true;
}

//scene cmd
bool LogicPlayer::ParaseSceneCmd(Cmd::t_NullCmd *recv)
{
    
    return true;
}

//world cmd
bool LogicPlayer::WorldMatchRes(Cmd::t_World_Match_Res *recv)
{
    //ClientMsg::WorldMatchRes send;
    //send.ret = recv->ret;
    if (SUCCESS == recv->ret)
    {
        //send.dungeonBaseInfo.serverNetInfo.ip = recv->wdungeonInfo.ip;
        //send.dungeonBaseInfo.serverNetInfo.port = recv->wdungeonInfo.port;
        //send.dungeonBaseInfo.serverNetInfo.serverId = recv->wdungeonInfo.wfightServerId;
        //send.dungeonBaseInfo.dungeonUid = recv->wdungeonInfo.dungeonUid;
        //send.dungeonBaseInfo.serverNetInfo.serverType = "PVPServer";
    }
    //SendClientMsg(&send);

    return true;
}

//
bool LogicPlayer::MessageCreateRole(const ClientMsg::CreateRoleReq &msg)
{
    if (msg.name.size() >= MAX_PLAYER_NAME || msg.name.size() == 0)
    {
        LOGFMTT("ClientMsg::CreateRoleReq name error, name:%s", msg.name.c_str());
        return false;
    }

    RoleConfigData *data = RoleConfigDataManager::instance()->get(msg.jobId);
    if (!data)
    {
        return false;
    }

    if (m_roles.size() >= m_playerInfo.roleSolt)
        return false;

    Cmd::t_Data_Create_RoleInfo_Req send;
    strncpy(send.info.name, msg.name.c_str(), MAX_PLAYER_NAME - 1);
    send.info.jobId = msg.jobId;
    send.info.playerId = Id();
    send.info.level = 1;
    send.gameserverId = g_gameServerId;

    SendToDB(&send, sizeof(send));

    return true;
}

bool LogicPlayer::MessageCreateRole(const protocol::PackageNet *data)
{
    protocol::CreateRoleReqNet stream;
    stream.ParseFromArray((void *)data->body().c_str(), (int)data->body().size());

    protocol::CreateRoleRspNet send;
    do
    {
        if (stream.name().size() >= MAX_PLAYER_NAME || stream.name().size() == 0)
        {
            LOGFMTT("ClientMsg::CreateRoleReq name error, name:%s", stream.name().c_str());
            send.set_ret(INPUT_CHARACTER_LENGTH_MAX);
            break;
        }

        //RoleConfigData *data = RoleConfigDataManager::instance()->get(stream.jobid());
        //if (!data)
        //{
        //    break;
        //}
        //else if (data->genderlimite != stream.sex())
        //{
        //    break;
        //}

    //    if (!GetEmptyRoleSlot(slot))
    //    {
    //        LOGD("ClientMsg::CreateRoleReq role full = " << Account());
    //        //��ɫ��
    //        send.set_ret(MAX_ROLE_ERROR);
    //        break;
    //    }
    //    else
    //    {
    //        InitializesConfigData *data = InitializesConfigDataManager::instance()->get(stream.jobid());
    //        if (!data)
    //        {
    //            send.set_ret(NO_ROLEINFO);
    //            break;
    //        }

    //        Cmd::t_Data_Create_RoleInfo_Req send;
    //        strncpy(send.info.name, stream.name().c_str(), MAX_PLAYER_NAME - 1);
    //        send.info.jobId = stream.jobid();
    //        send.info.sex = stream.sex();
    //        send.info.playerId = Id();
    //        send.info.level = data->level;
    //        send.info.mapId = data->mapId;
    //        send.gameserverId = g_gameServerId;
    //        SendToDB(&send, sizeof(send));
    //        return true;
    //    }
    } while (false);
    
    SendClientMsg(&send, protocol::sc_createRole);

    return false;
}

void LogicPlayer::AddRoleInfo(const RoleInfoBase &roleinfo)
{
    //if (slot >= MAX_BUY_ROLE_NUM)
    //    return;
    //bcopy(&roleinfo, &m_allrolebase[slot], sizeof(RoleInfoBase));


    m_roles.push_back(SimpleRole());
    m_roles[m_roles.size() - 1].m_baseInfo = roleinfo;

    return;
}

int32_t LogicPlayer::HaveRole(uint64_t roleId)
{
    for (uint32_t i = 0; i < m_roles.size(); ++i)
        if (roleId == m_roles[i].m_baseInfo.roleId)
            return i;

    return -1;
}

void LogicPlayer::NotifyCreateRole(Cmd::t_Data_Create_RoleInfo_Res *recv)
{
    ClientMsg::CreateRoleRes send;
    send.ret = recv->ret;
    send.roleInfo.roleId = recv->roleinfo.roleId;
    send.roleInfo.jobId = recv->roleinfo.jobId;
    SendClientMsg(&send);

    //protocol::CreateRoleRspNet send;
    //send.set_ret(recv->ret);
    //protocol::RoleBaseInfo *role = send.mutable_role();
    //role->set_roleid(recv->roleinfo.roleId);
    //role->set_name(recv->roleinfo.name);
    //role->set_jobid(recv->roleinfo.jobId);
    //role->set_sex(recv->roleinfo.sex);
    //role->set_level(recv->roleinfo.level);
    //role->set_maincityid(recv->roleinfo.mapId);
    //SendClientMsg(&send, protocol::sc_createRole);

    return;
}




