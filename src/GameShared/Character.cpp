#include "Character.h"
#include "Map.h"
#include "TimeTick.h"
#include "SharedEvent.h"
#include "ClientMsg.h"
#include "Global.h"

//Character
Character::Character(uint64_t uid)
    :WorldObject(uid), EventManagerInterface(g_trigger_to_event, EVENT_TYPE_MAX)
{
}

Character::~Character()
{
	if (m_parent)
	{
		m_parent->DelChild(this);
	}

	for (auto p : m_childs)
	{
		p->SetParent(NULL);
	}
}

void Character::Clear()
{

    return;
}

void Character::Update()
{

	return;
}

void Character::AddChild(Character *child)
{
    m_childs.push_back(child);

}

void Character::DelChild(Character *child)
{
    child->SetParent(NULL);
	VECTOR_REMOVE_PTR(m_childs, child);

    return;
}









