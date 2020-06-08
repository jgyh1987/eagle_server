#ifndef _MMO_SKILL_H_ 
#define    _MMO_SKILL_H_

#include "Skill.h"
#include "EffectObject.h"


class MMOSkill : public Skill
{
public:
    MMOSkill(SkillConfigData * skillInfoData, SkillData * skillData, Character *owner);
    ~MMOSkill();

    uint32_t Type() { return OBJECT_MMO_SKILL; }
    bool IsType(uint32_t type) { return type == OBJECT_MMO_SKILL; }

    bool Init(uint64_t id);
    void Update();
    void Clear();

    void ReSet();
    bool StratCast(TargetPos *pos);
    void EndCast();

public:
    SkillConfigData *GetSkillInfoData() { return m_skillInfoData; }
    void AddEffectObject(EffectObject *);
    inline uint32_t EffectObjectsSize() { return (uint32_t)m_effectObjects.size(); }

    inline std::list<EffectAction *> &GetActionObjects()
    {
        return m_actionObjects;
    }

private:
    SkillConfigData *m_skillInfoData;
    std::list<EffectAction *> m_actionObjects;
    std::list<EffectObject *> m_effectObjects;
};

bool AllocMMOSkill(uint64_t skillId, Character *owner, std::vector<Skill *> &);

class MMOSkillManager : public SkillManager
{
public:
    MMOSkillManager(Character *owner);
    ~MMOSkillManager();

    bool CastSkill(uint32_t skillId, uint32_t subId, TargetPos *pos, bool trigger);
    void UpdateSkill();
    void SetSubSkillProtectedTime(Skill *);

public:
    inline MMOSkill *Casting() { return (MMOSkill *)m_casting; }
    void AddEffectSkills(MMOSkill *);
    void RemoveEffectSkill(MMOSkill *);

    uint32_t Serialize(uint8_t *buffer);
    uint32_t UnSerialize(uint8_t *buffer);

protected:
    

private:
    std::list<MMOSkill *> m_effectSkills;

};

#endif    


