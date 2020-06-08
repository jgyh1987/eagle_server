#ifndef _GATEWAYPLAYER_H_ 
#define    _GATEWAYPLAYER_H_

#include "ClientMsg.h"
#include "PlayerInfo.h"
#include "CmdQueue.h"
#include "WorldObject.h"
#include "./proto/package_net.pb.h"
#include "KcpPlayer.h"
#include "Session.h"


#define MOVEMSG_MAX_LEN 200

class CGatewayTask;

class GatewayPlayer : public WorldObject, public KcpPlayer
{
public:
    GatewayPlayer(uint64_t id, uint64_t tempid, AccountSession *account, CGatewayTask* task);
    ~GatewayPlayer();

    uint32_t Type() { return OBJECT_PLAYER; }
    bool IsType(uint32_t type) { return type == OBJECT_PLAYER; }
    bool Init(uint64_t id) { m_id = id; return true; }
    void Update();
    void Update5Sec();

    void UpdateBaseInfo(PlayerInfoBase *info, RoleInfoBase *roleInfo);
    void SetTask(CGatewayTask *task = NULL);
    bool SendClientMsg(ClientMsg::Message *message);
    bool SendClientMsg(::google::protobuf::Message *message, int id);
    bool SendCmd(const void *, uint32_t);
    bool SendToLogic(void *, uint32_t);
	bool SendToGame(void*, uint32_t);

	inline char* Account()
	{
		if (m_account)
			return (char*)m_account->account.c_str();
		return NULL;
	}
	inline CGatewayTask* Task()
	{
		return m_task;
	}

	void LeaveWorld();
	void NotifyBeTick(uint32_t type);

    //KCP
	void ParamKcpMsg(const char* data, uint32_t size);
    void KcpSendClientMsg(ClientMsg::Message *message);
    bool KcpSendClientMsg(::google::protobuf::Message *message, int id);
    void SetKcpId(uint32_t id);

	//无缝
	inline bool GetAgentLock() { return m_agentLock; }
	inline void SetAgentLock(bool val) { m_agentLock = val; }
	inline uint32_t GetAgentServerId() { return m_agentServerId; }
	inline void SetAgentServerId(uint32_t serverId) { m_agentServerId = serverId; }

protected:
	void MoveUpdate() {}

private:
    AccountSession *m_account;
    CGatewayTask *m_task;

	bool m_agentLock;
	uint32_t m_agentServerId;
};



#endif    


