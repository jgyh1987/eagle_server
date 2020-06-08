#ifndef _MISC_H_
#define _MISC_H_

#include "Sys.h"

namespace eagle
{

#define FMTString(msg,msglen,pat)    \
    do    \
{    \
    va_list ap;    \
    bzero(msg, msglen);    \
    va_start(ap, pat);        \
    vsnprintf(msg, msglen - 1, pat, ap);    \
    va_end(ap);    \
}while(false)

#define CheckCondition(condition,ret) \
        if(!(condition))\
            return ret;
    
#define CheckConditionVoid(condition) \
        if(!(condition))\
            return ;

#define CheckLogCondition(condition, ret, msg, ...) \
        if(!(condition))\
        {\
            LOGD(msg, ##__VA_ARGS__);\
            return ret;\
        }

#define CheckLogConditionVoid(condition, msg, ...) \
        if(!(condition))\
        {\
            LOGD(player, msg, ##__VA_ARGS__);\
            return ;\
        }

};

#endif
