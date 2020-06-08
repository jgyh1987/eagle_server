#include "WGameWorld.h"
#include "TimeTick.h"
#include "Defs.h"
#include "WGamePlayer.h"
#include "WGameRole.h"
#include "WorldCommand.h"
#include "WGameService.h"
#include "Fighter.h"
#include "EffectObject.h"
#include "XMLParser.h"
#include "WGameConnectClient.h"

EagleLandmassEx::~EagleLandmassEx()
{
	for (auto &itr : m_players)
	{
		GamePlayerSystem::instance()->SetWorld(itr.second, NULL);
	}
	m_players.clear();
}

bool EagleLandmassEx::Init(uint64_t id)
{
	EagleLandmass::Init(id);

	for (auto d : m_data->maps)
	{
		auto map = new WBigMap(this);
		if (map && map->Init(d))
		{
			m_maps.push_back(map);

			if (!m_map)
				m_map = map;
		}
		else
			SAFE_DELETE(map);
	}

	return true;
}

void EagleLandmassEx::EntityExit(ECS::ECSEntity* entity)
{
	auto itr = m_players.find(entity->Uid());
	if (itr != m_players.end())
	{
		GamePlayerSystem::instance()->SetWorld(itr->second, NULL);
		m_players.erase(itr);
	}
}

bool EagleLandmassEx::EntityEnter(ECS::ECSEntity* entity)
{


	return false;
}

void EagleLandmassEx::UpdateGrid(WorldObject *o)
{


	return;
}

void EagleLandmassEx::GetTargetVec(Character *, WorldObject *c, HitRangeInfo *, std::vector<Character *> *)
{

	return;
}

void EagleLandmassEx::PlayerEnter(WGamePlayer *p)
{
	GamePlayerSystem::instance()->SetWorld(p->GetEntity(), this);
	m_players[p->GetEntity()->Uid()] = p->GetEntity();
	//m_objects.emplace(c->Uid(), c);
	//m_map->EnterMap(c);

	return;
}

void EagleLandmassEx::PlayerExit(WGamePlayer *p)
{
	

	return;
}

void EagleLandmassEx::EnterNine(Character *c)
{
	c->UpdateGird();

	//auto g = GetGrid(c);
	//if (m_grid != grid)
	//{
	//	if (m_grid)
	//		m_grid->RemoveObject(this);

	//	if (grid)
	//		grid->AddObject(this);

	//	force = true;
	//}

	//if (force)
	//	NineGridBraodcast();

	return;
}

//WGameWorldManager
WGameWorldManager::WGameWorldManager()
{

}

WGameWorldManager::~WGameWorldManager()
{
	SAFE_DELETE(m_landmass);
}

bool WGameWorldManager::Init()
{
	EagleLandmassManager::Init();

	parseStrToVecInt64(eagle::global["SceneIds"], m_sceneIds);

	if (m_sceneIds.size())
	{
		ServerImp()->UseBigWorld(true);

		auto land = FindLandmassBySceneId(m_sceneIds[0]);
		if (land)
		{
			auto data = LandmassConfigDataManager::instance()->get(land->Id());
			m_landmass = new EagleLandmassEx(data);
			if (m_landmass && !m_landmass->Init(m_landmass->Id()))
			{
				SAFE_DELETE(m_landmass);
			}
		}
	}

	for (auto v : m_sceneIds)
	{
		RegisterServerAgentSceneId(v, g_serverId);
	}

	return true;
}

void WGameWorldManager::Update()
{
	for (auto& itr : m_dungeons)
	{
		if (itr.second->IsEnd())
			continue;

		itr.second->Update();
	}

	return;
}

void WGameWorldManager::UpdateSec()
{
	for (auto& itr : m_dungeons)
	{
		itr.second->UpdateSec();
	}

	return;
}

void WGameWorldManager::Update5Sec()
{
	for (auto itr = m_dungeons.begin(); itr != m_dungeons.end();)
	{
		if (itr->second->CanClear())
		{
			SAFE_DELETE(itr->second);
			m_dungeons.erase(itr++);
		}
		else
			++itr;
	}
}

//void BroadcastClient(void*, Character* charactor);
//void BroadcastClientMove(SceneCharactorPos& pos);

void WGameWorldManager::EnterWorld(WGamePlayer* player)
{
	auto oldPlayer = World::instance()->FindPlayerByUid(player->Uid());
	if (oldPlayer)
	{
		World::instance()->RemovePlayer(oldPlayer);
	}

	World::instance()->AddPlayer(player);

	auto dungoenInfo = GamePlayerSystem::instance()->GetDungeonBaseInfo(player->GetEntity());
	if (dungoenInfo && dungoenInfo->dungeonId)
	{
		if (BeginEnterDungeon(player))
			return;
	}

	BeginEnterLand(player->GetEntity()); 

	return;
}

void WGameWorldManager::RoamWGameServer(WGamePlayer* player, DWORD serverId)
{
	Cmd::t_Enter_World_Req* send;
	World::instance()->ServerCmdBuffer(send);
	player->SerializeWithWorld(send);
	ServerImp()->ProxySendCmd(send, send->Size(), SERVER_TYPE_WGAME_SERVER, serverId);

	return;
}

void WGameWorldManager::ExitDungeon(ECS::ECSEntity * entyity)
{
	GamePlayerSystem::instance()->ClearDungeonInfo(entyity);
	BeginEnterLand(entyity);

	return;
}

void WGameWorldManager::AgentLockGate(WGamePlayer* player, uint32_t serverId)
{
	auto info = player->GetPlayrInfoBase();
	Cmd::t_Scene_Agent_Lock_Req req;
	req.lock = true;
	req.playerUid = info.playerUid;
	req.serverId = g_serverId;
	ServerImp()->SendCmdToServerTask(&req, sizeof(req), SERVER_TYPE_LOGIC_GATEWAY, info.gatewayServerId);

	return;
}

void WGameWorldManager::AgentUnLockGate(WGamePlayer* player, uint32_t serverId)
{
	auto info = player->GetPlayrInfoBase();
	Cmd::t_Scene_Agent_Lock_Req req;
	req.lock = false;
	req.playerUid = info.playerUid;
	req.serverId = g_serverId;
	ServerImp()->SendCmdToServerTask(&req, sizeof(req), SERVER_TYPE_LOGIC_GATEWAY, info.gatewayServerId);

	return;
}

void WGameWorldManager::NotityServerAgentSceneId(CWGameConnectClient *connect, DWORD serverType)
{
	if (!m_sceneIds.size())
		return;

	Cmd::t_Agent_SceneId_Notify* send;
	World::instance()->ServerCmdBuffer(send);

	send->serverId = g_serverId;
	uint64_t *ptr = (uint64_t *)send->data;
	for (auto v : m_sceneIds)
	{
		ptr[send->count++] = v;
	}
	send->len = UINT64_LEN * send->count;

	if (connect)
		connect->SendCmd(send, send->Size());
	else if (g_gameServerId)
		ServerImp()->ProxySendCmd(send, send->Size(), serverType, g_gameServerId);


	return;
}

void WGameWorldManager::ResSceneServer(WGamePlayer *player, uint32_t serverId, uint32_t type)
{
	switch (type)
	{
	case Cmd::Req_SceneServer_FunType_EnterLandmass:
	{
		AgentLockGate(player, serverId);
	}
	break;
	default:
		break;
	}

	return;
}

//private
WGameDungeon* WGameWorldManager::CreateDungeon(DungeonConfigData* data)
{
	WGameDungeon* dungeon = NULL;
	switch (data->type)
	{
	case OBJECT_DUNGEON_MAIN:
	{
		dungeon = new MainDungeon(data, NULL);
	}
	break;
	default:
		break;
	}

	if (dungeon)
	{
		if (dungeon->Init(data->id))
			m_dungeons[dungeon->Uid()] = dungeon;
		else
			SAFE_DELETE(dungeon);
	}
	
	return dungeon;
}

bool WGameWorldManager::BeginEnterDungeon(WGamePlayer* player)
{
	auto playerCmp = player->GetEntity()->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return false;

	//enter old dungeon
	if (playerCmp->m_wdungeonInfo.dungeonUid)
	{
		return true;
	}

	//enter new dungeon
	do
	{
		auto data = DungeonConfigDataManager::instance()->get(playerCmp->m_wdungeonInfo.dungeonId);
		if (!data)
		{
			return false;
		}

		switch (data->type)
		{
		case OBJECT_DUNGEON_MAIN:
		{
			auto dungeon = CreateDungeon(data);
			if (!dungeon)
			{
				break;
			}

			if (!EnterDungeon(dungeon, player))
			{
				break;
			}
		}
		return true;
		default:
			break;
		}


	} while (false);


	return false;
}

bool WGameWorldManager::EnterDungeon(uint64_t uid, WGamePlayer* player)
{
	auto itr = m_dungeons.find(uid);
	if (itr != m_dungeons.end())
		return EnterDungeon(itr->second, player);

	return false;
}

bool WGameWorldManager::EnterDungeon(WGameDungeon* dungeon, WGamePlayer* player)
{
	if (!dungeon->PlayerEnter(player))
		return false;

	return true;
}

bool WGameWorldManager::BeginEnterLand(ECS::ECSEntity *entity)
{
	auto playerCmp = entity->GetComponent<GamePlayerComponent>();
	if (!playerCmp)
		return false;

	auto player = playerCmp->m_player;
	if (!player)
		return false;

	if (CheckSceneIdAgent(player))
	{
		return EnterLand(player);
	}
	else
	{
		uint32_t serverId = GetSceneServer(player);
		if (serverId)
		{
			AgentLockGate(player, serverId);
		}
		else
		{
			ReqSceneServer(player);
		}
	}

	return true;
}

bool WGameWorldManager::EnterLand(WGamePlayer* player)
{
	ClientMsg::EnterLandNotify send;
	player->SerializeEnterLandNotify(&send);

	GamePlayerSystem::instance()->SendClientMsg(player->GetEntity(), &send);

	m_landmass->PlayerEnter(player);

	return true;
}

void WGameWorldManager::ReqSceneServer(WGamePlayer *player)
{
	auto role_info = GamePlayerSystem::instance()->GetRoleBaseInfo(player->GetEntity());
	if (!role_info)
		return;
	Cmd::t_Req_SceneServer send;
	send.funType = Cmd::Req_SceneServer_FunType_EnterLandmass;
	send.serverId = g_serverId;
	send.serverType = SERVER_TYPE_WGAME_SERVER;
	send.playerUid = player->Uid();
	send.mapId = role_info->mapId;
	send.pos = role_info->pos;
	ServerImp()->ProxySendCmd(&send, sizeof(send), SERVER_TYPE_LOGIC_SERVER, g_gameServerId);

	return;
}

bool WGameWorldManager::CheckSceneIdAgent(WGamePlayer *player)
{
	////test code begin
	//static bool first = true;
	//if (first)
	//{
	//	first = false;
	//	return false;
	//}
	////test code end

	if (!m_landmass)
		return false;

	auto role_info = GamePlayerSystem::instance()->GetRoleBaseInfo(player->GetEntity());
	if (!role_info)
		return false;
	uint64_t sceneId = m_landmass->FindScene(role_info->pos.x / POS_DENOMINATOR, role_info->pos.y / POS_DENOMINATOR, role_info->pos.z / POS_DENOMINATOR);
	if (sceneId)
	{
		for (auto v : m_sceneIds)
			if (v == sceneId)
				return true;
	}

	return false;
}

uint32_t WGameWorldManager::GetSceneServer(WGamePlayer* player)
{
	if (!m_landmass)
		return 0;
	auto role_info = GamePlayerSystem::instance()->GetRoleBaseInfo(player->GetEntity());
	if (!role_info)
		return 0;

	EaglePos pos(role_info->pos);

	auto landmass = FindLandmassByMapId(role_info->mapId);
	if (landmass && m_landmass && landmass->Id() == m_landmass->Id())
	{
		return GetServerIdBySceneId(m_landmass->FindScene(pos));
	}

	return GetServerIdByMapId(role_info->mapId, pos);
}

