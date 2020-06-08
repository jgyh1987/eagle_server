#ifndef _DBCONNECTCLIENT_H_
#define _DBCONNECTCLIENT_H_

#include "Sys.h"
#include "ServerConnect.h"
#include "Command.h"

class CDBConnectClient : public CServerConnectClient
{
public:
    CDBConnectClient(const std::string &name,const std::string &ip = "127.0.0.1",const unsigned short port = 17087, uint32_t queuesize = 102400)
        :CServerConnectClient(name, SERVER_TYPE_LOGIN_DATA, 0, ip, port)
    {
        m_isRegist = false;
    }

    bool cmdMsgParse(void *,const uint32_t);

    inline bool IsRegist()
    {
        return m_isRegist;
    }

protected:
    void CallBackConnectSuccessImp();
    void CallBackConnectErrorImp();

private:
    bool LoginDataMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);
    bool LoginAccountMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);
    bool LoginSessionMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);

private:
    bool m_isRegist;
};

#endif
