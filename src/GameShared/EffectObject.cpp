#include "EffectObject.h"
#include "Effect.h"
#include "MMOSkill.h"
#include "ClientMsg.h"
#include "Effect.h"
#include "GameBaseTask.h"

void DoSkillEffect(Character *caster, Skill *skill, EffectInfo *info, std::vector<Character *> &fighter)
{
    if (info->effectAction.type < g_skillEffectFuns.size() && g_skillEffectFuns[info->effectAction.type])
    {
        for (uint32_t i = 0; i < fighter.size(); ++i)
        {
            g_skillEffectFuns[info->effectAction.type](caster, skill, info->effectAction.values, (Character *)fighter[i]);
        }
    }
}

void BuffMove(Character *target, Character *caster, uint32_t type, const std::vector<double> &param)
{
    bool move = false;
    switch (type)
    {
    case CHARACTER_STATUS_TIMES_CLICKFLY:
    {
        double dis = 100;
        if (param.size() >= 3)
        {
            dis = param[2] * 100;

            double x = cos(caster->range) * dis;
            double y = sin(caster->range) * dis;
            target->x += x;
            target->y += y;

            move = true;
        }
    }
    break;
    case CHARACTER_STATUS_TIMES_HITBACK:
    {
        double dis = 60;
        double x = cos(caster->range) * dis;
        double y = sin(caster->range) * dis;
        target->x += x;
        target->y += y;

        move = true;
    }
    break;
    case CHARACTER_STATUS_TIMES_GRAVITATION:
    {
        double dis = 100;
        if (param.size() >= 2)
        {
            dis = param[1] * 100;
            double x1 = caster->x - target->x;
            double y1 = caster->y - target->y;
            if (x1 * x1 + y1 * y1 < dis * dis)
                break;
            double range = atan2(y1, x1);
            double x = cos(range) * dis;
            double y = sin(range) * dis;
            target->x += x;
            target->y += y;

            move = true;
        }
    }
    break;
    }

    if (move)
    {
       // target->SetStatus(CHARACTER_STATUS_TIMES_NOMOVE);

        target->UpdateGird(); 
    }
    
    return;
}

//EffectObject
EffectObject::EffectObject(MMOSkill *skill, EffectActionInfo *data, EaglePos &pos)
    :Character(GetServerObjectUid()), m_owner(skill)
{
    m_data = &data->objectInfo;
    m_end = false;
    m_startTime = CImpServerTimeTick::currentTime.msec();
    m_lifeTime = CImpServerTimeTick::currentTime.msec() + m_data->actorLifeTime;
    m_lastEffectTime = 0;

    x = pos.x;
    y = pos.y;
    z = pos.z;
    dirx = pos.dirx;
    diry = pos.diry;
    dirz = pos.dirz;
    RefRange();

    m_lastMoveTime = CImpServerTimeTick::currentTime.msec();

}

EffectObject::~EffectObject()
{
    ClientMsg::RemoveEffectObjectNotify notify;
    notify.effectObject.fightUid = Uid();
    //m_owner->Owner()->BroadcastClientMsg(&notify);
}

void EffectObject::Clear()
{

    return;
}

void EffectObject::Update()
{
    uint64_t curTime = CImpServerTimeTick::currentTime.msec();
    //move
    if (1 == m_data->actorSpeedType)
    {
        uint64_t difTime = curTime - m_lastMoveTime;
        m_lastMoveTime = curTime;
        double speed = (double)difTime / (double)MSEC_TO_SEC * m_data->actorSpeed;
        x += cos(range) * speed;
        y += sin(range) * speed;

        //LOGD("EffectObject move difTime = " << difTime << " speed = " << speed << " x = " << cos(range) * speed  << " y = " << sin(range) * speed << "  !!!");
    }

    if (1 == m_data->actorLifeType)
    {
        if (1 == m_data->triggerType)
        {
            if (!m_lastEffectTime)
                m_lastEffectTime = curTime;

            if (curTime > m_lastEffectTime + m_data->effectTime)
            {
                CollisionCheck();

                m_lastEffectTime = curTime;
            }
        }    
    }
    else if (2 == m_data->actorLifeType)
    {
        if (1 == m_data->triggerType)
        {
            if (!m_lastEffectTime)
                m_lastEffectTime = curTime;

            if (curTime > m_lastEffectTime + m_data->effectTime)
            {
                CollisionPenetrateCheck();

                m_lastEffectTime = curTime;
            }
        }
        else
        {
            if (!m_lastEffectTime || curTime >= m_lastEffectTime + m_data->effectTime)
            {
                if (2 == m_data->triggerType)
                    ContinuedEffectTrigger2();
                else if (0 == m_data->triggerType)
                    ContinuedEffectTrigger0();
                m_lastEffectTime = curTime;
            }
        }
    }

    if (curTime > m_startTime + m_data->actorLifeTime)
    {
        m_end = true;    
    }

    if (m_end)
        End();

    return;
}

void EffectObject::SerializeEnterMapInfo(void *ptr)
{
    EffectActionInfo *data = (EffectActionInfo *)ptr;

    ClientMsg::CreateEffectObjectNotify notify;
    notify.caster.fightUid = m_owner->Owner()->Uid();
    notify.effectObject.fightUid = Uid();
    notify.effectObject.pos.x = x;
    notify.effectObject.pos.y = y;
    notify.effectObject.pos.z = z;
    notify.effectObject.pos.dirx = dirx;
    notify.effectObject.pos.diry = diry;
    notify.effectObject.pos.dirz = dirz;
    notify.skillId = (uint32_t)m_owner->Id();
    notify.actionId = m_owner->SubId();
    notify.longDisId = data->id;
    //m_owner->Owner()->BroadcastClientMsg(&notify);
}

void EffectObject::End()
{
    std::vector<Character *> fighter;
    for (uint32_t i = 0; i < m_data->endEffectData.effectRangeData.size() && i < m_data->endEffectData.effectData.size(); ++i)
    {
        fighter.clear();
        //m_owner->Owner()->GetTargetVec(this, &m_data->endEffectData.effectRangeData[i], &fighter);

        if (fighter.size())
        {
            DoSkillEffect(this, m_owner, &m_data->endEffectData.effectData[i], fighter);

            //LOGD("EffectObject::End param Begin  !!!");
            //for (uint32_t z = 0; z < m_data->endEffectData.effectData[i].effectAction.values.size(); ++z)
            //    LOGD("EffectObject::End param " << m_data->endEffectData.effectData[i].effectAction.values[z] << "  !!!");
        }
    }


    return;
}

void EffectObject::ContinuedEffectTrigger0()
{
    //LOGD("EffectObject::ContinuedEffectTrigger0 CasterUid = " << m_owner->m_owner->Uid() << "   !!!");

    std::vector<Character *> fighter;
    //m_owner->Owner()->GetTargetVec(this, &m_data->collisionRangeData, &fighter);

    if (fighter.size())
    {
        for (uint32_t i = 0; i < m_data->triggerInfos.effectData.size(); ++i)
        {
            DoSkillEffect(this, m_owner, &m_data->triggerInfos.effectData[i], fighter);
        }
                
    }

    return;
}

void EffectObject::ContinuedEffectTrigger2()
{
    //LOGD("EffectObject::ContinuedEffectTrigger2 CasterUid = " << m_owner->m_owner->Uid() << "   !!!");

    std::vector<Character *> fighter;
    for (uint32_t i = 0; i < m_data->triggerInfos.effectRangeData.size() && i < m_data->triggerInfos.effectData.size(); ++i)
    {
        fighter.clear();
        //m_owner->Owner()->GetTargetVec(this, &m_data->triggerInfos.effectRangeData[i], &fighter);

        if (fighter.size())
        {
            DoSkillEffect(this, m_owner, &m_data->triggerInfos.effectData[i], fighter);
        }
    }

    return;
}

void EffectObject::CollisionCheck()
{
    //LOGD("EffectObject::CollisionCheck CasterUid = " << m_owner->m_owner->Uid() << " x = " << x << " y = " << y << "   !!!");

    std::vector<Character *> fighter;
    //m_owner->Owner()->GetTargetVec(this, &m_data->collisionRangeData, &fighter);
    if (fighter.size())
    {

        //LOGD("EffectObject::CollisionCheck Collision Fighter  !!!");

        for (uint32_t i = 0; i < m_data->triggerInfos.effectRangeData.size() && i < m_data->triggerInfos.effectData.size(); ++i)
        {
            fighter.clear();
            //m_owner->Owner()->GetTargetVec(this, &m_data->triggerInfos.effectRangeData[i], &fighter);

            if (fighter.size())
            {
                DoSkillEffect(this, m_owner, &m_data->triggerInfos.effectData[i], fighter);
            }
        }
        
        m_end = true;
    }

    return;
}

void EffectObject::CollisionPenetrateCheck()
{
    //LOGD("EffectObject::CollisionPenetrateCheck CasterUid = " << m_owner->m_owner->Uid() << "   !!!");

    std::vector<Character *> fighter;
    //m_owner->Owner()->GetTargetVec(this, &m_data->collisionRangeData, &fighter);
    if (fighter.size())
    {
        std::vector<Character *> fighter1;
        for (uint32_t i = 0; i < fighter.size(); ++i)
        {
            std::map<uint64_t, uint32_t>::iterator itr = m_collsion.find(fighter[i]->Uid());
            if (itr == m_collsion.end())
            {
                fighter1.push_back(fighter[i]);
                m_collsion[fighter[i]->Uid()] = 1;
            }
        }

        if (fighter1.size())
        {
            for (uint32_t i = 0; i < m_data->triggerInfos.effectData.size(); ++i)
            {
                DoSkillEffect(this, m_owner, &m_data->triggerInfos.effectData[i], fighter1);
            }
                    
        }
    }

    return;
}

//EffectAction
EffectAction::EffectAction(Character *owner, MMOSkill *skill, EffectActionInfo *data, uint32_t index)
    :m_owner(owner), m_skill(skill), m_data(data), m_index(index)
{
    m_end = false;
    m_overplusCount = 0;
    m_radiateInterval = 0;
    m_lastRadiateTime = 0;
    m_first = false;
}

EffectAction::~EffectAction()
{
}

void EffectAction::Update()
{
    std::vector<Character *> fighter;
    if (!m_first)
    {
        m_first = true;
        if (SKILL_CAST_TYPE_NORMAL == m_data->type)
        {
            //LOGD("CastSkill DoAction JinZhan Begin CasterUid = " << m_owner->Uid() << " ActionId = " << m_data->id << "   !!!");
            for (uint32_t i = 0; i < m_data->objectInfo.triggerInfos.effectRangeData.size() && i < m_data->objectInfo.triggerInfos.effectData.size(); ++i)
            {
                fighter.clear();

                //m_owner->GetTargetVec(m_owner, &m_data->objectInfo.triggerInfos.effectRangeData[i], &fighter);

                if (fighter.size())
                {
                    DoSkillEffect(m_owner, m_skill, &m_data->objectInfo.triggerInfos.effectData[i], fighter);
                }

            //LOGD("CastSkill DoAction JinZhan End CasterUid = " << m_owner->Uid() << " ActionId = " << m_data->id << "   !!!");
            }
        }
        else if (SKILL_CAST_TYPE_LOG == m_data->type)
        {
            if (3 == m_data->objectInfo.triggerType)
            {
            }
            else
            {
                EaglePos pos;
                TargetPos &targetPos = m_skill->GetTargetPos();
                if (1 == m_data->actionJudgeType)
                {
                    for (uint32_t i = 0; i < m_data->actorNum; ++i)
                    {
                        if (1 == m_data->actorNum)
                        {
                            pos.PosClear();
                            pos.x = targetPos.x / POS_DENOMINATOR;
                            pos.y = targetPos.y / POS_DENOMINATOR;
                            pos.z = targetPos.z / POS_DENOMINATOR;
                            pos.dirx = targetPos.dirx / POS_DENOMINATOR;
                            pos.diry = targetPos.diry / POS_DENOMINATOR;
                            pos.dirz = targetPos.dirz / POS_DENOMINATOR;
                        }
                        EffectObject *object = new EffectObject(m_skill, m_data, pos);
                        if (object)
                        {
                            object->SerializeEnterMapInfo(m_data);
                            m_skill->AddEffectObject(object);

                            //LOGD("CastSkill LongDis CreateEffectObject skiilid =" << m_skill->Id() << " longdisId = " << m_data->id << " x = " << object->x << " y = " << object->y << "   !!!");
                        }
                    }
                }
                else if (2 == m_data->actionJudgeType)
                {
                    m_overplusCount = m_data->actorNum;
                    if (m_overplusCount)
                        m_radiateInterval = m_data->continueTime / m_overplusCount;
                    else
                        m_radiateInterval = m_data->continueTime;
                }
            }
        }
    }

    if (SKILL_CAST_TYPE_LOG == m_data->type && 2 == m_data->actionJudgeType && 3 != m_data->objectInfo.triggerType)
    {
        if (m_overplusCount && CImpServerTimeTick::currentTime.msec() > m_lastRadiateTime + m_radiateInterval)
        {
            EaglePos pos;
            TargetPos &targetPos = m_skill->GetTargetPos();
            if (1 == m_data->actorLocType)
            {
                double rand = m_data->actorLocOff.maxy - m_data->actorLocOff.miny;
                rand = CRandom::RandomBetween(0, (uint32_t)rand);
                rand += m_data->actorLocOff.miny;

                double range = -atan2(m_owner->diry, m_owner->dirx);
                pos.x = m_data->actorLocOff.minx;
                pos.y = rand;

                double x4 = cos(range) * pos.x - sin(range) * pos.y;
                double y4 = sin(range) * pos.x + cos(range) * pos.y;

                pos.x = x4 + m_owner->x;
                pos.y = y4 + m_owner->y;
                pos.z = m_owner->z;
                pos.dirx = m_owner->dirx;
                pos.diry = m_owner->diry;
                pos.dirz = m_owner->dirz;
            }
            else
            {
                pos.x = targetPos.x / POS_DENOMINATOR;
                pos.y = targetPos.y / POS_DENOMINATOR;
                pos.z = targetPos.z / POS_DENOMINATOR;
                pos.dirx = targetPos.dirx / POS_DENOMINATOR;
                pos.diry = targetPos.diry / POS_DENOMINATOR;
                pos.dirz = targetPos.dirz / POS_DENOMINATOR;
            }

            EffectObject *object = new EffectObject(m_skill, m_data, pos);
            if (object)
            {
                object->SerializeEnterMapInfo(m_data);
                m_skill->AddEffectObject(object);

                //LOGD("CastSkill LongDis CreateEffectObject skiilid =" << m_skill->Id() << " longdisId = " << m_data->id << " x = " << object->x << " y = " << object->y << "   !!!");
            }

            --m_overplusCount;
            m_lastRadiateTime = CImpServerTimeTick::currentTime.msec();
        }
    }

    if (!m_overplusCount)
        m_end = true;

    return;
}



