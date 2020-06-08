#ifndef _LOGINCLIENT_TASK_H_
#define _LOGINCLIENT_TASK_H_

#include "ClientTask.h"
#include "ClientMsg.h"
#include "./proto/msg_net.pb.h"
#include "./proto/package_net.pb.h"

struct SAccountInfo;

class CLoginClientTask : public CClientTask
{
public:
    CLoginClientTask(CListenTCPServer *listenServer)
        :CClientTask(listenServer)
    {
        m_connectTime = 0;
        m_accountInfo = NULL;
    }

    ~CLoginClientTask();

    void Clear();
    bool cmdMsgParse(void *,const uint32_t);

public:
    bool SendClientMsg(ClientMsg::Message *message);
    bool SendClientMsg(::google::protobuf::Message *message, int id);
    void SetConnectTime(uint64_t time) { m_connectTime = time; }
    uint64_t GetConnectTime() { return m_connectTime; }
    void ClearAccountInfo() { m_accountInfo = NULL; }
    SAccountInfo *GetAccountInfo() { return m_accountInfo; }

public:
    bool C2SLoginAccountReq(void *data, int size);
    bool C2SSelectServerReq(void *data, int size);

private:
    uint64_t m_connectTime;
    SAccountInfo *m_accountInfo;
};

#endif
