#ifndef _LOGINSERVERCOMMAND_H_
#define _LOGINSERVERCOMMAND_H_

#include "CommonType.h"
#include "Command.h"

namespace Cmd 
{
    //////////////////////////////////////////////////////////////
    // START CMD_LOGIN_SERVER
    //////////////////////////////////////////////////////////////

    //REGIST ACCOUNT
    const uint32_t PARA_REGIST_ACCOUNT_REQ = LOGINDATACOMMAND + 1;

    struct t_Regist_Account_Req : t_NullCmd {
        char account[MAX_ACCOUNT_LENGHT];
        char passwd[MAX_PASSWD_LENGHT];

        t_Regist_Account_Req() : t_NullCmd(CMD_LOGIN_SERVER, PARA_REGIST_ACCOUNT_REQ)
        {
            bzero(account, sizeof(account));
            bzero(passwd, sizeof(passwd));
        }
    };

    const uint32_t PARA_REGIST_ACCOUNT_RES = LOGINDATACOMMAND + 2;

    struct t_Regist_Account_Res : t_NullCmd {
        //ret = 1
        uint32_t ret;
        char account[MAX_ACCOUNT_LENGHT];

        t_Regist_Account_Res() : t_NullCmd(CMD_LOGIN_SERVER, PARA_REGIST_ACCOUNT_RES)
        {
            ret = 0;
            bzero(account, sizeof(account));
        }
    };

    const uint32_t PARA_LOGIN_ACCOUNT_REQ = LOGINDATACOMMAND + 3;
    //
    struct t_Login_Account_Req : t_NullCmd {
        char account[MAX_ACCOUNT_LENGHT];
        char sdkId[MAX_ACCOUNT_LENGHT];
        char token[MAX_SDK_OPENKEY_LENGHT];
        char mac[MAX_PASSWD_LENGHT];
        char model[MAX_PASSWD_LENGHT];
        char platfrom[MAX_PASSWD_LENGHT];
        uint32_t sdkType;


        t_Login_Account_Req() : t_NullCmd(CMD_LOGIN_SERVER, PARA_LOGIN_ACCOUNT_REQ)
        {
            sdkType = SDK_TYPE_NONE;
            bzero(account, sizeof(account));
            bzero(sdkId, sizeof(sdkId));
            bzero(token, sizeof(token));
            bzero(mac, sizeof(mac));
            bzero(model, sizeof(model));
            bzero(platfrom, sizeof(platfrom));
        }
    };


    const uint32_t PARA_LOGIN_SESSIONACCOUNT_RES = LOGINDATACOMMAND + 4;
    //��½�˺ŷ��� LoginSessionAccountRes
    struct t_Login_SessionAccount_Res : t_NullCmd {
        uint32_t ret;
        char account[MAX_ACCOUNT_LENGHT];

        t_Login_SessionAccount_Res() : t_NullCmd(CMD_LOGIN_SERVER, PARA_LOGIN_SESSIONACCOUNT_RES)
        {
            ret = 0;
            bzero(account, sizeof(account));
        }
    };




    //////////////////////////////////////////////////////////////
    //��¼ָ�� END CMD_LOGIN_SERVER
    //////////////////////////////////////////////////////////////
};

#endif

