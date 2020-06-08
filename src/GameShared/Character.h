#ifndef _CHARACTER_H_ 
#define    _CHARACTER_H_

#include "WorldObject.h"
#include "PlayerInfo.h"
#include "CommonType.h"
#include "Skill.h"
#include "Buff.h"
#include "Map.h"
#include "Random.h"

class EagleEvent;
class EagleAction;

class Character : public WorldObject, public EventManagerInterface
{
public:
    Character(uint64_t uid);
    ~Character();

    uint32_t Type(){return OBJECT_CHARACTER;}
    virtual bool IsType(uint32_t type){return type == OBJECT_CHARACTER;}
    void Clear();

	virtual void Update();

public:
	bool IsAgent() { return true; }

    //
	inline Character* GetParent() { return m_parent; }
	inline void SetParent(Character* parent = NULL)
	{
		m_parent = parent;
		if (m_parent)
			m_parent->AddChild(this);
	}
    void AddChild(Character *child);
    void DelChild(Character *child);
    std::vector<Character *> &GetChilds(){return m_childs; }

	//临时 之后换掉
public:
	BuffManager m_buffMgr;
	BuffManager* GetBuffManager() { return &m_buffMgr; }

protected:
	Character *m_parent = NULL;
    std::vector<Character *> m_childs;


};



#endif    


