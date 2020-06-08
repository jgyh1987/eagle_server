#include "WGamePlayer.h"
#include "WGameService.h"
#include "World.h"
#include "Defs.h"
#include "WGameTask.h"
#include "ClientMsg.h"
#include "ServerCommand.h"
#include "WorldCommand.h"
#include "SharedEvent.h"
#include "Fighter.h"

//GamePlayerSystem
bool GamePlayerSystem::InitEntityData(ECS::ECSEntity* entity)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return false;

	RoleConfigData* initData = RoleConfigDataManager::instance()->get(playerCmp->m_player->GetRole()->GetRoleInfo()->jobId);
	if (!initData)
		return false;

	playerCmp->m_wdungeonInfo.dungeonId = initData->initDungeonId;

	return true;
}

bool GamePlayerSystem::OnEnterServer(ECS::ECSEntity* entity)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return false;

	return true;
}

void GamePlayerSystem::Clear(ECS::ECSEntity *entity)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return;

	if (playerCmp->m_world)
	{
		playerCmp->m_world->EntityExit(entity);
	}


	return;
}

uint32_t GamePlayerSystem::Serialize(ECS::ECSEntity* entity, uint8_t* buffer)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return 0;

	uint32_t length = 0;
	uint32_t* pLen = (uint32_t*)buffer;
	BuffWriteMoveLen(buffer, length, UINT32_LEN);

	BuffWriteInt(buffer, length, GAMEPLAYER_CMP_VERSION_1_1);

	bcopy(&playerCmp->m_wdungeonInfo, buffer, sizeof(playerCmp->m_wdungeonInfo));
	BuffWriteMoveLen(buffer, length, sizeof(playerCmp->m_wdungeonInfo));
	
	*pLen = length;

	return length;
}

uint32_t GamePlayerSystem::UnSerialize(ECS::ECSEntity* entity, uint8_t* buffer)
{
	uint32_t length = 0;
	BuffLoadInt(buffer, length, length);
	uint32_t ret = length + UINT32_LEN;

	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
	{
		return ret;
	}

	BuffLoadMoveLen(buffer, length, UINT32_LEN);	//version

	bcopy(buffer, &playerCmp->m_wdungeonInfo, sizeof(playerCmp->m_wdungeonInfo));
	BuffLoadMoveLen(buffer, length, sizeof(playerCmp->m_wdungeonInfo));

	return ret;
}

void GamePlayerSystem::SetNeedSave(ECS::ECSEntity* entity, bool noDelay)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return;

	playerCmp->m_player->SetNeedSave(noDelay);

	return;
}

void GamePlayerSystem::SendClientMsg(ECS::ECSEntity* entity, ClientMsg::Message* msg)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return ;

	if (!playerCmp->m_player->GetGateServerId() || !playerCmp->m_player->GetGateServerType())
		return ;

	Cmd::t_Server_Send_Trans_Msg* send = NULL;
	World::instance()->ServerCmdBuffer(send);
	BinaryWriteStream stream((char*)(send->data), SERVER_COMMAND_MAX_LENGTH - sizeof(Cmd::t_Server_Send_Trans_Msg));
	if (msg->Serialize(&stream) != 0)
	{
		LOGFMTE("msg serialize error（%d, %d）", msg->majorCmd, msg->minorCmd);
		return ;
	}
	stream.Flush();
	send->uid = playerCmp->m_player->Uid();
	send->dataLen = (uint32_t)stream.GetSize();
	send->targetServer.serverType = CLIENT_TYPE;
	send->srcServer.serverType = SERVER_TYPE_WGAME_SERVER;
	ServerImp()->SendCmdToServerTask(send, (uint32_t)send->Size(), playerCmp->m_player->GetGateServerType(), playerCmp->m_player->GetGateServerId());

	return ;
}

void GamePlayerSystem::SendClientMsg(ECS::ECSEntity* entity, ::google::protobuf::Message* message, int id)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return;

	if (!playerCmp->m_player->GetGateServerId() || !playerCmp->m_player->GetGateServerType())
		return ;

	Cmd::t_Server_Send_Trans_Msg* send = NULL;
	World::instance()->ServerCmdBuffer(send);
	int len = (int)message->ByteSizeLong();
	message->SerializeToArray(send->data, len);

	protocol::PackageNet stream;
	stream.set_id(id);
	stream.set_body(send->data, len);

	len = (int)stream.ByteSizeLong();
	stream.SerializeToArray(send->data, len);
	send->uid = playerCmp->m_player->Uid();
	send->dataLen = len;
	send->targetServer.serverType = CLIENT_TYPE;
	send->srcServer.serverType = SERVER_TYPE_WGAME_SERVER;
	ServerImp()->SendCmdToServerTask(send, (uint32_t)send->Size(), playerCmp->m_player->GetGateServerType(), playerCmp->m_player->GetGateServerId());

	return ;
}

void GamePlayerSystem::NotifyClientError(ECS::ECSEntity* entity, uint32_t error)
{
	protocol::ErrorNotifyNet send;
	send.set_err(error);
	SendClientMsg(entity, &send, protocol::sc_errorNotify);

	return;
}

void GamePlayerSystem::NotifyClientItemChange(ECS::ECSEntity* entity, bool send)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return;

	if (send)
	{
		if (playerCmp->m_itemChangeNotify.infos_size())
			SendClientMsg(entity, &playerCmp->m_itemChangeNotify, protocol::sc_itemChangeNotify);

		if (playerCmp->m_equipChangeNotify.infos_size())
			SendClientMsg(entity, &playerCmp->m_equipChangeNotify, protocol::sc_equipChangeNotify);
	}

	playerCmp->m_itemChangeNotify.Clear();
	playerCmp->m_equipChangeNotify.Clear();

	return;
}

EagleAction* GamePlayerSystem::CreateAction(ECS::ECSEntity* entity, uint32_t type, const std::vector<ConditionParm>& vecCmp, void* ptr2)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return NULL;

	auto action = ::CreateAction(type, entity, ptr2);
	if (action)
	{
		for (uint32_t i = 0; i < vecCmp.size(); ++i)
		{
			CreateCondition(action, vecCmp[i].type, vecCmp[i].value.c_str());
		}
	}

	return action;
}

bool GamePlayerSystem::RegisterEventAction(ECS::ECSEntity* entity, EagleAction* action)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return false;

	playerCmp->m_player->RegisterEventAction(action);

	return true;
}

EagleAction* GamePlayerSystem::RegisterEventAction(ECS::ECSEntity* entity, uint32_t type, const std::vector<ConditionParm>& vecCmp, void* ptr2)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return NULL;

	auto action = ::CreateAction(type, entity, ptr2);
	if (action)
	{
		for (uint32_t i = 0; i < vecCmp.size(); ++i)
		{
			CreateCondition(action, vecCmp[i].type, vecCmp[i].value.c_str());
		}
	}

	playerCmp->m_player->RegisterEventAction(action);

	return action;
}

void GamePlayerSystem::UnRegisterEventAction(ECS::ECSEntity* entity, EagleAction* action)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return;

	playerCmp->m_player->UnRegisterEventAction(action);

	return;
}

void GamePlayerSystem::GamePlayerDoEvent(ECS::ECSEntity* entity, EagleEvent& event)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return;

	LogicDoEvent<WGamePlayer> _event(playerCmp->m_player, event);
	_event();

	return;
}

Fighter *GamePlayerSystem::CreateFighter(ECS::ECSEntity* entity)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return NULL;

	if (!playerCmp->m_world)
		return NULL;

	playerCmp->m_fighter = new Fighter(playerCmp->m_player);

	return playerCmp->m_fighter;
}

Fighter *GamePlayerSystem::GetFighter(ECS::ECSEntity* entity)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return NULL;

	return playerCmp->m_fighter;
}

void GamePlayerSystem::SetWorld(ECS::ECSEntity* entity, EagleWorld* d)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return ;

	playerCmp->m_world = d;

	return;
}

EagleWorld* GamePlayerSystem::GetWorld(ECS::ECSEntity* entity)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return NULL;

	return playerCmp->m_world;
}

WGameDungeon* GamePlayerSystem::GetDungeon(ECS::ECSEntity* entity)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return NULL;

	if (playerCmp->m_world->IsType(OBJECT_DUNGEON))
		return (WGameDungeon *)playerCmp->m_world;
	
	return NULL;
}

void GamePlayerSystem::ClearDungeonInfo(ECS::ECSEntity* entity)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return;

	if (playerCmp->m_world->IsType(OBJECT_DUNGEON))
	{
		playerCmp->m_world = NULL;
		playerCmp->m_wdungeonInfo.Clear();

		SetNeedSave(entity);

	}

	return;
}

EagleLandmassEx* GamePlayerSystem::GetLandmass(ECS::ECSEntity* entity)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return NULL;

	if (playerCmp->m_world->IsType(OBJECT_LANDMASS))
		return (EagleLandmassEx *)playerCmp->m_world;

	return NULL;
}

RoleInfoBase *GamePlayerSystem::GetRoleBaseInfo(ECS::ECSEntity* entity)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return NULL;

	return playerCmp->m_player->GetRole()->GetRoleInfo();
}

WDungeonBaseInfo *GamePlayerSystem::GetDungeonBaseInfo(ECS::ECSEntity* entity)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return NULL;

	return &playerCmp->m_wdungeonInfo;
}

//Fight Msg
bool GamePlayerSystem::ParaseFightMessage(ECS::ECSEntity* entity, BinaryReadStream &stream, uint32_t minorCmd)
{
	switch (minorCmd)
	{
		//case ClientMsg::KillMonsterReq::MINOR_CMD:
		//{
		//    stream.Reset();
		//    ClientMsg::KillMonsterReq msg;
		//    if (msg.Unserialize(&stream) != 0)
		//    {
		//        LOGFMTE("ClientMsg::KillMonsterReq msg Unserialize Error");
		//        return false;
		//    }

		//    MessageKillMonsterReq(msg);
		//}
		//break;
	default:
		break;
	}

	return true;
}

//Map Msg
bool GamePlayerSystem::ParaseMapMessage(ECS::ECSEntity* entity, BinaryReadStream &stream, uint32_t minorCmd)
{
	switch (minorCmd)
	{
	case ClientMsg::EnterMapReq::MINOR_CMD:
	{
		stream.Reset();
		ClientMsg::EnterMapReq msg;
		if (msg.Unserialize(&stream) != 0)
		{
			LOGFMTE("ClientMsg::EnterMapReq msg Unserialize Error");
			return false;
		}

		//EnterScene();
	}
	break;
	case ClientMsg::KillNpcReq::MINOR_CMD:
	{
		stream.Reset();
		ClientMsg::KillNpcReq msg;
		if (msg.Unserialize(&stream) != 0)
		{
			LOGFMTE("ClientMsg::KillNpcReq msg Unserialize Error");
			return false;
		}

		MessageKillNpcReq(entity, msg);
	}
	break;
	case ClientMsg::LeaveDungeonReq::MINOR_CMD:
	{
		stream.Reset();
		ClientMsg::LeaveDungeonReq msg;
		if (msg.Unserialize(&stream) != 0)
		{
			LOGFMTE("ClientMsg::LeaveDungeonReq msg Unserialize Error");
			return false;
		}

		MessageLeaveDungeonReq(entity, msg);
	}
	break;
	case ClientMsg::EnterFinish::MINOR_CMD:
	{
		stream.Reset();
		ClientMsg::EnterFinish msg;
		if (msg.Unserialize(&stream) != 0)
		{
			LOGFMTE("ClientMsg::EnterFinish msg Unserialize Error");
			return false;
		}

		MessageEnterFinish(entity, msg);
	}
	break;
	default:
		break;
	}

	return true;
}

void GamePlayerSystem::MessageKillNpcReq(ECS::ECSEntity* entity, ClientMsg::KillNpcReq& msg)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return;

	if (playerCmp->m_world && playerCmp->m_world->IsType(OBJECT_DUNGEON_MAIN))
		((MainDungeon *)playerCmp->m_world)->MonsterDieById(msg.id);

	return;
}

void GamePlayerSystem::MessageLeaveDungeonReq(ECS::ECSEntity* entity, ClientMsg::LeaveDungeonReq& msg)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return;

	if (playerCmp->m_world)
		WGameWorldManager::instance()->ExitDungeon(entity);

	return;
}

void GamePlayerSystem::MessageEnterFinish(ECS::ECSEntity* entity, ClientMsg::EnterFinish& msg)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return;

	auto fighter = CreateFighter(entity);
	if (fighter)
		playerCmp->m_world->EntityEnter(fighter->GetEntity());

	return;
}

//PlayerInfo Msg
#define ParasePlayerInfoMsgFunMax 200
typedef bool(*ParasePlayerInfoMsgFun)(BinaryReadStream &stream, ECS::ECSEntity* entity);
ParasePlayerInfoMsgFun g_parasePlayerInfoMsgFun[ParasePlayerInfoMsgFunMax] = { NULL };

bool RecvMailReq(BinaryReadStream &stream, ECS::ECSEntity* entity)
{
	stream.Reset();
	ClientMsg::RecvMailReq msg;
	if (msg.Unserialize(&stream) != 0)
		return false;
	//return MailManager::instance()->RecvMail(player, &msg);
	return true;
}

bool QuestReceiveReq(BinaryReadStream &stream, ECS::ECSEntity* entity)
{
	stream.Reset();
	ClientMsg::QuestReceiveReq msg;
	if (msg.Unserialize(&stream) != 0)
		return false;

	QuestSystem::instance()->Receive(entity, msg.id);

	return true;
}

bool ClientNotifyCmpQuestReq(BinaryReadStream &stream, ECS::ECSEntity* entity)
{
	stream.Reset();
	ClientMsg::ClientNotifyCmpQuestReq msg;
	if (msg.Unserialize(&stream) != 0)
		return false;

	QuestSystem::instance()->ClientComplete(entity, msg.id);

	return true;
}

void InitParasePlayerInfoMsgFun()
{
	g_parasePlayerInfoMsgFun[ClientMsg::RecvMailReq::MINOR_CMD] = RecvMailReq;
	g_parasePlayerInfoMsgFun[ClientMsg::QuestReceiveReq::MINOR_CMD] = QuestReceiveReq;
	g_parasePlayerInfoMsgFun[ClientMsg::ClientNotifyCmpQuestReq::MINOR_CMD] = ClientNotifyCmpQuestReq;

	return;
}

bool GamePlayerSystem::ParasePlayerInfoMessage(ECS::ECSEntity* entity, BinaryReadStream &stream, uint32_t minorCmd)
{
	if (minorCmd <= ParasePlayerInfoMsgFunMax && g_parasePlayerInfoMsgFun[minorCmd])
		return g_parasePlayerInfoMsgFun[minorCmd](stream, entity);

	return false;
}

bool GamePlayerSystem::ParasePlayerInfoMessage(ECS::ECSEntity* entity, protocol::PackageNet *data)
{
	switch (data->id())
	{
	default:
		break;
	}


	return true;
}

//Chat Msg
bool GamePlayerSystem::ParaseChatMessage(ECS::ECSEntity* entity, BinaryReadStream &stream, uint32_t majorCmd)
{
	switch (majorCmd)
	{
	case  ClientMsg::GMCMDReq::MINOR_CMD:
	{
		stream.Reset();
		ClientMsg::GMCMDReq msg;
		if (msg.Unserialize(&stream) != 0)
			return false;

		//if (m_playerInfo.authority)
		//{
		//    std::string out;
		//    GMCommandManager::instance()->parse(msg.str, out);
		//}

		return true;
	}
	break;
	default:break;
	}

	return true;
}

bool GamePlayerSystem::ParaseChatMessage(ECS::ECSEntity* entity, protocol::PackageNet *data)
{
	switch (data->id())
	{
	case protocol::cs_GMCMD:
	{
		protocol::GMCMDReqNet stream;
		stream.ParseFromArray((void *)data->body().c_str(), (int)data->body().size());
		MessageGMCMD(entity, stream.cmd());
	}
	break;
	default:
		break;
	}


	return true;
}

void GamePlayerSystem::MessageGMCMD(ECS::ECSEntity* entity, const std::string &cmd)
{
	//protocol::GMCMDRspNet send;
	//if (!m_playerInfo.authority)
	//{
	//    protocol::GMCMDRspNet send;
	//    send.set_ret("NO_GM_AUTH_ERROR");
	//}
	//else 
	//{
	//    std::string out;
	//    GMCommandManager::instance()->parse(cmd, out);
	//    send.set_ret(out);
	//}

	//SendClientMsg(&send, protocol::sc_GMCMD);

	return;
}

//World Msg
bool GamePlayerSystem::ParaseWorldMessage(ECS::ECSEntity* entity, BinaryReadStream &stream, uint32_t minorCmd)
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
bool GamePlayerSystem::ParaseFriendMessage(ECS::ECSEntity* entity, BinaryReadStream &stream, uint32_t minorCmd, uint8_t *ptr, uint32_t len)
{
	return true;
}

bool GamePlayerSystem::BuyBagSolt(ECS::ECSEntity* entity)
{
	protocol::BuyBagSoltRspNet sendClient;
	sendClient.set_ret(SUCCESS);


	return true;
}

//WGamePlayer
WGamePlayer::WGamePlayer(const PlayerInfoBase &playerInfo, uint32_t gateServerType)
    :CIdNameSessionObject(playerInfo.playerUid), EventManagerInterface(g_condition_to_event, EVENT_TYPE_MAX), m_gateServerType(gateServerType), m_needSave(false), m_asyncMsg(false), m_playerInfo(playerInfo), m_role(this)
{
    m_id = playerInfo.playerId;
    m_session = playerInfo.account;
    m_name = playerInfo.account;
}

WGamePlayer::~WGamePlayer()
{

}

void WGamePlayer::Update()
{

    return;
}

void WGamePlayer::UpdateSec()
{

    return;
}

void WGamePlayer::Update5Sec()
{

    if (m_needSave)
    {
        Save();
    }

    return;
}

void WGamePlayer::UpdateMin()
{

    //GetQuestManager()->UpdateTime();


    return;
}

void WGamePlayer::UpdateHour()
{

    return;
}

void WGamePlayer::Update24()
{

    if (m_playerInfo.lastOffTime < DelayDayStart())
    {
        PlayerCounters()->Refresh();

        
        m_playerInfo.lastOffTime = DelayDayStart();

        //Save();
    }

    return;
}

void WGamePlayer::SyncEnterWorldMsg()
{
	m_role.SyncEnterWorldMsg();

	return;
}

bool WGamePlayer::OnEnterServer()
{
	m_counters.Refresh();

	m_role.OnEnterServer();

	return true;
}

bool WGamePlayer::CanFree()
{
    if (AsyncMsg())
        return false;

    return true;
}

uint32_t WGamePlayer::SerializeWithDB(Cmd::t_Data_Save_RoleInfo_Req *send)
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

	send->playerDataLen = length;

    return length;
}

bool WGamePlayer::UnSerializeWithWorld(Cmd::t_Enter_World_Req*recv)
{
	//
    uint32_t length = recv->playerDataLen;
    uint8_t *buffer = recv->data;

    LOGD("WGamePlayer::UnSerializeWithEnterWorld Playerid = " << Id() << " length = " << length);

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

	if (!m_role.UnSerializeWithWorld(recv))
		return false;

	OnEnterServer();

	NotifySelectDBServer();
	Save();

    return true;
}

void WGamePlayer::SerializeWithWorld(Cmd::t_Enter_World_Req *send)
{
	send->playerinfo = m_playerInfo;
	uint8_t* buffer = send->data;

	uint32_t length = 0;
#define SERIALIZE_PLAYER_DATA(system)	\
    auto size = system.Serialize(buffer);	\
    BuffWriteMoveLen(buffer, length, size);
#include "PlayerData.inl"
#undef SERIALIZE_PLAYER_DATA

	send->allBinarrayLength = send->playerDataLen = length;

	m_role.SerializeWithWorld(send);

	return;
}

void WGamePlayer::NotifySelectDBServer()
{
	Cmd::t_Data_Select_Server notifyDB;
	notifyDB.playerId = m_playerInfo.playerId;
	notifyDB.serverId = g_serverId;
	notifyDB.serverType = SERVER_TYPE_WGAME_SERVER;
	SendToDB(&notifyDB, sizeof(notifyDB), m_playerInfo.dbServerId);

	return;
}

void WGamePlayer::Save()
{
    m_needSave = false;

	Cmd::t_Data_Save_RoleInfo_Req* send;
	World::instance()->ServerCmdBuffer(send);

	send->serverId = g_serverId;
	send->serverType = SERVER_TYPE_WGAME_SERVER;
	m_playerInfo.lastOffTime = CImpServerTimeTick::currentTime.sec();
	send->playerinfo = m_playerInfo;

	SerializeWithDB(send);

	m_role.SerializeWithDB(send);

	SendToDB(send, send->Size(), m_playerInfo.dbServerId);

    return ;
}

Cmd::t_Data_Update_Item_Req *WGamePlayer::BeginUpdateItem()
{
    Cmd::t_Data_Update_Item_Req *send;
    World::instance()->ServerItemCmdBuffer(send);

    send->playerId = Id();
    send->serverId = g_serverId;
    send->serverType = SERVER_TYPE_WGAME_SERVER;
    //send->roleId = GetWorldRole()->RoleId();

    return send;
}

void WGamePlayer::EndUpdateItem(Cmd::t_Data_Update_Item_Req *send, bool saveRole)
{
    //SendToDB(send, send->Size());

    return;
}

////Serialize client msg
void WGamePlayer::SerializeEnterWorldRes(ClientMsg::EnterWorldRes* send)
{
	send->roleInfo.baseInfo.roleId = m_role.RoleId();
	send->roleInfo.baseInfo.mapId = m_role.GetRoleInfo()->mapId;

	return;
}

void WGamePlayer::SerializeEnterLandNotify(ClientMsg::EnterLandNotify *send)
{
	send->mapId = m_role.GetRoleInfo()->mapId;

	return;
}

void WGamePlayer::SerializeEnterDungeonRes(ClientMsg::EnterDungeonRes* send)
{


	return;
}

//world cmd
bool WGamePlayer::WorldMatchRes(Cmd::t_World_Match_Res *recv)
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
