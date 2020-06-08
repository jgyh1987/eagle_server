#ifndef _WORLDOBJECT_H_
#define _WORLDOBJECT_H_

#include "Sys.h"
#include "Unit.h"
#include "EaglePos.h"
#include "Grid.h"
#include "ECS_Entity.h"

class EagleMap;
class EagleWorld;

class WorldObject : public UnitObject, public EaglePos
{
public:
    WorldObject(uint64_t tempid);
    ~WorldObject();

	inline ECS::ECSEntity* GetEntity() { return m_entity; }

//tools fun
public:
	void Move(EaglePos& pos);
	void Move(double _x = 0, double _y = 0, double _z = 0, double _dx = 0, double _dy = 0, double _dz = 0);
	// pos / POS_DENOMINATOR
	void Move(CmdPos& pos);
	void UpdateGird();

    inline void SetGrid(Grid<WorldObject> *grid)
    {
        m_grid = grid;
    }
    inline Grid<WorldObject> *GetGrid() { return m_grid; }
	void SetMap(EagleMap *map)
	{
		m_map = map;
	}
	EagleMap* GetMap() { return m_map; }
	uint64_t GetMapId();
	void SetWorld(EagleWorld *world)
	{
		m_wolrd = world;
	}
	EagleWorld* GetWorld() { return m_wolrd; }
	uint64_t GetWorldId();

protected:
	//ecs 
	ECS::ECSEntity* m_entity;

	EagleMap* m_map = NULL;
	EagleWorld *m_wolrd = NULL;
    Grid<WorldObject> *m_grid = NULL;
    Grid<WorldObject> *m_nineGrids[NINE_GRID_NUM];
};

void FreeWorldObject(WorldObject *ptr);

#endif


