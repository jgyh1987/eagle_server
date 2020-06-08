#ifndef _ENTRY_H_
#define _ENTRY_H_

#include "Sys.h"
#include "Noncopyable.h"

namespace eagle
{

template <typename T,typename RTValue=bool>
struct CEntryCallback
{
    virtual RTValue exec(T *e)=0;
    virtual ~CEntryCallback(){};
};

};

#endif
