#include "LogicRole.h"
#include "Defs.h"
#include "LogicPlayer.h"
#include "LogicService.h"
#include "ECS_Bag.h"

//SimpleRole
SimpleRole::SimpleRole()
{

}

SimpleRole::~SimpleRole()
{

}

uint32_t SimpleRole::UnSerializeWithDB(uint8_t* buffer)
{
    memcpy(&m_baseInfo, buffer, sizeof(RoleInfoBase));

    return sizeof(RoleInfoBase);
}

///////////////////////
LogicRole::LogicRole(LogicPlayer *player)
    :m_owner(player)
{
	m_entity = ECSWorldManager::instance()->CreatePlayerEntity(m_owner, this);
}
LogicRole::~LogicRole()
{
	ECSWorldManager::instance()->DestroyPlayerEntrty(m_entity);
}

void LogicRole::Clear()
{

}

bool LogicRole::Init(Cmd::t_Data_GetRoleInfo_Res *recv)
{
	UnSerializeWithDB(recv);

    if (!recv->allBinarrayLength)
    {
		if (FirstEnter())
		{
			m_owner->SetNeedSave(true);

			return true;
		}
		else
			return false;
    }

    if (recv->funType == 0)
    {
	
    }

	m_owner->SetNeedSave(true);

    return true;
}

void LogicRole::UnSerializeWithDB(Cmd::t_Data_GetRoleInfo_Res* recv)
{
	m_roleInfo = recv->roleInfo;

	SAFE_DELETE(m_dbdata);
	m_dbdataLen = recv->allBinarrayLength;
	m_dbdata = new uint8_t[m_dbdataLen];
	memcpy(m_dbdata, recv->data, m_dbdataLen);

	if (recv->itemsCount)
		BagSystem::instance()->UnSerialize(m_entity, recv->data + recv->allBinarrayLength, recv->itemsLen, recv->itemsCount);

	return;
}

void LogicRole::SerializeWithEnter(Cmd::t_Enter_World_Req* send)
{
	send->roleInfo = m_roleInfo;

	if (m_dbdata && m_dbdataLen)
	{
		memcpy(send->data + send->playerDataLen, m_dbdata, m_dbdataLen);
		send->allBinarrayLength += m_dbdataLen;
	}

	BagSystem::instance()->Serialize(m_entity, send->data + send->allBinarrayLength, send->itemsLen, send->itemsCount);

	return;
}

bool LogicRole::FirstEnter()
{
    RoleConfigData *initData = RoleConfigDataManager::instance()->get(m_roleInfo.jobId);
    if (!initData)
    {
        return false;
    }

    m_roleInfo.mapId = initData->initMapId;
	initData->initMapPos.EagleToCmdPos(m_roleInfo.pos);

    Cmd::t_Data_Update_Item_Req *send = m_owner->BeginUpdateItem();
    uint8_t *ptr = send->data;

    ItemChangeData *data = new(ptr)ItemChangeData();
    data->type = OBJECT_TYPE_NORMAL;
    data->itemId = 0;
    data->configId = 0;
    data->count = 0;
    data->change = ITEM_CHANGE_STATUS_NEW;
    data->bagType = OBJECT_NORMAL_BAG;
    ++send->itemsCount;
    send->itemsDataLen += data->Size();
    ptr += data->Size();

    BagSystem::instance()->AddItem(m_entity, initData->items, ptr, send->itemsCount, send->itemsDataLen);
    m_owner->EndUpdateItem(send);

    return true;
}




