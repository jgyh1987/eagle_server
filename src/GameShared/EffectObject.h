#ifndef _EFFECT_OBJECT_H_
#define _EFFECT_OBJECT_H_

#include "Sys.h"
#include "Unit.h"
#include "Eagle_Time.h"
#include "EaglePos.h"
#include "Grid.h"
#include "CommonType.h"
#include "Character.h"
#include "LogicDataManager.h"

class EffectAction;
class MMOSkill;

class EffectObject : public Character
{
public:
    EffectObject(MMOSkill *, EffectActionInfo *data, EaglePos &pos);
    ~EffectObject();

    uint32_t Type() { return OBJECT_MMO_EFFECT_OBJECT; }
    bool IsType(uint32_t type) { return type == OBJECT_MMO_EFFECT_OBJECT; }
    bool Init(uint64_t id) { m_id = id; return true; }
    void Clear();
    void Update();

    void SerializeEnterMapInfo(void *);

public:
    bool IsEnd() { return m_end; }
    void End();
    void ContinuedEffectTrigger0();
    void ContinuedEffectTrigger2();
    void CollisionCheck();
    void CollisionPenetrateCheck();
    
protected:
    

private:
    bool m_end;
    MMOSkill *m_owner;
    uint64_t m_startTime;
    uint64_t m_lifeTime;
    uint64_t m_lastEffectTime;
    EffectObjectInfo *m_data;
    uint64_t m_lastMoveTime;
    std::map<uint64_t, uint32_t> m_collsion;
};

class EffectAction
{
public:
    EffectAction(Character *, MMOSkill *, EffectActionInfo *, uint32_t index);
    ~EffectAction();

    void Update();

    EffectActionInfo *GetConfigData() { return m_data; }
    bool IsEnd() { return m_end; }

public:
    Character * m_owner;
    MMOSkill *m_skill;
    EffectActionInfo *m_data;
    bool m_end;
    uint32_t m_index;
    bool m_first;

    uint32_t m_overplusCount;
    uint64_t m_radiateInterval;
    uint64_t m_lastRadiateTime;
};

void BuffMove(Character *, Character *, uint32_t type, const std::vector<double> &param);

#endif


