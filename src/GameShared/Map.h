#ifndef _MAP_H_
#define _MAP_H_

#include "Noncopyable.h"
#include "Singleton.h"
#include "CommonType.h"
#include "WorldObject.h"
#include "Event.h"
#include "ECS_Entity.h"

//
enum WORLD_STATUS
{
    WORLD_STATUS_NONE = 0,
    WORLD_STATUS_READY = 1,
    WORLD_STATUS_STRAT = 2,
    WORLD_STATUS_END = 3,
    WORLD_STATUS_CLEAR = 4,
};

class Character;
class EagleWorld;
struct MapConfigData;

class EagleMap : public UnitObject
{
public:
    EagleMap(EagleWorld *world);
    ~EagleMap();

    uint32_t Type(){return OBJECT_MAP;}
    bool IsType(uint32_t type){return type == OBJECT_MAP;}

	virtual bool Init(uint64_t id);

//virtual
public:
	virtual bool CanEnter(WorldObject*) { return true; }

	virtual bool IsEnemyImp(WorldObject *, WorldObject *) { return true; }
	virtual bool IsTeamImp(WorldObject *, WorldObject *) { return false; }

//virtual
protected:
	virtual bool EnterMapImp(WorldObject *) { return true; }
    virtual void LeaveMapImp(WorldObject *){}

//tools fun
public:
    WorldObject *FindObjectByUid(uint64_t uid);
    std::map<uint64_t, WorldObject*>* GetObjects() {return &m_objects;}
	EagleWorld* GetWorld() { return m_world; }

    inline MapConfigData* ConfigData(){return m_data;}

    bool EnterMap(WorldObject *);
    void LeaveMap(WorldObject *);

protected:
    std::map<uint64_t, WorldObject*> m_objects;
	MapConfigData* m_data = NULL;
    EagleWorld* m_world = NULL;
};

class EagleWorld : public UnitObject, public EventManagerInterface
{
public:
    EagleWorld();
    ~EagleWorld();

    uint32_t Type(){return OBJECT_WORLD;}
    bool IsType(uint32_t type){return type == OBJECT_WORLD;}

	virtual bool Init(uint64_t id) = 0;

	inline ECS::ECSEntity* GetEntity() { return m_entity; }

//virtual
public:
	virtual void EntityExit(ECS::ECSEntity*) = 0;
	virtual bool EntityEnter(ECS::ECSEntity*) { return false; }
	virtual void End() = 0;
    virtual void BroadcastMsg(void *, uint32_t len) {}
    virtual void BroadcastClientMsg(void *) {}
	virtual void UpdateGrid(WorldObject *o) {}
	virtual void GetTargetVec(Character *, WorldObject *c, HitRangeInfo *, std::vector<Character *> *) {}
	virtual bool IsEnemy(WorldObject *, WorldObject *) { return true; }
	virtual bool IsTeam(WorldObject *, WorldObject *) { return false; }

//tools fun
public:
    inline bool IsStatus(uint32_t status){return m_status == status;}
    inline void SetStatus(uint32_t status){m_status = status;}

protected:
	//ecs 
	ECS::ECSEntity* m_entity;

    std::vector<EagleMap *> m_maps;

    uint32_t m_status = WORLD_STATUS_NONE;    
};


#endif
