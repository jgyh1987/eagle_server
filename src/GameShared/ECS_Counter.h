#ifndef _ECS_COUNTER_H_ 
#define _ECS_COUNTER_H_

#include "Sys.h"
#include "Singleton.h"
#include "CObject.h"
#include "ECS_Component.h"
#include "ECS_Entity.h"
#include "Counter.h"
#include "ECS_System.h"

class CounterComponent : public ECS::ECSComponent
{
public:
	enum
	{
		Type = ECS_PLAYER_COMPONENT_TYPE_COUNTER
	};

	CounterComponent(ECS::ECSEntity* owner)
		:ECSComponent(owner)
	{

	}

	uint32_t GetType() override { return CounterComponent::Type; }

public:
	EagleCounter m_counters;
}; 

class CounterSystem : public ECS::ECSSystem, public CSingleton<CounterSystem>
{
public:
	bool InitEntityData(ECS::ECSEntity*) override;
	bool OnEnterServer(ECS::ECSEntity* entity) override;
	void Clear(ECS::ECSEntity* entity) override;
	uint32_t Serialize(ECS::ECSEntity*, uint8_t* buffer) override;
	uint32_t UnSerialize(ECS::ECSEntity*, uint8_t* buffer) override;

	uint32_t GetCounter(ECS::ECSEntity* entity, uint32_t type);

	void AddCounter(ECS::ECSEntity* entity, uint32_t type, int32_t addon = 1, int32_t timeType = COUNTER_TIME_ETERNAL);
	void SubCounter(ECS::ECSEntity* entity, uint32_t type, int32_t subValue = 1);

	void SetCounter(ECS::ECSEntity* entity, uint32_t type, int32_t val, int32_t timeType = COUNTER_TIME_ETERNAL);

	void RemoveCounter(ECS::ECSEntity* entity, uint32_t type);

};


#endif

