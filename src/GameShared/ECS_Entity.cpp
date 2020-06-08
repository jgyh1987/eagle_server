#include "ECS_Entity.h"
#include "ECS_Component.h"

namespace ECS
{

    ECSEntity::ECSEntity(uint32_t type, uint32_t cmpSize)
        :CObjectBase(GetObjectUid()), m_type(type)
    {
        m_components.resize(cmpSize, NULL);
    }

    ECSEntity::~ECSEntity()
    {
        for (auto c : m_components)
        {
            SAFE_DELETE(c);
        }
    }

    void ECSEntity::DestroyComponent(ECSComponent *&cmp)
    {
        if (!cmp || cmp->GetType() >= m_components.size() || cmp != m_components[cmp->GetType()])
            return;

        SAFE_DELETE(m_components[cmp->GetType()]);
        cmp = NULL;

        return;
    }

    bool ECSManager::Init(uint32_t entityTypeMax)
    {
        m_entitys.resize(entityTypeMax);

        return true;
    }

    ECSEntity* ECSManager::CreateEntity(uint32_t type, uint32_t cmpSize)
    {
        if (type >= m_entitys.size())
            return NULL;

        ECSEntity* entity = new ECSEntity(type, cmpSize);
        m_entitys[type][entity->Uid()] = entity;

        return entity;
    }

    void ECSManager::DestroyEntrty(ECSEntity* entity)
    {
        if (!entity)
            return;

        do
        {
            if (entity->Type() >= m_entitys.size())
                break;

            auto& eMap = m_entitys[entity->Type()];
            MAP_REMOVE(eMap, entity->Uid());

        } while (false);

        SAFE_DELETE(entity);

        return;
    }

    ECSEntity *ECSManager::GetEntity(uint32_t type, uint64_t uid)
    {
        if (type >= m_entitys.size())
            return NULL;

        auto itr = m_entitys[type].find(uid);
        if (itr != m_entitys[type].end())
            return itr->second;

        return NULL;
    }

}
