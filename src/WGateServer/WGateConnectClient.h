#ifndef _WGATE_CONNECTCLIENT_H_
#define _WGATE_CONNECTCLIENT_H_

#include "GameBaseTask.h"
#include "ServerCommand.h"
#include "ConstructInPlace.h"
#include "Singleton.h"

class CWGateConnectClient : public CServerConnectClientEx
{
public:
    CWGateConnectClient(const std::string &name, uint32_t serverType, uint32_t serverId, const std::string &ip = "127.0.0.1",const unsigned short port = 18057, uint32_t queuesize = 102400)
        :CServerConnectClientEx(name, serverType, serverId, 0, ip, port)
    {
    }

    bool cmdMsgParse(void *,const uint32_t);

    template<class cmd>
    unsigned char* ServerCmdBuffer(cmd* &name);

protected:
    void CallBackConnectSuccessImp();
    void CallBackConnectErrorImp();


private:
    bool ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);


private:
    buffercmdqueue m_sendBuffer;
};

template<class cmd>
unsigned char* CWGateConnectClient::ServerCmdBuffer(cmd* &name) {
    m_sendBuffer.ReSet();
    m_sendBuffer.WrReserve(SERVER_COMMAND_MAX_LENGTH);
    name = (cmd *)(m_sendBuffer.WrBuf());
    constructInPlace(name);
    return m_sendBuffer.WrBuf();
}

#endif
