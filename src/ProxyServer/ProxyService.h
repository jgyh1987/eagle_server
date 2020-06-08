#ifndef _PROXYSERVICE_H_
#define _PROXYSERVICE_H_

#include "ImpService.h"
#include "ServerCommand.h"
#include "ConstructInPlace.h"

class CProxyTask;

class CProxyServer : public CImpServer
{
public:
    CProxyServer(const std::string &name);
    ~CProxyServer();

    void Update5Sec();
    void UpdateMin();

private:
	template<class cmd>
	unsigned char* ServerCmdBuffer(cmd*& name);

private:
    buffercmdqueue m_sendBuffer;

};

template<class cmd>
unsigned char* CProxyServer::ServerCmdBuffer(cmd* &name){
    m_sendBuffer.ReSet(); 
    m_sendBuffer.WrReserve(SERVER_COMMAND_MAX_LENGTH); 
    name=(cmd *)(m_sendBuffer.WrBuf());
    constructInPlace(name);
    return m_sendBuffer.WrBuf();
}

CProxyServer *ServerImp();

#endif

