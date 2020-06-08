#ifndef _ECS_ENTITY_H_
#define _ECS_ENTITY_H_

#include "Sys.h"
#include "Singleton.h"
#include "Noncopyable.h"
#include "CObject.h"
#include "ECS.h"
#include "Global.h"

namespace ECS
{
    class ECSComponent;
    class ECSManager;

    class ECSEntity : public CObjectBase
    {
        friend class ECSManager;
    public:

        ~ECSEntity() final;

        inline uint32_t Type() { return m_type; }

        void DestroyComponent(ECSComponent *&cmp);
        template <typename T>
        void DestroyComponent(T *&cmp)
        {
            if (T::Type >= m_components.size() || m_components[T::Type] != cmp)
                return;

            SAFE_DELETEE(m_components[T::Type]);
            cmp = NULL;

            return;
        }

        template <typename T>
        T* GetComponent() 
        {
            if (T::Type >= m_components.size())
                return NULL;
            
            return (T *)m_components[T::Type];
        }

    private:
        ECSEntity(uint32_t type, uint32_t cmpSize);

    private:
        uint32_t m_type;
        std::vector<ECSComponent*> m_components;
    };


    class ECSManager : public CSingleton<ECSManager>
    {
    public:
        ECSManager()
        {
            m_entitys.resize(ECS_ENTITY_TYPE_DEFAULT + 1);
        }

        bool Init(uint32_t);

        ECSEntity* CreateEntity(uint32_t type, uint32_t cmpSize);
        void DestroyEntrty(ECSEntity *);
        ECSEntity *GetEntity(uint32_t type, uint64_t uid);

        template <int E, typename T, typename ...Args>
        bool ForeachEntity(T* t, void (T::* f)(ECSEntity *entity, Args...), Args&&... args)
        {
            if (E >= m_entitys.size())
                return false;

            for (auto &itr : m_entitys[E])
            {
                t->f(itr.second, std::forward<Args>(args) ...);
            }

            return true;
        }

        template <typename T>
        T* CreateComponent(ECSEntity *entity)
        {
            if (!entity)
                return NULL;

            if (T::Type >= entity->m_components.size())
                return NULL;

            if (entity->m_components[T::Type])
                return (T *)entity->m_components[T::Type];

            T* cmp = new T(entity);
            entity->m_components[T::Type] = cmp;

            return cmp;
        }

        template <typename T>
        void DestroyComponent(T* cmp)
        {
            cmp->GetEntity()->DestroyComponent<T>(cmp);

            return;
        }

    protected:

        std::vector< eagle_hash_map<uint64_t, ECSEntity *> > m_entitys;
    };
}



#endif

