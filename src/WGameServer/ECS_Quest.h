#ifndef _ECS_QUEST_H_
#define _ECS_QUEST_H_

#include "Sys.h"
#include "Singleton.h"
#include "CObject.h"
#include "ECS_Component.h"
#include "ECS_Entity.h"
#include "CommonType.h"
#include "LogicDataManager.h"
#include "WGameEvent.h"
#include "ECS_System.h"

#define QUESTMANAGERVERSION_1_1			1

//Quest Type
enum QUEST_TYPE
{
	QUEST_TYPE_NORMAL = 1, //
	QUEST_TYPE_DAY = 2,        //

};
//Quest Status Type
enum QUEST_STATUS_TYPE
{
	QUEST_STATUS_NONE = 0,
	QUEST_STATUS_CAN_ACCEPT = 1,
	QUEST_STATUS_ACCEPT = 2,
	QUEST_STATUS_COMPLETE = 3,
	QUEST_STATUS_RECEIVE = 4,
};

//Quest Open ConditionType
enum QUEST_PRE_CONDITION_TYPE
{
	QUEST_PRE_CONDITION_TYPE_NONE = 0,
	QUEST_PRE_CONDITION_TYPE_LEVEL = 1,

	QUEST_PRE_CONDITION_TYPE_QUEST = 4,

	QUEST_PRE_CONDITION_TYPE_MAX
};
//Quest End

class Quest
{
public:
	Quest(const QuestConfigData* data, uint32_t status = QUEST_STATUS_NONE);
	~Quest();

	inline uint64_t Id()
	{
		return m_data->id;
	}

	inline uint32_t Type()
	{
		return m_data->type;
	}

	inline const QuestConfigData* Data()
	{
		return m_data;
	}

	void SetConditionCurVal(uint32_t conditionId, int64_t curval);

private:
	friend class QuestSystem;
	const QuestConfigData* m_data;
	uint32_t m_status;
	EagleAction* m_action;
	bool m_isRegist;
};

class QuestComponent : public ECS::ECSComponent
{
public:
    enum
    {
        Type = ECS_PLAYER_COMPONENT_TYPE_QUEST
    };

	QuestComponent(ECS::ECSEntity* owner)
        :ECSComponent(owner)
    {
    }

	~QuestComponent();

    uint32_t GetType() override { return QuestComponent::Type; }

private:
	friend class QuestSystem;
	eagle_hash_map<uint64_t, Quest*> m_quests;
	eagle_hash_set<uint64_t> m_canAppectQuests;
	eagle_hash_set<uint64_t> m_closeQuests;
};


class QuestSystem : public ECS::ECSSystem, public CSingleton<QuestSystem>
{
	eagle_hash_map< uint32_t, std::vector<const QuestConfigData*> > m_quests;

public:
	void Init() override;
	bool InitEntityData(ECS::ECSEntity*) override;
	bool OnEnterServer(ECS::ECSEntity* entity) override;
	void Clear(ECS::ECSEntity* entity) override;
	uint32_t Serialize(ECS::ECSEntity*, uint8_t* buffer) override;
	uint32_t UnSerialize(ECS::ECSEntity*, uint8_t* buffer) override;

	Quest* AddQuest(QuestComponent* , const QuestConfigData*, uint32_t status, bool notify = true);
	void RegisterQuest(QuestComponent*, Quest *);
	void RemoveQuest(ECS::ECSEntity*, Quest* quest);
	void Complete(ECS::ECSEntity*, Quest* quest, bool notify = true);
	void Receive(ECS::ECSEntity*, uint64_t id);
	void NotifyQuestList(ECS::ECSEntity*);
	void NotifyQuest(ECS::ECSEntity*, Quest* quest);
	void NotifyQuest(ECS::ECSEntity*, uint64_t id);
	
	void ClientComplete(ECS::ECSEntity*, uint64_t id);

private:
	std::vector<const QuestConfigData*>* GetQuestMapByPreConditionType(uint32_t preconditionType);

};

#endif

