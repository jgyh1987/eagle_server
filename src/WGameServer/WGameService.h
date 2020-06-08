#ifndef _WGAME_SERVICE_H_
#define _WGAME_SERVICE_H_

#include "ImpService.h"
#include "ServerCommand.h"
#include "ConstructInPlace.h"
#include "ClientMsg.h"

class CWGameServer : public CImpServer
{
public:
    CWGameServer(const std::string &name);
    ~CWGameServer();

    void Update();
    void UpdateSec();
    void Update5Sec();

    void TickLongWarn(uint32_t t);
    inline uint32_t GetLoadHigh()
    {
        return m_loadHigh;
    }

    void ProxySendCmd(void *cmd, uint32_t len, uint32_t serverType, uint32_t serverId = 0);
	void ClearProxyServer();
	inline void SetProxyServer(Cmd::ServerInfoEx& info)
	{
		m_proxyServer = info;
	}

	inline bool UseDungeon() { return m_useDungeon; }
	inline void UseDungeon(bool v) { m_useDungeon = v; }
	inline bool UseBigWorld() { return m_bigWorld; }
	inline void UseBigWorld(bool v) { m_bigWorld = v; }

	void SendToGate(ClientMsg::Message* msg, uint32_t serverId);

private:
	template<class cmd>
	unsigned char* ServerCmdBuffer(cmd*& name);
    
private:
    uint32_t m_loadHigh;
	bool m_useDungeon = false;
	bool m_bigWorld = false;

    buffercmdqueue m_sendBuffer;
	Cmd::ServerInfoEx m_proxyServer;
};

template<class cmd>
unsigned char* CWGameServer::ServerCmdBuffer(cmd* &name){
    m_sendBuffer.ReSet(); 
    m_sendBuffer.WrReserve(SERVER_COMMAND_MAX_LENGTH); 
    name=(cmd *)(m_sendBuffer.WrBuf());
    constructInPlace(name);
    return m_sendBuffer.WrBuf();
}

CWGameServer *ServerImp();


#endif

