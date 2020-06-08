#ifndef _EFFECT_H_ 
#define    _EFFECT_H_

#include "EaglePos.h"
#include "SharedEvent.h"

//ACTION
enum SKILL_BUFF_EFFECT_TYPE
{
    SKILL_BUFF_EFFECT_TYPE_NONE = 0,
    SKILL_BUFF_EFFECT_TYPE_HURT = 1,                        //

    //BUFF
    BUFF_EFFECT_TYPE_ATTR_CHANGE_MIN = 2,                //
    BUFF_EFFECT_TYPE_ADD_STATUS = 2,                    //
    BUFF_EFFECT_TYPE_ADD_ATTR_PERCENT = 3,            //
    BUFF_EFFECT_TYPE_SUB_ATTR_PRECENT = 4,            //
    BUFF_EFFECT_TYPE_ADD_ATTR = 5,                    //
    BUFF_EFFECT_TYPE_SUB_ATTR = 6,                    //
    BUFF_EFFECT_TYPE_ATTR_CHANGE_MAX = 6,                //
    BUFF_EFFECT_TYPE_ATTR_CHANGE_NUM = BUFF_EFFECT_TYPE_ATTR_CHANGE_MAX - BUFF_EFFECT_TYPE_ATTR_CHANGE_MIN + 1,        //

    SKILL_BUFF_EFFECT_TYPE_CAST_SKILL = 7,                    //
    SKILL_BUFF_EFFECT_TYPE_HURT_PERCENT = 8,                //
    SKILL_BUFF_EFFECT_TYPE_HURT_FIX = 9,                    //
    SKILL_BUFF_EFFECT_TYPE_HEALT = 10,                        //
    SKILL_BUFF_EFFECT_TYPE_HEALT_PERCENT = 11,                //
    SKILL_BUFF_EFFECT_TYPE_HEALT_FIX = 12,                    //
    SKILL_BUFF_EFFECT_TYPE_CAST_BUFF = 13,                    //
    SKILL_BUFF_EFFECT_TYPE_CAST_DYNAMIC = 14,                //
    SKILL_BUFF_EFFECT_TYPE_STRENG_SKILL = 15,                //
    SKILL_BUFF_EFFECT_TYPE_CREATE_SUMMON = 16,                //
    SKILL_BUFF_EFFECT_TYPE_CHANGE_SKILL = 17,                //
    SKILL_BUFF_EFFECT_TYPE_BEHURT_FIX_1 = 18,                //
    SKILL_BUFF_EFFECT_TYPE_CHANGE_BEHIT_ACTION = 19,        //
    SKILL_BUFF_EFFECT_TYPE_CHANGE_BEHURT = 20,                //
    SKILL_BUFF_EFFECT_TYPE_SPECIAL_ATTACK = 21,                //
    SKILL_BUFF_EFFECT_TYPE_MAX
};

//HIT TYP
enum Hit_Type
{
    Hit_Type_Normal = 0,        //
    Hit_Type_Dodge = 1,            //
    Hit_Type_Crit = 2,            //

    Hit_Type_Max,    //
};

//Trigger Cast Target Type
enum TRIGGER_CAST_TARGET_TYPE
{
    TRIGGER_CAST_TARGET_TYPE_OWNER = 0,    //
    TRIGGER_CAST_TARGET_TYPE_TARGET = 1,    //
};

//Skill Streng Type
enum SKILL_STRENG_TYPE
{
    SKILL_STRENG_TYPE_NONE, 
    SKILL_STRENG_TYPE_CAST_TIME,        //
    SKILL_STRENG_TYPE_EFFECT_TIME,        //
    SKILL_STRENG_TYPE_EFFECT_PARAM,        //
    SKILL_STRENG_TYPE_TRIGGER_RATE,        //
    SKILL_STRENG_TYPE_CD,                //

    SKILL_STRENG_TYPE_MAX
};

//CONDITION
enum BUFF_TRIGGER_TYPE
{
    BUFF_TRIGGER_TYPE_NONE = 0,
    BUFF_TRIGGER_TYPE_TIME = 1,                //
    BUFF_TRIGGER_TYPE_BE_ATK = 2,            //
    BUFF_TRIGGER_TYPE_ATK = 3,                //

    BUFF_TRIGGER_TYPE_MAX
};

class Character;
class Buff;
class Skill;
class Effect;

EagleAction* CreateSkillBuffAction(uint32_t type, void *ptr1, void *ptr2);
extern std::vector<uint32_t> g_trigger_to_event;
void InitBuffTiggerToEventArray();
void CreateBuffCondition(EagleAction *action, uint32_t type, const std::vector<double> &param);

//Condition
class TriggerTimeCondition : public EagleCondition
{
protected:
    bool UpdateImp(EagleEvent *);

public:
    uint64_t m_lastTriggerTime;
    uint32_t m_triggerInterval;
    bool m_trigger;

public:
    TriggerTimeCondition(EagleAction *action, const std::vector<double> &param);

    bool operator()();
    uint32_t Id() { return BUFF_TRIGGER_TYPE_TIME; }
};

class TriggerBeAtkCondition : public EagleCondition
{
protected:
    bool UpdateImp(EagleEvent *);

public:
    uint32_t m_weaponType;
    uint64_t m_skillId;
    uint32_t m_hitType; // enum Hit_Type
    bool m_trigger;

public:
    TriggerBeAtkCondition(EagleAction *action, const std::vector<double> &param);

    bool operator()();
    uint32_t Id() { return BUFF_TRIGGER_TYPE_BE_ATK; }
};

class TriggerAtkCondition : public EagleCondition
{
protected:
    bool UpdateImp(EagleEvent *);

public:
    uint32_t m_weaponType;
    uint32_t m_weaponSubId;
    uint64_t m_skillId;
    uint32_t m_skillType;
    uint32_t m_hitType; // enum Hit_Type
    bool m_trigger;

public:
    TriggerAtkCondition(EagleAction *action, const std::vector<double> &param);

    bool operator()();
    uint32_t Id() { return BUFF_TRIGGER_TYPE_ATK; }
};

//effect
typedef Effect *(*NewEffect)(Buff *buff, const std::vector<double> &para);
extern std::vector<NewEffect> g_createBuffEffectFuns;
typedef bool(*SkillEffect)(Character *caster, Skill *skill, const std::vector<double> &param, Character *target);
extern std::vector<SkillEffect> g_skillEffectFuns;
void InitEffectFuncs();

class Effect 
{
public:
    Effect(){}
    virtual ~Effect(){}

    virtual uint32_t Id() = 0; 
    virtual bool DoAction(Buff *buff, void *ptr) = 0;
    virtual void UnDoAction(Buff *buff){}
};

class HurtEffect : public Effect
{
    double m_value;
public:
    HurtEffect(Buff *buff, const std::vector<double> &param);
    ~HurtEffect();

    uint32_t Id(){return SKILL_BUFF_EFFECT_TYPE_HURT;}
    bool DoAction(Buff *buff, void *ptr);

public:
    static Effect *NewEffect(Buff *buff, const std::vector<double> &param){return new HurtEffect(buff, param);}
    static bool DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target);
};

class AddStatusEffect : public Effect
{
    int64_t m_status;
public:
    AddStatusEffect(Buff *buff, const std::vector<double> &param);
    ~AddStatusEffect();

    uint32_t Id(){return BUFF_EFFECT_TYPE_ADD_STATUS;}
    bool DoAction(Buff *buff, void *ptr);
    void UnDoAction(Buff *buff);

public:
    static Effect *NewEffect(Buff *buff, const std::vector<double> &param) { return new AddStatusEffect(buff, param); }
    static bool DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target);
};

class AttrAddPercentEffect : public Effect
{
    uint32_t m_type;
    double m_value;
public:
    AttrAddPercentEffect(Buff *buff, const std::vector<double> &param);
    ~AttrAddPercentEffect();

    uint32_t Id(){return BUFF_EFFECT_TYPE_ADD_ATTR_PERCENT;}
    bool DoAction(Buff *buff, void *ptr);
    void UnDoAction(Buff *buff);

public:
    static Effect *NewEffect(Buff *buff, const std::vector<double> &param) { return new AttrAddPercentEffect(buff, param); }
};

class AttrSubPercentEffect : public Effect
{
    uint32_t m_type;
    double m_value;
public:
    AttrSubPercentEffect(Buff *buff, const std::vector<double> &param);
    ~AttrSubPercentEffect();

    uint32_t Id(){return BUFF_EFFECT_TYPE_SUB_ATTR_PRECENT;}
    bool DoAction(Buff *buff, void *ptr);
    void UnDoAction(Buff *buff);

public:
    static Effect *NewEffect(Buff *buff, const std::vector<double> &param) { return new AttrSubPercentEffect(buff, param); }

};

class AttrAddEffect : public Effect
{
    uint32_t m_type;
    double m_value;
public:
    AttrAddEffect(Buff *buff, const std::vector<double> &param);
    ~AttrAddEffect();

    uint32_t Id(){return BUFF_EFFECT_TYPE_ADD_ATTR;}
    bool DoAction(Buff *buff, void *ptr);
    void UnDoAction(Buff *buff);


public:
    static Effect *NewEffect(Buff *buff, const std::vector<double> &param) { return new AttrAddEffect(buff, param); }
};

class AttrSubEffect : public Effect
{
    uint32_t m_type;
    double m_value;
public:
    AttrSubEffect(Buff *buff, const std::vector<double> &param);
    ~AttrSubEffect();

    uint32_t Id(){return BUFF_EFFECT_TYPE_SUB_ATTR;}
    bool DoAction(Buff *buff, void *ptr);
    void UnDoAction(Buff *buff);

public:
    static Effect *NewEffect(Buff *buff, const std::vector<double> &param) { return new AttrSubEffect(buff, param); }

};

class CastSkillEffect : public Effect
{
public:
    CastSkillEffect(Buff *buff, const std::vector<double> &param);
    ~CastSkillEffect();

    uint32_t Id(){return SKILL_BUFF_EFFECT_TYPE_CAST_SKILL;}
    bool DoAction(Buff *buff, void *ptr);

public:
    static Effect *NewEffect(Buff *buff, const std::vector<double> &param){return new CastSkillEffect(buff, param);}
    static bool DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target);
};

class HurtPercentEffect : public Effect
{
    double m_value;
public:
    HurtPercentEffect(Buff *buff, const std::vector<double> &param);
    ~HurtPercentEffect();

    uint32_t Id(){return SKILL_BUFF_EFFECT_TYPE_HURT_PERCENT;}
    bool DoAction(Buff *buff, void *ptr);

public:
    static Effect *NewEffect(Buff *buff, const std::vector<double> &param){return new HurtPercentEffect(buff, param);}
    static bool DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target);
};

class HurtFixEffect : public Effect
{
    double m_value;
public:
    HurtFixEffect(Buff *buff, const std::vector<double> &param);
    ~HurtFixEffect();

    uint32_t Id(){return SKILL_BUFF_EFFECT_TYPE_HURT_FIX;}
    bool DoAction(Buff *buff, void *ptr);

public:
    static Effect *NewEffect(Buff *buff, const std::vector<double> &param){return new HurtFixEffect(buff, param);}
    static bool DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target);
};

class HealtEffect : public Effect
{
    double m_value;
public:
    HealtEffect(Buff *buff, const std::vector<double> &param);
    ~HealtEffect();

    uint32_t Id(){return SKILL_BUFF_EFFECT_TYPE_HEALT;}
    bool DoAction(Buff *buff, void *ptr);

public:
    static Effect *NewEffect(Buff *buff, const std::vector<double> &param){return new HealtEffect(buff, param);}
    static bool DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target);
};

class HealtPercentEffect : public Effect
{
    double m_value;
public:
    HealtPercentEffect(Buff *buff, const std::vector<double> &param);
    ~HealtPercentEffect();

    uint32_t Id(){return SKILL_BUFF_EFFECT_TYPE_HEALT_PERCENT;}
    bool DoAction(Buff *buff, void *ptr);

public:
    static Effect *NewEffect(Buff *buff, const std::vector<double> &param){return new HealtPercentEffect(buff, param);}
    static bool DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target);
};

class HealtFixEffect : public Effect
{
    double m_value;
public:
    HealtFixEffect(Buff *buff, const std::vector<double> &param);
    ~HealtFixEffect();

    uint32_t Id(){return SKILL_BUFF_EFFECT_TYPE_HEALT_FIX;}
    bool DoAction(Buff *buff, void *ptr);

public:
    static Effect *NewEffect(Buff *buff, const std::vector<double> &param){return new HealtFixEffect(buff, param);}
    static bool DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target);
};

class AddBuffEffect : public Effect
{
    uint64_t m_buffId;
    uint64_t m_time;
    uint32_t m_castRate;
    uint32_t m_castTargetType;    //Trigger Cast Type
public:
    AddBuffEffect(Buff *buff, const std::vector<double> &param);
    ~AddBuffEffect();

    uint32_t Id(){return SKILL_BUFF_EFFECT_TYPE_CAST_BUFF;}
    bool DoAction(Buff *buff, void *ptr);

public:
    static Effect *NewEffect(Buff *buff, const std::vector<double> &param){return new AddBuffEffect(buff, param);}
    static bool DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target);
};

class CastDynamicEffect : public Effect
{
public:
    CastDynamicEffect(Buff *buff, const std::vector<double> &param);
    ~CastDynamicEffect();

    uint32_t Id(){return SKILL_BUFF_EFFECT_TYPE_CAST_DYNAMIC;}
    bool DoAction(Buff *buff, void *ptr);

public:
    static Effect *NewEffect(Buff *buff, const std::vector<double> &param){return new CastDynamicEffect(buff, param);}
    static bool DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target);
};

class StrengSkillEffect : public Effect
{
    double m_value;
    uint32_t m_strengType;
    uint64_t m_skillId;
    uint32_t m_skillSubId;
public:
    StrengSkillEffect(Buff *buff, const std::vector<double> &param);
    ~StrengSkillEffect();

    uint32_t Id(){return SKILL_BUFF_EFFECT_TYPE_STRENG_SKILL;}
    bool DoAction(Buff *buff, void *ptr);
    void UnDoAction(Buff *buff);

public:
    static Effect *NewEffect(Buff *buff, const std::vector<double> &param){return new StrengSkillEffect(buff, param);}
    static bool DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target);
};

class CastSummonEffect : public Effect
{
public:
    CastSummonEffect(Buff *buff, const std::vector<double> &param);
    ~CastSummonEffect();

    uint32_t Id(){return SKILL_BUFF_EFFECT_TYPE_CREATE_SUMMON;}
    bool DoAction(Buff *buff, void *ptr);

public:
    static Effect *NewEffect(Buff *buff, const std::vector<double> &param){return new CastSummonEffect(buff, param);}
    static bool DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target);
};

class ChangeSkillEffect : public Effect
{
    const std::vector<double> &m_changeSkills;
public:
    ChangeSkillEffect(Buff *buff, const std::vector<double> &param);
    ~ChangeSkillEffect();

    uint32_t Id(){return SKILL_BUFF_EFFECT_TYPE_CHANGE_SKILL;}
    bool DoAction(Buff *buff, void *ptr);
    void UnDoAction(Buff *buff);

public:
    static Effect *NewEffect(Buff *buff, const std::vector<double> &param){return new ChangeSkillEffect(buff, param);}
    static bool DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target);
};

class BeHurtFix1Effect : public Effect
{
public:
    BeHurtFix1Effect(Buff *buff, const std::vector<double> &param);
    ~BeHurtFix1Effect();

    uint32_t Id(){return SKILL_BUFF_EFFECT_TYPE_BEHURT_FIX_1;}
    bool DoAction(Buff *buff, void *ptr);

public:
    static Effect *NewEffect(Buff *buff, const std::vector<double> &param){return new BeHurtFix1Effect(buff, param);}
    static bool DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target);
};

class ChangeBeHurtEffect : public Effect
{
public:
    ChangeBeHurtEffect(Buff *buff, const std::vector<double> &param);
    ~ChangeBeHurtEffect();

    uint32_t Id(){return SKILL_BUFF_EFFECT_TYPE_CHANGE_BEHURT;}
    bool DoAction(Buff *buff, void *ptr);

public:
    static Effect *NewEffect(Buff *buff, const std::vector<double> &param){return new ChangeBeHurtEffect(buff, param);}
    static bool DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target);
};

class SpecialAtkCountEffect : public Effect
{
public:
    SpecialAtkCountEffect(Buff *buff, const std::vector<double> &param);
    ~SpecialAtkCountEffect();

    uint32_t Id(){return SKILL_BUFF_EFFECT_TYPE_SPECIAL_ATTACK;}
    bool DoAction(Buff *buff, void *ptr);

public:
    static Effect *NewEffect(Buff *buff, const std::vector<double> &param){return new SpecialAtkCountEffect(buff, param);}
    static bool DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target);
};

bool DoSkillEffect(uint32_t type, Character *caster, Skill *skill, const std::vector<double> &param, Character *target);
Effect* CreateEffect(Buff *buff, uint32_t type, const std::vector<double> &param);
void FreeEffect(Effect *ptr);

#endif    


