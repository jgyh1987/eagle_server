#ifndef _EAGLE_TIME_H_
#define _EAGLE_TIME_H_

#include "Sys.h"

namespace eagle
{

/// @brief    秒,分,时,日,周的毫秒数的宏.FOREVER代表不再执行,是uint32_t的最大值 
#define ONE_SEC (1000)
#define HALF_SEC (500)
#define TEN_SEC (10000)
#define ONE_MIN (60000)
#define HALF_MIN (30000)
#define ONE_HOUR (3600000)
#define HALF_HOUR (1800000)
#define ONE_DAY (86400000)
#define HALF_DAY (43200000)
#define ONE_WEEK (604800000)
#define FOREVER (4294967294)

// @brief 时间定义 
class CTime
{
    public:
        /// @brief    设置时区 
        static bool setTimeZone();
        /// @brief    设置系统相对时间 
        /// @param    offset 偏移量(秒) 
        static void setAdjustTime(const int offset = 0);
        /// @brief    保留的时区信息 
        //            程序初始化的时候设置，运行过程中一般不变 
        //            当前在中国，东8区timeZone = -8 * 60 * 60 
        static long timeZone;
        /// @brief    调整系统相对时间 
        //             主要用于在线调整服务器运行时间而不影响系统时间 
        static long adjustTime;

    public:
        CTime()
        {
            now();
        }

        CTime(const CTime &rt)
        {
            _tv = rt._tv;
            _msec = rt._msec;
            _tm_ok = false;
        }

        CTime(const uint32_t timeInSec)
        {
            _tv.tv_sec = timeInSec + timeZone + adjustTime;
            _tv.tv_usec = 0;
            _msec = timeInSec * 1000;
            _tm_ok = false;
        }

        /// @brief 调用得到当前的系统时间  
        void now()
        {
            /// @brief 获得timespec系统时间,用来填充结构 
            gettimeofday(&_tv, NULL);
            _tv.tv_sec += timeZone + adjustTime;
            _msec = sec() * 1000L + _tv.tv_usec/1000;
            _tm_ok = false;
        }

        inline unsigned long sec() const
        {
            return _tv.tv_sec;
        }

        inline uint64_t msec() const
        {
            return _msec;
        }

        //inline unsigned long usec() const
        //{
        //    return msec() * 1000L + _tv.tv_usec;
        //}

        /// @brief 计时器延迟 
        /// @param delay 延迟的时间(毫秒) 
        inline void addDelay(const unsigned long delay)
        {
            _tv.tv_usec += (delay * 1000L);
            _tv.tv_sec += (_tv.tv_usec / 1000000L);
            _tv.tv_usec %= 1000000L;
            _msec = sec() * 1000L + _tv.tv_usec / 1000L;
            _tm_ok = false;
        }

        inline CTime & operator= (const CTime &rt)
        {
            _tv = rt._tv;
            _msec = rt._msec;
            _tm_ok = false;
            return *this;
        }

        inline bool operator > (const CTime &rt) const
        {
            if (_msec <= rt._msec)
                return false;
            else
                return true;
        }

        inline bool operator >= (const CTime &rt) const
        {
            if (_msec >= rt._msec)
                return true;
            else
                return false;
        }

        inline bool operator < (const CTime &rt) const
        {
            if ( this->_msec >= rt._msec)
                return false;
            else
                return true;
        }

        inline bool operator <= (const CTime &rt) const
        {
            if ( this->_msec > rt._msec)
                return false;
            else
                return true;
        }

        inline bool operator == (const CTime &rt) const
        {
            return (rt._msec == _msec);
        }

        /// @brief    计时器消逝的时间，单位毫秒 
        /// @param    rt 当前时间，需要比较的时间 
        /// @return    计时器消逝的时间，单位毫秒 
        uint64_t elapse(const CTime &rt) const
        {
            uint64_t val = rt.msec() - msec();
            if (val < 0L)
                return 0L;
            else
                return val;
        }

        /// @brief    得到本地时间 
        /// @param    tv1 需要输出的时间结构 
        /// @param    timeValue 输入时间 
        /// @return     
        static void getLocalTime(struct tm & tv1, time_t timValue)
        {
            tv1 = *localtime(&timValue);
        }

        /// @brief 进出夏令时 0没有变化，1进入夏令时，-1退出夏令时 
        static int dstCompare(time_t tim1, time_t tim2)
        {
            struct tm tm1 = *localtime(&tim1);
            struct tm tm2 = *localtime(&tim2);
            if(tm1.tm_isdst == tm2.tm_isdst)
                return 0;
            if(tm1.tm_isdst < tm2.tm_isdst)
                return 1;
            return -1;
        }

        /// @brief 计算机系统时间得到当前localtime换算出来的时间 
        static uint64_t getLocalTimeByUTC(time_t time)
        {
            struct tm _tm = *localtime(&time);
            _tm.tm_isdst = -1;
            return mktime(&_tm);
        }

    protected:
        /// @brief    真实时间(精确到微秒级) 
        struct timeval _tv;
        /// @brief    毫秒数 
        uint64_t _msec;    
        /// @brief    标志_tm结构体数据是否有效 
        bool _tm_ok;
};

/**
 * \brief 真实时间类,对timeval结构简单封装,提供一些常用时间函数 
 * 时间精度精确到毫秒， 
 * 关于timeval请man gettimeofday 
 */ 
class CRTime
{

    private:
        /**
         * \brief 真实时间换算为毫秒 
         *
         */ 
        uint64_t _msecs;
        //uint64_t _usecs;

        /**
         * \brief 得到当前真实时间  
         *          加上游戏调整时间 
         * \return 真实时间，单位毫秒 
         */ 
        uint64_t _now()
        {
            uint64_t retval = 0LL;
            struct timeval tv;
            gettimeofday(&tv,NULL);
            retval = tv.tv_sec;
            retval *= 1000;
            retval += tv.tv_usec / 1000;
            //_usecs = tv.tv_sec * 1000 * 1000 + tv.tv_usec + CTime::timeZone * 1000 * 1000 + CTime::adjustTime * 1000 * 1000;
            return retval + CTime::timeZone * 1000 + CTime::adjustTime * 1000;
        }

        /** 
         * \brief 得到当前真实时间延迟后的时间 
         * \param delay 延迟，可以为负数，单位毫秒 
         */ 
        void nowByDelay(int delay)
        {
            _msecs = _now();
            addDelay(delay);
        }

    public:
        /**
         * \brief 构造函数 
         *
         * \param delay 相对于现在时间的延时，单位毫秒 
         */ 
        CRTime(const int delay = 0)
        {
            nowByDelay(delay);
        }

        /**
         * \brief 拷贝构造函数 
         *
         * \param rt 拷贝的引用 
         */ 
        CRTime(const CRTime &rt)
        {
            _msecs = rt._msecs;
            //_usecs = rt._usecs;
        }

        /**
         * \brief 获取当前时间 
         *
         */ 
        void now()
        {
            _msecs = _now();
        }

        /**
         * \brief 返回秒数 
         *
         * \return 秒数 
         */ 
        uint64_t sec() const
        {
            return _msecs / 1000;
        }

        /** 
         * \brief 返回毫秒数 
         *
         * \return 毫秒数 
         */ 
        uint64_t msec() const
        {
            return _msecs;
        }
        //unsigned long usec() const
        //{
        //    return _usecs;
        //}

        /** 
         * \brief 返回总共的毫秒数 
         *
         * \return 总共的毫秒数 
         */ 
        uint64_t msecs() const
        {
            return _msecs;
        }

        /**
         * \brief 返回总共的毫秒数 
         *
         * \return 总共的毫秒数 
         */ 
        void setmsecs(uint64_t data)
        {
            _msecs = data;
        }

        /**
         * \brief 加延迟偏移量 
         *
         * \param delay 延迟，可以为负数，单位毫秒 
         */ 
        void addDelay(int delay)
        {
            _msecs += delay;
            //_usecs += delay * 1000;
        }

        CRTime & operator= (const CRTime &rt)
        {
            _msecs = rt._msecs;
            return *this;
        }

        const CRTime & operator+ (const CRTime &rt)
        {
            _msecs += rt._msecs;
            return *this;
        }

        const CRTime & operator- (const CRTime &rt)
        {
            _msecs -= rt._msecs;
            return *this;
        }

        bool operator > (const CRTime &rt) const
        {
            return _msecs > rt._msecs;
        }

        bool operator >= (const CRTime &rt) const
        {
            return _msecs >= rt._msecs;
        }

        bool operator < (const CRTime &rt) const
        {
            return _msecs < rt._msecs;
        }

        bool operator <= (const CRTime &rt) const
        {
            return _msecs <= rt._msecs;
        }

        bool operator == (const CRTime &rt) const
        {
            return _msecs == rt._msecs;
        }

        /** 
         * \brief 计时器消逝的时间，单位毫秒 
         * \param rt 当前时间  
         * \return 计时器消逝的时间，单位毫秒 
         */ 
        uint64_t elapse(const CRTime &rt) const
        {
            if (rt._msecs > _msecs)
                return (rt._msecs - _msecs);
            else
                return 0LL;
        }

        static std::string & getLocalTZ(std::string & s);
        static void getLocalTime(struct tm & tv1,time_t timValue)
        {
            tv1 = *gmtime(&timValue);
        }

};

class Timer
{
    public:
        Timer(const float how_long,const int delay=0) : _long((int)(how_long*1000)),_timer(delay*1000)
        {}
        Timer(const float how_long,const CRTime& cur) : _long((int)(how_long*1000)),_timer(cur)
        {
            _timer.addDelay(_long);
        }
        void next(const CRTime &cur)
        {
            _timer=cur;
            _timer.addDelay(_long);
        } 
        bool operator() (const CRTime& current)
        {
            if (_timer <= current) {
                _timer = current;
                _timer.addDelay(_long);
                return true;
            }

            return false;
        }
    private:
        int _long;
        CRTime _timer;
};

class CDayTime : public CTime
{
    public:
        CDayTime()
        {
        }

    public:
        /// @brief    获得dayDiff前/后的日期. 
        /// @param    dayDiff 正数表示以后,负数表示之前 
        int getMDays(uint16_t dayDiff)
        {
            if(dayDiff == 0)
            {
                return getMDays();
            }
            time_t time = _tv.tv_sec + dayDiff * (ONE_DAY/1000) ;
            struct tm tv;
            getLocalTime(tv, time);
            return tv.tm_mday;
        }

        /// @brief    检查_tm结构体是否有效 
        void checkTM()
        {
            if(!_tm_ok) 
            { 
                getLocalTime(_tm, _tv.tv_sec); 
                _tm_ok = true; 
            } 
        }

        /// @brief     对时间进行格式化 
        //             按照指定的格式把时间格式化成字符串形式 
        /// @param     buffer 输出字符串缓冲 
        /// @param     bufferlen 输出字符串缓冲大小 
        /// @param     format 时间格式，请参见man strftime 
        /// @return     
        uint64_t format(char *buffer, size_t bufferlen, const char *format = "%C/%m/%d %T")
        {
            checkTM();
            return strftime(buffer, bufferlen, format, &_tm);
        }

        /// @breif 时间格式化 
        static uint64_t format(time_t sec, char* buffer, size_t bufferlen, const char* format = "%C/%m/%d %T")
        {
            struct tm sectm = *localtime(&sec);
            return strftime(buffer, bufferlen, format, &sectm);
        }

        /// @brief    获取分钟内的秒数 
        /// @param    
        /// @return    分钟内的秒数 
        int getSeconds()
        {
            checkTM();
            return _tm.tm_sec;
        }

        int getMinutes()
        {
            checkTM();
            return _tm.tm_min;
        }

        int getHours()
        {
            checkTM();
            return _tm.tm_hour;
        }

        /// @brief    获取一月内的天数 
        /// @param    
        /// @return    一月内的天数 
        int getMDays()
        {
            checkTM();
            return _tm.tm_mday;
        }

        /// @brief    获取一年内的月份数 
        /// @param    
        /// @return    一年内的月份数 
        int getMonths()
        {
            checkTM();
            return _tm.tm_mon;
        }

        /// @brief    获取自1970后的年数 
        /// @param    
        /// @return    自1970后的年数 
        int getYears()
        {
            checkTM();
            return _tm.tm_year;
        }

        /// @brief    获取一年内的天数 
        /// @param    
        /// @return    一年内的天数 
        int getWDays()
        {
            checkTM();
            return _tm.tm_wday;
        }

        /// @brief    获取一年内的天数 
        /// @param    
        /// @return    一年内的天数 
        int getYDays()
        {
            checkTM();
            return _tm.tm_yday;
        }

        //根据年月日时分秒获取距离1970年的秒数 
        static uint32_t makeSecs(int year, int month, int day, int hour, int min, int sec){
            struct tm timevar;
            timevar.tm_year = year;
            timevar.tm_mon = month;
            timevar.tm_mday = day;
            timevar.tm_hour = hour;
            timevar.tm_min = min;
            timevar.tm_sec = sec;
            timevar.tm_isdst = -1;
            time_t ret = mktime(&timevar);
            ret += timeZone;
            return (uint32_t)ret;

        }

        static uint32_t getWeekStart(CDayTime& current, int week = 0){
            int wk = current.getWDays();
            if (wk == 0 ) wk = 7;
            wk--;
            return current.sec() - (wk + week * 7) * 86400 - 60 * current.getMinutes() - 
                3600 * current.getHours() - current.getSeconds();
        }

        static uint32_t makeSecs(const char* timestr)
        {
            if(!timestr)
                return 0;
            struct tm tim;
            strftime((char*)timestr, 1024, "%Y-%m-%d %H:%M:%S", &tim);
            tim.tm_isdst = -1;
            return (uint32_t)mktime(&tim);
        }


    private:
        struct tm _tm;
};

/// @brief 计时器定时闹钟 
class Clocker
{
    public:
        explicit Clocker(const unsigned long how_long, const unsigned long interval = 24 * 60 * 60 ) 
            : _long(how_long * 1000), _interval(interval * 1000)
        {
            CDayTime dayTime;
            dayTime.now();
            _clock = (uint64_t)(CDayTime::makeSecs(dayTime.getYears(), dayTime.getMonths(), dayTime.getMDays(), 0, 0, 0 ))* 1000 + ( dayTime.msec() % 1000 );
            _firstDelay = false;
            delay();
        }
        bool operator()(const CRTime& cur);
        unsigned int leftSec(const CRTime& cur);
    private:
        void delay();
    private:
        /// @brief 闹钟间隔,单位ms 
        const uint64_t _long;
        /// @brief 闹钟周期 
        const uint64_t _interval;
        /// @brief 时间类 
        uint64_t _clock;
        // @brief 首次设置延迟 
        uint8_t _firstDelay;
};

};

#endif
