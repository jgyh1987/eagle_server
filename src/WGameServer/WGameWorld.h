#ifndef _WORLD_MANAGER_H_
#define _WORLD_MANAGER_H_

#include "Sys.h"
#include "Singleton.h"
#include "PlayerInfo.h"
#include "WorldCommand.h"
#include "Grid.h"
#include "LandmassManager.h"
#include "WGameMap.h"
#include "WGameDungeon.h"

class CWGameConnectClient;
class WGamePlayer;

class EagleLandmassEx : public EagleLandmass
{
public:
	using EagleLandmass::EagleLandmass;

	~EagleLandmassEx();

	bool Init(uint64_t id);
	void EntityExit(ECS::ECSEntity*);
	bool EntityEnter(ECS::ECSEntity*);
	void UpdateGrid(WorldObject *o);
	void GetTargetVec(Character *, WorldObject *c, HitRangeInfo *, std::vector<Character *> *);
	bool IsEnemy(WorldObject *c, WorldObject *t) { if (m_map) return m_map->IsEnemyImp(c, t); return true; }
	bool IsTeam(WorldObject *c, WorldObject *t) { if (m_map) return m_map->IsTeamImp(c, t); return false; }

public:
	void PlayerEnter(WGamePlayer *);
	void PlayerExit(WGamePlayer *);
	void EnterNine(Character *);


private:
	std::vector<WBigMap *> m_maps;
	WBigMap *m_map = NULL;
	eagle_hash_map<uint64_t, Character *> m_objects;
	eagle_hash_map<uint64_t, ECS::ECSEntity *> m_players;
};

class WGameWorldManager : public EagleLandmassManager, public CSingleton<WGameWorldManager>
{
public:
	WGameWorldManager();
	~WGameWorldManager();

	bool Init();
	void Update();
	void UpdateSec();
	void Update5Sec();

	//void BroadcastClient(void*, Character* charactor);
	//void BroadcastClientMove(SceneCharactorPos& pos);

	void EnterWorld(WGamePlayer*);
	void RoamWGameServer(WGamePlayer*, DWORD serverId);
	void ExitDungeon(ECS::ECSEntity *);

	//
	void AgentLockGate(WGamePlayer* player, uint32_t serverId);
	void AgentUnLockGate(WGamePlayer* player, uint32_t serverId);
public:
	void NotityServerAgentSceneId(CWGameConnectClient *connect, DWORD serverType = SERVER_TYPE_NONE);

	//请求地图跳转服务器ID返回
	void ResSceneServer(WGamePlayer *, uint32_t serverId, uint32_t type = Cmd::Req_SceneServer_FunType_None);

private:
	WGameDungeon *CreateDungeon(DungeonConfigData *data);
	bool BeginEnterDungeon(WGamePlayer *);
	bool EnterDungeon(uint64_t uid, WGamePlayer*);
	bool EnterDungeon(WGameDungeon *dungeon, WGamePlayer*);

	bool BeginEnterLand(ECS::ECSEntity *);
	bool EnterLand(WGamePlayer*);
	void ReqSceneServer(WGamePlayer*);

	//自己是否持有该区域的管理权
	bool CheckSceneIdAgent(WGamePlayer*);
	uint32_t GetSceneServer(WGamePlayer*);



private:
	eagle_hash_map<uint64_t, WGameDungeon*> m_dungeons;
	EagleLandmassEx *m_landmass;
	std::vector<uint64_t> m_sceneIds;
};



#endif

 