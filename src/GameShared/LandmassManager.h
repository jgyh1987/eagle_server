#ifndef _LANDMASS_MANAGER_H_
#define _LANDMASS_MANAGER_H_

#include "Sys.h"
#include "Grid.h"
#include "LogicDataManager.h"
#include "Map.h"

class EagleLandmassManager;
class Character;

class EagleLandmass : public EagleWorld
{
public:
    EagleLandmass(LandmassConfigData* data);
    virtual ~EagleLandmass();

	uint32_t Type() { return OBJECT_LANDMASS; }
	bool IsType(uint32_t type) { return type == OBJECT_LANDMASS; }

	bool Init(uint64_t id);

	void EntityExit(ECS::ECSEntity*) {}
	void End() {}

	uint64_t FindScene(double x, double y, double z);
	uint64_t FindScene(EaglePos &pos);
    Grid<WorldObject> *GetGrid(WorldObject *charactor);
    Grid<WorldObject> *GetGrid(double x, double y, double z);
    bool GetNineGrid(WorldObject *charactor, Grid<WorldObject> **grids);
    bool GetNineGrid(double x, double y, double z, Grid<WorldObject> **grids);
    void GridDoExec(WorldObject *, double rang, CEntryCallback<WorldObject> *exec);
    void GridDoExec(double x, double y, double z, double rang, CEntryCallback<WorldObject> *exec);

	inline LandmassConfigData *ConfigData() { return m_data; }

protected:
    GridManager<WorldObject> m_grids;
	LandmassConfigData *m_data = NULL;

};

class EagleLandmassManager
{
public:
    EagleLandmassManager();
    virtual ~EagleLandmassManager();

	virtual bool Init();

    Grid<WorldObject> *GetGrid(WorldObject *charactor, uint64_t mapId);
    Grid<WorldObject> *GetGrid(uint64_t mapId, double x, double y, double z);
    bool GetNineGrid(WorldObject *charactor, uint64_t mapId, Grid<WorldObject> **grids);
    bool GetNineGrid(uint64_t mapId, double x, double y, double z, Grid<WorldObject> **grids);
    void GridDoExec(WorldObject *, uint64_t mapId,double rang, CEntryCallback<WorldObject> *exec);
    void GridDoExec(uint64_t mapId, double x, double y, double z, double rang, CEntryCallback<WorldObject> *exec);

	uint64_t FindScene(uint64_t mapId, double x, double y, double z);

	void RegisterServerAgentSceneId(uint64_t sceneId, uint32_t serverId);
	uint32_t GetServerIdByMapId(uint64_t mapId, EaglePos &pos);
	uint32_t GetServerIdBySceneId(uint64_t sceneId);

protected:
    EagleLandmass *FindLandmassByMapId(uint64_t mapId);
	EagleLandmass* FindLandmassByLandId(uint64_t landId);
	EagleLandmass *FindLandmassBySceneId(uint64_t sceneId);

protected:
    std::vector< EagleLandmass * > m_landmassgrids;
    std::unordered_map< uint64_t, EagleLandmass * > m_mapToLandmass;
	std::unordered_map< uint64_t, EagleLandmass * > m_sceneToLandmass;
	std::map<uint64_t, uint32_t> m_sceneIdToServerId;
};


#endif

 