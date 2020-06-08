#ifndef _HALOMEMALLOC_H_
#define _HALOMEMALLOC_H_

#include "Sys.h"
#include "Singleton.h"

namespace eagle
{

//not thread safe  
template<typename TYPE>
class StackMemAlloc
{
public:
    StackMemAlloc(uint32_t length = sizeof(TYPE)*10000);
    virtual ~StackMemAlloc();

    TYPE *AllocMem();
    //class TYPE()
    TYPE *NewMem();
    bool FreeMem(TYPE *);

private:
    void ResizeByExpand();

private:
    std::vector<TYPE*> m_recycleBuff;
    std::vector<char *> m_buff;
    uint32_t m_onceBuffLength;
    uint32_t m_maxCount;

    uint32_t m_useAt;
};

template<typename TYPE>
StackMemAlloc<TYPE>::StackMemAlloc(uint32_t length)
    :m_useAt(0)
{
    uint32_t typeLength = sizeof(TYPE);
    uint32_t count = length / typeLength;
    m_maxCount = count;
    m_onceBuffLength = count * typeLength;
    char *buf = new char[m_onceBuffLength];
    memset(buf, 0, m_onceBuffLength);
    m_buff.push_back(buf);

    m_recycleBuff.resize(count, 0);
    for (uint32_t i = 0; i < count; ++i)
    {
        m_recycleBuff[i] = (TYPE*)buf;
        buf += typeLength;
    }
}

template<typename TYPE>
StackMemAlloc<TYPE>::~StackMemAlloc()
{    
    m_recycleBuff.clear();

    for (uint32_t i = 0; i < m_buff.size(); ++i)
    {
        delete [] m_buff[i];
    }
    m_buff.clear();
}

template<typename TYPE>
TYPE *StackMemAlloc<TYPE>::AllocMem()
{
    if (m_useAt == m_maxCount - 1)
        ResizeByExpand();

    return m_recycleBuff[m_useAt++];
}

template<typename TYPE>
TYPE *StackMemAlloc<TYPE>::NewMem()
{
    if (m_useAt == m_maxCount - 1)
        ResizeByExpand();

    return new (m_recycleBuff[m_useAt++])TYPE();
}

template<typename TYPE>
bool StackMemAlloc<TYPE>::FreeMem(TYPE *ptr)
{
    if (!ptr)
        return false;

    bool isAt = false;
    for (uint32_t i = 0; i < m_buff.size(); ++i)
    {
        if ((void*)ptr >= m_buff[0] && (void*)ptr < m_buff[i] + m_onceBuffLength)
        {
            isAt = true;
            break;
        }
    }

    if (!isAt)
        return false;

    //ptr->Clear();
    m_recycleBuff[m_useAt--] = ptr;

    return true;
}

template<typename TYPE>
void StackMemAlloc<TYPE>::ResizeByExpand()
{
    char *buf = new char[m_onceBuffLength];
    memset(buf, 0, m_onceBuffLength);
    m_buff.push_back(buf);

    uint32_t typeLength = sizeof(TYPE);
    uint32_t count = m_onceBuffLength / typeLength;
    uint32_t oldCount = (uint32_t)m_recycleBuff.size();
    m_recycleBuff.resize(oldCount + count);

    for (uint32_t i = 0; i < count; ++i)
    {
        m_recycleBuff[oldCount + i] = (TYPE*)buf;
        buf += typeLength;
    }

    m_maxCount += count;

    return ;
}

};

#endif


