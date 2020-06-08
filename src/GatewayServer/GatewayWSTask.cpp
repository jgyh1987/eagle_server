#include "GatewayWSTask.h"
#include "Random.h"

CGatewayWSTask::~CGatewayWSTask()
{

}

void CGatewayWSTask::Clear()
{

    return CWebSockConnectTask::Clear();
}

bool CGatewayWSTask::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
    char *p = (char *)ptNull;

    if (CRandom::RandomBetween(0, 2))
    {
        char *send = new char[100];
        memset(send, '1', 100);
        SendCmd(send, 100);
    }
    else
    {
        char *send = new char[200];
        memset(send, '1', 200);
        SendCmd(send, 200);
    }
    


    return true;
}



