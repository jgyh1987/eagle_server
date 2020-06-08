#include "AIBehaviac.h"
#include "ECS_AIBehaviac.h"
#include "Logger.h"
#include "Random.h"
#include "ToolsFun.h"
#include "AIBehaviacAction.h"

namespace eagle
{
#define AI_BEHAVIOR_NODE_CREATE(classname)	\
		BehaviorNode *BehaviacConfigManager::Create##classname(const std::string &classname, uint32_t nid, BehaviorNode *pre){return new classname##Node(classname, nid, pre);}
#include "AIBehavior.inl"
#undef AI_BEHAVIOR_NODE_CREATE


	bool BehaviacConfigManager::LoadConfig(const std::string& path, const std::string& filename)
	{
#define AI_BEHAVIOR_NODE_CREATE(classname) \
		m_createNodeFuns[#classname] = &BehaviacConfigManager::Create##classname;
#include "AIBehavior.inl"
#undef AI_BEHAVIOR_NODE_CREATE

		eagle_hash_set<std::string> behaviors;
		{
			CXMLParser xml;
			std::string fullname = path + filename;
			if (!xml.loadFile(fullname.c_str()))
			{
				return false;
			}

			if (!xml.setCurNode("config"))
			{
				return false;
			}

			if (xml.setChildNode("behavior"))
			{
				do
				{
					std::string name;
					xml.getNodeAttrStr("name", name);

					if (name.length())
						behaviors.emplace(name);

				} while (xml.setNextNode());
			}
		}

		eagle_hash_map< std::string, eagle_hash_map<std::string, std::string> > temps;
		{
			for (auto& name : behaviors)
			{
				std::string filefullname = path + "Behavior/" + name + ".xml";

				CXMLParser xml;
				if (!xml.loadFile(filefullname.c_str()))
				{
					continue;
				}

				auto itr = m_datas.emplace(std::pair<std::string, BehaviorTree>(name, BehaviorTree()));
				if (!itr.second)
					continue;

				if (!xml.setCurNode("behavior"))
					continue;

				if (xml.setChildNode("node"))
				{
					std::string classname, nid;
					xml.getNodeAttrStr("class", classname);
					xml.getNodeAttrStr("id", nid);
					auto root = CreateBehaviorNode(classname, (uint32_t)stoi(nid), NULL);
					if (root)
					{
						itr.first->second.m_root = root;
						LoadNode(itr.first->second, itr.first->second.m_root, xml);
					}
				}
			}
		}

		return true;
	}

	BehaviorTree* BehaviacConfigManager::GetTree(const std::string& treename)
	{
		auto itr = m_datas.find(treename);
		if (itr == m_datas.end())
			return NULL;

		return &itr->second;
	}

	BehaviorNode* BehaviacConfigManager::CreateBehaviorNode(const std::string& classname, uint32_t nid, BehaviorNode* pre)
	{
		auto itr = m_createNodeFuns.find(classname);
		if (itr != m_createNodeFuns.end())
			return (this->*itr->second)(classname, nid, pre);

		return new TestNode(classname, nid, pre);
	}

	//private
	bool BehaviacConfigManager::LoadNode(BehaviorTree& tree, BehaviorNode* node, CXMLParser& xml)
	{
		node->LoadFromXml(xml);

		if (xml.setChildNode("node"))
		{
			do
			{
				std::string classname, nid;
				xml.getNodeAttrStr("class", classname);
				xml.getNodeAttrStr("id", nid);
				auto childnode = CreateBehaviorNode(classname, (uint32_t)stoi(nid), node);
				if (childnode)
				{
					node->m_childrens.push_back(childnode);
					LoadNode(tree, childnode, xml);
				}

			} while (xml.setNextNode());

			
		}

		xml.setUpNode();

		return true;
	}

	//BehaviorNode
	BehaviorNode::BehaviorNode(const std::string& classname, uint32_t nid, BehaviorNode* pre)
		:m_className(classname), m_nid(nid), m_parent(pre)
	{
		LOGD("BehaviorNode::Create classname = " << m_className << "  nid = " << m_nid << "  !!!");
	}

	BehaviorNode::~BehaviorNode()
	{
		for (auto p : m_childrens)
			SAFE_DELETE(p);
		m_childrens.clear();
	}

	BehaviorNode* BehaviorNode::Exec(BehaviacComponent*)
	{
		LOGD("BehaviorNode::Exec classname = " << m_className << "  nid = " << m_nid << " status = " << m_status << "  !!!");

		return this;
	}

	//BehaviorTree
	BehaviorTree::~BehaviorTree()
	{
		SAFE_DELETE(m_root);
	}

	bool BehaviorTree::Init(BehaviacComponent* cmp, const std::string& treename)
	{
		Clear();
		auto tree = BehaviacConfigManager::instance()->GetTree(treename);
		if (!tree)
			return false;

		auto src = tree->GetRoot();
		m_root = BehaviacConfigManager::instance()->CreateBehaviorNode(src->GetClassName(), src->GetId(), NULL);
		if (!m_root)
			return false;

		CopyFrom(cmp, m_root, src);

		return true;
	}

	void BehaviorTree::Clear()
	{
		SAFE_DELETE(m_root);
	}

	void BehaviorTree::CopyFrom(BehaviacComponent* cmp, BehaviorNode* des, const BehaviorNode* src)
	{
		des->CopyFrom(cmp, src);

		for (auto p : src->m_childrens)
		{
			auto node = BehaviacConfigManager::instance()->CreateBehaviorNode(p->GetClassName(), p->GetId(), des);
			if (!node)
				continue;
			des->m_childrens.push_back(node);
			CopyFrom(cmp, node, p);
		}

		return;
	}

	//TestNode
	void TestNode::CopyFrom(BehaviacComponent*, const BehaviorNode* src)
	{
		return;
	}

	BehaviorNode* TestNode::Exec(BehaviacComponent* cmp)
	{
		if (m_test > 0)
		{
			--m_test;
			m_status = BT_RUNNING;
		}
		else
		{
			m_test = 3;
			m_status = BT_SUCCESS;
		}
		
		return BehaviorNode::Exec(cmp);
	}

	//SelectorNode
	void SelectorNode::LoadFromXml(CXMLParser& xml)
	{

		return;
	}

	void SelectorNode::CopyFrom(BehaviacComponent*, const BehaviorNode* src)
	{
		return;
	}

	BehaviorNode* SelectorNode::Exec(BehaviacComponent* cmp)
	{
		uint32_t i = 0;
		if (BT_RUNNING == m_status)
		{
			for (; i < m_childrens.size(); ++i)
			{
				if (m_childrens[i]->GetStatus() == BT_RUNNING)
					break;
			}
		}
		else
		{
			m_status = BT_SUCCESS;
		}

		for (; i < m_childrens.size(); ++i)
		{
			m_status = m_childrens[i]->Exec(cmp)->GetStatus();
			if (BT_SUCCESS == m_status || BT_RUNNING == m_status)
				break;
		}

		return BehaviorNode::Exec(cmp);
	}

	//SequenceNode
	void SequenceNode::LoadFromXml(CXMLParser& xml)
	{

		return;
	}

	void SequenceNode::CopyFrom(BehaviacComponent*, const BehaviorNode* src)
	{
		return;
	}

	BehaviorNode* SequenceNode::Exec(BehaviacComponent* cmp)
	{
		uint32_t i = 0;
		if (BT_RUNNING == m_status)
		{
			for (; i < m_childrens.size(); ++i)
			{
				if (BT_RUNNING == m_childrens[i]->GetStatus())
					break;
			}
		}
		else
		{
			m_status = BT_SUCCESS;
		}

		for (; i < m_childrens.size(); ++i)
		{
			m_status = m_childrens[i]->Exec(cmp)->GetStatus();
			if (BT_FAILURE == m_status || BT_RUNNING == m_status)
				break;
		}

		return BehaviorNode::Exec(cmp);
	}

	//ParallelNode
	void ParallelNode::LoadFromXml(CXMLParser& xml)
	{
		std::string failure, success, exit;
		xml.getNodeAttrStr("FailurePolicy", failure);
		xml.getNodeAttrStr("SuccessPolicy", success);
		xml.getNodeAttrStr("ExitPolicy", exit);

		m_failure = 1;// (uint32_t)stoi(failure);
		m_success = 3;// (uint32_t)stoi(success);
		m_exit = 2;// (uint32_t)stoi(exit);

		return;
	}

	void ParallelNode::CopyFrom(BehaviacComponent*, const BehaviorNode* src)
	{
		auto node = (const ParallelNode*)src;
		m_failure = node->m_failure;
		m_success = node->m_success;
		m_exit = node->m_exit;

		return;
	}

	BehaviorNode* ParallelNode::Exec(BehaviacComponent* cmp)
	{
		m_status = BT_SUCCESS;

		for (auto p : m_childrens)
		{
			auto node = p->Exec(cmp);

			if (BT_RUNNING == node->m_status)
			{
				m_status = BT_RUNNING;
			}
		}

		return BehaviorNode::Exec(cmp);
	}

	//RandomNode
	void RandomNode::LoadFromXml(CXMLParser& xml)
	{
		std::string randoms;
		xml.getNodeAttrStr("Randoms", randoms);
		parseStrToVecInt(randoms, m_randoms, ',');

		for (auto& itr : m_randoms)
		{
			itr += m_allRate;
			m_allRate = itr;
		}

		return;
	}

	void RandomNode::CopyFrom(BehaviacComponent*, const BehaviorNode* src)
	{
		auto node = (const RandomNode*)src;
		m_randoms = node->m_randoms;
		m_allRate = node->m_allRate;

		return;
	}

	BehaviorNode* RandomNode::Exec(BehaviacComponent* cmp)
	{
		BehaviorNode* node = NULL;
		if (BT_RUNNING == m_status)
		{
			for (auto p : m_childrens)
			{
				if (BT_RUNNING == p->GetStatus())
				{
					node = p;
					break;
				}
			}
		}
		else
		{
			m_status = BT_SUCCESS;
		}

		if (!node)
			node = RandomOnceNode();

		if (!node)
			m_status = BT_FAILURE;
		else
		{
			m_status = node->Exec(cmp)->GetStatus();
		}

		return BehaviorNode::Exec(cmp);
	}

	BehaviorNode* RandomNode::RandomOnceNode()
	{
		if (!m_childrens.size())
			return NULL;

		auto rate = CRandom::RandomBetween(0, m_allRate);
		for (uint32_t i = 0; i < m_randoms.size(); ++i)
		{
			if (rate < m_randoms[i])
			{
				if (i < m_childrens.size())
					return m_childrens[i];
				else
					return m_childrens[m_childrens.size() - 1];
			}
		}

		return NULL;
	}

}


