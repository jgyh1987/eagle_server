#ifndef _EAGLE_ERROR_H_ 
#define    _EAGLE_ERROR_H_


//

enum RETURN_TYPE
{
    RETURN_TYPE_NONE,

    NO_SESSION = 2,    //
    NO_ACCOUNT = 3,    //
    PASS_ERROR = 4,    //
    SESSION_TIME_OUT = 5,    //
    SESSION_ERROR = 6,    //
    INPUT_CHARACTER_LENGTH_MAX = 7,        //
    REGIST_ACCOUNT_ERROR = 8,    //
    MYSQL_WRITE_ERROR = 9,        //
    ACCOUNT_ALREADY_EXISTS = 10,    //
    ACCOUNT_ASIC_ERROR = 11,        //
    NAME_ALREADY_EXISTS = 12,        //
    SDKTYPE_ERROR = 13,        //
    NO_LOGIN_ERROR = 14,        //
    NO_SERVERID_ERROR = 15,        //
    NO_GM_AUTH_ERROR = 16,        //
	SERVER_REGIST_ERROR = 17, //服务器注册失败

    PLAYER_DATA_ERROR = 99,        //

    SCENE_SERVER_ERROR = 100,    //
    CREATE_PLAYER_ERROR = 101,    //
    GOLD_NOT_ENOUGH = 102,
    MONEY_NOT_ENOUGH = 103,
    ITEM_NOT_ENOUGH = 104,
    BAG_IS_FULL = 105,
    LEVEL_NOT_ENOUGH = 106,        //
    EQUIP_IS_HAVEED = 107,        //
    VIP_LELVE_NOT_ENOUGH = 108,    //
    MAX_ROLE_ERROR = 118,        //
    NO_ROLEINFO = 121,        //
    REPEATED_LOGIN_LOGIC    = 123,        //
    PLAYER_DIE            =    124,    //
    PLAYER_ROLESOLT_BUY_MAX = 125,    //

    CONFIG_ERROR = 999,            //

    CLIENT_ERROR = 1000,    //1000~1999client msg


    //10000 ~ 20000 
    WORLD_WNSSERVER_CONNECT_ERROR = 10000, //
    WORLD_MATCH_EXIST              = 10001,    //
    WORLD_FIGHT_SERVER_ERROR      = 10002,    //
    WORLD_FIGHT_SERVER_CREATING   = 10003,    // 
    WORLD_FIGHT_CREATE_ERROR    = 10004,    //
    WORLD_MATCH_NOT_FIND        = 10005,    //
    WORLD_FIGHT_DUNGEON_NOT_FIND = 10006,    //
    WORLD_FIGHT_PLAYER_CREATE_ERROR = 10007, //
    WORLD_FIGHT_PLAYER_ERROR        = 10008,    //
    WORLD_MATCH_CREATE_ERROR = 10009,
    WORLD_TEAMER_HAVE_MATCH = 10010, 


};

//
enum E_ROLESTATUS_TYPE
{
    ROLESTATUS_DEFUAL = 0,            //
    ROLESTATUS_DELETE = 1,                //
};


#endif    

