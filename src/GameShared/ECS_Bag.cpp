#include "ECS_Bag.h"
#include "ECS_Mail.h"

//BagComponent
std::vector<ItemBase*>* BagComponent::GetBagByItemType(TypeIdCount& item)
{
    static uint32_t bagType[OBJECT_TYPE_ITEM_MAX] = { OBJECT_BAG, OBJECT_NORMAL_BAG, OBJECT_EQUIP_BAG, OBJECT_COIN_BAG };

    if (item.type >= OBJECT_TYPE_ITEM_MAX)
        return NULL;

    if (OBJECT_TYPE_COIN == item.type)
    {
        if (COIN_TYPE_DIAMOND == item.id)
            return &m_bagSlots[OBJECT_ACCOUNT_BAG];
    }

    return &m_bagSlots[bagType[item.type]];
}

BagComponent::~BagComponent()
{
	for (uint32_t i = 0; i < m_bagSlots.size(); ++i)
	{
		for (uint32_t j = 0; j < m_bagSlots[i].size(); ++j)
		{
			SAFE_DELETE(m_bagSlots[i][j]);
		}
	}
}

//BagSystem
void BagSystem::Clear(ECS::ECSEntity* entity)
{
	auto bagCmp = entity->GetComponent<BagComponent>();
	if (!bagCmp)
		return;

	for (uint32_t i = 0; i < OBJECT_BAG_MAX; ++i)
	{
		for (uint32_t j = 0; j < bagCmp->m_bagSlots[i].size(); ++j)
		{
			SAFE_DELETE(bagCmp->m_bagSlots[i][j]);
		}
	}

	bagCmp->m_bagSlots.clear();

	return;
}

bool BagSystem::HaveItems(ECS::ECSEntity *entity, TypeIdCount& item)
{
    auto bagCmp = entity->GetComponent<BagComponent>();
    if (!bagCmp)
        return false;

    switch (item.type)
    {
    case OBJECT_TYPE_COIN:
    {
        return HaveCoins(bagCmp, item);
    }
    break;
    default:
        if (GetItemCountByConfigId(bagCmp, item) >= item.count)
            return true;
    }

    return false;
}

bool BagSystem::HaveItems(ECS::ECSEntity *entity, std::vector<TypeIdCount>& items) 
{
    for (auto& itr : items)
    {
        if (!HaveItems(entity, itr))
            return false;
    }

    return true;
}

bool BagSystem::HaveCoins(BagComponent* bagCmp, TypeIdCount& item)
{
    if (GetItemCountByConfigId(bagCmp, item) >= item.count)
        return true;

    return false;
}

bool BagSystem::HaveCoinId(BagComponent* bagCmp, TypeIdCount& item)
{
	uint64_t count = 0;
	auto* vec = bagCmp->GetBagByItemType(item);
	if (!vec)
		return false;

	for (auto p : *vec)
	{
		if (item.id == p->ConfigId())
			return true;
	}

	return false;
}

bool BagSystem::AddItem(ECS::ECSEntity *entity, TypeIdCount& item, uint8_t*& ptr, uint32_t& dataCount, uint32_t& dataLen)
{
    switch (item.type)
    {
    case OBJECT_TYPE_NORMAL:
        return AddNormal(entity, item, ptr, dataCount, dataLen);
    case OBJECT_TYPE_EQUIP:
        return AddEquip(entity, item, ptr, dataCount, dataLen);
    case OBJECT_TYPE_COIN:
        return AddCoin(entity, item, ptr, dataCount, dataLen);
    default:
        break;
    }

    return false;
}

bool BagSystem::AddItem(ECS::ECSEntity *entity, std::vector<TypeIdCount>& items, uint8_t*& ptr, uint32_t& dataCount, uint32_t& dataLen)
{
    for (auto& v : items)
    {
        AddItem(entity, v, ptr, dataCount, dataLen);
    }

    return false;
}

bool BagSystem::AddCoin(ECS::ECSEntity *entity, TypeIdCount& item, uint8_t*& ptr, uint32_t& dataCount, uint32_t& dataLen)
{
    auto bagCmp = entity->GetComponent<BagComponent>();
    if (!bagCmp)
        return false;

    auto tempItem = item;
    tempItem.count = 0;
    CoinItem* itemPtr = NULL;
    if (HaveCoinId(bagCmp, tempItem))
    {
        itemPtr = (CoinItem*)StoreItemCount(bagCmp, item);
        if (itemPtr)
            SerializeItemDBUpdate(itemPtr, ITEM_CHANGE_STATUS_ADD, ptr, dataCount, dataLen, OBJECT_BAG, item.count);
        else
            MailSystem::instance()->SystemSendMail(entity, item, "system", "system");
    }
    else
    {
        itemPtr = (CoinItem*)MakeItem(bagCmp, item);
        if (!itemPtr)
        {
            return false;
        }

		if (COIN_TYPE_DIAMOND == item.id)
			itemPtr->SetBagType(OBJECT_ACCOUNT_BAG);
		else
			itemPtr->SetBagType(OBJECT_COIN_BAG);
        StoreItem(bagCmp, itemPtr, item);
        SerializeItemDBUpdate(itemPtr, ITEM_CHANGE_STATUS_NEW, ptr, dataCount, dataLen);
    }

    return true;
}

bool BagSystem::AddNormal(ECS::ECSEntity *entity, TypeIdCount& item, uint8_t*& ptr, uint32_t& dataCount, uint32_t& dataLen)
{
    auto bagCmp = entity->GetComponent<BagComponent>();
    if (!bagCmp)
        return false;

    NormalItem* itemPtr = (NormalItem*)StoreItemCount(bagCmp, item);
    if (itemPtr)
    {
        SerializeItemDBUpdate(itemPtr, ITEM_CHANGE_STATUS_ADD, ptr, dataCount, dataLen, OBJECT_BAG, item.count);

        return true;
    }

    if (!CanStoreItem(bagCmp, item))
    {
        //发邮件
        MailSystem::instance()->SystemSendMail(entity, item, "system", "system");

        return true;
    }

    itemPtr = (NormalItem*)MakeItem(bagCmp, item);
    if (!itemPtr)
    {
        return false;
    }

    itemPtr->SetBagType(OBJECT_NORMAL_BAG);
    StoreItem(bagCmp, itemPtr, item);
    SerializeItemDBUpdate(itemPtr, ITEM_CHANGE_STATUS_NEW, ptr, dataCount, dataLen);

    return true;
}

bool BagSystem::AddEquip(ECS::ECSEntity *entity, TypeIdCount& item, uint8_t*& ptr, uint32_t& dataCount, uint32_t& dataLen)
{
    auto bagCmp = entity->GetComponent<BagComponent>();
    if (!bagCmp)
        return false;

    for (uint32_t i = 0; i < item.count; ++i)
    {
        if (!CanStoreItem(bagCmp, item))
        {
            item.count -= i + 1;
            //发邮件
            MailSystem::instance()->SystemSendMail(entity, item, "system", "system");

            return true;
        }

        EquipItem* itemPtr = (EquipItem*)MakeItem(bagCmp, item);
        if (!itemPtr)
        {
            return false;
        }

        itemPtr->SetBagType(OBJECT_EQUIP_BAG);
        StoreItem(bagCmp, itemPtr, item);
        SerializeItemDBUpdate(itemPtr, ITEM_CHANGE_STATUS_NEW, ptr, dataCount, dataLen);
    }

    return true;
}

void BagSystem::RemoveItem(ECS::ECSEntity *entity, TypeIdCount& item, uint8_t*& ptr, uint32_t& dataCount, uint32_t& dataLen)
{

    switch (item.type)
    {
    case OBJECT_TYPE_COIN:

        return SubCoins(entity, item, ptr, dataCount, dataLen);
    default:
        {
            auto bagCmp = entity->GetComponent<BagComponent>();
            if (!bagCmp)
                return;

            RemoveItemByConfigId(bagCmp, item, ptr, dataCount, dataLen);
        }
        break;
    }

    return;
}

void BagSystem::RemoveItem(ECS::ECSEntity *entity, std::vector<TypeIdCount>& items, uint8_t*& ptr, uint32_t& dataCount, uint32_t& dataLen)
{
    for (auto& v : items)
    {
        RemoveItem(entity, v, ptr, dataCount, dataLen);
    }

    return;
}

void BagSystem::SubCoins(ECS::ECSEntity *entity, TypeIdCount& item, uint8_t*& ptr, uint32_t& dataCount, uint32_t& dataLen)
{
    auto bagCmp = entity->GetComponent<BagComponent>();
    if (!bagCmp)
        return;

    auto* vec = bagCmp->GetBagByItemType(item);
    if (!vec)
        return;

    for (uint32_t i = 0; i < vec->size();)
    {
        auto itemPtr = (*vec)[i];
        if (itemPtr->ConfigId() == item.id)
        {
            if (itemPtr->Count() < (int64_t)item.count)
            {
                item.count = itemPtr->Count();
            }

            itemPtr->SubCount(item.count);
            SerializeItemDBUpdate(itemPtr, ITEM_CHANGE_STATUS_SUB, ptr, dataCount, dataLen, OBJECT_BAG, item.count);

            return;
        }
    }

    return;
}

uint64_t BagSystem::GetItemCountByConfigId(ECS::ECSEntity* entity, TypeIdCount& item)
{
    auto bagCmp = entity->GetComponent<BagComponent>();
    if (!bagCmp)
        return 0;

    return GetItemCountByConfigId(bagCmp, item);
}

bool BagSystem::Serialize(ECS::ECSEntity* entity, uint8_t* buffer, uint32_t& length, uint32_t &count)
{
	auto bagCmp = entity->GetComponent<BagComponent>();
	if (!bagCmp)
		return false;

	for (uint32_t i = 0; i < bagCmp->m_bagSlots.size(); ++i)
	{
		for (uint32_t j = 0; j < bagCmp->m_bagSlots[i].size(); ++j)
		{
			if (bagCmp->m_bagSlots[i][j])
			{
				auto size = bagCmp->m_bagSlots[i][j]->Serialize(buffer);
				BuffWriteMoveLen(buffer, length, size);
				++count;
			}
		}
	}

    return true;
}

bool BagSystem::UnSerialize(ECS::ECSEntity* entity, uint8_t* buffer, uint32_t& length, uint32_t count)
{
    auto bagCmp = entity->GetComponent<BagComponent>();
    if (!bagCmp)
        return false;

    uint32_t ret = length;
    uint8_t* ptr = buffer;
    for (uint32_t i = 0; i < count; ++i)
    {
        ItemChangeData* info = (ItemChangeData*)ptr;

        do
        {
            TypeIdCount item = {info->type, info->configId, info->count};
            ItemBase* itemPtr = MakeItemOnUnSerialize(bagCmp, item);
            if (!itemPtr)
                break;

            if (!itemPtr->UnSerialize((uint8_t*)info))
            {
                SAFE_DELETE(itemPtr);
                break;
            }

            StoreItemOnUnSerialize(bagCmp, itemPtr);

        } while (false);

        ptr += info->Size();
    }


    return true;
}

//private
uint64_t BagSystem::GetItemCountByConfigId(BagComponent* bagCmp, TypeIdCount& item)
{
    uint64_t count = 0;
    auto *vec = bagCmp->GetBagByItemType(item);
    if (!vec)
        return count;

    for (auto p : *vec)
    {
        if (item.id == p->ConfigId())
            count += p->Count();
    }

    return count;
}

ItemBase* BagSystem::StoreItemCount(BagComponent* bagCmp, TypeIdCount& item)
{
    auto *vec = bagCmp->GetBagByItemType(item);
    if (!vec)
        return NULL;
    
    for (auto p : *vec)
    {
        if (p->ConfigId() == item.id)
        {
            if (p->Count() + item.count <= p->MaxOverLay())
            {
                p->AddCount(item.count);
                return p;
            }
        }
    }

    return NULL;
}

bool BagSystem::CanStoreItem(BagComponent* bagCmp, TypeIdCount& item)
{
    auto* vec = bagCmp->GetBagByItemType(item);
    if (!vec)
        return false;

    if (vec->size() >= BAGSLOTMAXCOUNT)
        return false;

    return true;
}

void BagSystem::StoreItem(BagComponent* bagCmp, ItemBase* itemPtr, TypeIdCount& item)
{
    auto* vec = bagCmp->GetBagByItemType(item);
    if (!vec)
        return;

    vec->emplace_back(itemPtr);

    return;
}

void BagSystem::StoreItemOnUnSerialize(BagComponent* bagCmp, ItemBase* itemPtr)
{
    if (itemPtr->GetBagType() >= bagCmp->m_bagSlots.size())
        return;

    auto* vec = &bagCmp->m_bagSlots[itemPtr->GetBagType()];
    if (!vec)
        return;

    vec->emplace_back(itemPtr);

    return;
}

void BagSystem::RemoveItemByConfigId(BagComponent* bagCmp, TypeIdCount& item, uint8_t*& ptr, uint32_t& dataCount, uint32_t& dataLen)
{
    auto* vec = bagCmp->GetBagByItemType(item);
    if (!vec)
        return;

    for (uint32_t i = 0; i < vec->size();)
    {
        auto itemPtr = (*vec)[i];
        if (itemPtr->ConfigId() == item.id)
        {
            if (itemPtr->Count() > (int64_t)item.count)
            {
                itemPtr->SubCount(item.count);
                SerializeItemDBUpdate(itemPtr, ITEM_CHANGE_STATUS_SUB, ptr, dataCount, dataLen, OBJECT_BAG, item.count);

                return;
            }
            else
            {
                item.count -= itemPtr->Count();
                SerializeItemDBUpdate(itemPtr, ITEM_CHANGE_STATUS_DEL, ptr, dataCount, dataLen);

                VECTOR_REMOVE_INDEX((*vec), i);
                SAFE_DELETE(itemPtr);

                if (!item.count)
                    return;
       
                continue;
            }
        }

        ++i;
    }

    return;
}

ItemBase* BagSystem::MakeItemOnUnSerialize(BagComponent* bagCmp, TypeIdCount& item)
{
    switch (item.type)
    {
    case OBJECT_TYPE_NORMAL:
        return new NormalItem(GetObjectUid(), item.count);
    case OBJECT_TYPE_EQUIP:
        return new EquipItem(GetObjectUid());
    case OBJECT_TYPE_COIN:
        return new CoinItem(GetObjectUid(), item.id, item.count);
    default:
        return NULL;
    }

    return NULL;
}

ItemBase* BagSystem::MakeItem(BagComponent* bagCmp, TypeIdCount& item)
{
    ItemBase* itemPtr = NULL;
    switch (item.type)
    {
    case OBJECT_TYPE_NORMAL:
        itemPtr = new NormalItem(GetObjectUid(), item.count);
        break;
    case OBJECT_TYPE_EQUIP:
        itemPtr = new EquipItem(GetObjectUid());
        break;
    case OBJECT_TYPE_COIN:
        itemPtr = new CoinItem(GetObjectUid(), item.id, item.count);
        break;
    default:
        return NULL;
    }

    if (itemPtr && itemPtr->Init(item.id))
        return itemPtr;

    LOGE("MakeItem Config No Item Type = " << item.type << " id = " << item.id << " !!!");
    SAFE_DELETE(itemPtr);

    return itemPtr;
}

void BagSystem::SerializeItemDBUpdate(ItemBase*item, uint32_t changeType, uint8_t*& ptr, uint32_t& dataCount, uint32_t& dataLen, uint32_t bagType, uint64_t count)
{
    item->Serialize(ptr);
    ItemChangeData* data = (ItemChangeData*)ptr;
    if (OBJECT_BAG != bagType)
        data->bagType = bagType;
    data->change = changeType;
    if (count)
        data->count = count;
    ++dataCount;
    dataLen += data->Size();
    ptr = ptr + data->Size();

    return;
}

