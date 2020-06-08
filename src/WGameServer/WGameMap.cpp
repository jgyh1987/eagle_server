#include "WGameMap.h"
#include "World.h"
#include "Fighter.h"
#include "WGameDungeon.h"
#include "WGameWorld.h"

//WDungeonMap
WDungeonMap::WDungeonMap(WGameDungeon *dungeon)
    :EagleMap(dungeon)
{
}

WDungeonMap::~WDungeonMap()
{

}

bool WDungeonMap::Init(uint64_t id)
{


    return true;
}


//WBigMap
WBigMap::WBigMap(EagleLandmassEx* landmass)
	:EagleMap(landmass)
{

}

WBigMap::~WBigMap()
{

}

bool WBigMap::Init(uint64_t id)
{
	return true;
}

