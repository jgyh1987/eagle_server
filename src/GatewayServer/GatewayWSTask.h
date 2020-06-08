#ifndef _GATEWAYWSTASK_H_
#define _GATEWAYWSTASK_H_

#include "ConnectTask.h"

class CGatewayWSTask : public CWebSockConnectTask
{
public:
    CGatewayWSTask(CListenTCPServer *listenServer)
        :CWebSockConnectTask(listenServer)
    {

    }

    ~CGatewayWSTask();

    void Clear();

    bool cmdMsgParse(void *,const uint32_t);



public:

};

#endif
