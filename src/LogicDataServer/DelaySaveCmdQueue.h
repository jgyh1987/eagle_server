#ifndef _DELAYSAVECMDQUEUE_H_
#define _DELAYSAVECMDQUEUE_H_

#include "CmdQueue.h"
#include "LogicDataCommand.h"
#include "SockStream.h"
#include "ConstructInPlace.h"

#define UPDATE_MAIL_ONCE_COUNT 100

//

//DelaySaveCmdQueue
class DelaySaveCmdQueue : public CConCmdQueue
{
public:
    DelaySaveCmdQueue(uint32_t queuesize = 102400)
        :CConCmdQueue(queuesize)
    {
    }

    bool cmdMsgParse(void *,const uint32_t);
    void Update();

    //bool DBSendMailToAll(Cmd::t_Data_Send_Mail_To_All_Req *recv);
    //bool DBSendMail(Cmd::t_Data_Send_Mail_Req *recv);
    //bool DBDeleteMail(Cmd::t_Data_Delete_Mail_Req *recv);
    //bool DBGetMailList(Cmd::t_Data_Get_Mail_List_Req *recv);

    void SendCmdMsgParse();

    template<class cmd>
    unsigned char* ServerCmdBuffer(cmd* &name);

private:
    buffercmdqueue m_sendBuffer;

    //std::map< uint64_t, std::list<Cmd::t_Data_Delete_Mail_Req> > m_delMailErrorCmdQueue;
};

template<class cmd>
unsigned char* DelaySaveCmdQueue::ServerCmdBuffer(cmd* &name){
    m_sendBuffer.ReSet(); 
    m_sendBuffer.WrReserve(SERVER_COMMAND_MAX_LENGTH); 
    name=(cmd *)(m_sendBuffer.WrBuf());
    constructInPlace(name);
    return m_sendBuffer.WrBuf();
}


#endif
