#ifndef _LOGICSERVICE_H_
#define _LOGICSERVICE_H_

#include "ImpService.h"
#include "Command.h"
#include "ConstructInPlace.h"
#include "./proto/msg_net.pb.h"
#include "./proto/package_net.pb.h"
#include "ClientMsg.h"

class CLogicServer : public CImpServer
{
public:
    CLogicServer(const std::string &name);
    ~CLogicServer();

    bool CallBack();

    void Update();
    void UpdateSec();
    void Update5Sec();
    void UpdateMin();
    void Update5Min();
    void Update30Min();
    void UpdateHour();
    void Update24();

    void ProxySendCmd(void *cmd, uint32_t len, uint32_t serverType, uint32_t serverId);
	bool SendClientMsg(ClientMsg::Message* msg, uint64_t uid, uint32_t gateServerId);
	bool SendClientMsg(::google::protobuf::Message* message, int id, uint64_t uid, uint32_t gateServerId);

private:
	template<class cmd>
	unsigned char* ServerCmdBuffer(cmd*& name);

private:
    buffercmdqueue m_sendBuffer;
};

template<class cmd>
unsigned char* CLogicServer::ServerCmdBuffer(cmd* &name){
    m_sendBuffer.ReSet(); 
    m_sendBuffer.WrReserve(SERVER_COMMAND_MAX_LENGTH); 
    name=(cmd *)(m_sendBuffer.WrBuf());
    constructInPlace(name);
    return m_sendBuffer.WrBuf();
}

CLogicServer *ServerImp();

#endif

