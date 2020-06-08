#ifndef _ECS_KCP_PLAYER_H_
#define _ECS_KCP_PLAYER_H_

#include "ikcp.h"
#include "Sys.h"
#include "UdpServer.h"

namespace ClientMsg
{
	struct Message;
}

namespace google
{
	namespace protobuf
	{
		class Message;
	}
}

typedef int (*UpdOutPut)(const char* buf, int len, struct IKCPCB* kcp, void* user);

class KcpPlayer
{
public:
	KcpPlayer()
		:m_kcp(NULL), m_kcpId(0)
	{}
	virtual ~KcpPlayer()
	{
		if (m_kcp)
		{
			ikcp_release(m_kcp);
			m_kcp = NULL;
		}
	}

	void InitKcp(sockaddr*, uint32_t kcpId);
	virtual void ParamKcpMsg(const char* data, uint32_t size) = 0;
	virtual void KcpSendClientMsg(ClientMsg::Message* message) = 0;
	virtual bool KcpSendClientMsg(::google::protobuf::Message* message, int id) = 0;
	void KcpSendClientMsg(void* buff, uint32_t len);
	void IkcpInput(const char* data, uint32_t size);
	virtual void SetKcpId(uint32_t id);
	inline uint32_t GetKcpId() { return m_kcpId; }
	inline void SetUdpAddr(sockaddr* addr) { m_addr = *(sockaddr_storage*)addr; }
	inline sockaddr* GetUdpAddr() { return (sockaddr*)& m_addr; }


protected:
	ikcpcb* m_kcp;
	uint32_t m_kcpId;
	sockaddr_storage m_addr;

public:
	static UpdOutPut m_udpOutPut;

};


#endif

