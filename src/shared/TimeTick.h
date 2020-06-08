#ifndef _TIMETICK_H_
#define _TIMETICK_H_

#include "Thread.h"
#include "Singleton.h"
#include "Eagle_Time.h"

#define MSEC_TO_SEC        1000            //���뵽�� ϵ��
#define ONE_DAY_SEC    86400
#define ONE_WEEK_SEC 604800
#define THIRTY_DAY_SEC 2592000

class CImpServerTimeTick : public CThread, public CSingleton<CImpServerTimeTick>
{
public:
    CImpServerTimeTick()
        :CThread("CImpServerTimeTick"),
        m_one_sec(1),
        m_five_sec(5),
        m_one_min(60),
        m_five_min(300),
        m_thirty_min(1800),
        m_one_hour(3600)
    {
        currentTime.now();
        dayTime.now();
    }
    ~CImpServerTimeTick()
    {
    }

public:
    
    bool Init();
    void Run();
    void SetDelayTime(uint64_t time);

    static DWORD getMonthStart(CDayTime& current)
    {
        int monthDay = current.getMDays();
        --monthDay;
        return current.sec() - monthDay * 86400 - 60 * current.getMinutes() - 
            3600 * current.getHours() - current.getSeconds();
    }

public:
    static CRTime currentTime;
    static CDayTime dayTime;
    static uint64_t dayStart;
    static uint64_t weekStart;
    static uint64_t monthStart;
    static uint64_t m_update24Timer;
    static uint64_t m_delayTime;

private:
    Timer m_one_sec;
    Timer m_five_sec;
    Timer m_one_min;
    Timer m_five_min;
    Timer m_thirty_min;
    Timer m_one_hour;
    
};

inline uint64_t DelayDayStart()
{
    return CImpServerTimeTick::dayStart + CImpServerTimeTick::m_delayTime;
}

inline bool IsNextDay(uint64_t time)
{
    if (time < DelayDayStart() && CImpServerTimeTick::currentTime.sec() > DelayDayStart())
        return true;

    return false;
}

inline uint64_t DelayWeekStart()
{
    return CImpServerTimeTick::weekStart + CImpServerTimeTick::m_delayTime;
}

inline uint64_t DelayMonthStart()
{
    return CImpServerTimeTick::monthStart + CImpServerTimeTick::m_delayTime;
}

#endif
