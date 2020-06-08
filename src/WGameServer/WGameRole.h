#ifndef _WGAME_ROLE_H_
#define _WGAME_ROLE_H_

#include "Sys.h"
#include "Singleton.h"
#include "CObject.h"
#include "ECS_Component.h"
#include "ECS_Entity.h"
#include "CommonType.h"
#include "WorldCommand.h"
#include "Counter.h"
#include "LogicDataManager.h"
#include "LogicDataCommand.h"

class WGamePlayer;

//此为玩家在游戏中角色 游戏中真正的PLAYER
class WGameRole
{
	friend class WGamePlayer;
public:
	WGameRole(WGamePlayer*);
	~WGameRole();

	inline RoleInfoBase* GetRoleInfo()
	{
		return &m_roleInfo;
	}

	//manager
	inline ECS::ECSEntity* GetEntity() { return m_entity; }

	//data
	uint32_t SerializeWithDB(Cmd::t_Data_Save_RoleInfo_Req* send);
	bool UnSerializeWithWorld(Cmd::t_Enter_World_Req* recv);
	void SerializeWithWorld(Cmd::t_Enter_World_Req* send);
	void SyncEnterWorldMsg();
	bool OnEnterServer();

	void AddExp(uint64_t exp);

	//
	inline uint64_t RoleId() { return m_roleInfo.roleId; }

private:
	bool FirstEnter();//

protected:
	WGamePlayer* m_owner;
	RoleConfigData* m_data;
	RoleInfoBase m_roleInfo;        //

	//ex data

	//ecs 
	ECS::ECSEntity* m_entity;
};

#endif

