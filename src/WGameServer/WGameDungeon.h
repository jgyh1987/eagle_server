#ifndef _WGAME_DUNGEON_H_
#define _WGAME_DUNGEON_H_

#include "Sys.h"
#include "Singleton.h"
#include "WorldCommand.h"
#include "ClientMsg.h"
#include "Map.h"
#include "PlayerInfo.h"
#include "WGameMap.h"

class CWGameClientTask;
class WGamePlayer;

class WGameDungeon : public EagleWorld
{
public:
    WGameDungeon(DungeonConfigData* data, MatchBaseInfo *);
    ~WGameDungeon();

    bool IsType(uint32_t type) { return type == OBJECT_DUNGEON; }
    uint32_t Type() { return OBJECT_DUNGEON; }

	bool Init(uint64_t id);

	void EntityExit(ECS::ECSEntity*);
	void End();
    void BroadcastMsg(void *, uint32_t len) override;
    void BroadcastClientMsg(void *) override;

public:
	virtual void Update();
	virtual void UpdateSec();
	virtual void Update5Sec();

	virtual void TickAllPlayer();
	virtual bool PlayerEnter(WGamePlayer *);
	virtual void PlayerExit(WGamePlayer *);
	virtual void MonsterDie(uint64_t uid);

public:
	inline bool IsEnd() { return m_status >= WORLD_STATUS_END; }
	inline bool CanClear() { return IsStatus(WORLD_STATUS_CLEAR); }
    inline uint64_t GetMatchUID(){return m_matchBaseInfo.matchUid;}
    inline uint32_t GetMatchType(){return m_matchBaseInfo.matchType;}

	WGamePlayer*FindPlayerById(uint32_t gameServerId, uint64_t playerId);
    void AddPlayer(WGamePlayer*);
    void RemovePlayer(WGamePlayer*);

	inline DungeonConfigData* ConfigData() { return m_data; }

protected:
	DungeonConfigData *m_data = NULL;
    MatchBaseInfo m_matchBaseInfo;
    uint64_t m_beginTime = 0;
	uint64_t m_endTime = 0;
    std::vector<ECS::ECSEntity *> m_players;
};

class MainDungeon : public WGameDungeon
{
public:
	using WGameDungeon::WGameDungeon;

	bool IsType(uint32_t type) { return type == OBJECT_DUNGEON_MAIN; }
	uint32_t Type() { return OBJECT_DUNGEON_MAIN; }

	void End();
	void Update();

public:
	void MonsterDieById(uint64_t id);

};

class TeamDungeon : public WGameDungeon
{
public:
	using WGameDungeon::WGameDungeon;

	bool IsType(uint32_t type) { return type == OBJECT_DUNGEON_TEAM; }
	uint32_t Type() { return OBJECT_DUNGEON_TEAM; }

	void End();
};

#endif

 