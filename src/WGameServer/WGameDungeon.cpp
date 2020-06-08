#include "WGameDungeon.h"
#include "World.h"
#include "Fighter.h"
#include "WGamePlayer.h"
#include "WGameWorld.h"

//WGameDungeon
WGameDungeon::WGameDungeon(DungeonConfigData* data, MatchBaseInfo*)
	:m_data(data)
{

}

WGameDungeon::~WGameDungeon()
{
	for (auto p : m_players)
	{
		GamePlayerSystem::instance()->SetWorld(p, NULL);
	}
}

bool WGameDungeon::Init(uint64_t id)
{
	if (!m_data)
		return false;

	auto action = CreateAction(ACTION_TYPE_DUNGEON_COMPLETE, this, this);
	if (!action)
		return false;
	for (uint32_t i = 0; i < m_data->vecCmpCondition.size(); ++i)
	{
		CreateCondition(action, m_data->vecCmpCondition[i].type, m_data->vecCmpCondition[i].value.c_str());
	}

	m_actions.push_back(action);

	RegisterEventAction(action);

	return true;
}

void WGameDungeon::End()
{
	SetStatus(WORLD_STATUS_END);
	m_endTime = CImpServerTimeTick::currentTime.sec() + m_data->autoTickTime;

	return;
}

void WGameDungeon::EntityExit(ECS::ECSEntity *entity)
{


	return;
}

void WGameDungeon::Update()
{
	

    return;
}

void WGameDungeon::UpdateSec()
{
	if (IsStatus(WORLD_STATUS_END))
	{
		if (CImpServerTimeTick::currentTime.sec() >= m_endTime)
		{
			TickAllPlayer();
			SetStatus(WORLD_STATUS_CLEAR);
		}
	}

	return;
}

void WGameDungeon::Update5Sec()
{


    return;
}

void WGameDungeon::BroadcastMsg(void *ptr, uint32_t len)
{
    

    return;
}

void WGameDungeon::BroadcastClientMsg(void *ptr)
{


    return;
}

void WGameDungeon::TickAllPlayer()
{
	for (auto p : m_players)
	{
		WGameWorldManager::instance()->ExitDungeon(p);
	}
	m_players.clear();

	return;
}

bool WGameDungeon::PlayerEnter(WGamePlayer* player)
{
	ClientMsg::EnterDungeonRes send;
	player->SerializeEnterDungeonRes(&send);
	send.dungeonId = Id();
	send.ret = SUCCESS;

	GamePlayerSystem::instance()->SendClientMsg(player->GetEntity(), &send);

	AddPlayer(player);
	GamePlayerSystem::instance()->SetWorld(player->GetEntity(), this);

	return true;
}

void WGameDungeon::PlayerExit(WGamePlayer* player) 
{
	GamePlayerSystem::instance()->SetWorld(player->GetEntity(), NULL);
	RemovePlayer(player);
}

void WGameDungeon::MonsterDie(uint64_t uid)
{

	return;
}

WGamePlayer*WGameDungeon::FindPlayerById(uint32_t gameServerId, uint64_t playerId)
{


    return NULL;
}

void WGameDungeon::AddPlayer(WGamePlayer*player)
{
    m_players.push_back(player->GetEntity());
    
    return;
}

void WGameDungeon::RemovePlayer(WGamePlayer*player)
{
	auto entity = player->GetEntity();
	VECTOR_REMOVE_PTR(m_players, entity);

    return;
}

//MainDungeon
void MainDungeon::End()
{
	WGameDungeon::End();

	ClientMsg::DungeonEndNotify notify;
	if (m_players.size())
	{
		GamePlayerSystem::instance()->SendClientMsg(m_players[0], &notify);
	}

	return;
}

void MainDungeon::Update()
{
	if (!m_players.size())
	{
		SetStatus(WORLD_STATUS_CLEAR);
	}

	return;
}

void MainDungeon::MonsterDieById(uint64_t id)
{
	//todo 副本配置检查杀死的数量是否一致

	OnKillLogicEvent event(id);
	LogicDoEvent<WGameDungeon> _event(this, event);
	_event();

	return;
}

//TeamDungeon
void TeamDungeon::End()
{

	return;
}


