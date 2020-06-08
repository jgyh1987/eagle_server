#include "KcpPlayer.h"

UpdOutPut KcpPlayer::m_udpOutPut = NULL;

void KcpPlayer::InitKcp(sockaddr* addr, uint32_t kcpId)
{
	if (!m_udpOutPut)
		return;

	SetUdpAddr(addr);
	SetKcpId(kcpId);

	if (m_kcp)
	{
		ikcp_release(m_kcp);
		m_kcp = NULL;
	}

	m_kcp = ikcp_create(GetKcpId(), (void*)this);
	if (!m_kcp)
		return;
	m_kcp->output = m_udpOutPut;

	// 配置窗口大小：平均延迟200ms，每20ms发送一个包，
	// 而考虑到丢包重发，设置最大收发窗口为128
	ikcp_wndsize(m_kcp, 128, 128);

	int mode = 2;
	// 判断测试用例的模式
	if (mode == 0) {
		// 默认模式
		ikcp_nodelay(m_kcp, 0, 10, 0, 0);
	}
	else if (mode == 1) {
		// 普通模式，关闭流控等
		ikcp_nodelay(m_kcp, 0, 10, 0, 1);
	}
	else {
		// 启动快速模式
		// 第二个参数 nodelay-启用以后若干常规加速将启动
		// 第三个参数 interval为内部处理时钟，默认设置为 10ms
		// 第四个参数 resend为快速重传指标，设置为2
		// 第五个参数 为是否禁用常规流控，这里禁止
		ikcp_nodelay(m_kcp, 1, 7, 2, 1);
		m_kcp->rx_minrto = 10;
		m_kcp->fastresend = 1;
	}
}

void KcpPlayer::KcpSendClientMsg(void* buff, uint32_t len)
{
	ikcp_send(m_kcp, (const char*)buff, len);

	return;
}

void KcpPlayer::IkcpInput(const char* data, uint32_t size)
{
	if (!m_kcp)
		return;

	printf("KcpPlayer::IkcpInput len = %d ", size);

	ikcp_input(m_kcp, data, size);
	char buffer[MAX_DATABUFFERSIZE];
	int32_t len = ikcp_recv(m_kcp, buffer, MAX_DATABUFFERSIZE);


	//解析数据
	if (len > 0)
	{
		ParamKcpMsg(buffer, len);
	}

	return;
}

void KcpPlayer::SetKcpId(uint32_t id)
{
	m_kcpId = id;

	return;
}


