#ifndef _ECS_AIBEHAVIAC_H_ 
#define _ECS_AIBEHAVIAC_H_

#include "Sys.h"
#include "Singleton.h"
#include "ECS_Component.h"
#include "ECS_Entity.h"
#include "AIBehaviac.h"

class BehaviacComponent : public ECS::ECSComponent
{
public:
	enum
	{
		Type = ECS_CHAR_COMPONENT_TYPE_BEHAVIAC
	};

	BehaviacComponent(ECS::ECSEntity* owner)
		: ECSComponent(owner)
	{
	
	}

	uint32_t GetType() override { return BehaviacComponent::Type; }

public:
	BehaviorTree m_tree;

	eagle_hash_map<uint32_t, uint64_t> m_timers;
};

class BehaviacSystem : public CSingleton<BehaviacSystem>
{
public:
	bool SetTree(BehaviacComponent *, const std::string &);
	void RunBehaviac(BehaviacComponent *);
};

#endif    


