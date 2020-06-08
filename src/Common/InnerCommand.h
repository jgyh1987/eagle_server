/* 
 * File:   InnerCommand.h
 */

#ifndef _INNERCOMMAND_H_
#define    _INNERCOMMAND_H_

#include "CommonType.h"
#include "Command.h"

namespace Cmd 
{
    struct t_InnerNullCmd : public t_NullCmd
    {
        t_InnerNullCmd(const uint32_t para = PARA_NULL)
            :t_NullCmd(CMD_INNER_MESSAGE, para)
        {
        }
    };

    //verify SESSION
    const uint32_t PARA_VERIFY_SESSOIN_REQ = INNERCOMMAND + 1;

    struct t_Verify_Session_Req : t_InnerNullCmd {
        char account[MAX_ACCOUNT_LENGHT];
        char openid[MAX_ACCOUNT_LENGHT];
        char openkey[MAX_SDK_OPENKEY_LENGHT];
        uint32_t sdkType;
        uint32_t accountId;
        uint32_t vistor;

        t_Verify_Session_Req() : t_InnerNullCmd(PARA_VERIFY_SESSOIN_REQ)
        {
            bzero(account, sizeof(account));
            bzero(openid, sizeof(openid));
            bzero(openkey, sizeof(openkey));
            sdkType = 0;
            vistor = 0;
        }
    };
}

#endif    /* _INNERCOMMAND_H_ */

