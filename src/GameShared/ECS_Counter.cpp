#include "ECS_Counter.h"
#include "TimeTick.h"

bool CounterSystem::InitEntityData(ECS::ECSEntity* entity)
{


	return true;
}

bool CounterSystem::OnEnterServer(ECS::ECSEntity* entity)
{
	auto counterCmp = entity->GetComponent<CounterComponent>();
	if (!counterCmp)
		return false;

	counterCmp->m_counters.Refresh();

	return true;
}

void CounterSystem::Clear(ECS::ECSEntity* entity)
{
	auto counterCmp = entity->GetComponent<CounterComponent>();
	if (!counterCmp)
		return;

	counterCmp->m_counters.Clear();

	return;
}

uint32_t CounterSystem::Serialize(ECS::ECSEntity* entity, uint8_t* buffer)
{
	auto counterCmp = entity->GetComponent<CounterComponent>();
	if (!counterCmp)
		return 0;

	return counterCmp->m_counters.Serialize(buffer);
}

uint32_t CounterSystem::UnSerialize(ECS::ECSEntity* entity, uint8_t* buffer)
{
	auto counterCmp = entity->GetComponent<CounterComponent>();
	if (!counterCmp)
	{
		uint32_t* pLen = (uint32_t*)buffer;
		return *pLen;
	}

	return counterCmp->m_counters.UnSerialize(buffer);
}

uint32_t CounterSystem::GetCounter(ECS::ECSEntity* entity, uint32_t type)
{
	auto counterCmp = entity->GetComponent<CounterComponent>();
	if (!counterCmp)
		return 0;

	return counterCmp->m_counters.GetCounter(type);
}

void CounterSystem::AddCounter(ECS::ECSEntity* entity, uint32_t type, int32_t addon, int32_t timeType)
{
	auto counterCmp = entity->GetComponent<CounterComponent>();
	if (!counterCmp)
		return;

	counterCmp->m_counters.AddCounter(type, addon, timeType);

	return;
}

void CounterSystem::SubCounter(ECS::ECSEntity* entity, uint32_t type, int32_t subValue)
{
	auto counterCmp = entity->GetComponent<CounterComponent>();
	if (!counterCmp)
		return;

	counterCmp->m_counters.SubCounter(type, subValue);

	return;
}

void CounterSystem::SetCounter(ECS::ECSEntity* entity, uint32_t type, int32_t val, int32_t timeType)
{
	auto counterCmp = entity->GetComponent<CounterComponent>();
	if (!counterCmp)
		return;

	counterCmp->m_counters.SetCounter(type, val, timeType);

	return;
}

void CounterSystem::RemoveCounter(ECS::ECSEntity* entity, uint32_t type)
{
	auto counterCmp = entity->GetComponent<CounterComponent>();
	if (!counterCmp)
		return;

	counterCmp->m_counters.RemoveCounter(type);

	return;
}


