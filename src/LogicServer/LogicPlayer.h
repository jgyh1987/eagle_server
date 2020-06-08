#ifndef _LOGICPLAYER_H_ 
#define _LOGICPLAYER_H_

#include "Character.h"
#include "ClientMsg.h"
#include "LogicDataCommand.h"
#include "LogicGateCommand.h"
#include "LogicEvent.h"
#include "Counter.h"
#include "LogicRole.h"
#include "WorldCommand.h"
#include "WorldCommand.h"
#include "./proto/msg_net.pb.h"
#include "./proto/package_net.pb.h"
#include "PlayerDataInfo.h"

class CLogicTask;

#define PLAYERINFOVERSION_1_1            1

class LogicPlayer : public CIdNameSessionObject, public EventManagerInterface
{
public:
    LogicPlayer(const PlayerInfoBase &playerInfo);
    ~LogicPlayer();

    uint32_t Type(){return OBJECT_PLAYER;}
    bool IsType(uint32_t type){return type == OBJECT_PLAYER;}
    
public:
    void Clear();
    inline bool IsAgent(){ return m_isAgent; }
    
    inline bool AsyncMsg(){return m_asyncMsg;}
    inline bool SetAsyncMsg(bool async = false){return m_asyncMsg = async;}
	void SetGateServer(uint32_t gateServerId);
	inline uint32_t GetGateServer() { return m_playerInfo.gatewayServerId; }
    bool SendCmd(void *, uint32_t);
    bool SendClientMsg(ClientMsg::Message *msg);
    bool SendClientMsg(::google::protobuf::Message *message, int id);
    void NotifyClientError(uint32_t error);

    void Update();
    void UpdateSec();
    void Update5Sec();
    void UpdateMin();
    void UpdateHour();
    void Update24();
    
    bool FirstLogin();
    bool OnLogin();
    bool ReConnect();
	void NotifyLoginGame();
    void SyncLoginMsg();
    bool OnUnLogin();
    bool CanFree();
    void KickPlayerOnline(uint32_t type = 0);
	void EnterToWorld();

    //
    void SerializeWithDB(Cmd::t_Data_Save_PlayerInfo_Req* send);
	bool UnSerializeWithDB(Cmd::t_Data_Get_PlayerInfo_Res*);
	void SerializeWithEnter(Cmd::t_Enter_World_Req *send);
    void UnSerializeRoleSimpleWithDB(uint8_t* buffer, uint32_t length);
    inline void SetNeedSave(bool noDelay = false) { m_needSave = true; if (noDelay)Save(); }
    void Save();
    //Off Player Data CallBack
    void OffPlayerDataCallBack(LogicPlayer *target, uint32_t funType);
    //
    Cmd::t_Data_Update_Item_Req *BeginUpdateItem();
    void EndUpdateItem(Cmd::t_Data_Update_Item_Req *, bool saveRole = false);

    //base info
    inline PlayerInfoBase& GetPlayrInfoBase(){return m_playerInfo;}
    inline const char *Account(){return Session();}
    inline const char *GetIp(){return "";}
    inline uint32_t Level(){return 0;}
    inline uint32_t VipLevel(){return m_playerInfo.vipLevel;}

    //role info 
    bool InitRoleInfo(Cmd::t_Data_GetRoleInfo_Res *recv);
    
//client msg parase
public:
    //Login Msg
    bool ParaseLoginMessage(BinaryReadStream &stream, uint32_t minorCmd);
    bool ParaseLoginMessage(protocol::PackageNet *data);
    bool MessageCreateRole(const ClientMsg::CreateRoleReq &msg);
    bool MessageCreateRole(const protocol::PackageNet *data);
    void AddRoleInfo(const RoleInfoBase &roleinfo);
    int32_t HaveRole(uint64_t roleId);
    void NotifyCreateRole(Cmd::t_Data_Create_RoleInfo_Res *);

    //PlayerInfo Msg
    bool ParasePlayerInfoMessage(BinaryReadStream &stream, uint32_t minorCmd);
    bool ParasePlayerInfoMessage(protocol::PackageNet *data);
    
    //Chat Msg
    bool ParaseChatMessage(BinaryReadStream &stream, uint32_t minorCmd);
    bool ParaseChatMessage(protocol::PackageNet *data);
    void MessageGMCMD(const std::string &cmd);

    //World Msg
    bool ParaseWorldMessage(BinaryReadStream &stream, uint32_t minorCmd);

    //Friend Msg
    bool ParaseFriendMessage(BinaryReadStream &stream, uint32_t minorCmd, uint8_t *ptr, uint32_t len);

    //scene cmd
    bool ParaseSceneCmd(Cmd::t_NullCmd *recv);

    //world cmd
    bool WorldMatchRes(Cmd::t_World_Match_Res *);

private:
    bool m_isAgent = false;
    bool m_needSave = false;
    bool m_asyncMsg = false;

    PlayerInfoBase m_playerInfo;
    EagleCounter m_counters;

    std::vector<SimpleRole> m_roles;
    LogicRole *m_role = NULL;        //

};

void InitParasePlayerInfoMsgFun();

///////////////


#endif    


