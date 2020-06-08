#ifndef _NULLCMD_H_
#define _NULLCMD_H_

#define CMD_NAMESPACE_BEGIN namespace Cmd{
#define CMD_NAMESPACE_END  };

CMD_NAMESPACE_BEGIN

const uint32_t CMD_NULL = 0;
const uint32_t PARA_NULL = 0;

    struct t_NullCmd
    {
        uint32_t packets;
        uint32_t cmd;
        uint32_t para;
        t_NullCmd(const uint32_t cmd = CMD_NULL,const uint32_t para = PARA_NULL)
            :packets(0),cmd(cmd),para(para)
        {
        }
    };
    const uint32_t SERVER_PARA_NULL=0;
    struct t_ServerNullCmd :public t_NullCmd
    {
        t_ServerNullCmd()
            :t_NullCmd(CMD_NULL,SERVER_PARA_NULL)
        {
        }
    };
    const uint32_t CLIENT_PARA_NULL =1;
    struct t_ClientNullCmd : public t_NullCmd
    {
        t_ClientNullCmd()
            :t_NullCmd(CMD_NULL,CLIENT_PARA_NULL)
        {
        }
    };

    //Server Info
    struct ServerInfo
    {
        uint32_t serverId;
        uint32_t serverType;
        char serverName[MAX_SERVERNAME_LENGTH];
        char serverIP[MAX_IP_LENGTH];
        uint32_t port;

        ServerInfo()
        {
            bzero(this, sizeof(ServerInfo));
        }

        ServerInfo(uint32_t _serverId, uint32_t _serverType, char *_serverName, char *_serverIp, uint32_t _port)
            :serverId(_serverId), serverType(_serverType), port(_port)
        {
            strncpy(serverName, _serverName, sizeof(serverName));
            strncpy(serverIP, _serverIp, sizeof(serverIP));
        }

		ServerInfo& operator =(const ServerInfo& rhs)
		{
			memcpy(this, &rhs, sizeof(ServerInfo));

			return *this;
		}

        void Clear()
        {
            bzero(this, sizeof(ServerInfo));
        }
    };

CMD_NAMESPACE_END

#endif
