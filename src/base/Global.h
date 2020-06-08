#ifndef _EAGLE_GLOBAL_H_
#define _EAGLE_GLOBAL_H_

#include "Sys.h"
#include "Logger.h"
#include "ParamMap.h"

namespace eagle
{
    /// @brief 
    extern CLogger g_logger;
    /// @brief 
    extern CParamMap global;

#define MAP_REMOVE(m, k) \
        {                        \
            auto itr = m.find(k);    \
            if (itr != m.end())        \
                m.erase(itr);        \
        }

#define MAPMAP_REMOVE(m, k1, k2) \
        {                        \
            auto itr = m.find(k1);    \
            if (itr != m.end())        \
            {                        \
                auto itr1 = itr->second.find(k2);    \
                if (itr1 != itr->second.end())        \
                    itr->second.erase(itr1);        \
            }                            \
        }

    //仅VECTOR内是指针可用
#define VECTOR_REMOVE_PTR(v, p)    \
    {        \
        for (uint32_t i = 0; i < v.size(); ++i)    \
        {    \
            if (v[i] == p)                    \
            {    \
                v[i] = v[v.size() - 1];        \
                v.pop_back();                \
                break;                        \
            }    \
        }    \
    }

 #define VECTOR_REMOVE_INDEX(v, i)  \
        {   \
            if (i + 1 < v.size())   \
            {   \
                v[i] = v[v.size() - 1]; \
            }   \
            v.pop_back();           \
        }
};

#endif


