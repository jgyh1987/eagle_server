#ifndef _SKILL_H_ 
#define    _SKILL_H_

#include "Noncopyable.h"
#include "PlayerInfo.h"
#include "LogicDataManager.h"
#include "TimeTick.h"
#include "WorldObject.h"

class Character;
class SkillManager;

enum SKILL_CAST_STATUS
{
    SKILL_CAST_STATUS_NONE = 0,
    SKILL_CAST_STATUS_PRE = 1,
    SKILL_CAST_STATUS_CASTING = 2,
    SKILL_CAST_STATUS_END = 3
};

class Skill : public UnitObject
{
public:
    Skill(SkillData * skillData, Character *owner);
    ~Skill();

    uint32_t Type() { return OBJECT_SKILL; }
    bool IsType(uint32_t type) { return type == OBJECT_SKILL; }

	bool Init(uint64_t id);
	uint32_t SubId() { return m_data->id; }
	void Update();
    bool IsEnd() { return SKILL_CAST_STATUS_END == m_status; }

public:
    virtual void ReSet();
    virtual bool StratCast(TargetPos *pos);
    virtual void EndCast();
    virtual void Attack();
    virtual void Attack(uint32_t index, std::vector<uint64_t> &targetUid);
    virtual bool CanSuspend() { return false; }
    virtual bool CanForceEnd() { return false; }
    virtual uint64_t LiftTime()
    {
        if (m_data)
            return m_data->loadTime;

        return 0;
    }
    //inline
public:
    inline SkillData *GetConfigData()
    {
        return m_data;
    }

    inline void SetDel()
    {
        m_needDel = false;
        return;
    }

    inline bool NeedDel()
    {
        return m_needDel;
    }

    inline Character *Owner()
    {
        return m_owner;
    }

    inline uint32_t &Status()
    {
        return m_status;
    }

    inline TargetPos &GetTargetPos()
    {
        return m_targetPos;
    }

    inline bool IsCD()
    {
        return !(CImpServerTimeTick::currentTime.msec() >= m_lastEndTime);
    }

    inline uint64_t GetStartTime()
    {
        return m_startTime;
    }

    inline void SetStartTime(uint64_t time)
    {
        m_startTime = time;
    }

    inline uint32_t GetIndex()
    {
        return m_index;
    }

    inline void SetIndex(uint32_t index)
    {
        m_index = index;
    }

    inline uint64_t GetLastEndTime()
    {
        return m_lastEndTime;
    }

    inline void SetLastEndTime(uint64_t time)
    {
        m_lastEndTime = time;
    }

protected:
    SkillData * m_data;
    Character *m_owner;
    uint64_t m_startTime;
    bool m_needDel;
    uint32_t m_status;
    TargetPos m_targetPos;
    uint32_t m_index;
    uint64_t m_lastEndTime;
};

bool AllocSkill(uint64_t skillId, Character *owner, std::vector<Skill *> &);
bool FreeSkill(Skill*);

typedef bool(*CREATESKILL)(uint64_t skillId, Character *owner, std::vector<Skill *> &);

struct SubSkillProtect
{
    uint32_t subId;
    uint64_t ProtectTime;
};

class SkillManager
{
public:
    SkillManager(Character *owner, CREATESKILL CreateSkill = AllocSkill);
    virtual ~SkillManager();

    virtual void AddSkill(uint64_t id, Character *owner);
    virtual void RemoveSkill(uint64_t id);
    virtual std::vector<Skill *> *HaveSkill(uint64_t id);
    virtual bool CastSkill(uint64_t skillId, uint32_t subId, TargetPos *pos, bool trigger = false);
    virtual void EndSkill();
    virtual void UpdateSkill();
    virtual void SetSubSkillProtectedTime(Skill *);

    bool IsCastSkill();

protected:
    virtual void EndSkill(Skill *skill);

    bool CanSkill(Skill *skill, uint32_t index, bool trigger);

protected:
    std::map< uint64_t, std::vector<Skill *> > m_skills;
    Skill *m_casting;
    CREATESKILL _CreateSkill;
    Character *m_owner;
    std::map<uint64_t, SubSkillProtect> m_subSkillProtectTime;
};





#endif    


