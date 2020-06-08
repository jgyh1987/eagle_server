#ifndef _EAGLE_ACTION_H_ 
#define    _EAGLE_ACTION_H_

#include "Sys.h"

#define ACTION_TYPE_NONE 0

class EagleEvent;
class EagleCondition;

class EagleAction
{
protected:
    std::vector<EagleCondition *> m_conditions;
    void *m_object;
    bool m_end;

public:
    EagleAction(void * ptr1);
    virtual ~EagleAction();

    //return false is more  and return true is once
    virtual bool DoAction(EagleEvent *_event) = 0;

    virtual void UpdateCondition(EagleEvent *_event);
    virtual bool IsComplete();
    
    virtual uint32_t Id() = 0;

    void ReSet();

    inline bool IsEnd(){return m_end;}
    inline void PushCondition(EagleCondition *condition)
    {
        m_conditions.push_back(condition);
    }
    inline std::vector<EagleCondition *> &GetConditions()
    {
        return m_conditions;
    }
};

class Test1 : public EagleAction
{
    std::string m_test;
public:
    Test1(void * ptr1, void *ptr2)
        :EagleAction(ptr1), m_test((char *)ptr2)
    {
    }

    uint32_t Id(){return ACTION_TYPE_NONE;}

    bool DoAction(EagleEvent *_event);
};

#endif    


