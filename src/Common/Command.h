// =====================================================================================
// 
//       Filename:  Command.h
// 
//    Description:  消息command定义
// 
// =====================================================================================
#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "NullCmd.h"

CMD_NAMESPACE_BEGIN
    const uint32_t CMD_SERVER_INIT = 1; //服务器初始化
    const uint32_t CMD_MESSAGE_TRANS = 2; //消息转发
    const uint32_t CMD_INNER_MESSAGE = 3;    //单个服务器内部线程消息
    const uint32_t CMD_LOGIN_SERVER = 4; //登录服务器数据
    const uint32_t CMD_LOGIC_PLAYERINFO = 5; //游戏服务器玩家信息数据
    const uint32_t CMD_LOGIN_LOGIC = 6; //登陆服务器和游戏服务器之间消息
    const uint32_t CMD_CHAT_MESSAGE = 7; //CHAT MESSAGE
    const uint32_t CMD_FRIEND_MESSAGE = 8;    //FRIEND MESSAGE
    const uint32_t CMD_WORLD_MESSAGE = 13;    //WORLD MESSAGE
    const uint32_t CMD_PT_MESSAGE = 30;    //PT MESSAGE
    
    

CMD_NAMESPACE_END

enum SERVER_TYPE
{
    SERVER_TYPE_NONE = 0,
    SERVER_TYPE_LOGIN_DATA = 1,
    SERVER_TYPE_LOGIN_SERVER = 2,
    SERVER_TYPE_LOGIC_DATA = 3,
    SERVER_TYPE_LOGIC_SERVER = 4,
    SERVER_TYPE_LOGIC_GATEWAY = 5,
    SERVER_TYPE_CHAT_SERVER = 6,
	SERVER_TYPE_LOG_DATA = 7,
    SERVER_TYPE_FRIENDGUILD_SERVER = 8,

    SERVER_TYPE_CENTRAL_SERVER = 20,
    SERVER_TYPE_PROXY_SERVER = 21,
    SERVER_TYPE_WMATCH_SERVER = 22,
    SERVER_TYPE_WGATE_SERVER = 23,
    SERVER_TYPE_WGAME_SERVER = 24,

    SERVER_TYPE_MAX,

    CLIENT_TYPE = 1000,
    CLIENT_BROADCAST_TYPE = 1001
};

#define SingleProxyConnectServerType(type) (SERVER_TYPE_WGAME_SERVER == type || SERVER_TYPE_WGATE_SERVER == type || SERVER_TYPE_CHAT_SERVER == type || SERVER_TYPE_LOGIC_SERVER == type || SERVER_TYPE_LOGIC_DATA == type || SERVER_TYPE_LOG_DATA == type)

#define SERVERCOMMAND            1000
#define LOGICGATECOMMAND        2000
#define LOGINDATACOMMAND        3000
#define LOGICDATACOMMAND        4000
#define GATECHATCOMMAND            5000
#define LOGICLOGINCOMMAND        6000

#define INNERCOMMAND            11000
#define WORLDCOMMAND            13000

#endif
