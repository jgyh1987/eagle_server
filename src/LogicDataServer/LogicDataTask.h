#ifndef _LOGICDATATASK_H_
#define _LOGICDATATASK_H_

#include "ServerTask.h"
#include "LogicDataCommand.h"
#include "ConstructInPlace.h"

class CLogicDataTask : public CServerTask
{
public:
    CLogicDataTask(CListenTCPServer *listenServer)
        :CServerTask(listenServer)
    {
    }

    bool cmdMsgParse(void *,const uint32_t);

    template<class cmd>
    unsigned char* ServerCmdBuffer(cmd* &name);

private:
    bool DBServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);

    bool DBLogicPlayerInfoMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);
	bool DBSelectServer(Cmd::t_Data_Select_Server*);
    bool DBGetPlayerInfoByAccount(Cmd::t_Data_Get_PlayerInfo_Req *);
    bool DBSavePlayerInfo(Cmd::t_Data_Save_PlayerInfo_Req *recv);
    bool DBCreateRole(Cmd::t_Data_Create_RoleInfo_Req *recv);
    bool DBGetRoleInfo(Cmd::t_Data_GetRoleInfo_Req *recv);
    bool DBSetRoleStatus(const uint64_t roleId, const uint32_t status, uint32_t &ret, uint64_t playerId);
    bool DBSaveRoleInfo(Cmd::t_Data_Save_RoleInfo_Req *recv);
    bool UpdateItemReq(Cmd::t_Data_Update_Item_Req *recv);

private:
    buffercmdqueue m_sendBuffer;
};

template<class cmd>
unsigned char* CLogicDataTask::ServerCmdBuffer(cmd* &name){
    m_sendBuffer.ReSet(); 
    m_sendBuffer.WrReserve(SERVER_COMMAND_MAX_LENGTH); 
    name=(cmd *)(m_sendBuffer.WrBuf());
    constructInPlace(name);
    return m_sendBuffer.WrBuf();
}

#endif
