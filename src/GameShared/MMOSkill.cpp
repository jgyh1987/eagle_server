#include "MMOSkill.h"
#include "ClientMsg.h"

bool AllocMMOSkill(uint64_t skillId, Character *owner, std::vector<Skill *> &vec)
{
    MMOSkill *ptr = NULL;
    SkillConfigData * skillData = SkillConfigDataManager::instance()->get(skillId);
    if (!skillData)
        return false;

    for (uint32_t i = 0; i < skillData->skillsData.size(); ++i)
    {
        ptr = new MMOSkill(skillData, &skillData->skillsData[i], owner);
        if (ptr && !ptr->Init(skillId))
        {
            FreeSkill(ptr);
            ptr = NULL;
        }
        else
            vec.push_back(ptr);
    }

    return true;
}

//MMOSkill
MMOSkill::MMOSkill(SkillConfigData * skillInfoData, SkillData * skillData, Character *owner)
    :Skill(skillData, owner), m_skillInfoData(skillInfoData)
{

}

MMOSkill::~MMOSkill()
{
    for (std::list<EffectObject *>::iterator itr = m_effectObjects.begin(); itr != m_effectObjects.end(); ++itr)
    {
        SAFE_DELETE(*itr);
    }
    m_effectObjects.clear();
}

bool MMOSkill::Init(uint64_t id)
{
    Skill::Init(id);

    return true;
}

void MMOSkill::Update()
{
    for (std::list<EffectObject *>::iterator itr = m_effectObjects.begin(); itr != m_effectObjects.end();)
    {
        (*itr)->Update();

        if ((*itr)->IsEnd())
        {
            SAFE_DELETE(*itr);
            m_effectObjects.erase(itr++);
        }
        else
            ++itr;
    }

    if (SKILL_CAST_STATUS_CASTING != m_status)
        return;

    if (m_index < m_data->effectTimes.size() && m_index < m_data->effectActions.size())
    {
        if (CImpServerTimeTick::currentTime.msec() >= m_startTime + m_data->effectTimes[m_index])
        {
            EffectAction *action = new EffectAction(m_owner, this, &m_data->effectActions[m_index], m_index);
            if (SKILL_CAST_TYPE_NORMAL == action->GetConfigData()->type)
            {
                action->Update();
                SAFE_DELETE(action);
            }
            else if (SKILL_CAST_TYPE_LOG == action->GetConfigData()->type)
            {
                m_actionObjects.push_back(action);
            }

            ++m_index;
        }    
    }

    for (std::list<EffectAction *>::iterator itr = m_actionObjects.begin(); itr != m_actionObjects.end();)
    {
        (*itr)->Update();
    
        if ((*itr)->IsEnd())
        {
            SAFE_DELETE(*itr);
            m_actionObjects.erase(itr++);
        }
        else
            ++itr;
    }

    //Skill::Update();
    if (SKILL_CAST_STATUS_CASTING == m_status && CImpServerTimeTick::currentTime.msec() > m_startTime + LiftTime() && !m_actionObjects.size())
    {
        EndCast();

        return;
    }

    return;
}

void MMOSkill::Clear()
{

}

void MMOSkill::ReSet()
{
    Skill::ReSet();

    for (std::list<EffectAction *>::iterator itr = m_actionObjects.begin(); itr != m_actionObjects.end(); ++itr)
        SAFE_DELETE(*itr);

    m_actionObjects.clear();

    //if (m_effectObjects.size() && m_owner->GetSkillManager())
    //    ((MMOSkillManager *)m_owner->GetSkillManager())->AddEffectSkills(this);

    return;
}

bool MMOSkill::StratCast(TargetPos *pos)
{
    ClientMsg::CastSkilNotify notify;
    notify.skillId = (uint32_t)Id();
    notify.actionId = m_data->id;
    notify.caster.fightUid = m_owner->Uid();
    notify.caster.pos.x = m_owner->x;
    notify.caster.pos.y = m_owner->y;
    notify.caster.pos.z = m_owner->z;
    notify.caster.pos.dirx = m_owner->dirx;
    notify.caster.pos.diry = m_owner->diry;
    notify.caster.pos.dirz = m_owner->dirz;
    notify.targetPos.pos.x = m_targetPos.x / POS_DENOMINATOR;
    notify.targetPos.pos.y = m_targetPos.y / POS_DENOMINATOR;
    notify.targetPos.pos.z = m_targetPos.z / POS_DENOMINATOR;
    notify.targetPos.pos.dirx = m_targetPos.dirx / POS_DENOMINATOR;
    notify.targetPos.pos.diry = m_targetPos.diry / POS_DENOMINATOR;
    notify.targetPos.pos.dirz = m_targetPos.dirz / POS_DENOMINATOR;
    notify.targetPos.fightUid = m_targetPos.uid;
    //m_owner->BroadcastClientMsg(&notify);

    Skill::StratCast(pos);

    return true;
}

void MMOSkill::EndCast()
{
    Skill::EndCast();

    LOGD("CastSkill END CasterUid = " << m_owner->Uid() << " SkillId = " << Id() << " ActionId = " << SubId() << "   !!!");

    return;
}

void MMOSkill::AddEffectObject(EffectObject *object)
{
    m_effectObjects.push_back(object);
}

//MMOSkillManager
MMOSkillManager::MMOSkillManager(Character *owner)
    :SkillManager(owner, AllocMMOSkill)
{

}

MMOSkillManager::~MMOSkillManager()
{

}

bool MMOSkillManager::CastSkill(uint32_t skillId, uint32_t subId, TargetPos *pos, bool trigger)
{
    if (SkillManager::CastSkill(skillId, subId, pos, trigger))
    {
        RemoveEffectSkill((MMOSkill *)m_casting);

        return true;
    }
        

    return false;
}

void MMOSkillManager::UpdateSkill()
{
    for (std::list<MMOSkill *>::iterator itr = m_effectSkills.begin(); itr != m_effectSkills.end();)
    {
        (*itr)->Update();

        if (!(*itr)->EffectObjectsSize())
        {
            m_effectSkills.erase(itr++);
        }
        else
            ++itr;
    }

    SkillManager::UpdateSkill();

    return;
}

void MMOSkillManager::SetSubSkillProtectedTime(Skill *skill)
{
    MMOSkill *mmoskill = ((MMOSkill *)skill);
    SkillConfigData *data = mmoskill->GetSkillInfoData();
    for (uint32_t i = 0; i < data->skillsData.size(); ++i)
    {
        if (skill->SubId() == data->skillsData[i].id)
        {
            if (i + 1 < data->skillsData.size())
            {
                SubSkillProtect info;
                info.subId = data->skillsData[i + 1].id;
                info.ProtectTime = CImpServerTimeTick::currentTime.msec() + mmoskill->GetConfigData()->actionProtectTime;
                m_subSkillProtectTime[skill->Id()] = info;
            }
        
            break;
        }
    }

    return;
}

void MMOSkillManager::AddEffectSkills(MMOSkill *skill)
{
    bool have = false;
    for (std::list<MMOSkill *>::iterator itr = m_effectSkills.begin(); itr != m_effectSkills.end(); ++itr)
    {
        if (skill == *itr)
        {
            have = true;
            break;
        }
    }

    if (!have)
        m_effectSkills.push_back(skill);

    return;
}

void MMOSkillManager::RemoveEffectSkill(MMOSkill *skill)
{
    for (std::list<MMOSkill *>::iterator itr = m_effectSkills.begin(); itr != m_effectSkills.end(); ++itr)
    {
        if (skill == *itr)
        {
            m_effectSkills.erase(itr);
            return;
        }
    }

    return;
}

#define SCENE_SYNC_SKILL_VERSION_1_1     1

uint32_t MMOSkillManager::Serialize(uint8_t *buffer)
{
    uint32_t size = 0;
    uint32_t *pLen = (uint32_t *)buffer;
    BuffWriteMoveLen(buffer, size, UINT32_LEN);

    BuffWriteInt(buffer, size, SCENE_SYNC_SKILL_VERSION_1_1);

    BuffWriteInt(buffer, size, (uint32_t)m_subSkillProtectTime.size());
    for (std::map<uint64_t, SubSkillProtect>::iterator itr = m_subSkillProtectTime.begin(); itr != m_subSkillProtectTime.end(); ++itr)
    {
        BuffWriteInt64(buffer, size, itr->first);
        BuffWriteInt(buffer, size, itr->second.subId);
        BuffWriteInt64(buffer, size, itr->second.ProtectTime);
    }

    if (m_casting)
    {
        MMOSkill *skill = (MMOSkill *)m_casting;
        BuffWriteInt(buffer, size, 1);
        BuffWriteInt64(buffer, size, skill->Id());
        BuffWriteInt(buffer, size, skill->SubId());
        BuffWriteInt64(buffer, size, skill->GetStartTime());
        BuffWriteInt64(buffer, size, skill->GetLastEndTime());
        BuffWriteInt(buffer, size, skill->GetIndex());
        BuffWriteInt64(buffer, size, skill->GetTargetPos().x);
        BuffWriteInt64(buffer, size, skill->GetTargetPos().y);
        BuffWriteInt64(buffer, size, skill->GetTargetPos().z);
        BuffWriteInt64(buffer, size, skill->GetTargetPos().dirx);
        BuffWriteInt64(buffer, size, skill->GetTargetPos().diry);
        BuffWriteInt64(buffer, size, skill->GetTargetPos().dirz);
        BuffWriteInt64(buffer, size, skill->GetTargetPos().uid);

        std::list<EffectAction *> &actionObjects = skill->GetActionObjects();
        BuffWriteInt(buffer, size, (uint32_t)actionObjects.size());
        for (std::list<EffectAction *>::iterator itr = actionObjects.begin(); itr != actionObjects.end(); ++itr)
        {
            BuffWriteInt(buffer, size, (*itr)->m_index);
            BuffWriteInt(buffer, size, (*itr)->m_overplusCount);
            BuffWriteInt64(buffer, size, (*itr)->m_radiateInterval);
            BuffWriteInt64(buffer, size, (*itr)->m_lastRadiateTime);
        }
    }
    else
    {
        BuffWriteInt(buffer, size, 0);
    }



    *pLen = size;

    return size;
}

uint32_t MMOSkillManager::UnSerialize(uint8_t *buffer)
{
    uint32_t length = 0;

    BuffLoadInt(buffer, length, length);
    uint32_t ret = length + UINT32_LEN;

    BuffLoadMoveLen(buffer, length, UINT32_LEN);    //version

    uint32_t count = 0;
    BuffLoadInt(buffer, length, count);
    for (uint32_t i = 0; i < count; ++i)
    {
        uint64_t skillId = 0;
        SubSkillProtect info;
        BuffLoadInt64(buffer, length, skillId);
        BuffLoadInt(buffer, length, info.subId);
        BuffLoadInt64(buffer, length, info.ProtectTime);

        m_subSkillProtectTime[skillId] = info;
    }
    
    do
    {
        BuffLoadInt(buffer, length, count);
        if (!count)
            break;
        
        uint64_t skillId = 0;
        uint32_t subId = 0;
        BuffLoadInt64(buffer, length, skillId);
        BuffLoadInt(buffer, length, subId);

        std::vector<Skill *> *skillvec = HaveSkill(skillId);
        if (!skillvec || !skillvec->size())
            return false;

        MMOSkill *skill = NULL;
        uint32_t index = 0;
        for (; index < skillvec->size(); ++index)
        {
            if (subId == (*skillvec)[index]->SubId())
            {
                skill = (MMOSkill *)(*skillvec)[index];
                break;
            }
        }

        if (!skill)
            break;

        m_casting = skill;

        uint64_t startTime = 0;
        uint64_t endTime = 0;
        BuffLoadInt64(buffer, length, startTime);
        BuffLoadInt64(buffer, length, endTime);
        BuffLoadInt(buffer, length, index);
        BuffLoadInt64(buffer, length, skill->GetTargetPos().x);
        BuffLoadInt64(buffer, length, skill->GetTargetPos().y);
        BuffLoadInt64(buffer, length, skill->GetTargetPos().z);
        BuffLoadInt64(buffer, length, skill->GetTargetPos().dirx);
        BuffLoadInt64(buffer, length, skill->GetTargetPos().diry);
        BuffLoadInt64(buffer, length, skill->GetTargetPos().dirz);
        BuffLoadInt64(buffer, length, skill->GetTargetPos().uid);
        skill->SetStartTime(startTime);
        skill->SetIndex(index);
        skill->SetLastEndTime(endTime);

        BuffLoadInt(buffer, length, count);
        for (uint32_t i = 0; i < count; ++i)
        {
            BuffLoadInt(buffer, length, index);
            uint32_t overplusCount;
            BuffLoadInt(buffer, length, overplusCount);
            uint64_t radiateInterval;
            BuffLoadInt64(buffer, length, radiateInterval);
            uint64_t lastRadiateTime;
            BuffLoadInt64(buffer, length, lastRadiateTime);

            if (index >= m_casting->GetConfigData()->effectActions.size())
                continue;

            EffectAction *action = new EffectAction(m_owner, skill, &m_casting->GetConfigData()->effectActions[index], index);
            skill->GetActionObjects().push_back(action);
            action->m_first = true;
            action->m_overplusCount = overplusCount;
            action->m_radiateInterval = radiateInterval;
            action->m_lastRadiateTime = lastRadiateTime;
        }

        skill->Status() = SKILL_CAST_STATUS_CASTING;
        
    } while (false);

    return ret;
}




