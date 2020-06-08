#include "AIBehaviacAction.h"
#include "ECS_AIBehaviac.h"
#include "Logger.h"
#include "Random.h"
#include "ToolsFun.h"
#include "TimeTick.h"

namespace eagle
{
	//WanderNode
	WanderNode::~WanderNode()
	{

	}

	void WanderNode::LoadFromXml(CXMLParser& xml)
	{
		std::string radius;
		xml.getNodeAttrStr("Radius", radius);
		m_radius = stod(radius);

		return;
	}

	void WanderNode::CopyFrom(BehaviacComponent*, const BehaviorNode* src)
	{
		auto node = (const WanderNode*)src;
		m_radius = node->m_radius;

		return;
	}

	BehaviorNode* WanderNode::Exec(BehaviacComponent* cmp)
	{
		if (BT_RUNNING == m_status)
		{
			if (m_randomsPath <= 0)
			{
				m_status = BT_SUCCESS;
			}
			else
			{
				--m_randomsPath;
			}
		
		}
		else
		{
			m_randomsPath = (double)CRandom::RandomBetween(1, (uint32_t)m_radius + 1);

			m_status = BT_RUNNING;
		}

		return BehaviorNode::Exec(cmp);
	}

	//IdleNode
	IdleNode::~IdleNode()
	{
	
	}

	void IdleNode::LoadFromXml(CXMLParser& xml)
	{
		std::string delay;
		xml.getNodeAttrStr("Delay", delay);
		m_delay = stoull(delay);

		return;
	}

	void IdleNode::CopyFrom(BehaviacComponent*, const BehaviorNode* src)
	{
		auto node = (const IdleNode*)src;
		m_delay = node->m_delay;

		return;
	}

	BehaviorNode* IdleNode::Exec(BehaviacComponent* cmp)
	{
		if (BT_RUNNING == m_status)
		{
			if (CImpServerTimeTick::currentTime.msec() > m_endTime)
			{
				m_status = BT_SUCCESS;
			}
			else
			{
			}

		}
		else
		{
			m_endTime = CImpServerTimeTick::currentTime.msec() + m_delay;

			m_status = BT_RUNNING;
		}

		return BehaviorNode::Exec(cmp);
	}

	//SetTimerNode
	SetTimerNode::~SetTimerNode()
	{

	}

	void SetTimerNode::LoadFromXml(CXMLParser& xml)
	{
		std::string delay, id;
		xml.getNodeAttrStr("TimerId", id);
		xml.getNodeAttrStr("Delay", delay);
		m_delay = stoull(delay);
		m_timerId = stoi(id);

		return;
	}

	void SetTimerNode::CopyFrom(BehaviacComponent*, const BehaviorNode* src)
	{
		auto node = (const SetTimerNode*)src;
		m_delay = node->m_delay;
		m_timerId = node->m_timerId;

		return;
	}

	BehaviorNode* SetTimerNode::Exec(BehaviacComponent* cmp)
	{
		cmp->m_timers[m_timerId] = CImpServerTimeTick::currentTime.msec() + m_delay;

		return BehaviorNode::Exec(cmp);
	}



}