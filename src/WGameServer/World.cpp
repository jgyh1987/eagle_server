#include "Defs.h"
#include "TimeTick.h"
#include "LogicDataManager.h"
#include "Buff.h"
#include "Skill.h"
#include "WGameWorld.h"
#include "WGamePlayer.h"
#include "WGameRole.h"
#include "AIBehaviac.h"
#include "ECS_AIBehaviac.h"
#include "ECS_FightInfo.h"

//Common data
namespace game
{
	

    void InitGameGlobalParameters()
    {



        return;
    }



};

bool ECSWorldManager::Init()
{
	if (!ECS::ECSManager::instance()->Init(ECS_ENTITY_TYPE_MAX))
		return false;

	QuestSystem::instance()->Init();	

	return true;
}

void ECSWorldManager::DestroyEntity(ECS::ECSEntity *&entity)
{
	if (entity)
	{
		ECS::ECSManager::instance()->DestroyEntrty(entity);
		entity = NULL;
	}

	return;
}

ECS::ECSEntity* ECSWorldManager::CreatePlayerEntity(WGamePlayer* player)
{
	auto entity = ECS::ECSManager::instance()->CreateEntity(ECS_ENTITY_TYPE_PLAYER, ECS_PLAYER_COMPONENT_TYPE_MAX);
	if (entity)
	{
		auto playerCmp = ECS::ECSManager::instance()->CreateComponent<GamePlayerComponent>(entity);
		playerCmp->m_player = player; 
		ECS::ECSManager::instance()->CreateComponent<CounterComponent>(entity);
		ECS::ECSManager::instance()->CreateComponent<BagComponent>(entity);
		ECS::ECSManager::instance()->CreateComponent<MailComponent>(entity);
		ECS::ECSManager::instance()->CreateComponent<QuestComponent>(entity);
	}

	return entity;
}

ECS::ECSEntity* ECSWorldManager::CreateFighterEntity(WGamePlayer* player)
{
	auto entity = ECS::ECSManager::instance()->CreateEntity(ECS_ENTITY_TYPE_CHAR, ECS_CHAR_COMPONENT_TYPE_MAX);
	if (entity)
	{
		ECS::ECSManager::instance()->CreateComponent<FightComponent>(entity);
	}

	return entity;
}

ECS::ECSEntity* ECSWorldManager::CreateNpcEntity(EagleWorld *)
{
	auto entity = ECS::ECSManager::instance()->CreateEntity(ECS_ENTITY_TYPE_CHAR, ECS_CHAR_COMPONENT_TYPE_MAX);
	if (entity)
	{
		ECS::ECSManager::instance()->CreateComponent<BehaviacComponent>(entity);
		ECS::ECSManager::instance()->CreateComponent<FightComponent>(entity);
	}

	return entity;
}

//world
World::World()
{

}

World::~World()
{

}

bool World::Init()
{
    CRandom::Init();
    InitConditionToEventArray();
    InitEffectFuncs();
    InitBuffTiggerToEventArray();

    if (!LogicDataManager::instance()->Init(eagle::global["ConfigPath"]))
        return false;

	if (!ECSWorldManager::instance()->Init())
		return false;

    if (!WGameWorldManager::instance()->Init())
        return false;

	InitParasePlayerInfoMsgFun();

    return true;
}

//
void World::Clear()
{

	return;
}

void World::Update()
{


	return;
}

void World::UpdateSec()
{
	WGameWorldManager::instance()->UpdateSec();

	return;
}

void World::Update5Sec()
{
	for (auto& itr : m_players)
	{
		itr.second->Update5Sec();
	}

	WGameWorldManager::instance()->Update5Sec();

	return;
}

void World::UpdateMin()
{



	return;
}

void World::UpdateHour()
{


	return;
}

void World::Update24()
{


	return;
}

WGamePlayer *World::CreatePlayer(const PlayerInfoBase& playerInfo, uint32_t gateServerType)
{
	return new WGamePlayer(playerInfo, gateServerType);
}

void World::AddPlayer(WGamePlayer* player)
{
	m_players[player->Uid()] = player;

	return;
}

void World::RemovePlayer(WGamePlayer* &player)
{
	auto itr = m_players.find(player->Uid());
	if (itr != m_players.end())
	{
		m_players.erase(itr);
	}

	SAFE_DELETE(player);

	return;
}

void World::RemovePlayer(uint64_t uid)
{
	WGamePlayer* player = NULL;
	auto itr = m_players.find(player->Uid());
	if (itr != m_players.end())
	{
		player = itr->second;
		m_players.erase(itr);
	}

	SAFE_DELETE(player);

	return;
}

WGamePlayer* World::FindPlayerByUid(uint64_t playerUid)
{
	auto itr = m_players.find(playerUid);
	if (itr != m_players.end())
		return itr->second;

	return NULL;
}

