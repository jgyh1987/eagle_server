#include "WorldObject.h"
#include "ToolsFun.h"
#include "LogicDataManager.h"
#include "Map.h"

//WorldObject
WorldObject::WorldObject(uint64_t tempid)
    :UnitObject(tempid), m_grid(NULL)
{
    memset(m_nineGrids, 0, sizeof(m_nineGrids));
}

WorldObject::~WorldObject()
{
    if (m_grid)
        m_grid->RemoveObject(this);
}

void WorldObject::Move(EaglePos& pos)
{
	x = pos.x;
	y = pos.y;
	z = pos.z;
	dirx = pos.dirx;
	diry = pos.diry;
	dirz = pos.dirz;
	range = pos.range;

	UpdateGird();

	return;
}

void WorldObject::Move(double _x, double _y, double _z, double _dx, double _dy, double _dz)
{
	x = _x;
	y = _y;
	z = _z;
	dirx = _dx;
	diry = _dy;
	dirz = _dz;

	UpdateGird();

	return;
}

void WorldObject::Move(CmdPos& pos)
{
	x = pos.x / POS_DENOMINATOR;
	y = pos.y / POS_DENOMINATOR;
	z = pos.z / POS_DENOMINATOR;
	dirx = pos.dirx / POS_DENOMINATOR;
	diry = pos.diry / POS_DENOMINATOR;
	dirz = pos.dirz / POS_DENOMINATOR;

	UpdateGird();

	return;
}

void WorldObject::UpdateGird()
{
	if (m_wolrd)
		m_wolrd->UpdateGrid(this);

	return;
}

uint64_t WorldObject::GetMapId()
{
	if (m_map)
		return m_map->Id();

	return 0;
}

uint64_t WorldObject::GetWorldId()
{
	if (m_wolrd)
		return m_wolrd->Id();

	return 0;
}

//global
void FreeWorldObject(WorldObject *ptr)
{
    delete ptr;

    return;
}

