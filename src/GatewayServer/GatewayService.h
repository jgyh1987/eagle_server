#ifndef _GATEWAYSERVICE_H_
#define _GATEWAYSERVICE_H_

#include "ImpService.h"
#include "LogicGateCommand.h"
#include "ConstructInPlace.h"

class CGatewayServer : public CImpServer
{
public:
    CGatewayServer(const std::string &name);
    ~CGatewayServer();

    bool CallBack();

    void Update();
    void UpdateSec();
    void Update5Sec();

    void NotifyPlayerLeave(uint64_t playerId);

	//此处特殊为public 一般应该是private
public:
	template<class cmd>
	unsigned char* ServerCmdBuffer(cmd*& name);

private:
    buffercmdqueue m_sendBuffer;
};

template<class cmd>
unsigned char* CGatewayServer::ServerCmdBuffer(cmd* &name){
    m_sendBuffer.ReSet(); 
    m_sendBuffer.WrReserve(SERVER_COMMAND_MAX_LENGTH); 
    name=(cmd *)(m_sendBuffer.WrBuf());
    constructInPlace(name);
    return m_sendBuffer.WrBuf();
}

CGatewayServer *ServerImp();

#endif

