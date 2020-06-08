#ifndef _LOGICSERVERCOMMAND_H_
#define _LOGICSERVERCOMMAND_H_

#include "CommonType.h"
#include "Command.h"
#include "PlayerInfo.h"

namespace Cmd 
{
    //////////////////////////////////////////////////////////////
    //登录指令 START CMD_LOGIC_PLAYERINFO
    //////////////////////////////////////////////////////////////
    //GET ACCOUNT
    const uint32_t PARA_GET_PLAYERINFO_REQ = LOGICGATECOMMAND + 1;

    struct t_Get_PlayerInfo_Req : t_NullCmd {
        char account[MAX_ACCOUNT_LENGHT];

        t_Get_PlayerInfo_Req() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_GET_PLAYERINFO_REQ)
        {
            bzero(account, sizeof(account));
        }
    };

    const uint32_t PARA_GET_PLAYERINFO_RES = LOGICGATECOMMAND + 2;

    struct t_Get_PlayerInfo_Res : t_NullCmd {
        //ret 0 no player
        uint32_t ret;
        PlayerInfoBase playerinfo;

        t_Get_PlayerInfo_Res() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_GET_PLAYERINFO_RES)
        {
            ret = 0;
        }

    };

    const uint32_t PARA_PLAYER_LEAVE_NOTIFY = LOGICGATECOMMAND + 3;

    struct t_Player_Leave_Notify : t_NullCmd {
        uint64_t playerId;

        t_Player_Leave_Notify() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_PLAYER_LEAVE_NOTIFY)
        {
            playerId = 0;
        }
    };

    const uint32_t PARA_PLAYER_KICK_NOTIFY = LOGICGATECOMMAND + 4;

    struct t_Player_Kick_Notify : t_NullCmd {
        //
        uint32_t ret;        //踢出原因
        uint64_t playerId;        //踢出原因
        
        t_Player_Kick_Notify() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_PLAYER_KICK_NOTIFY)
        {
            playerId = 0;
            ret = 0;
        }
    };

    ///////////////////////////////////////////////////////


    const uint32_t PARA_ROLE_ENTER_SCENE = LOGICGATECOMMAND + 11;

    struct t_Role_Enter_Scene : t_NullCmd {

        uint64_t playerId;
        uint32_t len;
        uint8_t data[1];

        t_Role_Enter_Scene() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_ROLE_ENTER_SCENE)
        {
            playerId = 0;
            len = 0;
        }

        uint32_t Size()
        {
            return sizeof(t_Role_Enter_Scene) + len;
        }
    };

    //////////////////////////////////////////////////////////////
    //登录指令 END CMD_LOGIC_PLAYERINFO
    //////////////////////////////////////////////////////////////
};

#endif

