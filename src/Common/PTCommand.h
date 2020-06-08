#ifndef _PTCOMMAND_H_
#define _PTCOMMAND_H_

#include "CommonType.h"
#include "Command.h"

namespace Cmd 
{
    /////////////////////////////////////////////////////////////
    //平台消息 START CMD_PT_MESSAGE
    //////////////////////////////////////////////////////////////
    const uint32_t PT_MESSAGE_LENGTH_MAX = 4096 - 24;
    const uint32_t PARA_PT_GM_CMD_REQ = 1;

    struct t_PT_GmCmd_Req : t_NullCmd {
        uint32_t len;
        char data[PT_MESSAGE_LENGTH_MAX];

        t_PT_GmCmd_Req() : t_NullCmd(CMD_PT_MESSAGE, PARA_PT_GM_CMD_REQ)
        {
            len = 0;
            memset(data, 0, PT_MESSAGE_LENGTH_MAX);
        }
    };

    const uint32_t PARA_PT_GM_CMD_RES = 2;

    struct t_PT_GmCmd_Res : t_NullCmd {
        uint32_t len;
        char data[PT_MESSAGE_LENGTH_MAX];

        t_PT_GmCmd_Res() : t_NullCmd(CMD_PT_MESSAGE, PARA_PT_GM_CMD_RES)
        {
            len = 0;
            memset(data, 0, PT_MESSAGE_LENGTH_MAX);
        }
    };

    /////////////////////////////////////////////////////////////
    //平台消息 END CMD_PT_MESSAGE
    //////////////////////////////////////////////////////////////
};

#endif

