#ifndef _ECS_BAG_H_
#define _ECS_BAG_H_

#include "Sys.h"
#include "Singleton.h"
#include "CObject.h"
#include "ECS_Component.h"
#include "ECS_Entity.h"

#include "PlayerDataInfo.h"
#include "Item.h"
#include "ECS_System.h"

#define BAGSLOTMAXCOUNT            1000

class BagComponent : public ECS::ECSComponent
{
public:
    enum
    {
        Type = ECS_PLAYER_COMPONENT_TYPE_BAG
    };

    BagComponent(ECS::ECSEntity* owner)
        :ECSComponent(owner)
    {
        m_bagSlots.resize(OBJECT_BAG_MAX);
        for (auto& itr : m_bagSlots)
            itr.reserve(BAGSLOTMAXCOUNT);
    }
	~BagComponent();

    uint32_t GetType() override { return BagComponent::Type; }

    std::vector<ItemBase*>* GetBagByItemType(TypeIdCount& item);

private:
	friend class BagSystem;
    std::vector< std::vector<ItemBase*> > m_bagSlots;

};

//
class BagSystem : public ECS::ECSSystem, public CSingleton<BagSystem>
{
public:
	void Clear(ECS::ECSEntity* entity) override;

    bool HaveItems(ECS::ECSEntity*, TypeIdCount &item);
    bool HaveItems(ECS::ECSEntity*, std::vector<TypeIdCount>& items);
 
    bool AddItem(ECS::ECSEntity *, TypeIdCount& item, uint8_t*& ptr, uint32_t& dataCount, uint32_t& dataLen);
    bool AddItem(ECS::ECSEntity *, std::vector<TypeIdCount>& items, uint8_t*& ptr, uint32_t& dataCount, uint32_t& dataLen);

    void RemoveItem(ECS::ECSEntity *, TypeIdCount& item, uint8_t*& ptr, uint32_t& dataCount, uint32_t& dataLen);
    void RemoveItem(ECS::ECSEntity *, std::vector<TypeIdCount>& items, uint8_t*& ptr, uint32_t& dataCount, uint32_t& dataLen);

    uint64_t GetItemCountByConfigId(ECS::ECSEntity *entity, TypeIdCount& item);

    //
    bool Serialize(ECS::ECSEntity*, uint8_t* buffer, uint32_t& length, uint32_t &count);
    bool UnSerialize(ECS::ECSEntity*, uint8_t* buffer, uint32_t& length, uint32_t count);

private:
    bool HaveCoins(BagComponent*, TypeIdCount& item);
	bool HaveCoinId(BagComponent*, TypeIdCount& item);

    bool AddCoin(ECS::ECSEntity*, TypeIdCount& item, uint8_t*& ptr, uint32_t& dataCount, uint32_t& dataLen);
    bool AddNormal(ECS::ECSEntity*, TypeIdCount& item, uint8_t*& ptr, uint32_t& dataCount, uint32_t& dataLen);
    bool AddEquip(ECS::ECSEntity*, TypeIdCount& item, uint8_t*& ptr, uint32_t& dataCount, uint32_t& dataLen);

    void SubCoins(ECS::ECSEntity*, TypeIdCount& item, uint8_t*& ptr, uint32_t& dataCount, uint32_t& dataLen);

    uint64_t GetItemCountByConfigId(BagComponent *bagCmp, TypeIdCount& item);

    //
    ItemBase* StoreItemCount(BagComponent* bagCmp, TypeIdCount& item);
    bool CanStoreItem(BagComponent* bagCmp, TypeIdCount& item);
    void StoreItem(BagComponent* bagCmp, ItemBase *itemPtr, TypeIdCount& item);
    void StoreItemOnUnSerialize(BagComponent* bagCmp, ItemBase* itemPtr);
    void RemoveItemByConfigId(BagComponent* bagCmp, TypeIdCount& item, uint8_t*& ptr, uint32_t& dataCount, uint32_t& dataLen);

    //创建道具
    ItemBase* MakeItemOnUnSerialize(BagComponent* bagCmp, TypeIdCount& item);
    ItemBase* MakeItem(BagComponent* bagCmp, TypeIdCount& item);

    //封装发送DBSERVER
    void SerializeItemDBUpdate(ItemBase*, uint32_t changeType, uint8_t*& ptr, uint32_t& dataCount, uint32_t& dataLen, uint32_t bagType = OBJECT_BAG, uint64_t count = 0);

};

#endif

