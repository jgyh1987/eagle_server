#ifndef _LOGICTASK_H_
#define _LOGICTASK_H_

#include "GameBaseTask.h"
#include "ClientMsg.h"
#include "ConstructInPlace.h"
#include "ServerCommand.h"

class LogicPlayer;
class CLogicTask : public CServerTaskEx
{
public:
    CLogicTask(CListenTCPServer *listenServer)
        :CServerTaskEx(listenServer)
    {
    }

    void Clear();

    bool cmdMsgParse(void *,const uint32_t);

    template<class cmd>
    unsigned char* ServerCmdBuffer(cmd* &name);

private:
    bool ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);

    bool LogicPlayerInfoMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);
    bool TransMsgParase(const Cmd::t_Server_Send_Trans_Msg* pNullCmd, const unsigned int nCmdLen);
    bool PTMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);

private:
    buffercmdqueue m_sendBuffer;
};

template<class cmd>
unsigned char* CLogicTask::ServerCmdBuffer(cmd* &name){
    m_sendBuffer.ReSet(); 
    m_sendBuffer.WrReserve(SERVER_COMMAND_MAX_LENGTH); 
    name=(cmd *)(m_sendBuffer.WrBuf());
    constructInPlace(name);
    return m_sendBuffer.WrBuf();
}


#endif
