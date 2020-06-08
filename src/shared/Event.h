#ifndef _EAGLE_EVENT_H_ 
#define    _EAGLE_EVENT_H_

#include "Sys.h"

#define EVENT_TYPE_NONE 0

class EagleCondition;
class EagleAction;

class EagleEvent
{
public:
    EagleEvent(void *ptr)
        :m_exParam(ptr)
    {
    
    }
    virtual ~EagleEvent() = 0;

    virtual uint32_t Id() = 0; 
    virtual void DoEvent(void *ptr){}

    inline void *ExParam()
    {
        return m_exParam;
    }
protected:
    void *m_exParam;
};

template <class T>
class LogicDoEvent
{
protected:
    T *m_ptr;
    EagleEvent &m_event;
public:
    LogicDoEvent(T * ptr, EagleEvent &event)
        :m_ptr(ptr), m_event(event)
    {}

    ~LogicDoEvent()
    {
    }
    
    inline uint32_t Id(){return m_event.Id();}
    void operator () ()
    {
        m_event.DoEvent(m_ptr);
        m_ptr->DoEvent(&m_event);
    }

protected:
};


class OnNoneEvent : public EagleEvent
{
public:
    OnNoneEvent(void *ptr = NULL);

    uint32_t Id(){return EVENT_TYPE_NONE;}
    
};

class EventManager
{
public:
    EventManager(std::vector<uint32_t> &conditionIdToEventId, uint32_t eventSize)
        :m_conditionIdToEventId(conditionIdToEventId)
    {
        m_events.resize(eventSize);
    }

    ~EventManager();

    void Register(EagleAction *action);
    void UnRegister(std::vector<EagleAction *> &actions);
    void UnRegister(EagleAction *action);
    void DoEvent(EagleEvent *);

private:
    std::vector< std::map<uint64_t, EagleCondition *> > m_events;
    std::vector<uint32_t> &m_conditionIdToEventId;
};

class EventManagerInterface
{
public:
	EventManagerInterface(std::vector<uint32_t> &vec, uint32_t typeMax)
		:m_eventManager(vec, typeMax)
	{
	}
	virtual ~EventManagerInterface();

	inline EventManager *GetEventManager() { return &m_eventManager; }

	void DoEvent(EagleEvent*);
	void RegisterEventAction(EagleAction*);
	void UnRegisterEventAction(std::vector<EagleAction*>& actions);
	void UnRegisterEventAction(EagleAction* action);

protected:
	EventManager m_eventManager;
	std::vector<EagleAction *> m_actions;
};


#endif    


