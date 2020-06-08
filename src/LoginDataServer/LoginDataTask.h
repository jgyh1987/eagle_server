#ifndef _LOGINDATATASK_H_
#define _LOGINDATATASK_H_

#include "ServerTask.h"
#include "LogicLoginCommand.h"

class CLoginDataTask : public CServerTask
{
public:
    CLoginDataTask(CListenTCPServer *listenServer)
        :CServerTask(listenServer)
    {
    }

    bool cmdMsgParse(void *,const uint32_t);

private:
    bool DBServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);
    bool DBLogicPlayerInfoMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);
    bool DBLoginSessionMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);

    bool DBGetAccountPasswdByAccount(char *account);
    bool DBGetAccountByAccountPasswd(char *account, char *passwd);
    bool DBGetPackageCodeReq(Cmd::t_Get_PackageCode_Req *recv);
    bool DBPackageCodeRewardRes(Cmd::t_PackageCode_Reward_Res *recv);

};

#endif
