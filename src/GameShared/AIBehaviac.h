#ifndef _AI_BEHAVIAC_H_ 
#define _AI_BEHAVIAC_H_

#include "Sys.h"
#include "XMLParser.h"
#include "Singleton.h"

class BehaviacComponent;

namespace eagle
{
	enum BTStatus
	{
		BT_INVALID,
		BT_SUCCESS,
		BT_FAILURE,
		BT_RUNNING,
	};

	enum BehaviorType
	{
		BehaviorType_Base = 0,
		BehaviorType_Selector = 1,//选择节点
		BehaviorType_Sequence = 2,
		BehaviorType_Random,
		BehaviorType_Parallel,
		BehaviorType_Condition,
		BehaviorType_Action,
		BehaviorType_Test,

		BehaviorType_Max
	};

	class BehaviorNode
	{
	public:
		std::string m_className;
		uint32_t m_nid;
		uint32_t m_status = BT_INVALID;
		BehaviorNode* m_parent = NULL;
		std::vector<BehaviorNode*> m_childrens;

	public:
		BehaviorNode(const std::string &classname, uint32_t nid, BehaviorNode *pre);
		virtual ~BehaviorNode();

		virtual uint32_t Type() = 0;
		virtual uint32_t SubType() { return 0; }
		virtual void LoadFromXml(CXMLParser& xml) = 0;
		virtual void CopyFrom(BehaviacComponent*, const BehaviorNode *) = 0;

		virtual BehaviorNode *Exec(BehaviacComponent *);

		inline uint32_t GetId() { return m_nid; }
		inline const std::string& GetClassName() { return m_className; }
		inline uint32_t GetStatus() { return m_status; }
		inline BehaviorNode* GetParent() { return m_parent; }

	};

	class BehaviorTree
	{
		friend class BehaviacConfigManager;
	public:
		~BehaviorTree();

		bool Init(BehaviacComponent* cmp, const std::string &treename);
		void Clear();

		inline BehaviorNode* GetRoot() { return m_root; }

	private:
		void CopyFrom(BehaviacComponent*, BehaviorNode *des, const BehaviorNode *src);

	private:
		BehaviorNode* m_root = NULL;

	};

	class BehaviacConfigManager : public CSingleton<BehaviacConfigManager>
	{
		typedef BehaviorNode* (BehaviacConfigManager::* CreateNode)(const std::string &classname, uint32_t nid, BehaviorNode *pre);

	public:
		bool LoadConfig(const std::string &path, const std::string & filename);

		BehaviorTree* GetTree(const std::string &treename);
		BehaviorNode* CreateBehaviorNode(const std::string &classname, uint32_t nid, BehaviorNode *pre);

#define AI_BEHAVIOR_NODE_CREATE(classname)	\
		BehaviorNode *Create##classname(const std::string &classname, uint32_t nid, BehaviorNode *pre);
#include "AIBehavior.inl"
#undef AI_BEHAVIOR_NODE_CREATE

	private:
		bool LoadNode(BehaviorTree &tree, BehaviorNode *, CXMLParser &xml);

	private:
		eagle_hash_map<std::string, BehaviorTree> m_datas;
		eagle_hash_map<std::string, CreateNode> m_createNodeFuns;

	};

	class TestNode : public BehaviorNode
	{
	public:
		using BehaviorNode::BehaviorNode;

		uint32_t Type() { return BehaviorType_Test; }
		void LoadFromXml(CXMLParser& xml) { return; }
		void CopyFrom(BehaviacComponent*, const BehaviorNode*);

		BehaviorNode* Exec(BehaviacComponent*);

	private:
		uint32_t m_test = 3;
	};

	class SelectorNode : public BehaviorNode
	{
	public:
		SelectorNode(const std::string& classname, uint32_t nid, BehaviorNode* pre)
			:BehaviorNode(classname, nid, pre)
		{
		}

		uint32_t Type() { return BehaviorType_Selector; }
		void LoadFromXml(CXMLParser& xml);
		void CopyFrom(BehaviacComponent*, const BehaviorNode*);

		BehaviorNode* Exec(BehaviacComponent*);

	};

	class SequenceNode : public BehaviorNode
	{
	public:
		using BehaviorNode::BehaviorNode;

		uint32_t Type() { return BehaviorType_Sequence; }
		void LoadFromXml(CXMLParser& xml);
		void CopyFrom(BehaviacComponent*, const BehaviorNode*);

		BehaviorNode* Exec(BehaviacComponent*);

	};

	class ParallelNode : public BehaviorNode
	{
		uint32_t m_failure = 0;
		uint32_t m_success = 0;
		uint32_t m_exit = 0;
	public:
		using BehaviorNode::BehaviorNode;

		uint32_t Type() { return BehaviorType_Parallel; }
		void LoadFromXml(CXMLParser& xml);
		void CopyFrom(BehaviacComponent*, const BehaviorNode*);

		BehaviorNode* Exec(BehaviacComponent*);

	};

	class RandomNode : public BehaviorNode
	{
		std::vector<uint32_t> m_randoms;
		uint32_t m_allRate = 0;

	public:
		using BehaviorNode::BehaviorNode;

		uint32_t Type() { return BehaviorType_Random; }
		void LoadFromXml(CXMLParser& xml);
		void CopyFrom(BehaviacComponent*, const BehaviorNode*);

		BehaviorNode* Exec(BehaviacComponent*);

	private:
		BehaviorNode* RandomOnceNode();

	};

}

#endif    


