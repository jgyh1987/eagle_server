#include "Counter.h"
#include "TimeTick.h"
#include "CommonType.h"

uint32_t EagleCounter::GetCounter(uint32_t type)
{
    std::map<uint32_t, CounterType>::iterator itr = m_counts.find(type);
    if (itr != m_counts.end())
        return itr->second.value;

    return 0;
}

void EagleCounter::AddCounter(uint32_t type, int32_t addon, int32_t timeType)
{
    std::map<uint32_t, CounterType>::iterator itr = m_counts.find(type);
    if (itr != m_counts.end())
        itr->second.value += addon;
    else
    {
        CounterType info;
        info.value = addon;
        info.timeType = timeType;
        info.untilTime = DelayDayStart();

        m_counts[type] = info;
    }

    return ;
}

void EagleCounter::SubCounter(uint32_t type, int32_t subValue)
{
    std::map<uint32_t, CounterType>::iterator itr = m_counts.find(type);
    if (itr != m_counts.end())
    {
        if (itr->second.value >= subValue)
            itr->second.value -= subValue;
        else
            itr->second.value = 0;
    }

    return ;
}

void EagleCounter::SetCounter(uint32_t type, int32_t val, int32_t timeType)
{
    std::map<uint32_t, CounterType>::iterator itr = m_counts.find(type);
    if (itr != m_counts.end())
        itr->second.value = val;
    else
    {
        CounterType info;
        info.value = val;
        info.timeType = timeType;
        info.untilTime = DelayDayStart();

        m_counts[type] = info;
    }

    return;
}

void EagleCounter::RemoveCounter(uint32_t type)
{
    std::map<uint32_t, CounterType>::iterator itr = m_counts.find(type);
    if (itr != m_counts.end())
    {
        m_counts.erase(itr);
    }

    return;
}

uint32_t EagleCounter::Serialize(uint8_t *buffer)
{
    uint32_t size = 0;
    uint32_t *pLen = (uint32_t *)buffer;
    BuffWriteMoveLen(buffer, size, UINT32_LEN);

    BuffWriteInt(buffer, size, COUNTERVERSION_1_1);

    uint32_t *pNum = (uint32_t *)buffer;
    BuffWriteMoveLen(buffer, size, UINT32_LEN);

    uint32_t count = 0;
    for (std::map<uint32_t, CounterType>::iterator itr = m_counts.begin(); itr != m_counts.end(); ++itr)
    {
        if (itr->second.value)
        {
            BuffWriteInt(buffer, size, itr->first);
            BuffWriteInt(buffer, size, itr->second.value);
            BuffWriteInt64(buffer, size, itr->second.untilTime);
            BuffWriteInt(buffer, size, itr->second.timeType);

            ++count;
        }
    }

    *pNum = count;
    *pLen = size;

    return size;
}

uint32_t EagleCounter::UnSerialize(uint8_t *buffer)
{
	Clear();

    uint32_t length = 0;

    BuffLoadInt(buffer, length, length);
    uint32_t ret = length + UINT32_LEN;

    BuffLoadMoveLen(buffer, length, UINT32_LEN);    //version

    uint32_t count = 0;
    BuffLoadInt(buffer, length, count);
    for (uint32_t i = 0; i < count; ++i)
    {
        uint32_t type = 0;
        BuffLoadInt(buffer, length, type);

        CounterType info;
        BuffLoadInt(buffer, length, info.value);
        BuffLoadInt64(buffer, length, info.untilTime);
        BuffLoadInt(buffer, length, info.timeType);

        m_counts[type] = info;
    }

    return ret;
}

void EagleCounter::Clear()
{
    m_counts.clear();

    return;
}

void EagleCounter::Refresh()
{
    for (std::map<uint32_t, CounterType>::iterator itr = m_counts.begin(); itr != m_counts.end(); ++itr)
    {
        if (COUNTER_TIME_DAY == itr->second.timeType)
        {
            if (itr->second.untilTime < DelayDayStart())
            {
                itr->second.value = 0;
                itr->second.untilTime = DelayDayStart();
            }
        }
        else if (COUNTER_TIME_WEEK == itr->second.timeType)
        {
            if (itr->second.untilTime < DelayWeekStart())
            {
                itr->second.value = 0;
                itr->second.untilTime = DelayWeekStart();
            }
        }
        else if (COUNTER_TIME_MONTH == itr->second.timeType)
        {
            if (itr->second.untilTime < DelayMonthStart())
            {
                itr->second.value = 0;
                itr->second.untilTime = DelayMonthStart();
            }
        }
    }

    return;
}
