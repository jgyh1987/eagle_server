#ifndef _CLIENTTASK_H_
#define _CLIENTTASK_H_

#include "ConnectTask.h"
#include "MessageFilter.h"
#include "TimeTick.h"


class CClientTask : public CClientConnectTask
{
public:
    CClientTask(CListenTCPServer *listenServer)
        :CClientConnectTask(listenServer), m_openFilter(true)
    {
    }
    ~CClientTask();

    void Clear();

    bool msgParase(void *ptNullCmd ,const unsigned int cmdLen);
    inline void SetOpenFilter(bool set){m_openFilter = set;}
    
protected:
    MessageFilter m_filter;
    bool m_openFilter;
};

#endif
