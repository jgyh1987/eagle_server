#ifndef _EAGLE_COUNTER_H_ 
#define _EAGLE_COUNTER_H_

#include "Sys.h"

#define COUNTERVERSION_1_1            1

enum COUNTER_TYPE_ID
{
    COUNTER_TYPE_LAST_LOGINOUT_TIME = 1,    //

    COUNTER_TYPE_MAX, 
};

enum COUNTER_TIME_TYPE
{
    COUNTER_TIME_ETERNAL = 0,    //
    COUNTER_TIME_DAY = 1,        //
    COUNTER_TIME_WEEK = 2,    //
    COUNTER_TIME_MONTH = 3,    //
};

struct CounterType
{
    int32_t value;
    uint64_t untilTime;
    int32_t timeType;
    CounterType() : value(0), untilTime(0), timeType(COUNTER_TIME_ETERNAL)
    {}
};

class EagleCounter
{
    public:
        uint32_t GetCounter(uint32_t type);

        void AddCounter(uint32_t type, int32_t addon = 1, int32_t timeType = COUNTER_TIME_ETERNAL);
        void SubCounter(uint32_t type, int32_t subValue=1);

        void SetCounter(uint32_t type, int32_t val, int32_t timeType = COUNTER_TIME_ETERNAL);

        void RemoveCounter(uint32_t type);

        uint32_t Serialize(uint8_t *outBuff);
        uint32_t UnSerialize(uint8_t *buff);

        void Clear();
        void Refresh();

    private:
        std::map<uint32_t, CounterType> m_counts;
};

#endif

