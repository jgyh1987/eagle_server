#include "AIBehaviacCondition.h"
#include "ECS_AIBehaviac.h"
#include "Logger.h"
#include "Random.h"
#include "ToolsFun.h"
#include "TimeTick.h"

namespace eagle
{
	//TrueCondNode
	TrueCondNode::~TrueCondNode()
	{

	}

	void TrueCondNode::LoadFromXml(CXMLParser& xml)
	{
		return;
	}

	void TrueCondNode::CopyFrom(BehaviacComponent*, const BehaviorNode* src)
	{

		return;
	}

	BehaviorNode* TrueCondNode::Exec(BehaviacComponent* cmp)
	{
		m_status = BT_SUCCESS;

		return BehaviorNode::Exec(cmp);
	}

	//FalseCondNode
	FalseCondNode::~FalseCondNode()
	{

	}

	void FalseCondNode::LoadFromXml(CXMLParser& xml)
	{
		return;
	}

	void FalseCondNode::CopyFrom(BehaviacComponent*, const BehaviorNode* src)
	{

		return;
	}

	BehaviorNode* FalseCondNode::Exec(BehaviacComponent* cmp)
	{
		m_status = BT_FAILURE;

		return BehaviorNode::Exec(cmp);
	}

	//TimerCondNode
	TimerCondNode::~TimerCondNode()
	{

	}

	void TimerCondNode::LoadFromXml(CXMLParser& xml)
	{
		std::string id;
		xml.getNodeAttrStr("TimerId", id);
		m_timerId = stoi(id);

		return;
	}

	void TimerCondNode::CopyFrom(BehaviacComponent*, const BehaviorNode* src)
	{
		auto node = (const TimerCondNode*)src;
		m_timerId = node->m_timerId;

		return;
	}

	BehaviorNode* TimerCondNode::Exec(BehaviacComponent* cmp)
	{
		m_status = BT_FAILURE;
		auto itr = cmp->m_timers.find(m_timerId);
		if (itr != cmp->m_timers.end())
		{
			if (CImpServerTimeTick::currentTime.msec() >= itr->second)
				m_status = BT_SUCCESS;
		}

		return BehaviorNode::Exec(cmp);
	}



}