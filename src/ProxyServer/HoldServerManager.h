#ifndef _HOLDSERVER_MANAGER_H_
#define _HOLDSERVER_MANAGER_H_

#include "Sys.h"
#include "Singleton.h"
#include "ImpService.h"
#include "ServerCommand.h"
#include "ConstructInPlace.h"

class CProxyTask;
class CProxyConnectClient;

class HoldServerManager : public CSingleton<HoldServerManager>
{
public:
    HoldServerManager();
    ~HoldServerManager();

    void HoldServerNotify(CProxyTask *);
    void HoldServerNotify(CProxyConnectClient *);
    bool UpdateHoldMap(Cmd::t_HoldServer_Notify *recv, CProxyTask *holdTask);
    void HoldMapDelTask(CProxyTask *);
    void SendCmd(Cmd::t_Server_Send_Trans_Msg *recv, uint32_t len);

    bool TransMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);

private:
    void CheckHoldMapByServerType(uint32_t serverType);

	template<class cmd>
	unsigned char* ServerCmdBuffer(cmd*& name);


private:
	buffercmdqueue m_sendBuffer;

    std::map< uint32_t, std::map<uint32_t, CProxyTask *> > m_proxyHoldMap;

};

template<class cmd>
unsigned char* HoldServerManager::ServerCmdBuffer(cmd*& name) {
	m_sendBuffer.ReSet();
	m_sendBuffer.WrReserve(SERVER_COMMAND_MAX_LENGTH);
	name = (cmd*)(m_sendBuffer.WrBuf());
	constructInPlace(name);
	return m_sendBuffer.WrBuf();
}


#endif

