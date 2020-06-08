#include "GatewayPlayer.h"
#include "Defs.h"
#include "GatewayTask.h"
#include "Stream.h"
#include "GatewayService.h"
#include "ClientMsg.h"
#include "GatewayUdpServer.h"
#include "PlayerManager.h"
#include "ikcp.h"
#include "SessionManager.h"

GatewayPlayer::GatewayPlayer(uint64_t id, uint64_t tempid, AccountSession *account, CGatewayTask* task)
    :WorldObject(tempid), m_task(task), m_agentLock(false), m_agentServerId(0)
{
    m_id = id;
    m_account = account;
    account->player = this;
}

GatewayPlayer::~GatewayPlayer()
{
    if (m_account)
    {
        m_account->player = NULL;
        m_account->task = NULL;
    }
        

    if (m_grid)
        m_grid->RemoveObject(this);

    if (m_task)
        m_task->SetPlayer(NULL);

    PlayerManager::instance()->RemoveKcpPlayer(GetKcpId());
}

void GatewayPlayer::Update()
{
    if (m_kcp)
    {
        ikcp_update(m_kcp, (uint32_t)CImpServerTimeTick::currentTime.msec());
        
    }

    return;
}

void GatewayPlayer::Update5Sec()
{
    //LOGD("GatewayPlayer::Update name" << Account() << " m_kdp = " << m_kcp);

    return;
}

void GatewayPlayer::UpdateBaseInfo(PlayerInfoBase *info, RoleInfoBase *roleInfo)
{

    return;
}

void GatewayPlayer::SetTask(CGatewayTask *task)
{
    m_task = task;
}

bool GatewayPlayer::SendClientMsg(ClientMsg::Message *message)
{
    if (m_task)
        m_task->SendClientMsg(message);

    return true;
}

bool GatewayPlayer::SendClientMsg(::google::protobuf::Message *message, int id)
{
    if (m_task)
        m_task->SendClientMsg(message, id);

    return true;
}

bool GatewayPlayer::SendCmd(const void * ptr, uint32_t len)
{
    if (m_task)
        m_task->SendCmd(ptr, len);

    return true;
}

bool GatewayPlayer::SendToLogic(void *ptr, uint32_t len)
{
    SendToLogicServer(ptr, len);

    return true;
}

bool GatewayPlayer::SendToGame(void* ptr, uint32_t nCmdLen)
{
	if (m_agentServerId && !m_agentLock)
		SendToGameServer(ptr, nCmdLen, GetAgentServerId());

	return true;
}

void GatewayPlayer::ParamKcpMsg(const char* data, uint32_t size)
{
	protocol::PackageNet stream;
	stream.ParseFromArray(data, size);

	switch (stream.id())
	{
	case protocol::cs_udpTest:
	{
		protocol::UpdTestReqNet msg;
		msg.ParseFromArray((void*)stream.body().c_str(), (int)stream.body().size());

		protocol::UpdTestRspNet send;
		send.set_dataid(msg.dataid());

		KcpSendClientMsg(&send, protocol::sc_udpTest);
	}
	break;
	}

	return;
}

void GatewayPlayer::KcpSendClientMsg(ClientMsg::Message *message)
{
    if (!m_kcp)
        return;

    unsigned char buff[MAX_DATASIZE];
    BinaryWriteStream stream((char*)buff, MAX_DATASIZE - PH_LEN);
    if (message->Serialize(&stream) != 0)
    {
        LOGFMTE("msg Serialize Error, （%d, %d）", message->majorCmd, message->minorCmd);
        return ;
    }
    stream.Flush();
    ikcp_send(m_kcp, (const char *)buff, (uint32_t)stream.GetSize());

    return;
}

bool GatewayPlayer::KcpSendClientMsg(::google::protobuf::Message *message, int id)
{
    if (!m_kcp)
        return false;

    unsigned char buff[MAX_DATASIZE];
    int len = (int)message->ByteSizeLong();
    message->SerializeToArray(buff, len);

    protocol::PackageNet stream;
    stream.set_id(id);
    stream.set_body(buff, len);

    len = (int)stream.ByteSizeLong();
    stream.SerializeToArray(buff, len);

    ikcp_send(m_kcp, (const char *)buff, len);

    return true;
}

void GatewayPlayer::SetKcpId(uint32_t id)
{
	KcpPlayer::SetKcpId(id);

    if (id)
        PlayerManager::instance()->AddKcpPlayer(id, this);

    return;
}

void GatewayPlayer::LeaveWorld()
{
    //ClientMsg::LeaveMapRes notify;
    //SendClientMsg(&notify);

    return;
}

void GatewayPlayer::NotifyBeTick(uint32_t type)
{
    ClientMsg::KickPlayerNotify send;
    send.ret = type;
    SendClientMsg(&send);

    return;
}


