#ifndef _EAGLE_SYS_H_
#define _EAGLE_SYS_H_

#include <string>
#include <deque>
#include <signal.h>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fstream>
#include <stdarg.h>
#include <vector>
#include <errno.h>
#include <cstdlib>
#include <fcntl.h>
#include <cstdio>
#include <math.h>
#include <map>
#include <algorithm>
#include <time.h>
#include <queue>
#include <ostream>
#include <set>
#include <malloc.h>
#include <cctype>
#include <cerrno>
#include <ctime>
#include <list>
#include <streambuf>
#include <stack>
#include <memory>
#include <cstring>
#include <limits.h>
#include <cassert>
#include <iostream>

//
#ifdef EXT_BUILD
#include "curl/curl.h"
#include "zlib.h"
#include "iconv.h"
//#include "argp.h"
#endif
#include "uv.h"
#include "MersenneTwister.h"

//
#if defined (WIN32) || defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <winsock2.h>
#include <stdint.h>
#include "Eagle_Alloc.h"
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "UserEnv.lib")
#pragma comment(lib, "ws2_32.lib")
#define uv_thread_close(t) CloseHandle(t)
#define uv_thread_sleep(ms) ::Sleep(ms)//
#define uv_thread_id GetCurrentThreadId//
#define snprintf _snprintf
#define bswap_64 _byteswap_uint64
#define eagle_strcasecmp stricmp
#define eagle_strncasecmp  strnicmp 
#if _MSC_VER >= 1900    //vs 2017
#include <unordered_map>
#include <unordered_set>
#define eagle_hash std::hash
#define eagle_hash_map std::unordered_map
#define eagle_hash_set std::unordered_set
#else
#include <hash_map>
#include <hash_set>
#define eagle_hash std::hash
#define eagle_hash_map std::hash_map
#define eagle_hash_map std::hash_set
#endif
#define SIGQUIT SIGTERM
#define eagle_mt_alloc_char CEagle_Alloc_Pool<unsigned char>

namespace eagle
{

int gettimeofday(struct timeval *tp, void *tzp);
inline void* bzero(void* dest, size_t count)
{
    return memset(dest, 0, count);
}

inline void* bcopy(const void* src, void* dest, size_t count)
{
    return memcpy(dest, src, count);
}

};

#elif defined(__linux__)
#include <pthread.h>
#include <unistd.h>
#include <byteswap.h>
#include <arpa/inet.h> 
#include <pwd.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/syscall.h>
#include <regex.h>
#include <ext/mt_allocator.h>

#define uv_thread_close(t) pthread_exit(t)
#define uv_thread_sleep(ms) usleep((ms) * 1000)
#define uv_thread_id pthread_self//
#define eagle_strcasecmp strcasecmp
#define eagle_strncasecmp  strncasecmp 

#include <hash_map>
#ifdef CPP11
#include <unordered_map>
#include <unordered_set>
#define eagle_hash std::hash
#define eagle_hash_map std::unordered_map
#define eagle_hash_set std::unordered_set
#else
#include <ext/hash_map>
#include <ext/hash_set>
#define eagle_hash  __gnu_cxx::hash
#define eagle_hash_map  __gnu_cxx::hash_map
#define eagle_hash_set  __gnu_cxx::hash_set
#endif

#define eagle_mt_alloc_char __gnu_cxx::__mt_alloc<unsigned char>

namespace __gnu_cxx
{
    template<> struct hash<const std::string>
    {
        size_t operator()(const std::string& s) const
        { return hash<const char*>()( s.c_str() ); } 
    };
    template<> struct hash<std::string>
    {
        size_t operator()(const std::string& s) const
        { return hash<const char*>()( s.c_str() ); }
    };
}

typedef unsigned short        WORD;
typedef uint64_t            DWORD;
typedef unsigned char        BYTE;

#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(x)        { if (x) { delete (x); (x) = NULL; } }
#endif

namespace eagle
{

enum RERURN_DEFAULT_TYPE
{
    DEFAULT_ERROR = 0,    //
    SUCCESS = 1,        //
};

typedef signed char                SBYTE;
typedef signed short            SWORD;
typedef signed int                SDWORD;
typedef unsigned long long        QWORD;
typedef signed long long        SQWORD;

const unsigned int ServerSize = 64*1024;
#define ServerCount(size) (((size)+ServerSize-1)/ServerSize)
#define unzip_size(zip_size) ((zip_size)+120/100+12)
const unsigned int PACKET_ZIP_BUFFER = unzip_size(ServerSize - 1) + sizeof(unsigned int) + 8;
#ifndef MAXUINT32
#define MAXUINT32 0xffffffff
#endif
const int MAX_SERVERNAME_LENGTH = 128;
const int MAX_IP_LENGTH = 32;
const uint32_t UINT8_LEN = sizeof(uint8_t);
const uint32_t UINT16_LEN = sizeof(uint16_t);
const uint32_t UINT32_LEN = sizeof(uint32_t);
const uint32_t UINT64_LEN = sizeof(uint64_t);
const uint32_t UDPADDRLEN = sizeof(sockaddr_storage);
#ifndef M_PI
#define M_PI            3.14159265358979323846
#endif

#ifdef _NETTOHOST_
#define eagle_htonl(n)        htonl(n)
#define eagle_htons(n)        htons(n)
#define eagle_bswap_64(n)    bswap_64(n)
#define eagle_ntohl(n)        ntohl(n)
#define eagle_ntohs(n)        ntohs(n)

#else

#define eagle_htonl(n)        (n)
#define eagle_htons(n)        (n)
#define eagle_bswap_64(n)    (n)
#define eagle_ntohl(n)        (n)
#define eagle_ntohs(n)        (n)

#endif

//share 
extern eagle_mt_alloc_char g_mt_alloc_char;

inline std::string GetUVError(int errcode)
{
    if (0 == errcode) 
    {
        return "";
    }
    std::string err;
    const char* tmpChar = uv_err_name(errcode);
    if (tmpChar)
    {
        err.append(tmpChar);
    }
    else
    {
        err.append("unknown system errcode %d", errcode);
    }
    err.append(":");
    tmpChar = uv_strerror(errcode);
    if (tmpChar) 
    {
        err += tmpChar;
    }
    return err;
}

struct Eagle_Uv_Write
{
    uv_write_t req;
    uv_buf_t buf;
};

struct Eagle_Uv_Udp_Write
{
    uv_udp_send_t req;
    uv_buf_t buf;
};

void AfterUdpSend(uv_udp_send_t* req, int status);
//close all handle in loop
void CloseWalkCB(uv_handle_t* handle, void* arg);
//separator1 separator2  num example �� "1-2;2-3;"  separator1 = '-' separator2 = ';' num = 2
void ParseStringToVectorUint32(const std::string &str, std::vector<uint32_t> &out, char separator1, char separator2, int num);
//
void signal_cb(uv_signal_t* handle, int signum);
void signal_pipe_cb(uv_signal_t* handle, int signum);

#define EFFECTIVETIME 1510329600		//超过该时间, 将限制接入人数 为200
extern uint32_t g_effectiveTime;

};

using namespace eagle;

#endif

