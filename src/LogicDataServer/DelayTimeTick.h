#ifndef _DELAY_TIMETICK_H_
#define _DELAY_TIMETICK_H_

#include "Thread.h"
#include "Singleton.h"
#include "Eagle_Time.h"

class CDelayTimeTick : public CThread, public CSingleton<CDelayTimeTick>
{
public:
    CDelayTimeTick()
        :CThread("DelayTimeTick"),
        m_one_sec(1),
        m_five_sec(5),
        m_one_min(60),
        m_five_min(300),
        m_thirty_min(1800),
        m_one_hour(3600)
    {
        currentTime.now();
    }
    ~CDelayTimeTick()
    {
    }

public:
    bool Init();
    void Run();

public:
    static CRTime currentTime;

private:
    Timer m_one_sec;
    Timer m_five_sec;
    Timer m_one_min;
    Timer m_five_min;
    Timer m_thirty_min;
    Timer m_one_hour;
};

#endif
