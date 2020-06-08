#ifndef _LOGICDATACOMMAND_H_
#define _LOGICDATACOMMAND_H_

#include "CommonType.h"
#include "Command.h"
#include "PlayerInfo.h"
#include "PlayerDataInfo.h"

namespace Cmd 
{
    /////////////////////////////////////////////////////////////
    //游戏服务器玩家信息数据 START CMD_LOGIC_PLAYERINFO
    //////////////////////////////////////////////////////////////
        
    const uint32_t PARA_DATA_SELECT_SERVER = LOGICDATACOMMAND + 2;

    struct t_Data_Select_Server : t_NullCmd {
        uint32_t serverType;
        uint32_t serverId;
        uint64_t playerId; 

        t_Data_Select_Server() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_SELECT_SERVER)
        {
            serverType = 0;
            serverId = 0;
            playerId = 0;
        }
    };

    //Get Player Info
    const uint32_t PARA_DATA_GET_PLAYERINFO_REQ = LOGICDATACOMMAND + 3;

    struct t_Data_Get_PlayerInfo_Req : t_NullCmd {
        PlayerInfoBase playerInfo;
        uint32_t funType; //大于0 表示拉取的是离线玩家
        uint64_t srcPlayer; //if funType > 0 then useful 

        t_Data_Get_PlayerInfo_Req() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_GET_PLAYERINFO_REQ)
        {
            funType = 0;
            srcPlayer = 0;
        }
    };

    const uint32_t PARA_DATA_GET_PLAYERINFO_RES = LOGICDATACOMMAND + 4;

    struct t_Data_Get_PlayerInfo_Res : t_NullCmd {
        //ret 0 角色不存在 需要创建
        uint32_t funType; //大于0 表示拉取的是离线玩家
        uint64_t srcPlayer; //if funType > 0 then useful 
        uint32_t ret;
        PlayerInfoBase playerinfo;
        uint32_t playerDataLen;
        uint32_t allBinarrayLength;
        uint8_t data[1];

        t_Data_Get_PlayerInfo_Res() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_GET_PLAYERINFO_RES)
        {
            funType = 0;
            srcPlayer = 0;
            ret = 0;   
            playerDataLen = 0;
            allBinarrayLength = 0;
        }

        uint32_t Size()
        {
            return sizeof(t_Data_Get_PlayerInfo_Res) + allBinarrayLength;
        }
    };

    //Create Player Info
    const uint32_t PARA_DATA_CREATE_ROLEINFO_REQ = LOGICDATACOMMAND + 5;

    struct t_Data_Create_RoleInfo_Req : t_NullCmd {
        RoleInfoBase info;
        uint32_t gameserverId;

        t_Data_Create_RoleInfo_Req() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_CREATE_ROLEINFO_REQ)
        {
            gameserverId = 0;
        }
    };

    const uint32_t PARA_DATA_CREATE_ROLEINFO_RES = LOGICDATACOMMAND + 6;

    struct t_Data_Create_RoleInfo_Res : t_NullCmd {
        // ret 1 create success  2 account is haved 3 create param error   4 login error
        uint32_t ret;
        RoleInfoBase roleinfo;

        t_Data_Create_RoleInfo_Res() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_CREATE_ROLEINFO_RES)
        {
            ret = 0;   
        }
    };

    //save player data
    const uint32_t PARA_DATA_SAVE_ROLEINFO_REQ = LOGICDATACOMMAND + 7;

    struct t_Data_Save_RoleInfo_Req : t_NullCmd {
		PlayerInfoBase playerinfo;
        uint32_t serverType;
        uint32_t serverId;
        RoleInfoBase roleInfo;
        uint32_t playerDataLen;
        uint32_t roleDataLen;
        uint8_t data[1];

        t_Data_Save_RoleInfo_Req() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_SAVE_ROLEINFO_REQ)
        {
            playerDataLen = 0;
            roleDataLen = 0;
            serverType = 0;
            serverId = 0;
        }

        uint32_t Size()
        {
            return sizeof(t_Data_Save_RoleInfo_Req) + roleDataLen + playerDataLen;
        }
    };

    const uint32_t PARA_DATA_SAVE_ROLEINFO_RES = LOGICDATACOMMAND + 8;

    struct t_Data_Save_RoleInfo_Res : t_NullCmd {
        uint32_t ret; //1 为成功
        uint64_t playerId;

        t_Data_Save_RoleInfo_Res() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_SAVE_ROLEINFO_RES)
        {
            ret = 0;
            playerId = 0;
        }
    };

    //save player data
    const uint32_t PARA_DATA_SAVE_PLAYERINFO_REQ = LOGICDATACOMMAND + 9;

    struct t_Data_Save_PlayerInfo_Req : t_NullCmd {
		PlayerInfoBase playerinfo;
        uint32_t serverId;
		uint32_t serverType;
        uint32_t allBinarrayLength;
        uint8_t data[1];

        t_Data_Save_PlayerInfo_Req() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_SAVE_PLAYERINFO_REQ)
        {  
            allBinarrayLength = 0;
            serverType = 0;
            serverId = 0;
        }

        uint32_t Size()
        {
            return sizeof(t_Data_Save_PlayerInfo_Req) + allBinarrayLength;
        }
    };

    const uint32_t PARA_DATA_SAVE_PLAYERINFO_RES = LOGICDATACOMMAND + 10;

    struct t_Data_Save_PlayerInfo_Res : t_NullCmd {
        uint32_t ret; //1 为成功
        uint64_t playerId;

        t_Data_Save_PlayerInfo_Res() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_SAVE_PLAYERINFO_RES)
        {
           ret = 0;
           playerId = 0;
        }
    };

    //get role all info(选择角色进入游戏获得角色所有数据)
    const uint32_t PARA_DATA_GETROLEINFO_REQ = LOGICDATACOMMAND + 11;

    struct t_Data_GetRoleInfo_Req : t_NullCmd {
        uint64_t playerId;
        uint64_t roleId;
        uint32_t funType; //大于0 表示拉取的是离线玩家
        uint64_t srcPlayer; //if funType > 0 then useful 

        t_Data_GetRoleInfo_Req() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_GETROLEINFO_REQ)
        {
            roleId = 0;
            playerId = 0;
            funType = 0;
            srcPlayer = 0;
        }
    };

    const uint32_t PARA_DATA_GETROLEINFO_RES = LOGICDATACOMMAND + 12;

    struct t_Data_GetRoleInfo_Res : t_NullCmd {
        uint32_t ret;
        uint32_t funType; //大于0 表示拉取的是离线玩家
        uint64_t srcPlayer; //if funType > 0 then useful 
		RoleInfoBase roleInfo;
        uint32_t itemsLen;
        uint32_t itemsCount;
        uint32_t allBinarrayLength;
        uint8_t data[1];

        t_Data_GetRoleInfo_Res() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_GETROLEINFO_RES)
        {
            ret = 0;
            funType = 0;
            srcPlayer = 0;
            allBinarrayLength = 0;
            itemsLen = 0;
            itemsCount = 0;
        }

        uint32_t Size()
        {
            return sizeof(t_Data_GetRoleInfo_Res) + allBinarrayLength + itemsLen;
        }
    };


    //delete role
    const uint32_t PARA_DATA_DELETEROLE_REQ = LOGICDATACOMMAND + 13;

    struct t_Data_DeleteRole_Req : t_NullCmd {
        uint32_t slot;
        uint64_t playerId;
        uint64_t roleId;
        char account[MAX_ACCOUNT_LENGHT];
        t_Data_DeleteRole_Req() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_DELETEROLE_REQ)
        {
            bzero(account, sizeof(account));
            roleId = 0;
            slot = 0;
        }
    };

    const uint32_t PARA_DATA_DELETEROLE_RES = LOGICDATACOMMAND + 14;

    struct t_Data_DeleteRole_Res : t_NullCmd {
        uint32_t slot;
        uint32_t ret;
        uint64_t playerId;
        uint64_t roleId;
        t_Data_DeleteRole_Res() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_DELETEROLE_RES)
        {
            ret = 0;
            roleId = 0;
            slot = 0;
            playerId = 0;
        }
    };

    const uint32_t PARA_DATA_UPDATE_ITEM_REQ = LOGICDATACOMMAND + 15;

    struct t_Data_Update_Item_Req : t_NullCmd {
        uint64_t playerId;
        uint32_t serverType;
        uint32_t serverId;
        uint64_t roleId;
        uint32_t itemsCount;
        uint32_t itemsDataLen;
        uint8_t data[1];

        t_Data_Update_Item_Req() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_UPDATE_ITEM_REQ)
        {
            playerId = 0;
            serverType = 0;
            serverId = 0;
            roleId = 0;
            itemsCount = 0;
            itemsDataLen = 0;
        }

        uint32_t Size()
        {
            return sizeof(t_Data_Update_Item_Req) + itemsDataLen;
        }
    };

    const uint32_t PARA_DATA_UPDATE_ITEM_RES = LOGICDATACOMMAND + 16;

    struct t_Data_Update_Item_Res: t_NullCmd {
        uint32_t ret;
        uint64_t playerId;
        uint64_t roleId;
        uint32_t itemsCount;
        uint32_t itemsDataLen;
        uint8_t data[1];

        t_Data_Update_Item_Res() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_UPDATE_ITEM_RES)
        {
            ret = 0;
            playerId = 0;
            roleId = 0;
            itemsCount = 0;
            itemsDataLen = 0;
        }

        uint32_t Size()
        {
            return sizeof(t_Data_Update_Item_Res) + itemsDataLen;
        }
    };


    //   const uint32_t PARA_DATA_SEND_MAIL_REQ = LOGICDATACOMMAND + 11;

    //   struct t_Data_Send_Mail_Req : t_NullCmd {
    //    char account[MAX_ACCOUNT_LENGHT];
    //    char name[MAX_PLAYER_NAME];
    //    uint64_t playerId;        
    //    uint64_t sendPlayerId;
    //       ServerMailInfo mailinfo;
    //    uint32_t isGM;
    //    
    //       t_Data_Send_Mail_Req() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_SEND_MAIL_REQ)
    //       {
    //        isGM = 0;
    //        playerId = 0;
    //        sendPlayerId = 0;
    //        memset(account, 0, MAX_ACCOUNT_LENGHT);
    //        memset(name, 0, MAX_PLAYER_NAME);
    //       }
    //   };

    //const uint32_t PARA_DATA_SEND_MAIL_RES = LOGICDATACOMMAND + 12;

    //   struct t_Data_Send_Mail_Res : t_NullCmd {
    //       uint32_t ret; //1 为成功    0 没有角色 3 插入失败
    //    uint64_t playerId;
    //    uint64_t sendPlayerId;
    //    ServerMailInfo mailinfo;
    //    uint32_t isGM;

    //       t_Data_Send_Mail_Res() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_SEND_MAIL_RES)
    //       {
    //        isGM = 0;
    //        ret = 0;
    //        sendPlayerId = 0;
    //        playerId = 0;
    //       }
    //   };

    ////Delete Mail
    //   const uint32_t PARA_DATA_DELETE_MAIL_REQ = LOGICDATACOMMAND + 13;

    //   struct t_Data_Delete_Mail_Req : t_NullCmd {
    //    uint64_t playerId;
    //    uint32_t num;
    //    uint32_t mailId[MAIL_MAX_COUNT];
    //       
    //    
    //       t_Data_Delete_Mail_Req() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_DELETE_MAIL_REQ)
    //       {
    //        playerId = 0;
    //        num = 0;
    //        memset(mailId, 0, sizeof(mailId));
    //       }
    //   };

    ////Get Mail List
    //const uint32_t PARA_DATA_GET_MAIL_LIST_REQ = LOGICDATACOMMAND + 14;

    //   struct t_Data_Get_Mail_List_Req : t_NullCmd {
    //    uint64_t playerId;
    //    
    //       t_Data_Get_Mail_List_Req() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_GET_MAIL_LIST_REQ)
    //       {
    //        playerId = 0;
    //       }
    //   };

    //const uint32_t PARA_DATA_GET_MAIL_LIST_RES = LOGICDATACOMMAND + 15;

    //   struct t_Data_Get_Mail_List_Res : t_NullCmd {
    //       uint32_t num; //
    //    uint64_t playerId;
    //    char data[1];

    //       t_Data_Get_Mail_List_Res() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_GET_MAIL_LIST_RES)
    //       {
    //        num = 0;
    //        playerId = 0;
    //       }

    //    uint32_t Size()
    //    {
    //        return sizeof(t_Data_Get_Mail_List_Res) + num * sizeof(ServerMailInfo);
    //    }
    //   };

    //const uint32_t PARA_DATA_SEND_MAIL_TO_ALL_REQ = LOGICDATACOMMAND + 16;

    //   struct t_Data_Send_Mail_To_All_Req : t_NullCmd {
    //       ServerMailInfo mailinfo;
    //    
    //       t_Data_Send_Mail_To_All_Req() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_SEND_MAIL_TO_ALL_REQ)
    //       {
    //       }
    //   };

    //const uint32_t PARA_DATA_SEND_MAIL_TO_ALL_RES = LOGICDATACOMMAND + 17;

    //   struct t_Data_Send_Mail_To_All_Res : t_NullCmd {
    //       uint32_t ret; //1 SUCCESS 0 ERROR
    //    
    //       t_Data_Send_Mail_To_All_Res() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_SEND_MAIL_TO_ALL_RES)
    //       {
    //       }
    //   };

    //log info
    const uint32_t PARA_DATA_SAVE_RECOUNT_LOGINFO = LOGICDATACOMMAND + 999;

    struct t_SendCmdToData_LogInfo : t_NullCmd 
    {
        uint64_t playerId;
        uint16_t type;
        uint16_t level;
        uint32_t time;
        char name[MAX_PLAYER_NAME];
        char account[MAX_ACCOUNT_LENGHT];
        uint32_t len; ///include '\0'
        char info[1];

        t_SendCmdToData_LogInfo() : t_NullCmd(CMD_LOGIC_PLAYERINFO, PARA_DATA_SAVE_RECOUNT_LOGINFO)
        {
            playerId = 0;
            type = 0;
            level = 0;
            time = 0;
            bzero(name, sizeof(name));
            bzero(account, sizeof(account));
            len = 0;
        }

        uint32_t Size() const
        {
            return sizeof(*this) + len;
        }
    };
    //////////////////////////////////////////////////////////////
    //游戏服务器玩家信息数据 END CMD_LOGIC_PLAYERINFO
    //////////////////////////////////////////////////////////////

};

#endif

