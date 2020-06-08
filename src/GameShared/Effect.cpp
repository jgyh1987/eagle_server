#include "Effect.h"
#include "Buff.h"
#include "Character.h"
#include "ClientMsg.h"
#include "EffectObject.h"
#include "WorldCommand.h"

std::vector<NewEffect> g_createBuffEffectFuns;
std::vector<SkillEffect> g_skillEffectFuns;
std::vector<uint32_t> g_trigger_to_event;


void InitEffectFuncs()
{
    g_createBuffEffectFuns.resize(SKILL_BUFF_EFFECT_TYPE_MAX, NULL);
    g_createBuffEffectFuns[SKILL_BUFF_EFFECT_TYPE_HURT] = HurtEffect::NewEffect;
    g_createBuffEffectFuns[BUFF_EFFECT_TYPE_ADD_STATUS] = AddStatusEffect::NewEffect;
    g_createBuffEffectFuns[BUFF_EFFECT_TYPE_ADD_ATTR_PERCENT] = AttrAddPercentEffect::NewEffect;
    g_createBuffEffectFuns[BUFF_EFFECT_TYPE_SUB_ATTR_PRECENT] = AttrSubPercentEffect::NewEffect;
    g_createBuffEffectFuns[BUFF_EFFECT_TYPE_ADD_ATTR] = AttrAddEffect::NewEffect;
    g_createBuffEffectFuns[BUFF_EFFECT_TYPE_SUB_ATTR] = AttrSubEffect::NewEffect;
    g_createBuffEffectFuns[SKILL_BUFF_EFFECT_TYPE_CAST_SKILL] = CastSkillEffect::NewEffect;
    g_createBuffEffectFuns[SKILL_BUFF_EFFECT_TYPE_HURT_PERCENT] = HurtPercentEffect::NewEffect;
    g_createBuffEffectFuns[SKILL_BUFF_EFFECT_TYPE_HURT_FIX] = HurtFixEffect::NewEffect;
    g_createBuffEffectFuns[SKILL_BUFF_EFFECT_TYPE_HEALT] = HealtEffect::NewEffect;
    g_createBuffEffectFuns[SKILL_BUFF_EFFECT_TYPE_HEALT_PERCENT] = HealtPercentEffect::NewEffect;
    g_createBuffEffectFuns[SKILL_BUFF_EFFECT_TYPE_HEALT_FIX] = HealtFixEffect::NewEffect;
    g_createBuffEffectFuns[SKILL_BUFF_EFFECT_TYPE_CAST_BUFF] = AddBuffEffect::NewEffect;
    g_createBuffEffectFuns[SKILL_BUFF_EFFECT_TYPE_CAST_DYNAMIC] = CastDynamicEffect::NewEffect;
    g_createBuffEffectFuns[SKILL_BUFF_EFFECT_TYPE_STRENG_SKILL] = StrengSkillEffect::NewEffect;
    g_createBuffEffectFuns[SKILL_BUFF_EFFECT_TYPE_CREATE_SUMMON] = CastSummonEffect::NewEffect;
    g_createBuffEffectFuns[SKILL_BUFF_EFFECT_TYPE_CHANGE_SKILL] = ChangeSkillEffect::NewEffect;
    g_createBuffEffectFuns[SKILL_BUFF_EFFECT_TYPE_BEHURT_FIX_1] = BeHurtFix1Effect::NewEffect;
    g_createBuffEffectFuns[SKILL_BUFF_EFFECT_TYPE_CHANGE_BEHURT] = ChangeBeHurtEffect::NewEffect;
    g_createBuffEffectFuns[SKILL_BUFF_EFFECT_TYPE_SPECIAL_ATTACK] = SpecialAtkCountEffect::NewEffect;

    g_skillEffectFuns.resize(SKILL_BUFF_EFFECT_TYPE_MAX, NULL);
    g_skillEffectFuns[SKILL_BUFF_EFFECT_TYPE_HURT] = HurtEffect::DoAction;
    g_skillEffectFuns[BUFF_EFFECT_TYPE_ADD_STATUS] = AddStatusEffect::DoAction;
    g_skillEffectFuns[SKILL_BUFF_EFFECT_TYPE_CAST_SKILL] = CastSkillEffect::DoAction;
    g_skillEffectFuns[SKILL_BUFF_EFFECT_TYPE_HURT_PERCENT] = HurtPercentEffect::DoAction;
    g_skillEffectFuns[SKILL_BUFF_EFFECT_TYPE_HURT_FIX] = HurtFixEffect::DoAction;
    g_skillEffectFuns[SKILL_BUFF_EFFECT_TYPE_HEALT] = HealtEffect::DoAction;
    g_skillEffectFuns[SKILL_BUFF_EFFECT_TYPE_HEALT_PERCENT] = HealtPercentEffect::DoAction;
    g_skillEffectFuns[SKILL_BUFF_EFFECT_TYPE_HEALT_FIX] = HealtFixEffect::DoAction;
    g_skillEffectFuns[SKILL_BUFF_EFFECT_TYPE_CAST_BUFF] = AddBuffEffect::DoAction;
    g_skillEffectFuns[SKILL_BUFF_EFFECT_TYPE_CAST_DYNAMIC] = CastDynamicEffect::DoAction;
    g_skillEffectFuns[SKILL_BUFF_EFFECT_TYPE_STRENG_SKILL] = StrengSkillEffect::DoAction;
    g_skillEffectFuns[SKILL_BUFF_EFFECT_TYPE_CREATE_SUMMON] = CastSummonEffect::DoAction;
    g_skillEffectFuns[SKILL_BUFF_EFFECT_TYPE_CHANGE_SKILL] = ChangeSkillEffect::DoAction;
    g_skillEffectFuns[SKILL_BUFF_EFFECT_TYPE_BEHURT_FIX_1] = BeHurtFix1Effect::DoAction;
    g_skillEffectFuns[SKILL_BUFF_EFFECT_TYPE_CHANGE_BEHURT] = ChangeBeHurtEffect::DoAction;
    g_skillEffectFuns[SKILL_BUFF_EFFECT_TYPE_SPECIAL_ATTACK] = SpecialAtkCountEffect::DoAction;

    return;
}

void InitBuffTiggerToEventArray()
{
    g_trigger_to_event.resize(BUFF_TRIGGER_TYPE_MAX);
    g_trigger_to_event[BUFF_TRIGGER_TYPE_NONE] = EVENT_TYPE_NONE;
    g_trigger_to_event[BUFF_TRIGGER_TYPE_TIME] = EVENT_TYPE_TIME;
    g_trigger_to_event[BUFF_TRIGGER_TYPE_BE_ATK] = EVENT_TYPE_BE_ATK;
    g_trigger_to_event[BUFF_TRIGGER_TYPE_ATK] = EVENT_TYPE_ATK;

    return;
}

void CreateBuffCondition(EagleAction *action, uint32_t type, const std::vector<double> &param)
{
    switch (type)
    {
    case BUFF_TRIGGER_TYPE_TIME:
        new TriggerTimeCondition(action, param);
        break;
    case BUFF_TRIGGER_TYPE_BE_ATK:
        new TriggerBeAtkCondition(action, param);
        break;
    case BUFF_TRIGGER_TYPE_ATK:
        new TriggerAtkCondition(action, param);
        break;
    default:
        break;
    }

    return;
}

EagleAction* CreateSkillBuffAction(uint32_t type, void *ptr1, void *ptr2)
{
    EagleAction *temp = NULL;
    switch (type)
    {
    case ACTION_TRIGGER_EFFECT:
        return new TiggerEffect(ptr1, ptr2);
        break;
    default:
        break;
    }

    return temp;
}

//trigger 
//TriggerTimeCondition
TriggerTimeCondition::TriggerTimeCondition(EagleAction *action, const std::vector<double> &param)
    :EagleCondition(action), m_trigger(false)
{
    if (param.size())
        m_triggerInterval = (uint32_t)param[0];

    m_lastTriggerTime = 0;
}

bool TriggerTimeCondition::UpdateImp(EagleEvent *_event)
{
    OnTimeEvent *tempEvent = (OnTimeEvent *)_event;
    if (!m_lastTriggerTime || tempEvent->CurTime() - m_lastTriggerTime > m_triggerInterval)
    {
        m_lastTriggerTime = tempEvent->CurTime();
        m_trigger = true;
    }

    return true;
}

bool TriggerTimeCondition::operator()()
{
    bool ret = m_trigger;
    m_trigger = false;

    return ret;
}

//TriggerBeAtkCondition
TriggerBeAtkCondition::TriggerBeAtkCondition(EagleAction *action, const std::vector<double> &param)
    :EagleCondition(action), m_trigger(false)
{
    if (3 == param.size())
    {
        m_hitType = (uint32_t)param[0];
        m_skillId = (uint64_t)param[1];
        m_weaponType = (uint32_t)param[2];
    }
    else
    {
        m_hitType = 0;
        m_skillId = 0;
        m_weaponType = 0;
    }
}

bool TriggerBeAtkCondition::UpdateImp(EagleEvent *_event)
{
    OnBeAtkEvent *tempEvent = (OnBeAtkEvent *)_event;
    if ((!m_weaponType || tempEvent->WeaponType() == m_weaponType) && (!m_hitType || tempEvent->HitType() == m_hitType) && (!m_skillId || tempEvent->SkillId() == m_skillId))
    {
        m_trigger = true;
    }

    return true;
}

bool TriggerBeAtkCondition::operator()()
{
    bool ret = m_trigger;
    m_trigger = false;

    return ret;
}

//TriggerAtkCondition
TriggerAtkCondition::TriggerAtkCondition(EagleAction *action, const std::vector<double> &param)
    :EagleCondition(action), m_trigger(false)
{
    if (5 == param.size())
    {
        m_weaponType = (uint32_t)param[0];
        m_weaponSubId = (uint32_t)param[1];
        m_skillId = (uint64_t)param[2];
        m_skillType = (uint32_t)param[3];
        m_hitType = (uint32_t)param[4];
    }
    else
    {
        m_weaponType = 0;
        m_weaponSubId = 0;
        m_skillId = 0;
        m_skillType = 0;
        m_hitType = 0;
    }
}

bool TriggerAtkCondition::UpdateImp(EagleEvent *_event)
{
    //OnAtkEvent *tempEvent = (OnAtkEvent *)_event;
    //if ((!m_weaponType || tempEvent->WeaponType() == m_weaponType) && (!m_hitType || tempEvent->HitType() == m_hitType) && (!m_skillId || tempEvent->GetSkillConfigData()->id == m_skillId) && (!m_weaponSubId || tempEvent->WeaponSubId() == m_weaponSubId) && (!m_skillType || tempEvent->GetSkillConfigData()->type == m_skillType))
    //{
    //    m_trigger = true;
    //}

    return true;
}

bool TriggerAtkCondition::operator()()
{
    bool ret = m_trigger;
    m_trigger = false;

    return ret;
}

bool DoSkillEffect(uint32_t type, Character *caster, Skill *skill, const std::vector<double> &param, Character *target)
{
    if (type > SKILL_BUFF_EFFECT_TYPE_NONE && type < SKILL_BUFF_EFFECT_TYPE_MAX)
        return g_skillEffectFuns[type](caster, skill, param, target);

    return false;
}

Effect* CreateEffect(Buff *buff, uint32_t type, const std::vector<double> &param)
{
    if (type > SKILL_BUFF_EFFECT_TYPE_NONE && type < SKILL_BUFF_EFFECT_TYPE_MAX)
        if (g_createBuffEffectFuns[type])
            return g_createBuffEffectFuns[type](buff, param);

    return NULL;
}

void FreeEffect(Effect *ptr)
{
    delete ptr;

    return  ;
}

//Effect
uint32_t Effect::Id()
{
    return SKILL_BUFF_EFFECT_TYPE_NONE;
}

//HurtEffect
HurtEffect::HurtEffect(Buff *buff, const std::vector<double> &param)
{
    if (buff->Caster() && 2 == param.size())
    {
		int64_t ackValue = 10;// buff->Caster()->GetFightCurAttr(EAT_ATTACK);
        if (ackValue < 0)
            ackValue = 0;
        m_value = ackValue * param[1] / POS_DENOMINATOR;
    }
    else
        m_value = 0;
}

HurtEffect::~HurtEffect()
{

}

bool HurtEffect::DoAction(Buff *buff, void *ptr)
{
    Character *owner = buff->Owner();
    Character *caster = buff->Caster();

    double hurt = m_value;

    hurt *= buff->OverLay();
    if (hurt <= 0)
        hurt = 1;

    //owner->SubHp((uint32_t)hurt, caster);

    return true;
}

bool HurtEffect::DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target)
{
    double value;

    Character *parent = skill->Owner();

	int64_t ackValue = 10;// parent->GetFightCurAttr(EAT_ATTACK);
    //if (ackValue < 0)
    //    ackValue = 0;
    //value = ackValue * param[0] / POS_DENOMINATOR;

    //Character *targeter = target;

    //if (value <= 0)
    //    value = 1;

    if (param.size() > 1)
        value = ackValue * param[param.size() - 2] / POS_DENOMINATOR;
    else
        value = 10;

    if (!target->IsAgent())
    {
        Cmd::t_Scene_HurtEffect send;
        send.actionId = skill->SubId();
        send.skillId = skill->Id();
        send.change = 1;
        send.hurt = (int64_t)value;
        send.src = parent->Uid();
        send.target = target->Uid();
        //target->AsyncChangeInfo(&send, sizeof(send));
    }
    else
    {
        //if (target->SubHp((int64_t)value, parent))
        //{
        //    ClientMsg::DoHurtNotify notify;
        //    notify.hurt = value;
        //    notify.actionId = skill->SubId();
        //    notify.skillId = (uint32_t)skill->Id();
        //    notify.caster.fightUid = caster->Uid();
        //    notify.target.fightUid = target->Uid();
        //    target->BroadcastClientMsg(&notify);
        //}
    }

    //LOGD("HurtEffect::DoAction   CasterUid = " << caster->Uid() << " TargetUid = " << target->Uid() << " Hurt = " << value << " param = " << param[param.size() - 2] << "   !!!");
        

    return true;
}

//AddStatusEffect
AddStatusEffect::AddStatusEffect(Buff *buff, const std::vector<double> &param)
{
    if (param.size() && ((uint64_t)param[0]) < CHARACTER_STATUS_TIMES_MAX)
        m_status = (int64_t)param[0];
    else
        m_status = -1;
}

AddStatusEffect::~AddStatusEffect()
{

}

bool AddStatusEffect::DoAction(Buff *buff, void *ptr)
{
    if (-1 != m_status)
    {
		return true;// buff->Owner()->SetStatus(m_status);
    }

    return false;
}

void AddStatusEffect::UnDoAction(Buff *buff)
{
    //if (-1 != m_status)
    //    buff->Owner()->ClearStatus(m_status);

    return;
}

bool AddStatusEffect::DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target)
{
    //if (target->IsCastSkill() || target->IsStatus(CHARACTER_STATUS_TIMES_OVERLORD) || target->IsStatus(CHARACTER_STATUS_TIMES_INVINCIBLE))
    //    return true;

    Character *parent = skill->Owner();

    if (param.size() > 2 && 302 == (uint32_t)param[1])
    {
        if (!target->IsAgent())
        {
            Cmd::t_Scene_AddStatus_Effect send;
            send.change = 1;
            send.src = parent->Uid();
            send.target = target->Uid();
            send.triggerEffectId = (uint32_t)param[param.size() - 1];
            send.type = CHARACTER_STATUS_TIMES_HITBACK;
            if (param.size() >= 1)
                send.param1 = (int64_t)(param[0] * POS_DENOMINATOR);
            if (param.size() >= 2)
                send.param1 = (int64_t)(param[1] * POS_DENOMINATOR);
            if (param.size() >= 3)
                send.param1 = (int64_t)(param[2] * POS_DENOMINATOR);
            if (param.size() >= 4)
                send.param1 = (int64_t)(param[3] * POS_DENOMINATOR);

           // target->AsyncChangeInfo(&send, sizeof(send));

            return true;
        }
        else
        {
            BuffMove(target, caster, CHARACTER_STATUS_TIMES_HITBACK, param);
        }
    }    

    ClientMsg::AddBuffNotify notify;
    notify.buff.buffId = 0;
    notify.buff.caster.fightUid = caster->Uid();
    notify.buff.caster.pos.x = caster->x;
    notify.buff.caster.pos.y = caster->y;
    notify.buff.caster.pos.z = caster->z;
    notify.buff.caster.pos.dirx = caster->dirx;
    notify.buff.caster.pos.diry = caster->diry;
    notify.buff.caster.pos.dirz = caster->dirz;
    notify.buff.layer = 0;
    notify.buff.target.fightUid = target->Uid();
    notify.buff.target.pos.x = target->x;
    notify.buff.target.pos.y = target->y;
    notify.buff.target.pos.z = target->z;
    notify.buff.target.pos.dirx = target->dirx;
    notify.buff.target.pos.diry = target->diry;
    notify.buff.target.pos.dirz = target->dirz;
    notify.buff.triggerEffectId = (uint32_t)param[param.size() - 1];
    //target->BroadcastClientMsg(&notify);

    return true;
}

//AttrAddPercentEffect
AttrAddPercentEffect::AttrAddPercentEffect(Buff *buff, const std::vector<double> &param)
{
    if (2 == param.size())
    {
        m_type = (uint32_t)param[0];
        m_value = param[1] / POS_DENOMINATOR;

        if (m_type < EAT_MAX || (m_type >= EAT_RESISTANT && m_type < EAT_RESISTANT_MAX))
        {
        }
        else
        {
            m_type = 0;
            m_value = 0;
        }
    }
    else
    {
        m_type = 0;
        m_value = 0;
    }
}

AttrAddPercentEffect::~AttrAddPercentEffect()
{

}

bool AttrAddPercentEffect::DoAction(Buff *buff, void *ptr)
{
    Character *owner = buff->Owner();
    if (m_type < EAT_MAX)
        owner->GetBuffManager()->AddFightAttrPrecent(m_type, m_value);
    else
        owner->GetBuffManager()->AddFightResistantPrecent(m_type - EAT_RESISTANT, m_value);

    return true;
}

void AttrAddPercentEffect::UnDoAction(Buff *buff)
{
    Character *owner = buff->Owner();
    if (m_type < EAT_MAX)
        owner->GetBuffManager()->SubFightAttrPrecent(m_type, m_value);
    else
        owner->GetBuffManager()->SubFightResistantPrecent(m_type - EAT_RESISTANT, m_value);

    return;
}

//AttrSubPercentEffect
AttrSubPercentEffect::AttrSubPercentEffect(Buff *buff, const std::vector<double> &param)
{
    if (2 == param.size())
    {
        m_type = (uint32_t)param[0];
        m_value = param[1] / POS_DENOMINATOR;

        if (m_type < EAT_MAX || (m_type >= EAT_RESISTANT && m_type < EAT_RESISTANT_MAX))
        {
        }
        else
        {
            m_type = 0;
            m_value = 0;
        }
    }
    else
    {
        m_type = 0;
        m_value = 0;
    }
}

AttrSubPercentEffect::~AttrSubPercentEffect()
{

}

bool AttrSubPercentEffect::DoAction(Buff *buff, void *ptr)
{
    Character *owner = buff->Owner();
    if (m_type < EAT_MAX)
        owner->GetBuffManager()->SubFightAttrPrecent(m_type, m_value);
    else
        owner->GetBuffManager()->SubFightResistantPrecent(m_type - EAT_RESISTANT, m_value);

    return true;
}

void AttrSubPercentEffect::UnDoAction(Buff *buff)
{
    Character *owner = buff->Owner();
    if (m_type < EAT_MAX)
        owner->GetBuffManager()->AddFightAttrPrecent(m_type, m_value);
    else
        owner->GetBuffManager()->AddFightResistantPrecent(m_type - EAT_RESISTANT, m_value);

    return;
}

//AttrAddEffect
AttrAddEffect::AttrAddEffect(Buff *buff, const std::vector<double> &param)
{
    if (2 == param.size())
    {
        m_type = (uint32_t)param[0];
        m_value = param[1];

        if (m_type < EAT_MAX || (m_type >= EAT_RESISTANT && m_type < EAT_RESISTANT_MAX))
        {
        }
        else
        {
            m_type = 0;
            m_value = 0;
        }
    }
    else
    {
        m_type = 0;
        m_value = 0;
    }
}

AttrAddEffect::~AttrAddEffect()
{

}

bool AttrAddEffect::DoAction(Buff *buff, void *ptr)
{
    Character *owner = buff->Owner();
    if (m_type < EAT_MAX)
        owner->GetBuffManager()->AddFightAttr(m_type, m_value);
    else
        owner->GetBuffManager()->AddFightResistant(m_type - EAT_RESISTANT, m_value);

    return true;
}

void AttrAddEffect::UnDoAction(Buff *buff)
{
    Character *owner = buff->Owner();
    if (m_type < EAT_MAX)
        owner->GetBuffManager()->SubFightAttr(m_type, m_value);
    else
        owner->GetBuffManager()->SubFightResistant(m_type - EAT_RESISTANT, m_value);

    return;
}

//AttrSubEffect
AttrSubEffect::AttrSubEffect(Buff *buff, const std::vector<double> &param)
{
    if (2 == param.size())
    {
        m_type = (uint32_t)param[0];
        m_value = param[1];

        if (m_type < EAT_MAX || (m_type >= EAT_RESISTANT && m_type < EAT_RESISTANT_MAX))
        {
        }
        else
        {
            m_type = 0;
            m_value = 0;
        }
    }
    else
    {
        m_type = 0;
        m_value = 0;
    }
}

AttrSubEffect::~AttrSubEffect()
{

}

bool AttrSubEffect::DoAction(Buff *buff, void *ptr)
{
    Character *owner = buff->Owner();
    if (m_type < EAT_MAX)
        owner->GetBuffManager()->SubFightAttr(m_type, m_value);
    else
        owner->GetBuffManager()->SubFightResistant(m_type - EAT_RESISTANT, m_value);

    return true;
}

void AttrSubEffect::UnDoAction(Buff *buff)
{
    Character *owner = buff->Owner();
    if (m_type < EAT_MAX)
        owner->GetBuffManager()->AddFightAttr(m_type, m_value);
    else
        owner->GetBuffManager()->AddFightResistant(m_type - EAT_RESISTANT, m_value);

    return;
}


//CastSkillEffect
CastSkillEffect::CastSkillEffect(Buff *buff, const std::vector<double> &param)
{

}

CastSkillEffect::~CastSkillEffect()
{

}

bool CastSkillEffect::DoAction(Buff *buff, void *ptr)
{

    return true;
}

bool CastSkillEffect::DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target)
{

    return true;
}

//HurtPercentEffect
HurtPercentEffect::HurtPercentEffect(Buff *buff, const std::vector<double> &param)
{
    if (2 == param.size())
        m_value = param[1] / POS_DENOMINATOR;
    else
        m_value = 0;
}

HurtPercentEffect::~HurtPercentEffect()
{

}

bool HurtPercentEffect::DoAction(Buff *buff, void *ptr)
{
    Character *owner = buff->Owner();
	int64_t maxhp = 100;// owner->GetFightCurAttr(EAT_MAXHP);

    double hurt = maxhp * m_value * buff->OverLay();
    if (hurt <= 0)
        hurt = 1;

    //owner->SubHp((uint32_t)hurt, buff->Caster());

    return true;
}

bool HurtPercentEffect::DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target)
{

    return true;
}

//HurtFixEffect
HurtFixEffect::HurtFixEffect(Buff *buff, const std::vector<double> &param)
{
    if (2 == param.size())
        m_value = param[1];
    else
        m_value = 0;
}

HurtFixEffect::~HurtFixEffect()
{

}

bool HurtFixEffect::DoAction(Buff *buff, void *ptr)
{
    double hurt = m_value * buff->OverLay();
    if (hurt <= 0)
        hurt = 1;

    //buff->Owner()->SubHp((uint32_t)hurt, buff->Caster());

    return true;
}

bool HurtFixEffect::DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target)
{

    return true;
}

//HealtEffect
HealtEffect::HealtEffect(Buff *buff, const std::vector<double> &param)
{
    if (buff->Caster() && 2 == param.size())
    {
		m_value = 10;// buff->Caster()->GetFightCurAttr(EAT_ATTACK)* param[1] / POS_DENOMINATOR;
    }
    else
        m_value = 0;
}

HealtEffect::~HealtEffect()
{

}

bool HealtEffect::DoAction(Buff *buff, void *ptr)
{
    double healt = m_value * buff->OverLay();
    if (healt <= 0)
        healt = 1;

    //buff->Owner()->AddHp((uint32_t)healt, buff->Caster());

    return true;
}

bool HealtEffect::DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target)
{

    return true;
}

//HealtPercentEffect
HealtPercentEffect::HealtPercentEffect(Buff *buff, const std::vector<double> &param)
{
    if (2 == param.size())
        m_value = param[1] / POS_DENOMINATOR;
    else
        m_value = 0;
}

HealtPercentEffect::~HealtPercentEffect()
{

}

bool HealtPercentEffect::DoAction(Buff *buff, void *ptr)
{
    Character *owner = buff->Owner();
	int64_t maxhp = 100;// owner->GetFightCurAttr(EAT_MAXHP);

    double healt = maxhp * m_value * buff->OverLay();
    if (healt <= 0)
        healt = 1;

    //owner->AddHp((uint32_t)healt, buff->Caster());

    return true;
}

bool HealtPercentEffect::DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target)
{

    return true;
}

//HealtFixEffect
HealtFixEffect::HealtFixEffect(Buff *buff, const std::vector<double> &param)
{
    if (2 == param.size())
        m_value = param[1];
    else
        m_value = 0;
}

HealtFixEffect::~HealtFixEffect()
{

}

bool HealtFixEffect::DoAction(Buff *buff, void *ptr)
{
    double healt = m_value * buff->OverLay();
    if (healt <= 0)
        healt = 1;

    //buff->Owner()->AddHp((uint32_t)healt, buff->Caster());

    return true;
}

bool HealtFixEffect::DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target)
{

    return true;
}

//AddBuffEffect
AddBuffEffect::AddBuffEffect(Buff *buff, const std::vector<double> &param)
{
    if (3 == param.size())
    {
        m_buffId = (uint64_t)param[1];
        m_castRate = (uint32_t)param[0];
        m_castTargetType = (uint32_t)param[2];
    }
    else
    {
        m_buffId = 0;
        m_castRate = 0;
        m_castTargetType = 0;
    }
}

AddBuffEffect::~AddBuffEffect()
{

}

bool AddBuffEffect::DoAction(Buff *buff, void *ptr)
{
    if (buff->IsDeBuff())
    {
        if (!buff->Caster())
            return false;

        uint32_t random = CRandom::RandomBetween(0, (uint32_t)POS_DENOMINATOR);
        if (random < m_castRate)
        {
            buff->Owner()->GetBuffManager()->AddBuff(m_buffId, m_time, buff->Caster(), buff->Owner());
        }
    }
    else
    {
        uint32_t random = CRandom::RandomBetween(0, (uint32_t)POS_DENOMINATOR);
        if (random < m_castRate)
        {
            if (TRIGGER_CAST_TARGET_TYPE_OWNER == m_castTargetType)
            {
                buff->Owner()->GetBuffManager()->AddBuff(m_buffId, m_time, buff->Caster(), buff->Owner());
            }
            else
            {
                Character *object = (Character *)ptr;
                if (object)
                    object->GetBuffManager()->AddBuff(m_buffId, m_time, buff->Owner(), object);
            }
        }
    }

    return true;
}

bool AddBuffEffect::DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target)
{
    if (param.size() < 4)
    {
        LOGE("AddBuffEffect::DoAction No Para !!!");
        return false;
    }

    Character *parent = skill->Owner();

    uint64_t buffId = (uint32_t)param[param.size() - 4];
    uint64_t buffTime = (uint64_t)param[param.size() - 3];
    uint64_t rate = (uint64_t)param[param.size() - 2];

    if (CRandom::RandomBetween(0, 10000) < rate)
    {
        if (!target->IsAgent())
        {
            Cmd::t_Scene_AddBuff_Effect send;
            send.change = 1;
            send.src = parent->Uid();
            send.target = target->Uid();
            send.buffId = buffId;
            send.time = buffTime;
            send.triggerEffectId = (uint32_t)param[param.size() - 1];
            if (param.size() >= 1)
                send.param1 = (int64_t)(param[0] * POS_DENOMINATOR);
            if (param.size() >= 2)
                send.param1 = (int64_t)(param[1] * POS_DENOMINATOR);
            if (param.size() >= 3)
                send.param1 = (int64_t)(param[2] * POS_DENOMINATOR);
            if (param.size() >= 4)
                send.param1 = (int64_t)(param[3] * POS_DENOMINATOR);

            //target->AsyncChangeInfo(&send, sizeof(send));
        }
        else
        {
            Buff *buff = target->GetBuffManager()->AddBuff(buffId, buffTime, parent, target);
            if (buff)
            {

                if (CHARACTER_STATUS_TIMES_DIE != buff->EffectType())
                    BuffMove(target, caster, buff->EffectType(), param);

                //LOGD("AddBuffEffect::DoAction  CasterUid = " << caster->Uid() << " TargetUid = " << target->Uid() << " BuffId = " << buffId << " BuffTime = " << buffTime << "casterrange = " << caster->range << " casterdirx = " << caster->dirx << " casterdiry = " << caster->diry << " targetx = " << target->x << " targety = " << target->y << "   !!!");

                ClientMsg::AddBuffNotify notify;
                notify.buff.buffUid = buff->Uid();
                notify.buff.buffId = buffId;
                notify.buff.caster.fightUid = caster->Uid();
                notify.buff.caster.pos.x = caster->x;
                notify.buff.caster.pos.y = caster->y;
                notify.buff.caster.pos.z = caster->z;
                notify.buff.caster.pos.dirx = caster->dirx;
                notify.buff.caster.pos.diry = caster->diry;
                notify.buff.caster.pos.dirz = caster->dirz;
                notify.buff.layer = buff->OverLay();
                notify.buff.target.fightUid = target->Uid();
                notify.buff.target.pos.x = target->x;
                notify.buff.target.pos.y = target->y;
                notify.buff.target.pos.z = target->z;
                notify.buff.target.pos.dirx = target->dirx;
                notify.buff.target.pos.diry = target->diry;
                notify.buff.target.pos.dirz = target->dirz;
                notify.buff.triggerEffectId = (uint32_t)param[param.size() - 1];
               // target->BroadcastClientMsg(&notify);

            }
        }
    }
    else
    {
        //LOGD("AddBuffEffect::DoAction rate not trigger   CasterUid = " << caster->Uid() << "!!!");
    }


    return true;
}

//CastDynamicEffect
CastDynamicEffect::CastDynamicEffect(Buff *buff, const std::vector<double> &param)
{

}

CastDynamicEffect::~CastDynamicEffect()
{

}

bool CastDynamicEffect::DoAction(Buff *buff, void *ptr)
{

    return true;
}

bool CastDynamicEffect::DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target)
{

    return true;
}

//StrengSkillEffect
StrengSkillEffect::StrengSkillEffect(Buff *buff, const std::vector<double> &param)
{
    if (4 == param.size())
    {
        m_value = param[3] / POS_DENOMINATOR;
        m_strengType = (uint32_t)param[2];
        m_skillId = (uint64_t)param[0];
        m_skillSubId = (uint32_t)param[1];
    }
    else
    {
        m_value = 0;
        m_strengType = 0;
        m_skillId = 0;
        m_skillSubId = 0;
    }
}

StrengSkillEffect::~StrengSkillEffect()
{

}

bool StrengSkillEffect::DoAction(Buff *buff, void *ptr)
{
    if (!m_strengType)
        return true;

    buff->Owner()->GetBuffManager()->AddStrengSkill(m_skillId, m_skillSubId, m_strengType, m_value);

    return true;
}

void StrengSkillEffect::UnDoAction(Buff *buff)
{
    if (!m_strengType)
        return;

    buff->Owner()->GetBuffManager()->SubStrengSkill(m_skillId, m_skillSubId, m_strengType, m_value);

    return;
}

bool StrengSkillEffect::DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target)
{

    return true;
}

//CastSummonEffect
CastSummonEffect::CastSummonEffect(Buff *buff, const std::vector<double> &param)
{

}

CastSummonEffect::~CastSummonEffect()
{

}

bool CastSummonEffect::DoAction(Buff *buff, void *ptr)
{

    return true;
}

bool CastSummonEffect::DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target)
{

    return true;
}

//ChangeSkillEffect
ChangeSkillEffect::ChangeSkillEffect(Buff *buff, const std::vector<double> &param)
    :m_changeSkills(param)
{

}

ChangeSkillEffect::~ChangeSkillEffect()
{

}

bool ChangeSkillEffect::DoAction(Buff *buff, void *ptr)
{
    for (uint32_t i = 0; i < m_changeSkills.size(); ++i)
    {
        //if (!buff->Owner()->GetSkillManager())
        //    return false;

        //if (buff->Owner()->GetSkillManager()->HaveSkill(m_changeSkills[i++]))
        //{
        //    buff->Owner()->GetSkillManager()->AddSkill(m_changeSkills[i], buff->Owner());
        //}
    }

    return true;
}

void ChangeSkillEffect::UnDoAction(Buff *buff)
{
    for (uint32_t i = 0; i < m_changeSkills.size(); ++i)
    {
        //if (!buff->Owner()->GetSkillManager())
        //    buff->Owner()->GetSkillManager()->RemoveSkill(m_changeSkills[++i]);
    }

    return;
}

bool ChangeSkillEffect::DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target)
{

    return true;
}

//BeHurtFix1Effect
BeHurtFix1Effect::BeHurtFix1Effect(Buff *buff, const std::vector<double> &param)
{

}

BeHurtFix1Effect::~BeHurtFix1Effect()
{

}

bool BeHurtFix1Effect::DoAction(Buff *buff, void *ptr)
{

    return true;
}

bool BeHurtFix1Effect::DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target)
{

    return true;
}

//ChangeBeHurtEffect
ChangeBeHurtEffect::ChangeBeHurtEffect(Buff *buff, const std::vector<double> &param)
{

}

ChangeBeHurtEffect::~ChangeBeHurtEffect()
{

}

bool ChangeBeHurtEffect::DoAction(Buff *buff, void *ptr)
{

    return true;
}

bool ChangeBeHurtEffect::DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target)
{

    return true;
}

//SpecialAtkCountEffect
SpecialAtkCountEffect::SpecialAtkCountEffect(Buff *buff, const std::vector<double> &param)
{

}

SpecialAtkCountEffect::~SpecialAtkCountEffect()
{

}

bool SpecialAtkCountEffect::DoAction(Buff *buff, void *ptr)
{

    return true;
}

bool SpecialAtkCountEffect::DoAction(Character *caster, Skill *skill, const std::vector<double> &param, Character *target)
{

    return true;
}
