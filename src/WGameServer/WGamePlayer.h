#ifndef		_WGAMEPLAYER_H_ 
#define    _WGAMEPLAYER_H_

#include "Character.h"
#include "ClientMsg.h"
#include "LogicDataCommand.h"
#include "LogicGateCommand.h"
#include "WGameEvent.h"
#include "Counter.h"
#include "WorldCommand.h"
#include "./proto/msg_net.pb.h"
#include "./proto/package_net.pb.h"
#include "PlayerDataInfo.h"
#include "ECS_Component.h"
#include "WGameRole.h"
#include "ECS_System.h"
#include "ECS_Entity.h"

class CWGameTask;
class WGameDungeon;
class EagleLandmassEx;
class Fighter;

#define PLAYERINFOVERSION_1_1            1

//此类为现实中玩家及玩家账号 实际为ACCOUNT及SOCKET等管理
class WGamePlayer : public CIdNameSessionObject, public EventManagerInterface
{
public:
	WGamePlayer(const PlayerInfoBase &playerInfo, uint32_t gateServerType);
    ~WGamePlayer();

    uint32_t Type(){return OBJECT_PLAYER;}
    bool IsType(uint32_t type){return type == OBJECT_PLAYER;}
    
public:
	inline WGameRole* GetRole() { return &m_role; }
	inline ECS::ECSEntity* GetEntity() { return m_role.GetEntity(); }
    
    inline bool AsyncMsg(){return m_asyncMsg;}
    inline bool SetAsyncMsg(bool async = false){return m_asyncMsg = async;}
	inline uint32_t GetGateServerId() { return m_playerInfo.gatewayServerId; }
	inline uint32_t GetGateServerType() { return m_gateServerType; }

    void Update();
    void UpdateSec();
    void Update5Sec();
    void UpdateMin();
    void UpdateHour();
    void Update24();
    
	void SyncEnterWorldMsg();
	bool OnEnterServer();
    bool CanFree();

    //
	uint32_t SerializeWithDB(Cmd::t_Data_Save_RoleInfo_Req* send);
    bool UnSerializeWithWorld(Cmd::t_Enter_World_Req*);
	void SerializeWithWorld(Cmd::t_Enter_World_Req *send);
	void NotifySelectDBServer();
    inline void SetNeedSave(bool noDelay = false) { m_needSave = true; if (noDelay)Save();}
    void Save();
    Cmd::t_Data_Update_Item_Req *BeginUpdateItem();
    void EndUpdateItem(Cmd::t_Data_Update_Item_Req *, bool saveRole = false);

	//Serialize client msg
	void SerializeEnterWorldRes(ClientMsg::EnterWorldRes *);
	void SerializeEnterLandNotify(ClientMsg::EnterLandNotify *);
	void SerializeEnterDungeonRes(ClientMsg::EnterDungeonRes *);

    //base info
    inline PlayerInfoBase& GetPlayrInfoBase(){return m_playerInfo;}
    inline EagleCounter *PlayerCounters(){return &m_counters;}
    inline const char *Account(){return Session();}
    inline const char *GetIp(){return "";}
    inline uint32_t Level(){return 0;}
    inline uint32_t VipLevel(){return m_playerInfo.vipLevel;}

public:
    //world cmd
    bool WorldMatchRes(Cmd::t_World_Match_Res *);

private:

	uint32_t m_gateServerType;
    bool m_needSave;
    bool m_asyncMsg;

    PlayerInfoBase m_playerInfo;
    EagleCounter m_counters;

	WGameRole m_role;
};

void InitParasePlayerInfoMsgFun();

///////////////
#define GAMEPLAYER_CMP_VERSION_1_1			1

class GamePlayerComponent : public ECS::ECSComponent
{
public:
	enum
	{
		Type = ECS_PLAYER_COMPONENT_TYPE_PLAYER
	};

	GamePlayerComponent(ECS::ECSEntity* owner)
		:ECSComponent(owner)
	{
	}

	uint32_t GetType() override { return GamePlayerComponent::Type; }

public:
	WGamePlayer* m_player = NULL;
	EagleWorld* m_world = NULL;
	Fighter *m_fighter = NULL;        //

	protocol::ItemChangeNotifyNet m_itemChangeNotify;
	protocol::EquipChangeNotifyNet m_equipChangeNotify;

	WDungeonBaseInfo m_wdungeonInfo;
};

class GamePlayerSystem : public ECS::ECSSystem, public CSingleton<GamePlayerSystem>
{
public:
	bool InitEntityData(ECS::ECSEntity*) override;
	bool OnEnterServer(ECS::ECSEntity* entity) override;
	void Clear(ECS::ECSEntity *) override;
	uint32_t Serialize(ECS::ECSEntity*, uint8_t* buffer) override;
	uint32_t UnSerialize(ECS::ECSEntity*, uint8_t* buffer) override;

	void SetNeedSave(ECS::ECSEntity*, bool noDelay = false);
	void SendClientMsg(ECS::ECSEntity*, ClientMsg::Message* msg);
	void SendClientMsg(ECS::ECSEntity*, ::google::protobuf::Message* message, int id);
	void NotifyClientError(ECS::ECSEntity*, uint32_t error);
	void NotifyClientItemChange(ECS::ECSEntity*, bool send = true);

	EagleAction* CreateAction(ECS::ECSEntity* entity, uint32_t type, const std::vector<ConditionParm>&, void* ptr2);
	bool RegisterEventAction(ECS::ECSEntity* entity, EagleAction *action);
	EagleAction* RegisterEventAction(ECS::ECSEntity* entity, uint32_t type, const std::vector<ConditionParm> &, void* ptr2);
	void UnRegisterEventAction(ECS::ECSEntity* entity, EagleAction* action);
	void GamePlayerDoEvent(ECS::ECSEntity* entity, EagleEvent& m_event);

	//Scene related
	Fighter *CreateFighter(ECS::ECSEntity* entity);
	Fighter *GetFighter(ECS::ECSEntity* entity);

	void SetWorld(ECS::ECSEntity* entity, EagleWorld* d);
	EagleWorld* GetWorld(ECS::ECSEntity* entity);
	WGameDungeon* GetDungeon(ECS::ECSEntity* entity);
	void ClearDungeonInfo(ECS::ECSEntity* entity);
	EagleLandmassEx* GetLandmass(ECS::ECSEntity* entity);

	RoleInfoBase *GetRoleBaseInfo(ECS::ECSEntity* entity);
	WDungeonBaseInfo *GetDungeonBaseInfo(ECS::ECSEntity* entity);

	//client msg
public:
	//Fight Msg
	bool ParaseFightMessage(ECS::ECSEntity* entity, BinaryReadStream &stream, uint32_t minorCmd);

	//Map Msg
	bool ParaseMapMessage(ECS::ECSEntity* entity, BinaryReadStream &stream, uint32_t minorCmd);
	void MessageKillNpcReq(ECS::ECSEntity* entity, ClientMsg::KillNpcReq& msg);
	void MessageLeaveDungeonReq(ECS::ECSEntity* entity, ClientMsg::LeaveDungeonReq& msg);
	void MessageEnterFinish(ECS::ECSEntity* entity, ClientMsg::EnterFinish& msg);

	//PlayerInfo Msg
	bool ParasePlayerInfoMessage(ECS::ECSEntity* entity, BinaryReadStream &stream, uint32_t minorCmd);
	bool ParasePlayerInfoMessage(ECS::ECSEntity* entity, protocol::PackageNet *data);
	bool BuyBagSolt(ECS::ECSEntity* entity);

	//Chat Msg
	bool ParaseChatMessage(ECS::ECSEntity* entity, BinaryReadStream &stream, uint32_t minorCmd);
	bool ParaseChatMessage(ECS::ECSEntity* entity, protocol::PackageNet *data);
	void MessageGMCMD(ECS::ECSEntity* entity, const std::string &cmd);

	//World Msg
	bool ParaseWorldMessage(ECS::ECSEntity* entity, BinaryReadStream &stream, uint32_t minorCmd);

	//Friend Msg
	bool ParaseFriendMessage(ECS::ECSEntity* entity, BinaryReadStream &stream, uint32_t minorCmd, uint8_t *ptr, uint32_t len);

};


#endif    


