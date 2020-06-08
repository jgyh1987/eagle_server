#include "LandmassManager.h"
#include "Character.h"
#include "Global.h"

//EagleLandmass
EagleLandmass::EagleLandmass(LandmassConfigData* data)
	:m_data(data)
{
	m_id = data->id;
}

EagleLandmass::~EagleLandmass()
{

}

bool EagleLandmass::Init(uint64_t id)
{
	m_grids.Init(&m_data->gridInfo);

	for (auto sid : m_data->scenes)
	{
		auto data = SceneConfigDataManager::instance()->get(sid);
		if (!data)
			continue;

		m_grids.UpdateScene(data->id, &data->gridInfo);

	}

	return true;
}

uint64_t EagleLandmass::FindScene(double x, double y, double z)
{
	auto grid = GetGrid(x, y, z);
	if (grid)
		return grid->sceneId;

	return 0;
}

uint64_t EagleLandmass::FindScene(EaglePos &pos)
{
	return FindScene(pos.x, pos.y, pos.z);
}

Grid<WorldObject> *EagleLandmass::GetGrid(WorldObject *charactor)
{
    return m_grids.GetGrid(charactor);
}

Grid<WorldObject> *EagleLandmass::GetGrid(double x, double y, double z)
{
    return m_grids.GetGrid(x, y, z);
}

bool EagleLandmass::GetNineGrid(WorldObject *charactor, Grid<WorldObject> **grids)
{
    return m_grids.GetNineGrid(charactor, grids);
}

bool EagleLandmass::GetNineGrid(double x, double y, double z, Grid<WorldObject> **grids)
{
    return m_grids.GetNineGrid(x, y, z, grids);
}

void EagleLandmass::GridDoExec(WorldObject *charactor, double rang, CEntryCallback<WorldObject> *exec)
{
    return m_grids.GetStrategy().DoExec(charactor, rang, exec);
}

void EagleLandmass::GridDoExec(double x, double y, double z, double rang, CEntryCallback<WorldObject> *exec)
{
    return m_grids.GetStrategy().DoExec(x, y, z, rang, exec);
}

//EagleLandmassManager
EagleLandmassManager::EagleLandmassManager()
{

}

EagleLandmassManager::~EagleLandmassManager()
{
    m_mapToLandmass.clear();
    for (auto p : m_landmassgrids)
        SAFE_DELETE(p);
}

bool EagleLandmassManager::Init()
{
	auto itrL = LandmassConfigDataManager::instance()->begin();
	for (; itrL != LandmassConfigDataManager::instance()->end(); ++itrL)
	{
		auto land = new EagleLandmass((LandmassConfigData *)&*itrL);
		m_landmassgrids.push_back(land);
		for (auto id : itrL->maps)
		{
			m_mapToLandmass[id] = land;
		}

		for (auto id : itrL->scenes)
		{
			m_sceneToLandmass[id] = land;
		}
	}

	return true;
}

Grid<WorldObject> *EagleLandmassManager::GetGrid(WorldObject *charactor, uint64_t mapId)
{
    EagleLandmass *landmass = FindLandmassByMapId(mapId);
    if (landmass)
        return landmass->GetGrid(charactor);

    return NULL;
}

Grid<WorldObject> *EagleLandmassManager::GetGrid(uint64_t mapId, double x, double y, double z)
{
    EagleLandmass *landmass = FindLandmassByMapId(mapId);
    if (landmass)
        return landmass->GetGrid(x, y, z);

    return NULL;
}

bool EagleLandmassManager::GetNineGrid(WorldObject *charactor, uint64_t mapId, Grid<WorldObject> **grids)
{
    EagleLandmass *landmass = FindLandmassByMapId(mapId);
    if (landmass)
        return landmass->GetNineGrid(charactor, grids);

    return NULL;
}

bool EagleLandmassManager::GetNineGrid(uint64_t mapId, double x, double y, double z, Grid<WorldObject> **grids)
{
    EagleLandmass *landmass = FindLandmassByMapId(mapId);
    if (landmass)
        return landmass->GetNineGrid(x, y, z, grids);

    return NULL;
}

void EagleLandmassManager::GridDoExec(WorldObject *charactor, uint64_t mapId, double rang, CEntryCallback<WorldObject> *exec)
{
    EagleLandmass *landmass = FindLandmassByMapId(mapId);
    if (landmass)
        return landmass->GridDoExec(charactor, rang, exec);

    return;
}

void EagleLandmassManager::GridDoExec(uint64_t mapId, double x, double y, double z, double rang, CEntryCallback<WorldObject> *exec)
{
    EagleLandmass *landmass = FindLandmassByMapId(mapId);
    if (landmass)
        return landmass->GridDoExec(x, y, z, rang, exec);

    return;
}

uint64_t EagleLandmassManager::FindScene(uint64_t mapId, double x, double y, double z)
{
	auto land = FindLandmassByMapId(mapId);
	if (land)
		return land->FindScene(x, y, z);

	return 0;
}

void EagleLandmassManager::RegisterServerAgentSceneId(uint64_t sceneId, uint32_t serverId)
{
	m_sceneIdToServerId[sceneId] = serverId;
}

uint32_t EagleLandmassManager::GetServerIdByMapId(uint64_t mapId, EaglePos &pos)
{
	return GetServerIdBySceneId(FindScene(mapId, pos.x, pos.y, pos.z));
}

uint32_t EagleLandmassManager::GetServerIdBySceneId(uint64_t sceneId)
{
	auto itr = m_sceneIdToServerId.find(sceneId);
	if (itr != m_sceneIdToServerId.end())
		return itr->second;

	return 0;
}

EagleLandmass* EagleLandmassManager::FindLandmassByMapId(uint64_t mapId)
{
	auto itr = m_mapToLandmass.find(mapId);
	if (itr != m_mapToLandmass.end())
		return itr->second;

	return NULL;
}

EagleLandmass* EagleLandmassManager::FindLandmassByLandId(uint64_t landId)
{
	for (auto p : m_landmassgrids)
		if (p->Id() == landId)
			return p;

	return NULL;
}

EagleLandmass *EagleLandmassManager::FindLandmassBySceneId(uint64_t sceneId)
{
	auto itr = m_sceneToLandmass.find(sceneId);
	if (itr != m_sceneToLandmass.end())
		return itr->second;

	return NULL;
}

