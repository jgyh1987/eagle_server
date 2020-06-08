#ifndef _WMATCH_SERVICE_H_
#define _WMATCH_SERVICE_H_

#include "ImpService.h"
#include "ServerCommand.h"
#include "ConstructInPlace.h"

class CWMatchTask;

class CWMatchServer : public CImpServer
{
public:
    CWMatchServer(const std::string &name);
    ~CWMatchServer();

    void UpdateSec();
    void Update5Sec();

    void RemoveServer(CWMatchTask *);

    void ProxySendCmd(void *cmd, uint32_t len, uint32_t serverType, uint32_t serverId, CWMatchTask *proxyTask = NULL);

private:
	template<class cmd>
	unsigned char* ServerCmdBuffer(cmd*& name);

private:
    std::map<uint32_t, CWMatchTask *> m_fights;
    std::map< uint32_t, std::map<uint32_t, CWMatchTask *> > m_logics;

    buffercmdqueue m_sendBuffer;
};

template<class cmd>
unsigned char* CWMatchServer::ServerCmdBuffer(cmd* &name){
    m_sendBuffer.ReSet(); 
    m_sendBuffer.WrReserve(SERVER_COMMAND_MAX_LENGTH); 
    name=(cmd *)(m_sendBuffer.WrBuf());
    constructInPlace(name);
    return m_sendBuffer.WrBuf();
}

CWMatchServer *ServerImp();


#endif

