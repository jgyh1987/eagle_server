#ifndef _LOGDBCONNECTCLIENT_H_
#define _LOGDBCONNECTCLIENT_H_

#include "ServerConnect.h"
#include "Command.h"
#include "ConstructInPlace.h"
#include "ImpService.h"

class CLogDBConnectClient : public CServerConnectClient
{
public:
    CLogDBConnectClient(const std::string &name,const std::string &ip = "127.0.0.1",const unsigned short port = 17078, uint32_t queuesize = 102400)
        :CServerConnectClient(name, SERVER_TYPE_LOG_DATA, g_serverId, ip, port)
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
unsigned char* CLogDBConnectClient::ServerCmdBuffer(cmd* &name){
    m_sendBuffer.ReSet(); 
    m_sendBuffer.WrReserve(SERVER_COMMAND_MAX_LENGTH); 
    name=(cmd *)(m_sendBuffer.WrBuf());
    constructInPlace(name);
    return m_sendBuffer.WrBuf();
}


#endif
