#include "Item.h"
#include "LogicDataManager.h"
#include "PlayerDataInfo.h"

//ItemBase
ItemBase::ItemBase(uint64_t uid, int64_t count)
    :UnitObject(uid), m_count(count)
{
    m_isLock = false;
    m_data = NULL;
    m_configId = 0;
	m_bagType = OBJECT_BAG;
}

uint32_t ItemBase::Serialize(uint8_t* buffer)
{
	ItemChangeData* data = new(buffer)ItemChangeData();
	data->type = Type();
	data->itemId = Id();
	data->configId = ConfigId();
	data->uid = Uid();
	data->count = Count();
	data->bagType = GetBagType();

	return 0;
}

bool ItemBase::UnSerialize(uint8_t* buffer)
{
	ItemChangeData* info = (ItemChangeData*)buffer;
	m_id = info->itemId;
	m_bagType = info->bagType;


	return true;
}

//coin item
CoinItem::CoinItem(uint64_t uid, uint64_t configId, int64_t count)
    :ItemBase(uid, count)
{
    m_configId = configId;
}

uint32_t CoinItem::Serialize(uint8_t* buffer)
{
	ItemBase::Serialize(buffer);

    ItemChangeData* data = (ItemChangeData *)buffer;

	return data->Size();
}

bool CoinItem::UnSerialize(uint8_t* buffer)
{
	ItemBase::UnSerialize(buffer);

    ItemChangeData* info = (ItemChangeData*)buffer;


    return true;
}

//////NormalItem
NormalItem::NormalItem(uint64_t uid, int64_t count)
    :ItemBase(uid, count)
{
}

NormalItem::~NormalItem()
{
}

bool NormalItem::Init(uint64_t id)
{
    m_configId = id;

    m_data = ItemsConfigDataManager::instance()->get(id);
    if (!m_data)
        return false;

    return true;
}

void NormalItem::Update()
{
    return;
}

uint32_t NormalItem::Serialize(uint8_t* buffer)
{
	ItemBase::Serialize(buffer);

    ItemChangeData *data = (ItemChangeData*)buffer;

    uint8_t *ptr = (uint8_t *)data->data;
    uint32_t *pLen = (uint32_t *)data->data;
    uint32_t& length = data->len;
    BuffWriteMoveLen(ptr, length, UINT32_LEN);

    BuffWriteInt(ptr, length, NORMALITEMVERSION_1_1);

    *pLen = length;

    return data->Size();
}

bool NormalItem::UnSerialize(uint8_t *buffer)
{
	ItemBase::UnSerialize(buffer);

    ItemChangeData *info = (ItemChangeData *)buffer;

    if (!Init(info->configId))
        return false;

    if (!info->len)
        return true;

    uint8_t *ptr = (uint8_t *)info->data;
    uint32_t length = 0;
    BuffLoadInt(ptr, length, length);
    uint32_t ret = length + UINT32_LEN;

    BuffLoadMoveLen(ptr, length, UINT32_LEN);    //version

    return true;
}

bool NormalItem::SerializeClient(protocol::ItemInfo *info)
{
    protocol::ItemBaseInfo *baseInfo = info->mutable_baseinfo();
    baseInfo->set_count(Count());
    baseInfo->set_id(ConfigId());
    baseInfo->set_itemtype(Type());
    baseInfo->set_uid(Uid());

    return true;
}

//equip item ///////////////////////////////////////////////////////////////////////////////
EquipItem::EquipItem(uint64_t uid)
    :EquipBase(uid)
{

}

EquipItem::~EquipItem()
{

}

bool EquipItem::Init(uint64_t id)
{
    m_configId = id;

    m_data = EquipsConfigDataManager::instance()->get(id);
    if (!m_data)
        return false;

    return true;
}

void EquipItem::Update()
{

}

uint32_t EquipItem::Serialize(uint8_t* buffer)
{
	ItemBase::Serialize(buffer);

    ItemChangeData *data = (ItemChangeData*)buffer;

    uint8_t* ptr = (uint8_t *)data->data;
    uint32_t *pLen = (uint32_t *)data->data;
    uint32_t& size = data->len;
    BuffWriteMoveLen(ptr, size, UINT32_LEN);

    BuffWriteInt(ptr, size, EQUIPVERSION_1_1);

    *pLen = size;

	return data->Size();
}

bool EquipItem::UnSerialize(uint8_t* buffer)
{
	ItemBase::UnSerialize(buffer);

    ItemChangeData *info = (ItemChangeData *)buffer;

    if (!Init(info->configId))
        return false;

    if (!info->len)
        return true;

    uint8_t *ptr = (uint8_t *)info->data;
    uint32_t length = 0;
    BuffLoadInt(ptr, length, length);
    uint32_t ret = length + UINT32_LEN;

    BuffLoadMoveLen(ptr, length, UINT32_LEN);    //version

    return true;
}

bool EquipItem::SerializeClient(protocol::EquipInfo *info)
{
    protocol::EquipBaseInfo *baseInfo = info->mutable_baseinfo();
    baseInfo->set_id(ConfigId());
    baseInfo->set_uid(Uid());

    return true;
}

