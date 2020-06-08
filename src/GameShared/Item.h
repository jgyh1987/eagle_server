#ifndef _ITEM_H_ 
#define _ITEM_H_

#include "Unit.h"
#include "LogicDataManager.h"
#include "./proto/msg_net.pb.h"
#include "./proto/package_net.pb.h"

#define NORMALITEMVERSION_1_1            1
#define EQUIPVERSION_1_1            1

class ItemBase : public UnitObject
{
public:
    ItemBase(uint64_t uid, int64_t count);
    ~ItemBase() = default;

    uint32_t Type() { return OBJECT_ITEM; }
    bool IsType(uint32_t type) { return OBJECT_ITEM == type; }

	virtual bool Init(uint64_t id) { m_id = id; return true; }
    virtual uint32_t Serialize(uint8_t* buffer) = 0;
    virtual bool UnSerialize(uint8_t* buffer) = 0;
    virtual uint32_t SubType() { return 0; }
    virtual uint32_t SubId() { return 0; }
    virtual uint32_t MaxOverLay() { return 0xFFFFFFFF; }
    virtual bool CanToAccount() { return false; }


    inline uint64_t ConfigId() { return m_configId; }
    inline void AddCount(uint64_t count) { m_count += count; }
    inline void SubCount(uint64_t count) { m_count -= count; if (m_count < 0)m_count = 0; }
    inline int64_t Count() { return m_count; }
    inline void Lock() { m_isLock = true; }
    inline void UnLock() { m_isLock = false; }
    inline bool IsLock() { return m_isLock; }
    inline const void* Data() { return m_data; }
    inline void SetBagType(uint32_t v) { m_bagType = v; }
    inline uint32_t GetBagType() { return m_bagType; }

protected:
    int64_t m_count;
    bool m_isLock;
    const void* m_data;
    uint64_t m_configId;
    uint32_t m_bagType;
};

class CoinItem : public ItemBase
{
public:
    CoinItem(uint64_t uid, uint64_t configId, int64_t count);
    ~CoinItem() = default;

    uint32_t Type() { return OBJECT_TYPE_COIN; }
    bool IsType(uint32_t type) { return type == OBJECT_TYPE_COIN; }

public:
	uint32_t Serialize(uint8_t* buffer) override;
    bool UnSerialize(uint8_t* buffer) override;

};

class NormalItem : public ItemBase
{
public:
    NormalItem(uint64_t uid, int64_t count);
    ~NormalItem();

    uint32_t Type(){return OBJECT_TYPE_NORMAL;}
    bool IsType(uint32_t type){return type == OBJECT_TYPE_NORMAL;}

    bool Init(uint64_t id);
    void Update();

public:
	uint32_t Serialize(uint8_t* buffer) override;
    bool UnSerialize(uint8_t* buffer) override;
    bool SerializeClient(protocol::ItemInfo *info);

    uint32_t SubType(){return ConfigData()->subtype;}
    uint32_t SubId(){return 0;}
    uint32_t MaxOverLay() { if (ConfigData())ConfigData()->maxStack; return ItemBase::MaxOverLay(); }

public:
    inline const ItemsConfigData *ConfigData(){return (ItemsConfigData *)Data();}

private:
};

class EquipBase : public ItemBase
{
public:
    EquipBase(uint64_t uid)
        :ItemBase(uid, 1)
    {
    }

    virtual uint32_t GetPos() = 0;

protected:
    
};

class EquipItem : public EquipBase
{
public:
    EquipItem(uint64_t uid);
    ~EquipItem();

    uint32_t Type() { return OBJECT_TYPE_EQUIP; }
    bool IsType(uint32_t type) { return type == OBJECT_TYPE_EQUIP; }

    bool Init(uint64_t id);
    void Update();

public:
	uint32_t Serialize(uint8_t* buffer) override;
    bool UnSerialize(uint8_t* buffer) override;
    bool SerializeClient(protocol::EquipInfo *info);

    uint32_t SubType() { return ConfigData()->subtype; }
    uint32_t SubId() { return 0; }
    uint32_t MaxOverLay() { return 1; }

    uint32_t GetPos() { return  0; }
public:
    inline const EquipsConfigData *ConfigData() { return (EquipsConfigData *)Data(); }

private:
};

#endif    


