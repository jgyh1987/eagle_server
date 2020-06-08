#include "ECS_Quest.h"
#include "WGamePlayer.h"

//Quest
Quest::Quest(const QuestConfigData* data, uint32_t status)
	:m_data(data), m_status(status), m_isRegist(false)
{
	m_action = NULL;
}

Quest::~Quest()
{
	SAFE_DELETE(m_action);
}

void Quest::SetConditionCurVal(uint32_t conditionId, int64_t curval)
{
	if (!m_action)
		return;

	for (uint32_t i = 0; i < m_action->GetConditions().size(); ++i)
	{
		if (conditionId == m_action->GetConditions()[i]->Id())
			m_action->GetConditions()[i]->SetCurVar(curval);
	}

	return;
}

//QuestComponent
QuestComponent::~QuestComponent()
{
	for (auto& itr : m_quests)
	{
		SAFE_DELETE(itr.second);
	}
}

//QuestSystem
void QuestSystem::Init()
{
	auto itr = QuestConfigDataManager::instance()->begin();
	for (; itr != QuestConfigDataManager::instance()->end(); ++itr)
	{
		if (itr->preCondition.size())
		{
			m_quests[itr->preCondition[0].type].push_back(&(*itr));
		}
	}

	return;
}

bool QuestSystem::InitEntityData(ECS::ECSEntity* entity)
{
	auto questCmp = entity->GetComponent<QuestComponent>();
	if (!questCmp)
		return false;

	auto v = GetQuestMapByPreConditionType(QUEST_PRE_CONDITION_TYPE_NONE);
	for (uint32_t i = 0; i < v->size(); ++i)
	{
		if ((*v)[i]->initAccept)
		{
			questCmp->m_canAppectQuests.emplace((*v)[i]->id);
		}
		else
		{
			AddQuest(questCmp, (*v)[i], QUEST_STATUS_ACCEPT, false);
		}
	}

	return true;
}

bool QuestSystem::OnEnterServer(ECS::ECSEntity* entity)
{
	auto questCmp = entity->GetComponent<QuestComponent>();
	if (!questCmp)
		return false;

	for (auto& itr : questCmp->m_quests)
	{
		auto quest = itr.second;
		if (quest->m_action && GamePlayerSystem::instance()->RegisterEventAction(entity, quest->m_action))
		{
			quest->m_isRegist = true;
		}
			
	}

	return true;
}

void QuestSystem::Clear(ECS::ECSEntity* entity)
{
	auto questCmp = entity->GetComponent<QuestComponent>();
	if (!questCmp)
		return;

	for (auto& itr : questCmp->m_quests)
	{
		if (itr.second->m_isRegist)
		{
			GamePlayerSystem::instance()->UnRegisterEventAction(entity, itr.second->m_action);
		}

		SAFE_DELETE(itr.second);
	}
	questCmp->m_quests.clear();

	return;
}

uint32_t QuestSystem::Serialize(ECS::ECSEntity* entity, uint8_t* buffer)
{
	auto questCmp = entity->GetComponent<QuestComponent>();
	if (!questCmp)
		return 0;

	uint32_t length = 0;
	uint32_t* pLen = (uint32_t*)buffer;
	BuffWriteMoveLen(buffer, length, UINT32_LEN);

	BuffWriteInt(buffer, length, QUESTMANAGERVERSION_1_1);

	BuffWriteInt(buffer, length, (uint32_t)questCmp->m_closeQuests.size());
	for (auto itr = questCmp->m_closeQuests.begin(); itr != questCmp->m_closeQuests.end(); ++itr)
	{
		BuffWriteInt64(buffer, length, *itr);
	}

	BuffWriteInt(buffer, length, (uint32_t)questCmp->m_canAppectQuests.size());
	for (auto itr = questCmp->m_canAppectQuests.begin(); itr != questCmp->m_canAppectQuests.end(); ++itr)
	{
		BuffWriteInt64(buffer, length, *itr);
	}

	BuffWriteInt(buffer, length, (uint32_t)questCmp->m_quests.size());
	for (auto itr = questCmp->m_quests.begin(); itr != questCmp->m_quests.end(); ++itr)
	{
		BuffWriteInt64(buffer, length, itr->second->Id());
		BuffWriteInt(buffer, length, itr->second->m_status);

		if (itr->second->m_action)
		{
			BuffWriteInt(buffer, length, (uint32_t)itr->second->m_action->GetConditions().size());
			for (uint32_t i = 0; i < itr->second->m_action->GetConditions().size(); ++i)
			{
				BuffWriteInt(buffer, length, itr->second->m_action->GetConditions()[i]->Id());
				BuffWriteInt64(buffer, length, itr->second->m_action->GetConditions()[i]->GetCurVar());
			}
		}
		else
		{
			BuffWriteInt(buffer, length, 0);
		}
	}

	*pLen = length;

	return length;
}

uint32_t QuestSystem::UnSerialize(ECS::ECSEntity* entity, uint8_t* buffer)
{
	uint32_t length = 0;
	BuffLoadInt(buffer, length, length);
	uint32_t ret = length + UINT32_LEN;

	auto questCmp = entity->GetComponent<QuestComponent>();
	if (!questCmp)
	{
		return ret;
	}

	BuffLoadMoveLen(buffer, length, UINT32_LEN);	//version

	uint32_t count = 0;
	BuffLoadInt(buffer, length, count);
	for (uint32_t i = 0; i < count; ++i)
	{
		uint64_t id = 0;
		BuffLoadInt64(buffer, length, id);

		questCmp->m_closeQuests.emplace(id);
	}

	count = 0;
	BuffLoadInt(buffer, length, count);
	for (uint32_t i = 0; i < count; ++i)
	{
		uint64_t id = 0;
		BuffLoadInt64(buffer, length, id);

		questCmp->m_canAppectQuests.emplace(id);
	}

	count = 0;
	BuffLoadInt(buffer, length, count);
	for (uint32_t i = 0; i < count; ++i)
	{
		uint64_t id = 0;
		uint32_t status = 0;
		BuffLoadInt64(buffer, length, id);
		BuffLoadInt(buffer, length, status);

		QuestConfigData* data = QuestConfigDataManager::instance()->get(id);
		Quest* quest = NULL;
		if (data)
		{
			quest = AddQuest(questCmp, data, status, true);
		}

		uint32_t conditionCount = 0;
		BuffLoadInt(buffer, length, conditionCount);
		if (quest)
		{
			for (uint32_t j = 0; j < conditionCount; ++j)
			{
				uint32_t conditionId = 0;
				uint64_t curval = 0;
				BuffLoadInt(buffer, length, conditionId);
				BuffLoadInt64(buffer, length, curval);

				quest->SetConditionCurVal(conditionId, curval);
			}
		}
		else
		{
			auto size = (UINT32_LEN + UINT64_LEN) * conditionCount;
			BuffLoadMoveLen(buffer, length, size);
		}
	}


	return ret;
}

Quest* QuestSystem::AddQuest(QuestComponent *cmp, const QuestConfigData* data, uint32_t status, bool notify)
{
	Quest* quest = new Quest(data, status);
	if (quest)
	{
		cmp->m_quests[quest->Id()] = quest;

		if (QUEST_STATUS_ACCEPT == quest->m_status)
		{
			if (quest->Data()->vecCmpCondition.size())
			{
				if (quest->Data()->client)
				{
					std::vector<ConditionParm> vec;
					vec.push_back({ CONDITION_TYPE_CLIENT_CMP_QUEST, std::to_string(quest->m_data->id) });
					quest->m_action = GamePlayerSystem::instance()->CreateAction(cmp->GetEntity(), ACTION_TYPE_QUEST_COMPLETE, vec, quest);
				}
				else
				{
					quest->m_action = GamePlayerSystem::instance()->CreateAction(cmp->GetEntity(), ACTION_TYPE_QUEST_COMPLETE, quest->Data()->vecCmpCondition, quest);
				}
			}
			else
			{
				quest->m_status = QUEST_STATUS_COMPLETE;
			}
		}

		if (notify)
			NotifyQuest(cmp->GetEntity(), quest);

		return quest;
	}

	return NULL;
}

void QuestSystem::RegisterQuest(QuestComponent* cmp, Quest* quest)
{
	if (quest->m_action && GamePlayerSystem::instance()->RegisterEventAction(cmp->GetEntity(), quest->m_action))
	{
		quest->m_isRegist = true;
	}

	return;
}

void QuestSystem::RemoveQuest(ECS::ECSEntity* entity, Quest* quest)
{
	auto questCmp = entity->GetComponent<QuestComponent>();
	if (!questCmp)
		return ;

	//if (quest->IsRegist())
	//	m_owner->UnRegisterEventAction(quest->m_action);

	//delete quest;

	return;
}

void QuestSystem::Complete(ECS::ECSEntity* entity, Quest* quest, bool notify)
{
	auto questCmp = entity->GetComponent<QuestComponent>();
	if (!questCmp)
		return;

	quest->m_status = QUEST_STATUS_COMPLETE;
	if (notify)
		NotifyQuest(entity, quest);
	
	GamePlayerSystem::instance()->SetNeedSave(entity);

	return;
}

void QuestSystem::Receive(ECS::ECSEntity* entity, uint64_t id)
{
	auto questCmp = entity->GetComponent<QuestComponent>();
	if (!questCmp)
		return;

	auto itr = questCmp->m_quests.find(id);
	if (itr == questCmp->m_quests.end())
	{
		return;
	}
	
	auto quest = itr->second;

	if (QUEST_STATUS_COMPLETE != quest->m_status)
		return;

	if (quest->m_isRegist)
	{
		GamePlayerSystem::instance()->UnRegisterEventAction(entity, quest->m_action);
		quest->m_isRegist = false;
	}

	quest->m_status = QUEST_STATUS_RECEIVE;
	NotifyQuest(entity, quest);

	std::vector<TypeIdCount> items;

	if (quest->m_data->acceptQuest)
	{
		auto data = QuestConfigDataManager::instance()->get(quest->m_data->acceptQuest);
		if (data)
		{
			auto newQuest = AddQuest(questCmp, data, QUEST_STATUS_ACCEPT);
			if (newQuest)
				RegisterQuest(questCmp, newQuest);
		}
	}

	if (itr->second->Type() == QUEST_TYPE_NORMAL)
	{
		questCmp->m_closeQuests.emplace(id);
	}

	SAFE_DELETE(quest);
	questCmp->m_quests.erase(itr);

	GamePlayerSystem::instance()->SetNeedSave(entity);

	return;
}

void QuestSystem::NotifyQuestList(ECS::ECSEntity* entity)
{
	auto questCmp = entity->GetComponent<QuestComponent>();
	if (!questCmp)
		return;

	ClientMsg::NotifyQuestInfo send;
	send.normals.reserve(questCmp->m_quests.size());
	send.days.reserve(questCmp->m_quests.size());
	for (auto itr = questCmp->m_quests.begin(); itr != questCmp->m_quests.end(); ++itr)
	{
		Struct::QuestInfo* info = NULL;
		if (itr->second->Type() == QUEST_TYPE_NORMAL)
		{
			send.normals.push_back(Struct::QuestInfo());
			info = &send.normals.back();
		}
		else
		{
			send.days.push_back(Struct::QuestInfo());
			info = &send.days.back();
		}


		info->id = itr->second->Id();
		info->status = itr->second->m_status;
		if (itr->second->m_action)
		{
			info->conditions.reserve(itr->second->m_action->GetConditions().size());
			for (uint32_t i = 0; i < itr->second->m_action->GetConditions().size(); ++i)
			{
				Struct::ConditionInfo conditionInfo;
				conditionInfo.type = itr->second->m_action->GetConditions()[i]->Id();
				conditionInfo.value = itr->second->m_action->GetConditions()[i]->GetCurVar();
				info->conditions.push_back(conditionInfo);
			}
		}
	}

	for (auto itr : questCmp->m_canAppectQuests)
	{
		send.canAccepts.push_back(itr);
	}

	GamePlayerSystem::instance()->SendClientMsg(entity, &send);

	return;
}

void QuestSystem::NotifyQuest(ECS::ECSEntity* entity, Quest* quest)
{
	ClientMsg::NotifyQuestChangeInfo send;
	send.info.id = quest->Id();
	send.info.status = quest->m_status;
	if (quest && quest->m_status != QUEST_STATUS_RECEIVE)
	{
		if (quest->m_action)
		{
			send.info.conditions.reserve(quest->m_action->GetConditions().size());
			for (uint32_t i = 0; i < quest->m_action->GetConditions().size(); ++i)
			{
				Struct::ConditionInfo conditionInfo;
				conditionInfo.type = quest->m_action->GetConditions()[i]->Id();
				conditionInfo.value = quest->m_action->GetConditions()[i]->GetCurVar();
				send.info.conditions.push_back(conditionInfo);
			}
		}
	}
	
	GamePlayerSystem::instance()->SendClientMsg(entity, &send);

	return;
}

void QuestSystem::NotifyQuest(ECS::ECSEntity* entity, uint64_t id)
{
	auto questCmp = entity->GetComponent<QuestComponent>();
	if (!questCmp)
		return;

	auto itr = questCmp->m_quests.find(id);
	if (itr != questCmp->m_quests.end())
		NotifyQuest(entity, itr->second);

	return;
}

void QuestSystem::ClientComplete(ECS::ECSEntity* entity, uint64_t id)
{
	auto questCmp = entity->GetComponent<QuestComponent>();
	if (!questCmp)
		return;

	auto itr = questCmp->m_quests.find(id);
	if (itr == questCmp->m_quests.end())
		return;

	auto quest = itr->second;
	auto data = quest->Data();

	if (QUEST_STATUS_ACCEPT != quest->m_status)
		return;

	if (!data->client)
		return;

	OnClientCmpQuestEvent event(id, entity);
	GamePlayerSystem::instance()->GamePlayerDoEvent(entity, event);

	return;
}

//private
std::vector<const QuestConfigData*>* QuestSystem::GetQuestMapByPreConditionType(uint32_t preconditionType)
{
	auto itr = m_quests.find(preconditionType);
	if (itr != m_quests.end())
	{
		return &(itr->second);
	}

	return NULL;
}


