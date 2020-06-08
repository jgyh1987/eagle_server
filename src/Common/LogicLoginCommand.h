#ifndef _LOGICLOGINCOMMAND_H_
#define _LOGICLOGINCOMMAND_H_

#include "Command.h"
#include "CommonType.h"

namespace Cmd
{
    //////////////////////////////////////////////////////////////
    //同步SESSION START CMD_LOGIN_LOGIC
    //////////////////////////////////////////////////////////////

    //Send Session From LOGIN TO LOGICGATE
    const uint32_t PARA_SEND_SESSION_SYNC = LOGICLOGINCOMMAND + 3;

    struct t_Send_Session_Sync : t_NullCmd {
        char session[MAX_SESSION_LENGHT];
        char account[MAX_ACCOUNT_LENGHT];

        t_Send_Session_Sync() : t_NullCmd(CMD_LOGIN_LOGIC, PARA_SEND_SESSION_SYNC)
        {
            bzero(session, sizeof(session));
            bzero(account, sizeof(account));
        }
    };

    const uint32_t PARA_SEND_SESSION_SYNC_RES = LOGICLOGINCOMMAND + 4;

    struct t_Send_Session_Sync_Res : t_NullCmd {
        char account[MAX_ACCOUNT_LENGHT];

        t_Send_Session_Sync_Res() : t_NullCmd(CMD_LOGIN_LOGIC, PARA_SEND_SESSION_SYNC_RES)
        {
            bzero(account, MAX_ACCOUNT_LENGHT);
        }
    };

    const uint32_t PARA_SEND_SERVER_PLAYERCOUNT_NOTIFY = LOGICLOGINCOMMAND + 5;

    struct t_Send_Server_PlayerCount_Notify : t_NullCmd {
        uint32_t serverId;
        uint32_t playerCount;

        t_Send_Server_PlayerCount_Notify() : t_NullCmd(CMD_LOGIN_LOGIC, PARA_SEND_SERVER_PLAYERCOUNT_NOTIFY)
        {
            serverId = 0;
            playerCount = 0;
        }
    };

    //GET PackageCode
    struct PackageCode
    {
        uint64_t playerId;
        uint32_t serverId;
        uint32_t id;
        char code[MAX_ACCOUNT_LENGHT];
        uint32_t type;
        uint32_t atTime;
        char title[MAIL_TITLE_LENGTH];
        char context[MAIL_CONTENT_LENGTH];
        char items[MAX_ACCOUNT_LENGHT];

        PackageCode()
        {
            memset(this, 0, sizeof(*this));
        }
    };

    const uint32_t PARA_GET_PACKAGECODE_REQ = LOGICLOGINCOMMAND + 6;

    struct t_Get_PackageCode_Req : t_NullCmd {
        char code[MAX_ACCOUNT_LENGHT];
        uint64_t playerId;
        uint32_t serverId;

        t_Get_PackageCode_Req() : t_NullCmd(CMD_LOGIN_LOGIC, PARA_GET_PACKAGECODE_REQ)
        {
            playerId = 0;
            serverId = 0;
            bzero(code, sizeof(code));
        }
    };

    const uint32_t PARA_GET_PACKAGECODE_RES = LOGICLOGINCOMMAND + 7;

    struct t_Get_PackageCode_Res : t_NullCmd {
        //ret = 1 正确 27 已使用
        uint32_t ret;
        PackageCode packageInfo;

        t_Get_PackageCode_Res() : t_NullCmd(CMD_LOGIN_LOGIC, PARA_GET_PACKAGECODE_RES)
        {
            ret = 0;
        }
    };

    const uint32_t PARA_PACKAGECODE_REWARD_RES = LOGICLOGINCOMMAND + 8;

    struct t_PackageCode_Reward_Res : t_NullCmd {
        char code[MAX_ACCOUNT_LENGHT];
        uint64_t playerId;
        uint32_t serverId;
        uint32_t ret;    // 1 SUCCESS 26 该类型礼包已经领过

        t_PackageCode_Reward_Res() : t_NullCmd(CMD_LOGIN_LOGIC, PARA_PACKAGECODE_REWARD_RES)
        {
            playerId = 0;
            serverId = 0;
            bzero(code, sizeof(code));
        }
    };


    //////////////////////////////////////////////////////////////
    //同步SESSION  END CMD_LOGIN_LOGIC
    //////////////////////////////////////////////////////////////
};

#endif

