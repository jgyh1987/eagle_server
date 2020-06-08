#include "Map.h"
#include "Character.h"
#include "SharedEvent.h"
#include "RangeCheck.h"
#include "LogicDataManager.h"
#include "LandmassManager.h"

//map
EagleMap::EagleMap(EagleWorld *world)
    :UnitObject(GetObjectUid()), m_data(NULL), m_world(world)
{
}

EagleMap::~EagleMap()
{
    for (auto itr = m_objects.begin(); itr != m_objects.end(); ++itr)
    {
        FreeWorldObject(itr->second);
    }
    m_objects.clear();

    m_data = NULL;
}

bool EagleMap::Init(uint64_t id)
{
	m_id = id;

	m_data = MapConfigDataManager::instance()->get(m_id);
	if (!m_data)
		return false;

	return true;
}

WorldObject *EagleMap::FindObjectByUid(uint64_t uid)
{
    auto itr = m_objects.find(uid);
    if (itr != m_objects.end())
    {
        return itr->second;
    }

    return NULL;
}

bool EagleMap::EnterMap(WorldObject*object)
{
    auto itr = m_objects.find(object->Uid());
    if (itr == m_objects.end())
    {
		if (EnterMapImp(object))
		{
			m_objects[object->Uid()] = object;

			return true;
		}
    }

    return false;
}

void EagleMap::LeaveMap(WorldObject*object)
{
    auto itr = m_objects.find(object->Uid());
    if (itr != m_objects.end())
    {
        LeaveMapImp(object);
        m_objects.erase(itr);
    }

    return ;
}

//EagleWorld
EagleWorld::EagleWorld()
    :UnitObject(GetObjectUid()), EventManagerInterface(g_condition_to_event, EVENT_TYPE_MAX), m_status(WORLD_STATUS_NONE)
{
}

EagleWorld::~EagleWorld()
{
    for (uint32_t i = 0; i < m_maps.size(); ++i)
    {
        SAFE_DELETE(m_maps[i]);
    }
    m_maps.clear();

    m_status = WORLD_STATUS_NONE;
}

