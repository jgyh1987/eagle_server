#include "Buff.h"
#include "TimeTick.h"
#include "Random.h"
#include "Character.h"
#include "Eagle_Time.h"

//AllocBuff manager
Buff *AllocBuff(uint64_t id, uint64_t time, Character *caster, Character *targer)
{
    BuffConfigData *buffData = BuffConfigDataManager::instance()->get(id);
    if (!buffData)
        return NULL;

    Buff *ptr = new Buff(buffData, time, caster, targer);
    if (ptr && !ptr->Init(buffData->id))
    {
        FreeBuff(ptr);
    }

    return ptr;
}

Buff *AllocBuff(const BuffConfigData *buffData, uint64_t time, Character *caster, Character *targer)
{
    Buff *ptr = new Buff(buffData, time, caster, targer);
    if (ptr && !ptr->Init(buffData->id))
    {
        FreeBuff(ptr);
    }

    return ptr;
}

bool FreeBuff(Buff* &ptr)
{
    SAFE_DELETE(ptr);

    return true;
}

//buff
Buff::Buff(const BuffConfigData *data, uint64_t time, Character *caster, Character *owner)
    :UnitObject(GetObjectUid()), m_data(data), m_caster(caster), m_owner(owner), m_isRegister(false)
{
    m_id = data->id;
    m_overLay = 1;
    m_endTime = CImpServerTimeTick::currentTime.msec() + time;
    m_isEnd = false;

    m_effectType = CHARACTER_STATUS_TIMES_DIE;

    if (m_caster)
        m_caster->GetBuffManager()->AddCastBuff(this);
}

Buff::~Buff()
{
    for (uint32_t i = 0; i < m_actions.size(); ++i)
        SAFE_DELETE(m_actions[i]);
    m_actions.clear();

    for (uint32_t i = 0; i < m_fixEffects.size(); ++i)
    {
        FreeEffect(m_fixEffects[i]);
    }
    m_fixEffects.clear();

    if (Caster())
        Caster()->GetBuffManager()->RemoveCastBuff(Uid());
}

bool Buff::Init(uint64_t id)
{
    //bool haveFixEffect = false;
    //uint32_t count = (uint32_t)(m_data->triggers.size() > m_data->effects.size() ? m_data->effects.size() : m_data->triggers.size());
    //m_fixEffects.reserve(count);
    //m_actions.reserve(count);
    //for (uint32_t i = 0; i < count; ++i)
    //{
    //    Effect *effect = CreateEffect(this, m_data->effects[i].type, m_data->effects[i].values);
    //    if (!effect)
    //        continue;

    //    if (!m_data->triggers[i].type)
    //    {
    //        m_fixEffects.push_back(effect);
    //        haveFixEffect = true;
    //    }
    //    else
    //    {
    //        EagleAction *action = CreateAction(ACTION_TRIGGER_BUFF, this, effect);
    //        if (!action)
    //        {
    //            FreeEffect(effect);
    //            continue;
    //        }

    //        CreateBuffCondition(action, m_data->triggers[i].type, m_data->triggers[i].values);

    //        m_actions.push_back(action);
    //    }
    //}

    uint32_t count = (uint32_t)(m_data->triggers.size() > m_data->effects.size() ? m_data->effects.size() : m_data->triggers.size());
    m_fixEffects.reserve(count);
    m_actions.reserve(count);
    for (uint32_t i = 0; i < count; ++i)
    {
        Effect *effect = CreateEffect(this, m_data->effects[i].type, m_data->effects[i].values);
        if (!effect)
            continue;

        if (m_data->effects[i].type >= BUFF_EFFECT_TYPE_ATTR_CHANGE_MIN && m_data->effects[i].type <= BUFF_EFFECT_TYPE_ATTR_CHANGE_MAX)
        {
            m_fixEffects.push_back(effect);
        }
        
        //Special realization
        if (CHARACTER_STATUS_TIMES_DIE == m_effectType && m_data->effects[i].type == BUFF_EFFECT_TYPE_ADD_STATUS && m_data->effects[i].values.size())
            m_effectType = (uint32_t)m_data->effects[i].values[0];
    }

    return Register();
}

bool Buff::InitUnSerialize()
{
    uint32_t count = (uint32_t)(m_data->triggers.size() > m_data->effects.size() ? m_data->effects.size() : m_data->triggers.size());
    m_fixEffects.reserve(count);
    m_actions.reserve(count);
    for (uint32_t i = 0; i < count; ++i)
    {
        Effect *effect = CreateEffect(this, m_data->effects[i].type, m_data->effects[i].values);
        if (!effect)
            continue;

        if (m_data->effects[i].type >= BUFF_EFFECT_TYPE_ATTR_CHANGE_MIN && m_data->effects[i].type <= BUFF_EFFECT_TYPE_ATTR_CHANGE_MAX)
        {
            m_fixEffects.push_back(effect);
        }

        //Special realization
        if (CHARACTER_STATUS_TIMES_DIE == m_effectType && m_data->effects[i].type == BUFF_EFFECT_TYPE_ADD_STATUS && m_data->effects[i].values.size())
            m_effectType = (uint32_t)m_data->effects[i].values[0];
    }

    for (uint32_t i = 0; i < m_actions.size(); ++i)
    {
        m_owner->RegisterEventAction(m_actions[i]);
    }

    if (m_fixEffects.size())
    {
        m_owner->GetBuffManager()->AddToFixBuffs(this);
    }

    m_isRegister = true;


    return true;
}

void Buff::Update()
{
    if (!m_isEnd && CImpServerTimeTick::currentTime.msec() > m_endTime)
    {
        EndUpdate();
    }

    return;
}

bool Buff::Register()
{
    if (m_isRegister)
        return false;

    for (uint32_t i = 0; i < m_actions.size(); ++i)
    {
        m_owner->RegisterEventAction(m_actions[i]);
    }

    if (m_fixEffects.size())
    {
        m_owner->GetBuffManager()->AddToFixBuffs(this);
        for (uint32_t i = 0; i < m_fixEffects.size(); ++i)
        {
            if (!m_fixEffects[i]->DoAction(this, NULL))
            {
                EndUpdate();
                return false;
            }
        }
    }

    m_isRegister = true;

    return true;
}

void Buff::UnRegister()
{
    if (!m_isRegister)
        return;

    m_owner->UnRegisterEventAction(m_actions);

    if (m_fixEffects.size())
    {
        m_owner->GetBuffManager()->RemoveToFixBuffs(this);
        for (uint32_t i = 0; i < m_fixEffects.size(); ++i)
        {
            m_fixEffects[i]->UnDoAction(this);
        }
    }

    return;
}

void Buff::EndUpdate()
{
    m_isEnd = true;

    UnRegister();

    return;
}

//BuffManager
BuffManager::BuffManager()
{
    memset(m_baseFightAttr, 0, sizeof(m_baseFightAttr));
    memset(m_baseFightAttrPercent, 0, sizeof(m_baseFightAttrPercent));
    memset(m_baseFightResistant, 0, sizeof(m_baseFightResistant));
    memset(m_baseFightResistantPercent, 0, sizeof(m_baseFightResistantPercent));
}

BuffManager::~BuffManager()
{
    m_fixEffectBuffs.clear();

    for (std::map<uint64_t, Buff *>::iterator itr = m_listMyCastBuffs.begin(); itr != m_listMyCastBuffs.end(); ++itr)
    {
        itr->second->ClearCaster();
    }
    m_listMyCastBuffs.clear();

    for (std::map<uint64_t, Buff *>::iterator itr = m_buffList.begin(); itr != m_buffList.end(); ++itr)
    {
        FreeBuff(itr->second);
    }
    m_buffList.clear();
}

void BuffManager::Clear()
{
    m_fixEffectBuffs.clear();

    for (std::map<uint64_t, Buff *>::iterator itr = m_buffList.begin(); itr != m_buffList.end(); ++itr)
    {
        FreeBuff(itr->second);
    }
    m_buffList.clear();

    return;
}

void BuffManager::UpdateBuff()
{
    for (std::map<uint64_t, Buff *>::iterator itr = m_buffList.begin(); itr != m_buffList.end();)
    {
        itr->second->Update();

        if (itr->second->IsEnd())
        {

            //LOGD("BuffManager::EndBuff casterUId = " << itr->second->Caster()->Uid() << " ownerUid = " << itr->second->Owner()->Uid() << " buffId = " << itr->second->Id() << "  !!!");

            Buff *buff = itr->second;
            m_buffList.erase(itr++);
            FreeBuff(buff);
        }
        else
            ++itr;
    }

    return;
}

Buff *BuffManager::AddBuff(uint64_t buffId, uint64_t time, Character *caster, Character *owner, bool needUpdate)
{
    Buff *buff = AllocBuff(buffId, time, caster, owner);
    if (buff)
    {
        //LOGD("BuffManager::AddBuff casterUId = " << caster->Uid() << " ownerUid = " << owner->Uid() << " buffId = " << buffId << "  !!!");
        m_buffList[buff->Uid()] = buff;

        return buff;
    }

    return NULL;
}

Buff *BuffManager::AddBuff(BuffConfigData *data, uint64_t time, Character *caster, Character *owner, bool needUpdate)
{

    return NULL;
}

void BuffManager::RemoveBuff(Buff *buff)
{
    return RemoveBuff(buff->Uid());
}

void BuffManager::RemoveBuff(uint64_t uid)
{
    std::map<uint64_t, Buff*>::iterator itr = m_buffList.find(uid);
    if (itr != m_buffList.end())
    {
        FreeBuff(itr->second);
        m_buffList.erase(itr);
    }

    return;
}

void BuffManager::AddCastBuff(Buff *buff)
{
    m_listMyCastBuffs[buff->Uid()] = buff;

    return;
}

void BuffManager::RemoveCastBuff(uint64_t uid)
{
    std::map<uint64_t, Buff *>::iterator itr = m_listMyCastBuffs.find(uid);
    if (itr != m_listMyCastBuffs.end())
        m_listMyCastBuffs.erase(itr);

    return;
}

void BuffManager::AddToFixBuffs(Buff *buff)
{
    m_fixEffectBuffs[buff->Uid()] = buff;

    return;
}

void BuffManager::RemoveToFixBuffs(Buff *buff)
{
    std::map<uint64_t, Buff*>::iterator itr = m_fixEffectBuffs.find(buff->Uid());
    if (itr != m_fixEffectBuffs.end())
        m_fixEffectBuffs.erase(itr);

    return;
}

void BuffManager::Die()
{
    Clear();

    return;
}

#define SCENE_SYNC_BUFF_VERSION_1_1     1

uint32_t BuffManager::Serialize(uint8_t *buffer)
{
    uint32_t size = 0;
    uint32_t *pLen = (uint32_t *)buffer;
    BuffWriteMoveLen(buffer, size, UINT32_LEN);

    BuffWriteInt(buffer, size, SCENE_SYNC_BUFF_VERSION_1_1);

    BuffWriteInt(buffer, size, (uint32_t)m_buffList.size());
    for (std::map<uint64_t, Buff*>::iterator itr = m_buffList.begin(); itr != m_buffList.end(); ++itr)
    {
        Buff *buff = itr->second;
        BuffWriteInt64(buffer, size, buff->Id());
        if (buff->EndTime() > CImpServerTimeTick::currentTime.msec())
        {
            BuffWriteInt64(buffer, size, buff->EndTime() - CImpServerTimeTick::currentTime.msec());
        }    
        else
        {
            BuffWriteInt64(buffer, size, 0);
        }
        BuffWriteInt(buffer, size, buff->OverLay());
        BuffWriteInt64(buffer, size, buff->Caster()->Uid());
    }

    *pLen = size;

    return size;
}

uint32_t BuffManager::UnSerialize(uint8_t *buffer, Character *owner)
{
    uint32_t length = 0;

    BuffLoadInt(buffer, length, length);
    uint32_t ret = length + UINT32_LEN;

    BuffLoadMoveLen(buffer, length, UINT32_LEN);    //version

    uint32_t count = 0;
    BuffLoadInt(buffer, length, count);
    for (uint32_t i = 0; i < count; ++i)
    {
        uint64_t buffId = 0;
        BuffLoadInt64(buffer, length, buffId);
        uint64_t time = 0;
        BuffLoadInt64(buffer, length, time);
        uint32_t overlay = 1;
        BuffLoadInt(buffer, length, overlay);
        uint64_t castUid = 0;
        BuffLoadInt64(buffer, length, castUid);
		Character* caster = NULL;

        BuffConfigData *buffData = BuffConfigDataManager::instance()->get(buffId);
        if (!buffData)
            continue;

        Buff *ptr = new Buff(buffData, time, caster, owner);
        if (!ptr || !ptr->InitUnSerialize())
        {
            FreeBuff(ptr);
            continue;
        }

        ptr->OverLay() = overlay;
        m_buffList[ptr->Uid()] = ptr;
    }

    return ret;
}

