#ifndef _SERVERCOMMAND_H_
#define _SERVERCOMMAND_H_

#include "Command.h"
#include "CommonType.h"

namespace Cmd 
{
    /////////////////////////////////////////////////////////////
    //服务器初始化 START CMD_SERVER_INIT
    //////////////////////////////////////////////////////////////

    struct ServerInfoEx : public ServerInfo
    {
        uint32_t gameServerId;

        ServerInfoEx()
        {
            gameServerId = 0;
        }

        ServerInfoEx &operator =(const ServerInfoEx &rhs)
        {
            memcpy(this, &rhs, sizeof(ServerInfoEx));

            return *this;
        }

		ServerInfoEx& operator =(const ServerInfo& rhs)
		{
			memcpy(this, &rhs, sizeof(ServerInfo));

			return *this;
		}

		void Clear()
		{
			bzero(this, sizeof(ServerInfoEx));
		}
    };

    struct ServerSimpleInfo
    {
        uint32_t serverType;
        uint32_t serverId;
        uint32_t gameServerId;

        ServerSimpleInfo()
        {
            serverId = 0;
            serverType = 0;
            gameServerId = 0;
        }
    };

    const uint32_t PARA_SERVER_REGIST_REQ = SERVERCOMMAND + 1;

    struct t_Server_Regist_Req : t_NullCmd 
    {
        ServerInfoEx info;

        t_Server_Regist_Req() : t_NullCmd(CMD_SERVER_INIT, PARA_SERVER_REGIST_REQ)
        {
        }
    };

    const uint32_t PARA_SERVER_REGIST_RES = SERVERCOMMAND + 2;

    struct t_Server_Regist_Res : t_NullCmd 
    {
        //res 1 success res != 1 error
        uint32_t res;
        ServerInfoEx info;

        t_Server_Regist_Res()  : t_NullCmd(CMD_SERVER_INIT, PARA_SERVER_REGIST_RES)
        {
            res = 0;
        }
    };

    const uint32_t PARA_SERVER_INFO_NOTIFY = SERVERCOMMAND + 3;

    struct t_Server_Info_Notify : t_NullCmd 
    {
        uint32_t count;
        uint32_t len;
        char data[1];

        t_Server_Info_Notify() : t_NullCmd(CMD_SERVER_INIT, PARA_SERVER_INFO_NOTIFY)
        {
            count = 0;
            len = 0;
        }

        inline uint32_t Size()
        {
            return sizeof(t_Server_Info_Notify) + len;
        }
    };

    const uint32_t PARA_SERVER_UNREGIST_NOTIFY = SERVERCOMMAND + 4;

    struct t_Server_UnRegist_Notify : t_NullCmd 
    {
        uint32_t serverId;
        uint32_t serverType;

        t_Server_UnRegist_Notify() : t_NullCmd(CMD_SERVER_INIT, PARA_SERVER_UNREGIST_NOTIFY)
        {
            serverId = 0;
            serverType = 0;
        }
    };

    const uint32_t PARA_SERVER_LOAD_NOTIFY = SERVERCOMMAND + 5;

    struct t_Server_Load_Notify : t_NullCmd
    {
		uint32_t serverId;
		uint32_t serverType;
        uint32_t loadInfo;

        t_Server_Load_Notify() : t_NullCmd(CMD_SERVER_INIT, PARA_SERVER_LOAD_NOTIFY)
        {
            loadInfo = 0;
        }
    };

    //Register ChatMessage Channel
    const uint32_t PARA_REGIST_CHATMESSAGE_CHANNEL_REQ = SERVERCOMMAND + 6;

    struct t_Regist_ChatMessage_Channel_Req : t_NullCmd {


        t_Regist_ChatMessage_Channel_Req() : t_NullCmd(CMD_SERVER_INIT, PARA_REGIST_CHATMESSAGE_CHANNEL_REQ)
        {

        }
    };

    const uint32_t PARA_REGIST_CHATMESSAGE_CHANNEL_RES = SERVERCOMMAND + 7;

    struct t_Regist_ChatMessage_Channel_Res : t_NullCmd {
        uint32_t ret; // 1 seccuss

        t_Regist_ChatMessage_Channel_Res() : t_NullCmd(CMD_SERVER_INIT, PARA_REGIST_CHATMESSAGE_CHANNEL_RES)
        {
            ret = 0;
        }
    };

    const uint32_t PARA_HOLDSERVER_NOTIFY = SERVERCOMMAND + 8;

    struct t_HoldServer_Notify : t_NullCmd {
        uint32_t count;
        uint32_t len;
        char data[1];

        t_HoldServer_Notify() : t_NullCmd(CMD_SERVER_INIT, PARA_HOLDSERVER_NOTIFY)
        {
            count = 0;
            len = 0;
        }

        inline uint32_t Size()
        {
            return sizeof(t_HoldServer_Notify) + len;
        }
    };

    const uint32_t PARA_SERVER_INIT_TEST_MSG = SERVERCOMMAND + 11;

    struct t_ServerInit_Test_Msg : t_NullCmd {
        uint32_t serverId;

        t_ServerInit_Test_Msg() : t_NullCmd(CMD_SERVER_INIT, PARA_SERVER_INIT_TEST_MSG)
        {
            serverId = 0;
        }


    };

    const uint32_t PARA_SERVER_NOTIFY_REREGIST_MATCH = SERVERCOMMAND + 13;

    struct t_Server_Notify_Notify_RegistMatch : t_NullCmd {

		t_Server_Notify_Notify_RegistMatch() : t_NullCmd(CMD_SERVER_INIT, PARA_SERVER_NOTIFY_REREGIST_MATCH)
        {

        }

    };

    const uint32_t PARA_SERVER_REQ_PROXYSERVER = SERVERCOMMAND + 14;

    struct t_Server_Req_ProxyServer : t_NullCmd {

        t_Server_Req_ProxyServer() : t_NullCmd(CMD_SERVER_INIT, PARA_SERVER_REQ_PROXYSERVER)
        {

        }

    };

	const uint32_t PARA_SERVER_NOTIFY_REREGIST_LOGIC = SERVERCOMMAND + 15;

	struct t_Server_Notify_RegistLogic : t_NullCmd {

		t_Server_Notify_RegistLogic() : t_NullCmd(CMD_SERVER_INIT, PARA_SERVER_NOTIFY_REREGIST_LOGIC)
		{

		}

	};

	const uint32_t PARA_AGENT_SCENEID_NOTIFY = SERVERCOMMAND + 16;

	struct t_Agent_SceneId_Notify : t_NullCmd
	{
		uint32_t serverId = 0;
		uint32_t count = 0;
		uint32_t len = 0;
		char data[1];

		t_Agent_SceneId_Notify() : t_NullCmd(CMD_SERVER_INIT, PARA_AGENT_SCENEID_NOTIFY)
		{
		}

		inline uint32_t Size()
		{
			return sizeof(t_Agent_SceneId_Notify) + len;
		}
	};

    /////////////////////////////////////////////////////////////
    //服务器初始化 END CMD_SERVER_INIT
    //////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////
    //聊天 START CMD_CHAT_MESSAGE
    //////////////////////////////////////////////////////////////

    //Send ChatMessage Channel
    const uint32_t PARA_SERVER_SEND_CHATMESSAGE_REQ = SERVERCOMMAND + 1;

    struct t_Server_Send_ChatMessage_Req : t_NullCmd {
        char channel[MAX_CHANNEL_NAME_LENGHT];
        char content[MAX_CHAT_MESSAGE_LENGHT];    

        t_Server_Send_ChatMessage_Req() : t_NullCmd(CMD_CHAT_MESSAGE, PARA_SERVER_SEND_CHATMESSAGE_REQ)
        {
            bzero(channel, sizeof(channel));
            bzero(content, sizeof(content));
        }
    };

    /////////////////////////////////////////////////////////////
    //聊天 END CMD_CHAT_MESSAGE
    //////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////
    //转发 START CMD_MESSAGE_TRANS
    //////////////////////////////////////////////////////////////

    const uint32_t PARA_SERVER_SEND_TRANS_MSG = SERVERCOMMAND + 1;

    struct t_Server_Send_Trans_Msg : t_NullCmd {
        uint64_t uid;
        ServerSimpleInfo targetServer;
        ServerSimpleInfo srcServer;
        uint64_t cmdUid;
        uint32_t dataLen;
        uint8_t data[1];

        t_Server_Send_Trans_Msg() : t_NullCmd(CMD_MESSAGE_TRANS, PARA_SERVER_SEND_TRANS_MSG)
        {
            uid = 0;
            cmdUid = 0;
            dataLen = 0;
        }

        uint32_t Size()
        {
            return sizeof(t_Server_Send_Trans_Msg) + dataLen;
        }
    };

    const uint32_t PARA_SERVER_SEND_TRANS_UDP_MSG = SERVERCOMMAND + 2;

    struct t_Server_Send_Trans_Udp_Msg : t_NullCmd {
        uint64_t uid;
        ServerSimpleInfo targetServer;
        ServerSimpleInfo srcServer;
        uint64_t cmdUid;
        uint32_t dataLen;
        uint8_t data[1];

        t_Server_Send_Trans_Udp_Msg() : t_NullCmd(CMD_MESSAGE_TRANS, PARA_SERVER_SEND_TRANS_UDP_MSG)
        {
            uid = 0;
            cmdUid = 0;
            dataLen = 0;
        }

        uint32_t Size()
        {
            return sizeof(t_Server_Send_Trans_Udp_Msg) + dataLen;
        }
    };

    /////////////////////////////////////////////////////////////
    //转发 END CMD_MESSAGE_TRANS
    //////////////////////////////////////////////////////////////
};

#endif

