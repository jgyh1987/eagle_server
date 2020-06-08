#ifndef _BUFF_H_ 
#define    _BUFF_H_

#include "Singleton.h"
#include "WorldObject.h"
#include "LogicDataManager.h"
#include "Noncopyable.h"
#include "SharedEvent.h"
#include "Effect.h"

class Skill;
class Character;
class BuffManager;

//
enum BUFF_TYPE
{
    BUFF_TYPE_FIGHT = 0,
    BUFF_TYPE_OUT_FIGHT = 1,
};

//buff
class Buff : public UnitObject
{
public:
    Buff(const BuffConfigData *data, uint64_t time, Character *caster, Character *owner);
    ~Buff();

    uint32_t Type(){return OBJECT_BUFF;}
    bool IsType(uint32_t type){return type == OBJECT_BUFF;}

    bool Init(uint64_t id);
    bool InitUnSerialize();
    void Update();


public:
    bool Register();
    void UnRegister();

    void EndUpdate();

//inline
public:
    inline Character *Caster()
    {
    
        return m_caster;
    }

    inline Character *Owner()
    {
    
        return m_owner;
    }

    inline uint32_t &OverLay()
    {
        return m_overLay;
    }

    inline bool IsDeBuff()
    {
        return m_data->isDebuff > 0;
    }

    inline void ClearCaster()
    {
        m_caster = NULL;
        return;
    }

    inline bool IsEnd()
    {
        return m_isEnd;
    }

    //Special realization
    inline uint32_t EffectType()
    {
        return m_effectType;
    }

    inline uint64_t EndTime()
    {
        return m_endTime;
    }

private:
    const BuffConfigData *m_data;
    Character *m_caster;        
    Character *m_owner;
    uint32_t m_overLay;
    uint64_t m_endTime;
    std::vector<EagleAction *> m_actions;
    std::vector<Effect *> m_fixEffects;
    bool m_isRegister;
    bool m_isEnd;
    //Special realization
    uint32_t m_effectType;
};

class BuffManager
{
public:
    BuffManager();
    ~BuffManager();

    void Clear();
    void UpdateBuff();
    Buff *AddBuff(uint64_t buffId, uint64_t time, Character *caster, Character *owner, bool needUpdate = true);
    Buff * AddBuff(BuffConfigData *data, uint64_t time, Character *caster, Character *owner, bool needUpdate = true);
    void RemoveBuff(Buff *);
    void RemoveBuff(uint64_t);
    void AddCastBuff(Buff *);
    void RemoveCastBuff(uint64_t uid);
    void AddToFixBuffs(Buff *);
    void RemoveToFixBuffs(Buff *);
    void Die();

    uint32_t Serialize(uint8_t *buffer);
    uint32_t UnSerialize(uint8_t *buffer, Character *owner);

public:
    //
    inline void AddFightAttr(uint32_t type, double value){m_baseFightAttr[type] += value;}
    inline void AddFightAttrPrecent(uint32_t type, double value){m_baseFightAttrPercent[type] += value;}
    inline void AddFightResistant(uint32_t type, double value){m_baseFightResistant[type] += value;}
    inline void AddFightResistantPrecent(uint32_t type, double value){m_baseFightResistantPercent[type] += value;}
    inline void SubFightAttr(uint32_t type, double value){m_baseFightAttr[type] -= value;}
    inline void SubFightAttrPrecent(uint32_t type, double value){m_baseFightAttrPercent[type] -= value;}
    inline void SubFightResistant(uint32_t type, double value){m_baseFightResistant[type] -= value;}
    inline void SubFightResistantPrecent(uint32_t type, double value){m_baseFightResistantPercent[type] -= value;}
    inline double GetFightAttr(uint32_t type){return m_baseFightAttr[type];}
    inline double GetFightAttrPrecent(uint32_t type){return m_baseFightAttrPercent[type];}
    inline double GetFightResistant(uint32_t type){return m_baseFightResistant[type];}
    inline double GetFightResistantPrecent(uint32_t type){return m_baseFightResistantPercent[type];}

    //
    inline void AddStrengSkill(uint64_t skillId, uint32_t skillSubId, uint32_t strengType, double value)
    {
        if (skillId)
        {
            m_strengSkillIds[strengType][skillId] += value;
        }
        else if (skillSubId)
        {
            m_strengSkillSubIds[strengType][skillSubId] += value;
        }

        return;
    }
    inline void SubStrengSkill(uint64_t skillId, uint32_t skillSubId, uint32_t strengType, double value)
    {
        if (skillId)
        {
            m_strengSkillIds[strengType][skillId] -= value;
        }
        else if (skillSubId)
        {
            m_strengSkillSubIds[strengType][skillSubId] -= value;
        }

        return;
    }
    inline double StrengSkill(uint64_t skillId, uint32_t skillSubId, uint32_t strengType)
    {
        double value = 0;
        if (skillId)
        {
            value = m_strengSkillIds[strengType][skillId];
        }

        if (skillSubId)
        {
            value += m_strengSkillSubIds[strengType][skillSubId];
        }

        return value;
    }

private:

    //
    std::map<uint64_t, Buff *> m_listMyCastBuffs;
    //
    std::map<uint64_t, Buff*> m_buffList;
    //
    std::map<uint64_t, Buff*> m_fixEffectBuffs;

    //
    double m_baseFightAttr[EAT_MAX];
    double m_baseFightAttrPercent[EAT_MAX];
    double m_baseFightResistant[CHARACTER_STATUS_TIMES_MAX];
    double m_baseFightResistantPercent[CHARACTER_STATUS_TIMES_MAX];
    //
    std::vector< std::map< uint64_t, double > > m_strengSkillIds;
    std::vector< std::map< uint64_t, double > > m_strengSkillSubIds;
};


Buff *AllocBuff(uint64_t id, uint64_t time, Character *caster, Character *hoster);
Buff *AllocBuff(const BuffConfigData *buffData, uint64_t time, Character *caster, Character *hoster);
bool FreeBuff(Buff*&);


#endif    


