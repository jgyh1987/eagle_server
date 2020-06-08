#ifndef _GATEWAY_CONNECTCLIENT_H_
#define _GATEWAY_CONNECTCLIENT_H_

#include "ServerConnect.h"
#include "Command.h"

class CGatewayConnectClient : public CServerConnectClient
{
public:
    CGatewayConnectClient(uint32_t serverType, uint32_t serverId, const std::string &name,const std::string &ip = "127.0.0.1",const unsigned short port = 18087)
        :CServerConnectClient(name, serverType, serverId, ip, port)
    {
    }

    bool cmdMsgParse(void *,const uint32_t);

    void SendPlayerCountToLoginServer();

protected:
    void CallBackConnectSuccessImp();
    void CallBackConnectErrorImp();

private:
    bool ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);
    bool LoginServerMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);
    bool TransMsgParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);

    bool LogicServerMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);
    bool GetPlayerInfoRes(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);
	bool PlayerKickNotify(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);

    bool WorldMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);

};

#endif
