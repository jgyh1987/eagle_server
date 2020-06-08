#ifndef _CENTRAL_CONNECTCLIENT_H_
#define _CENTRAL_CONNECTCLIENT_H_

#include "GameBaseTask.h"
#include "ServerCommand.h"
#include "ConstructInPlace.h"
#include "Singleton.h"
#include "ImpService.h"

class CCentralConnectClient : public CServerConnectClientEx
{
public:
    CCentralConnectClient(const std::string &name, const std::string &ip = "127.0.0.1",const unsigned short port = 18057, uint32_t queuesize = 102400)
        :CServerConnectClientEx(name, SERVER_TYPE_CENTRAL_SERVER, g_serverId, 0, ip, port)
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
unsigned char* CCentralConnectClient::ServerCmdBuffer(cmd* &name) {
    m_sendBuffer.ReSet();
    m_sendBuffer.WrReserve(SERVER_COMMAND_MAX_LENGTH);
    name = (cmd *)(m_sendBuffer.WrBuf());
    constructInPlace(name);
    return m_sendBuffer.WrBuf();
}

#endif
