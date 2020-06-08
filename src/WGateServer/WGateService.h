#ifndef _WGATE_SERVICE_H_
#define _WGATE_SERVICE_H_

#include "ImpService.h"
#include "ServerCommand.h"
#include "ConstructInPlace.h"


class CWGateClientTask;
class CWGateConnectClient;

class CWGateServer : public CImpServer
{
public:
    CWGateServer(const std::string &name);
    ~CWGateServer();

    void Update();
    void UpdateSec();
    void Update5Sec();

    void ProxySendCmd(void *cmd, uint32_t len, uint32_t serverType, uint32_t serverId);
	void ClearProxyServer();
	inline void SetProxyServer(Cmd::ServerInfoEx& info)
	{
		m_proxyServer = info;
	}

	void PushNeedRemoveConnect(CWGateConnectClient* c) { m_needRemoveConnects.push_back(c); }

private:
	template<class cmd>
	unsigned char* ServerCmdBuffer(cmd*& name);
    
private:

    buffercmdqueue m_sendBuffer;
	Cmd::ServerInfoEx m_proxyServer;
	std::vector< CWGateConnectClient * > m_needRemoveConnects;
};

template<class cmd>
unsigned char* CWGateServer::ServerCmdBuffer(cmd* &name){
    m_sendBuffer.ReSet(); 
    m_sendBuffer.WrReserve(SERVER_COMMAND_MAX_LENGTH); 
    name=(cmd *)(m_sendBuffer.WrBuf());
    constructInPlace(name);
    return m_sendBuffer.WrBuf();
}

CWGateServer *ServerImp();


#endif

