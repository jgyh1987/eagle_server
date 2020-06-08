#include "WGameRole.h"
#include "WGamePlayer.h"
#include "Defs.h"

//WGameRole
WGameRole::WGameRole(WGamePlayer* player)
	:m_owner(player), m_data(NULL)
{

	m_entity = ECSWorldManager::instance()->CreatePlayerEntity(m_owner);
}

WGameRole::~WGameRole()
{
#define WGAME_ROLE_SYSTEM(system)		\
		system::instance()->Clear(m_entity);	

#include "WGameRoleData.inl"
#undef WGAME_ROLE_SYSTEM

	BagSystem::instance()->Clear(m_entity);

	ECSWorldManager::instance()->DestroyEntity(m_entity);
}

//data
uint32_t WGameRole::SerializeWithDB(Cmd::t_Data_Save_RoleInfo_Req* send)
{
	m_roleInfo.lastOffTime = CImpServerTimeTick::currentTime.sec();
	send->roleInfo = m_roleInfo;

	uint8_t* buffer = send->data + send->playerDataLen;
	uint32_t length = 0;
	uint32_t* pLen = (uint32_t*)buffer;
	BuffWriteMoveLen(buffer, length, UINT32_LEN);

	BuffWriteInt(buffer, length, ROLEVERSION_1_1);

#define WGAME_ROLE_SYSTEM(system)	\
	{						\
		auto size = system::instance()->Serialize(m_entity, buffer);	\
		BuffWriteMoveLen(buffer, length, size);		\
	}

#include "WGameRoleData.inl"
#undef WGAME_ROLE_SYSTEM

	*pLen = send->roleDataLen = length;

	return length;
}

bool WGameRole::UnSerializeWithWorld(Cmd::t_Enter_World_Req* recv)
{
	m_roleInfo = recv->roleInfo;

	if (recv->itemsCount)
		BagSystem::instance()->UnSerialize(m_entity, recv->data + recv->allBinarrayLength, recv->itemsLen, recv->itemsCount);

	uint32_t length = recv->allBinarrayLength - recv->playerDataLen;
	if (length)
	{
		uint8_t* buffer = recv->data + recv->playerDataLen;

		BuffLoadInt(buffer, length, length);
		uint32_t ret = length + UINT32_LEN;

		BuffLoadMoveLen(buffer, length, UINT32_LEN);	//version

		do
		{

#define WGAME_ROLE_SYSTEM(system)		\
    if (!length)								\
		break;								\
	{										\
		auto size = system::instance()->UnSerialize(m_entity, buffer);	\
		BuffLoadMoveLen(buffer, length, size);	\
	}

#include "WGameRoleData.inl"
#undef WGAME_ROLE_SYSTEM

		} while (false);
	}
	else
	{
		if (!FirstEnter())
			return false;
	}

	return true;
}

void WGameRole::SerializeWithWorld(Cmd::t_Enter_World_Req* send)
{
	send->roleInfo = m_roleInfo;

	uint8_t* buffer = send->data + send->playerDataLen;
	uint32_t length = 0;
	uint32_t* pLen = (uint32_t*)buffer;
	BuffWriteMoveLen(buffer, length, UINT32_LEN);

	BuffWriteInt(buffer, length, ROLEVERSION_1_1);

#define WGAME_ROLE_SYSTEM(system)	\
	{						\
		auto size = system::instance()->Serialize(m_entity, buffer);	\
		BuffWriteMoveLen(buffer, length, size);		\
	}

#include "WGameRoleData.inl"
#undef WGAME_ROLE_SYSTEM

	*pLen = length;
	send->allBinarrayLength += length;

	BagSystem::instance()->Serialize(m_entity, send->data + send->allBinarrayLength, send->itemsLen, send->itemsCount);

	return;
}

void WGameRole::SyncEnterWorldMsg()
{
	QuestSystem::instance()->NotifyQuestList(m_entity);

	return;
}

bool WGameRole::OnEnterServer()
{
#define WGAME_ROLE_SYSTEM(system)		\
		system::instance()->OnEnterServer(m_entity);	

#include "WGameRoleData.inl"
#undef WGAME_ROLE_SYSTEM

	return true;
}

void WGameRole::AddExp(uint64_t exp)
{

	return;
}


bool WGameRole::FirstEnter()
{
#define WGAME_ROLE_SYSTEM(system)		\
		system::instance()->InitEntityData(m_entity);	

#include "WGameRoleData.inl"
#undef WGAME_ROLE_SYSTEM



	return true;
}


