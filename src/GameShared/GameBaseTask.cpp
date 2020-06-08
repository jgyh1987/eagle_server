#include "GameBaseTask.h"
#include "CObject.h"
#include "CommonType.h"
#include "ImpService.h"

uint32_t g_gameServerId = 0;

uint64_t GetServerObjectUid()
{
	return GetObjectUid() * SERVER_CHARACTOR_UID_AV + (uint64_t)g_serverId;
}

void CServerTaskEx::Clear()
{
    m_gameServerId = 0;

    return CServerTask::Clear();
}

void CServerTaskEx::UpdateGameServerInfo(Cmd::ServerInfoEx* info)
{
	UpdateServerInfo(info);
	m_gameServerId = info->gameServerId;

	return;
}

//CServerConnectClientEx
CServerConnectClientEx::CServerConnectClientEx(const std::string &name, uint32_t serverType, uint32_t serverId, uint32_t gameServerId, const std::string &ip, const unsigned short port, uint32_t queuesize)
    :CServerConnectClient(name, serverType, serverId, ip, port), m_gameServerId(gameServerId)
{

}

CServerConnectClientEx::~CServerConnectClientEx()
{
}
