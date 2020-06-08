#include "Skill.h"
#include "Character.h"
#include "Buff.h"
#include "Random.h"

//skill manager
bool AllocSkill(uint64_t skillId, Character *owner, std::vector<Skill *> &)
{
    //SkillData * skillData = SkillConfigDataManager::instance()->get(id);
    //if (!skillData)
    //    return ptr;

    //ptr = new Skill(skillData, owner);
    //if (ptr && !ptr->Init(skillData->id))
    //{
    //    FreeSkill(ptr);
    //    ptr = NULL;
    //}

    return true;
}

bool FreeSkill(Skill* ptr)
{
    delete ptr;

    return true;
}

//skill
Skill::Skill(SkillData * skillData, Character *owner)
    :UnitObject(GetObjectUid()), m_data(skillData), m_owner(owner), m_startTime(0), m_needDel(false), m_status(SKILL_CAST_STATUS_NONE)
{
    m_index = 0;
    m_lastEndTime = 0;
}

Skill::~Skill()
{

}

bool Skill::Init(uint64_t id)
{
    m_id = id;

    return true;
}

void Skill::Update()
{
    if (SKILL_CAST_STATUS_CASTING == m_status && CImpServerTimeTick::currentTime.msec() > m_startTime + LiftTime())
    {
        EndCast();

        return;
    }

    return;
}

void Skill::ReSet()
{
    m_startTime = 0;
    m_index = 0;
    m_status = SKILL_CAST_STATUS_NONE;
    m_targetPos.Clear();

    m_lastEndTime = CImpServerTimeTick::currentTime.msec();
}

bool Skill::StratCast(TargetPos *pos)
{
    m_startTime = CImpServerTimeTick::currentTime.msec();
    m_targetPos = *pos;
    m_status = SKILL_CAST_STATUS_CASTING;

    return true;
}

void Skill::EndCast()
{
    m_status = SKILL_CAST_STATUS_END;

    //m_owner->GetSkillManager()->SetSubSkillProtectedTime(this);



    //LOGD("CastSkill End CasterUid = " << m_owner->Uid() << " SkillId = " << Id() << " ActionId = " << m_data->id << "   !!!");

    return;
}

void Skill::Attack()
{


    return;
}

void Skill::Attack(uint32_t index, std::vector<uint64_t> &targetUid)
{
    //if (index >= GetConfigData()->effect.size())
    //    return;

    //for (uint32_t i = 0; i < targetUid.size(); ++i)
    //{
    //    EffectTarget target;
    //    if (m_owner->GetMap())
    //        target.m_targeter = (Character *)m_owner->GetMap()->FindObjectByUid(targetUid[i]);
    //    if (target.m_targeter)
    //    {}
    //}

    return;
}

//SkillManager

SkillManager::SkillManager(Character *owner, CREATESKILL CreateSkill)
    :_CreateSkill(CreateSkill), m_owner(owner)
{
    m_casting = NULL;
}

SkillManager::~SkillManager()
{
    for (std::map< uint64_t, std::vector<Skill *> >::iterator itr = m_skills.begin(); itr != m_skills.end(); ++itr)
        for (uint32_t i = 0; i < itr->second.size(); ++i)
            FreeSkill(itr->second[i]);

    m_skills.clear();
}

void SkillManager::AddSkill(uint64_t id, Character *owner)
{
    std::vector<Skill *> *skill = HaveSkill(id);
    if (skill)
        return;

    std::vector<Skill *> skillVec;
    if (_CreateSkill(id, owner, skillVec))
        m_skills[id] = skillVec;

    return;
}

void SkillManager::RemoveSkill(uint64_t id)
{
    if (m_casting && id == m_casting->Id())
        m_casting->SetDel();
    else
    {
        std::map< uint64_t, std::vector<Skill *> >::iterator itr = m_skills.find(id);
        if (itr != m_skills.end())
        {
            for (uint32_t i = 0; i < itr->second.size(); ++i)
            {
                FreeSkill(itr->second[i]);
            }

            m_skills.erase(itr);
        }
    }

    return;
}

std::vector<Skill *> *SkillManager::HaveSkill(uint64_t id)
{
    std::map< uint64_t, std::vector<Skill *> >::iterator itr = m_skills.find(id);
    if (itr != m_skills.end())
    {
        return &itr->second;
    }

    return NULL;
}

bool SkillManager::CastSkill(uint64_t id, uint32_t subId, TargetPos *pos, bool trigger)
{
    //LOGD("CastSkill Begin CasterUid = " << m_owner->Uid() << " SkillId = " << id << " ActionId = " << subId << "   !!!");

    //if (!m_owner->CanSkill())
    //    return false;

    std::vector<Skill *> *skillvec = HaveSkill(id);
    if (!skillvec || !skillvec->size())
        return false;

    Skill *skill = NULL;
    uint32_t index = 0;
    for (; index < skillvec->size(); ++index)
    {
        if (subId == (*skillvec)[index]->SubId())
        {
            skill = (*skillvec)[index];
            break;
        }
    }

    if (!skill)
        return false;

    if (!CanSkill(skill, index, trigger))
        return false;

    LOGD("CastSkill SUCCESS CasterUid = " << m_owner->Uid() << " SkillId = " << id << " ActionId = " << subId << "   !!!");
    m_owner->RefRange();
    m_casting = skill;
    m_casting->StratCast(pos);

    return true;
}

void SkillManager::EndSkill()
{
    if (m_casting)
        EndSkill(m_casting);

    return;
}

void SkillManager::UpdateSkill()
{
    if (m_casting)
    {
        m_casting->Update();

        if (m_casting->IsEnd())
        {
            EndSkill(m_casting);
        }
    }

    for (std::map<uint64_t, SubSkillProtect>::iterator itr = m_subSkillProtectTime.begin(); itr != m_subSkillProtectTime.end();)
    {
        if (CImpServerTimeTick::currentTime.msec() > itr->second.ProtectTime)
        {
            m_subSkillProtectTime.erase(itr++);
        }
        else
            ++itr;
    }

    return;
}

void SkillManager::SetSubSkillProtectedTime(Skill *)
{

    return;
}

bool SkillManager::IsCastSkill()
{
    return m_casting != NULL;
}

void SkillManager::EndSkill(Skill *skill)
{
    skill->ReSet();

    if (skill == m_casting)
        m_casting = NULL;

    if (skill->NeedDel())
        RemoveSkill(skill->Id());

    return;
}

bool SkillManager::CanSkill(Skill *skill, uint32_t index, bool trigger)
{
    if (!trigger && m_casting)
        return false;

    if (skill->IsCD())
        return false;

    if (0 != index)
    {
        std::map<uint64_t, SubSkillProtect>::iterator itr = m_subSkillProtectTime.find(skill->Id());
        if (itr == m_subSkillProtectTime.end())
            return false;

        if (itr->second.subId != skill->SubId())
            return false;

        //
        m_subSkillProtectTime.erase(itr);

        return true;
    }

    return true;
}

