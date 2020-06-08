#ifndef _GATEWAYTASK_H_
#define _GATEWAYTASK_H_

#include "GameBaseTask.h"
#include "ClientMsg.h"
#include "LogicGateCommand.h"
#include "./proto/msg_net.pb.h"
#include "./proto/package_net.pb.h"

struct AccountSession;
class GatewayPlayer;
class CGatewayTask : public CClientTask
{
public:
    CGatewayTask(CListenTCPServer *listenServer)
        :CClientTask(listenServer), m_player(NULL)
    {
        m_hreatTime = 0;
        m_lockTime = 0;
        m_openFilter = false;
    }

    ~CGatewayTask();

    void Clear();

    bool cmdMsgParse(void *,const uint32_t);

    inline void SetPlayer(GatewayPlayer *player)
    { 
        m_player = player; 
        if (NULL == player)
            SetNeedClose();
    }

public:
    bool TransMsgToLogic(void *ptNull, const uint32_t nCmdLen);
	bool TransMsgToGame(void* ptNull, const uint32_t nCmdLen);
    bool SendClientMsg(ClientMsg::Message *message);
    bool SendClientMsg(::google::protobuf::Message *message, int id);
    bool RegistPlayer(PlayerInfoBase &playerinfo, AccountSession *account);

protected:
    void LoginGame(void *data, int size);

public:
    GatewayPlayer    *m_player;
    uint64_t m_hreatTime;
    uint64_t m_lockTime;
};

#endif
