#ifndef _AI_BEHAVIAC_CONDITION_H_ 
#define _AI_BEHAVIAC_CONDITION_H_

#include "Sys.h"
#include "XMLParser.h"
#include "Singleton.h"
#include "AIBehaviac.h"

class BehaviacComponent;

namespace eagle
{
	enum BehaviorConditionType
	{
		BehaviorConditionType_Base = 0,
		BehaviorConditionType_True = 1,//
		BehaviorConditionType_False = 2,//
		BehaviorConditionType_Timer = 3,//


		BehaviorConditionType_Max
	};

	class TrueCondNode : public BehaviorNode
	{
	public:
	

	public:
		using BehaviorNode::BehaviorNode;
		~TrueCondNode();

		uint32_t Type() { return BehaviorType_Condition; }
		uint32_t SubType() { return BehaviorConditionType_True; }
		void LoadFromXml(CXMLParser& xml);
		void CopyFrom(BehaviacComponent*, const BehaviorNode*);

		BehaviorNode* Exec(BehaviacComponent*);

	private:
	
	};

	class FalseCondNode : public BehaviorNode
	{
	public:


	public:
		using BehaviorNode::BehaviorNode;
		~FalseCondNode();

		uint32_t Type() { return BehaviorType_Condition; }
		uint32_t SubType() { return BehaviorConditionType_True; }
		void LoadFromXml(CXMLParser& xml);
		void CopyFrom(BehaviacComponent*, const BehaviorNode*);

		BehaviorNode* Exec(BehaviacComponent*);

	private:

	};

	class TimerCondNode : public BehaviorNode
	{
	public:
		uint32_t m_timerId = 0;

	public:
		using BehaviorNode::BehaviorNode;
		~TimerCondNode();

		uint32_t Type() { return BehaviorType_Condition; }
		uint32_t SubType() { return BehaviorConditionType_True; }
		void LoadFromXml(CXMLParser& xml);
		void CopyFrom(BehaviacComponent*, const BehaviorNode*);

		BehaviorNode* Exec(BehaviacComponent*);

	private:

	};
}

#endif    


