#ifndef _EAGLE_CONDITION_H_ 
#define    _EAGLE_CONDITION_H_

#include "StringTool.h"
#include "CObject.h"

#define CONDITION_TYPE_NONE 0

class EagleEvent;
class EagleAction;

class EagleCondition : public CObjectBase
{
protected:
    int64_t m_var;
    int64_t m_curVar; 
    EagleAction *m_action;

    virtual bool UpdateImp(EagleEvent *) = 0;
public:
    EagleCondition(EagleAction *action);
    virtual ~EagleCondition() = 0;

    virtual bool operator()();

    virtual uint32_t Id() = 0; 

    inline int64_t GetCurVar(){return m_curVar;}
    inline void SetCurVar(int64_t var){m_curVar = var;}

    void Update(EagleEvent *);
};

class NoneCondition : public EagleCondition 
{
protected:
    bool UpdateImp(EagleEvent *);

public:

public:
    NoneCondition( EagleAction *action, const char* param );
    NoneCondition( EagleAction *action, const std::vector<double> &param );

    bool operator()();
    uint32_t Id(){return CONDITION_TYPE_NONE;}
};

#endif    


