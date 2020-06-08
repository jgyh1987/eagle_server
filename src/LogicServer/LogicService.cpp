#include "LogicService.h"
#include "LogicDataCommand.h"
#include "DBConnectClient.h"
#include "Defs.h"
#include "World.h"
#include "ServerCommand.h"
#include "ECS_AIBehaviac.h"

CLogicServer *ServerImp()
{
    return (CLogicServer *)g_pServerImp;
}

CLogicServer::CLogicServer(const std::string &name)
    :CImpServer(SERVER_TYPE_MAX, name)
{
}
    
CLogicServer::~CLogicServer()
{

}

bool CLogicServer::CallBack()
{
    CServerConnectClient *conncect = GetConnectClient(SERVER_TYPE_LOGIC_DATA, g_serverId);
    if (((CDBConnectClient *)conncect)->IsRegist() && conncect->IsFinal())
        return false;

    return CImpServer::CallBack();
}

void CLogicServer::Update()
{
    World::instance()->Update();

    return;
}

void CLogicServer::UpdateSec()
{
    World::instance()->UpdateSec();

    return;
}

void CLogicServer::Update5Sec()
{
    World::instance()->Update5Sec();

    Cmd::t_ServerInit_Test_Msg send;
    send.serverId = g_serverId;
    ServerImp()->ProxySendCmd(&send, sizeof(send), SERVER_TYPE_WMATCH_SERVER, 0);

    return;
}

void CLogicServer::UpdateMin()
{
    World::instance()->UpdateMin();

    return;
}

void CLogicServer::Update5Min()
{

    return;
}

void CLogicServer::Update30Min()
{

    return;
}

void CLogicServer::UpdateHour()
{
    World::instance()->UpdateHour();

    return;
}

void CLogicServer::Update24()
{
    World::instance()->Update24();

    return;
}

void CLogicServer::ProxySendCmd(void *cmd, uint32_t len, uint32_t serverType, uint32_t serverId)
{
    Cmd::t_Server_Send_Trans_Msg* send = NULL;
    ServerCmdBuffer(send);
    memcpy(send->data, cmd, len);
    send->dataLen = len;
    send->targetServer.serverType = serverType;
    send->targetServer.serverId = serverId;
    send->srcServer.serverId = g_serverId;
    send->srcServer.serverType = SERVER_TYPE_LOGIC_SERVER;


    SendCmdToConnect(send, send->Size(), SERVER_TYPE_PROXY_SERVER, 0);

    return;
}

bool CLogicServer::SendClientMsg(ClientMsg::Message* msg, uint64_t uid, uint32_t gateServerId)
{
	Cmd::t_Server_Send_Trans_Msg* send = NULL;
	ServerImp()->ServerCmdBuffer(send);
	BinaryWriteStream stream((char*)(send->data), SERVER_COMMAND_MAX_LENGTH - sizeof(Cmd::t_Server_Send_Trans_Msg));
	if (msg->Serialize(&stream) != 0)
	{
		LOGFMTE("msg serialize error（%d, %d）", msg->majorCmd, msg->minorCmd);
		return false;
	}
	stream.Flush();
	send->uid = uid;
	send->dataLen = (uint32_t)stream.GetSize();
	send->targetServer.serverType = CLIENT_TYPE;
	send->srcServer.serverType = SERVER_TYPE_LOGIC_SERVER;

	SendCmdToServerTask(send, (uint32_t)send->Size(), SERVER_TYPE_LOGIC_GATEWAY, gateServerId);

	return true;
}

bool CLogicServer::SendClientMsg(::google::protobuf::Message* message, int id, uint64_t uid, uint32_t gateServerId)
{
	Cmd::t_Server_Send_Trans_Msg* send = NULL;
	ServerImp()->ServerCmdBuffer(send);
	int len = (int)message->ByteSizeLong();
	message->SerializeToArray(send->data, len);

	protocol::PackageNet stream;
	stream.set_id(id);
	stream.set_body(send->data, len);

	len = (int)stream.ByteSizeLong();
	stream.SerializeToArray(send->data, len);
	send->uid = uid;
	send->dataLen = len;
	send->targetServer.serverType = CLIENT_TYPE;
	send->srcServer.serverType = SERVER_TYPE_LOGIC_SERVER;

	SendCmdToServerTask(send, (uint32_t)send->Size(), SERVER_TYPE_LOGIC_GATEWAY, gateServerId);

	return true;
}



