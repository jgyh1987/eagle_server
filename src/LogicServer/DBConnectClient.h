#ifndef _DBCONNECTCLIENT_H_
#define _DBCONNECTCLIENT_H_

#include "ServerConnect.h"
#include "Defs.h"

class CDBConnectClient : public CServerConnectClient
{
public:
    CDBConnectClient(const std::string &name,const std::string &ip = "127.0.0.1",const unsigned short port = 17077, uint32_t queuesize = 102400);

    bool cmdMsgParse(void *,const uint32_t);

    inline bool IsRegist()
    {
        return m_isRegist;
    }

protected:
    void CallBackConnectSuccessImp();
    void CallBackConnectErrorImp();

private:
    bool ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);
    bool LogicDataMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);
    bool FriendMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);

private:
    bool m_isRegist;
};

#endif
