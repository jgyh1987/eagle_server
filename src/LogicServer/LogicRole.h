#ifndef _WORLDROLE_H_ 
#define    _WORLDROLE_H_

#include "PlayerInfo.h"
#include "LogicDataManager.h"
#include "ClientMsg.h"
#include "LogicDataCommand.h"
#include "Counter.h"
#include "ECS_Entity.h"
#include "ECS_Component.h"
#include "WorldCommand.h"

#define ROLEINFOVERSION_1_1 1

class LogicPlayer;

class SimpleRole
{
public:
    SimpleRole();
    ~SimpleRole();

    uint32_t UnSerializeWithDB(uint8_t* buffer);

public:
    RoleInfoBase m_baseInfo;
};

class LogicRole
{
    friend class LogicPlayer;
public:
    LogicRole(LogicPlayer *);
    ~LogicRole();

public:
    inline RoleInfoBase *GetRoleInfo()
    {
        return &m_roleInfo;
    }
    void Clear();
    bool Init(Cmd::t_Data_GetRoleInfo_Res *recv);

    //data
	void UnSerializeWithDB(Cmd::t_Data_GetRoleInfo_Res* recv);
	void SerializeWithEnter(Cmd::t_Enter_World_Req* send);

public:
    //
    inline uint64_t RoleId() { return m_roleInfo.roleId; }

private:
    bool FirstEnter();//

protected:
    LogicPlayer *m_owner = NULL;
    RoleConfigData *m_data = NULL;
	RoleInfoBase m_roleInfo;        //

	//ecs 
	ECS::ECSEntity* m_entity = NULL;

    //db data
    uint8_t *m_dbdata = NULL;
    uint32_t m_dbdataLen = 0;
};

class LogicPlayerComponent : public ECS::ECSComponent
{
public:
	enum
	{
		Type = ECS_PLAYER_COMPONENT_TYPE_PLAYER
	};

	LogicPlayerComponent(ECS::ECSEntity* owner)
		:ECSComponent(owner)
	{
	}

	uint32_t GetType() override { return LogicPlayerComponent::Type; }

public:
	LogicPlayer* m_player = NULL;
	LogicRole* m_role = NULL;
};

#endif    


