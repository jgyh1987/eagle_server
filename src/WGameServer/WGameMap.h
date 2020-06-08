#ifndef _WGAME_MAP_H_
#define _WGAME_MAP_H_

#include "Sys.h"
#include "Singleton.h"
#include "WorldCommand.h"
#include "ClientMsg.h"
#include "Map.h"
#include "PlayerInfo.h"
#include "LogicDataManager.h"

class WGameDungeon;
class EagleLandmassEx;

class WDungeonMap : public EagleMap
{
public:
	WDungeonMap(WGameDungeon *dungeon);
    ~WDungeonMap();

	uint32_t Type() { return OBJECT_MAP_DUNGEON; }
	bool IsType(uint32_t type) { return type == OBJECT_MAP_DUNGEON; }

	bool Init(uint64_t id);
    //

	inline WGameDungeon *GetWGameDungeon() { if (m_world->IsType(OBJECT_DUNGEON))return (WGameDungeon *)m_world; return NULL; }

private:

};

class WBigMap : public EagleMap
{
public:
	WBigMap(EagleLandmassEx* dungeon);
	~WBigMap();

	uint32_t Type() { return OBJECT_MAP_BIG; }
	bool IsType(uint32_t type) { return type == OBJECT_MAP_BIG; }

	bool Init(uint64_t id);
	//
	inline EagleLandmassEx *GetEagleLandmassEx() { if (m_world->IsType(OBJECT_LANDMASS))return (EagleLandmassEx *)m_world; return NULL; }

private:

};


#endif

 