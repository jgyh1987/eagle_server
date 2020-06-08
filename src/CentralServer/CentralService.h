#ifndef _CENTRALSERVICE_H_
#define _CENTRALSERVICE_H_

#include "ImpService.h"
#include "ServerCommand.h"
#include "ConstructInPlace.h"

class CCentralTask;

class CCentralServer : public CImpServer
{
public:
    CCentralServer(const std::string &name);
    ~CCentralServer();

    void Update5Sec();
    void UpdateMin();

    void AddCentralTask(CServerTask *);
    void RemoveCentralTask(CServerTask *);
    void NotifyProxyToServer(CCentralTask *);

private:
	template<class cmd>
	unsigned char* ServerCmdBuffer(cmd*& name);

protected:
    buffercmdqueue m_sendBuffer;

    std::map< uint32_t, std::map<uint32_t, CCentralTask *> > m_serverTasks;

};

template<class cmd>
unsigned char* CCentralServer::ServerCmdBuffer(cmd* &name) {
    m_sendBuffer.ReSet();
    m_sendBuffer.WrReserve(SERVER_COMMAND_MAX_LENGTH);
    name = (cmd *)(m_sendBuffer.WrBuf());
    constructInPlace(name);
    return m_sendBuffer.WrBuf();
}

CCentralServer *ServerImp();



#endif

