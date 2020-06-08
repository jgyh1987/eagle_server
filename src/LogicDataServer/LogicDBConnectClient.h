#ifndef _LOGICDB_CONNECTCLIENT_H_
#define _LOGICDB_CONNECTCLIENT_H_

#include "ServerConnect.h"
#include "ConstructInPlace.h"
#include "Singleton.h"
#include "LogicDataCommand.h"

class CLogicDBConnectClient : public CServerConnectClient
{
public:
	CLogicDBConnectClient(const std::string &name, uint32_t serverType, uint32_t serverId, const std::string &ip = "127.0.0.1",const unsigned short port = 18057, uint32_t queuesize = 102400)
        :CServerConnectClient(name, serverType, serverId, ip, port)
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

	bool DBLogicPlayerInfoMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);
	bool DBSelectServer(Cmd::t_Data_Select_Server*);
	bool DBSaveRoleInfo(Cmd::t_Data_Save_RoleInfo_Req* recv);
	bool UpdateItemReq(Cmd::t_Data_Update_Item_Req* recv);

private:
    buffercmdqueue m_sendBuffer;
};

template<class cmd>
unsigned char* CLogicDBConnectClient::ServerCmdBuffer(cmd* &name) {
    m_sendBuffer.ReSet();
    m_sendBuffer.WrReserve(SERVER_COMMAND_MAX_LENGTH);
    name = (cmd *)(m_sendBuffer.WrBuf());
    constructInPlace(name);
    return m_sendBuffer.WrBuf();
}

#endif
