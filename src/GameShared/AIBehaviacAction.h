#ifndef _AI_BEHAVIAC_ACTION_H_ 
#define _AI_BEHAVIAC_ACTION_H_

#include "Sys.h"
#include "XMLParser.h"
#include "Singleton.h"
#include "AIBehaviac.h"

class BehaviacComponent;

namespace eagle
{
	enum BehaviorActionType
	{
		BehaviorActionType_Base = 0,
		BehaviorActionType_Wander = 1,//
		BehaviorActionType_Idle = 2,
		BehaviorActionType_Timer = 3,

		BehaviorActionType_Max
	};

	class WanderNode : public BehaviorNode
	{
	public:
		double m_radius = 10.0;

	public:
		using BehaviorNode::BehaviorNode;
		~WanderNode();

		uint32_t Type() { return BehaviorType_Action; }
		uint32_t SubType() { return BehaviorActionType_Wander; }
		void LoadFromXml(CXMLParser& xml);
		void CopyFrom(BehaviacComponent*, const BehaviorNode*);

		BehaviorNode* Exec(BehaviacComponent*);

	private:
		double m_randomsPath = 0.0;
	};

	class IdleNode : public BehaviorNode
	{
	public:
		uint64_t m_delay = 1000;

	public:
		using BehaviorNode::BehaviorNode;
		~IdleNode();

		uint32_t Type() { return BehaviorType_Action; }
		uint32_t SubType() { return BehaviorActionType_Idle; }
		void LoadFromXml(CXMLParser& xml);
		void CopyFrom(BehaviacComponent*, const BehaviorNode*);

		BehaviorNode* Exec(BehaviacComponent*);

	private:
		uint64_t m_endTime = 0;
	};

	class SetTimerNode : public BehaviorNode
	{
	public:
		uint32_t m_timerId = 0;
		uint64_t m_delay = 1000;

	public:
		using BehaviorNode::BehaviorNode;
		~SetTimerNode();

		uint32_t Type() { return BehaviorType_Action; }
		uint32_t SubType() { return BehaviorActionType_Idle; }
		void LoadFromXml(CXMLParser& xml);
		void CopyFrom(BehaviacComponent*, const BehaviorNode*);

		BehaviorNode* Exec(BehaviacComponent*);

	private:
	};
}

#endif    


