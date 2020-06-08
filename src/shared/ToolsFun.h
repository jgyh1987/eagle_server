#ifndef _TOOLSFUN_H_
#define _TOOLSFUN_H_

#include "Sys.h"
#include "EaglePos.h"

#ifdef WIN32

#define ALT_E          0x01
#define ALT_O          0x02
//#define LEGAL_ALT(x)       { if (alt_format & ~(x)) return (0); }
#define LEGAL_ALT(x)       { ; }
#define TM_YEAR_BASE   (1900)

char * strptime(const char *buf, const char *fmt, struct tm *tm);

#endif

template<typename T1, typename T2>
inline uint16_t HashToWORD(const T1& key1, const T2& key2)
{
    return ( ( uint16_t )key1 << 8 )+ key2;
}

template<typename T1, typename T2>
inline uint32_t HashToDWORD(const T1& key1, const T2& key2)
{
    return ( ( uint32_t )key1 << 16 ) + key2;
}

template<typename T1, typename T2>
inline uint64_t HashToQWORD(const T1& key1, const T2& key2)
{
    return ( ( uint64_t )key1 << 32 ) + key2;
}

void parseStrToVecInt( const std::string& param, std::vector< uint32_t > & posVec, char fege = ';' );
void parseStrToVecVecInt( const std::string& param, std::vector< std::vector< uint32_t > >& posVec, char fege1 = '-', char fege2 = ';' );
void parseStrToVecInt64(const std::string& param, std::vector< uint64_t >& posVec, char fege = ';');
void parseStrToVecVecInt64(const std::string& param, std::vector< std::vector< uint64_t > >& posVec, char fege1 = '-', char fege2 = ';');
void parseStrToIntAndString( const std::string& param, uint32_t &, std::string &, char fege = ';' );
void parseStrToVecDouble(const std::string& param, std::vector< double > & posVec, char fege = ';');
void parseStrToVecVecDouble(const std::string& param, std::vector< std::vector< double > >& posVec, char fege1 = '-', char fege2 = ';');
void parseStrToPos(const std::string& param, EaglePos &pos, char fege2 = ',');
void parseStrToPosDir(const std::string& param, EaglePos &pos, char fege2 = ',');


/**
 * @brief 
 *
 * @param input_date    date string 
 * @param format        format string , eg "%y-%m-%d %H:%M:%S"
 * @param to_time       utc time
 *
 * @return              utc time or -1
 */
uint64_t GetUtcSecondsEx(const char * input_date, const char* format, uint64_t &to_time);

#endif
