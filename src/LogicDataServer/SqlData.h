#ifndef _DATAS_SQLSDATA_H_
#define _DATAS_SQLSDATA_H_ 

#include "datetime.h"
#include "mystring.h"
#include "row.h"
#include <ssqls.h>

//logic player info
sql_create_complete_13(SqlPlayerInfo,
        1,
        0,
        mysqlpp::sql_bigint_unsigned,            playerId,                "PLAYERID",
        mysqlpp::sql_int_unsigned,            vipLevel,                "VIPLEVEL",    
        mysqlpp::sql_char,            account,                "ACCOUNT",    
        mysqlpp::sql_char,            model,                    "MODEL",    
        mysqlpp::sql_bigint_unsigned,            lastoffTime,            "LASTOFFLINETIME",
        mysqlpp::sql_int_unsigned,            sex,                    "SEX",    
        mysqlpp::sql_int_unsigned,            allcharge,                "ALLCHARGE",    
        mysqlpp::sql_int_unsigned,            authority,                "AUTHORITY",    
        mysqlpp::sql_int_unsigned,            isRobot,                "ISROBOT",    
        mysqlpp::sql_char,            platFormId,                "PLATFORMID",    
        mysqlpp::sql_char,            inviteId,                "INVITEID",
        mysqlpp::sql_int_unsigned, roleSolt,                "ROLESOLT",
        mysqlpp::sql_blob,    allbinary,                "ALLBINARY"
        );

//logic player create info
sql_create_complete_6(SqlPlayerCreateInfo,
        1,
        0,
        mysqlpp::sql_bigint_unsigned, playerId,                "PLAYERID",
        mysqlpp::sql_char,            account,                "ACCOUNT",    
        mysqlpp::sql_int_unsigned,            createTime,                "CREATETIME",    
        mysqlpp::sql_char,            createIp,                "CREATEIP",    
        mysqlpp::sql_char,            lastLoginIp,            "LASTLOGINIP",    
        mysqlpp::sql_char,            lastMac,                "LASTMAC"        
        );


//logic role info
sql_create_complete_20(SqlRoleInfo,
    1,
    0,
    mysqlpp::sql_bigint_unsigned, roleId, "ROLEID",
    mysqlpp::sql_bigint_unsigned, playerId, "PLAYERID",
    mysqlpp::sql_int_unsigned, createTime, "CREATETIME",
    mysqlpp::sql_char, name, "NAME",
    mysqlpp::sql_int_unsigned, lastoffTime, "LASTOFFLINETIME",
    mysqlpp::sql_int_unsigned, level, "LEVEL",
    mysqlpp::sql_bigint_unsigned, exp, "EXP",
    mysqlpp::sql_int_unsigned, fight, "FIGHT",
    mysqlpp::sql_int_unsigned, jobId, "JOBID",
    mysqlpp::sql_bigint_unsigned, mapId, "MAPID",
    mysqlpp::sql_int_unsigned, roleStatus, "ROLESTATUS",
    mysqlpp::sql_int_unsigned, functionOpenBitMap, "FUNCTIONOPENBITMAP",
    mysqlpp::sql_int_unsigned, otherFunOpenBitMap, "OTHERFUNOPENBITMAP",
	mysqlpp::sql_bigint_unsigned, x, "x",
	mysqlpp::sql_bigint_unsigned, y, "y",
	mysqlpp::sql_bigint_unsigned, z, "z",
	mysqlpp::sql_bigint_unsigned, dirx, "dirx",
	mysqlpp::sql_bigint_unsigned, diry, "diry",
	mysqlpp::sql_bigint_unsigned, dirz, "dirz",
    mysqlpp::sql_blob, allbinary, "ALLBINARY"
);

// mail
sql_create_complete_11(SqlMail,
        1,
        0,
        mysqlpp::sql_int_unsigned,            mailId,                        "MAILID",    
        mysqlpp::sql_bigint_unsigned,            playerId,                "PLAYERID",
        mysqlpp::sql_char,            account,                "ACCOUNT",    
        mysqlpp::sql_bigint_unsigned,    createTime,                "CREATETIME",
        mysqlpp::sql_int_unsigned,            itemType,                "ITEMTYPE",
        mysqlpp::sql_bigint_unsigned,            itemId,                    "ITEMID",
        mysqlpp::sql_int_unsigned,            itemCount,                "ITEMCOUNT",
        mysqlpp::sql_char,            title,                    "TITLE",
        mysqlpp::sql_char,            content,                "CONTENT",
        mysqlpp::sql_char,            sendName,                "SENDNAME",
        mysqlpp::sql_char,            sendAccount,            "SENDACCOUNT"
        );

// PLAYER_ITEM
sql_create_complete_7(SqlPlayerItem,
    1,
    0,
    mysqlpp::sql_bigint_unsigned, itemId, "ITEMID",
    mysqlpp::sql_bigint_unsigned, roleId, "ROLEID",
    mysqlpp::sql_bigint_unsigned, configId, "CONFIGID",
    mysqlpp::sql_int_unsigned, itemType, "ITEMTYPE",
    mysqlpp::sql_bigint_unsigned, itemCount, "ITEMCOUNT",
    mysqlpp::sql_int_unsigned, bagType, "BAGTYPE",
    mysqlpp::sql_blob, allbinary, "ALLBINARY"
);

//LOG DATA
sql_create_complete_8(SqlLogActionInfo,
        1,
        0,
        mysqlpp::sql_int_unsigned,            id,                "ID",
        mysqlpp::sql_char,                    account,        "ACCOUNT",
        mysqlpp::sql_bigint_unsigned,            playerId,          "PLAYERID",
        mysqlpp::sql_char,                  playerName,     "PLAYERNAME", 
        mysqlpp::sql_int_unsigned,            playerLevel,    "PLAYERLEVEL",
        mysqlpp::sql_int_unsigned,            type,            "TYPE",
        mysqlpp::sql_int_unsigned,            time,            "TIME",
        mysqlpp::sql_char,                  info,           "INFO" 
        );


class DataSsqls
{    
    public:        
        static bool init()        
        {             
            
            SqlPlayerInfo::table("PLAYER_INFO");
            SqlPlayerCreateInfo::table("PLAYER_CREATE_INFO");
            SqlRoleInfo::table("ROLE_INFO");
            SqlMail::table("MAIL");
            SqlPlayerItem::table("PLAYER_ITEM");
            SqlLogActionInfo::table("ACTION_LOG");
            
            return true;
        }
};


#endif

