#ifndef _WGATE_CLIENT_TASK_H_
#define _WGATE_CLIENT_TASK_H_

#include "ClientTask.h"
#include "Stream.h"

class CWGateClientTask : public CClientTask
{
public:
    CWGateClientTask(CListenTCPServer *listenServer)
        :CClientTask(listenServer)
    {
        m_openFilter = false;
    }

    void Clear();

    bool cmdMsgParse(void *,const uint32_t);


private:
    


};

#endif
