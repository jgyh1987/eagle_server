#ifndef _ECS_COMPONENT_H_
#define _ECS_COMPONENT_H_

#include "Sys.h"
#include "Singleton.h"
#include "CObject.h"
#include "ECS.h"

namespace ECS
{
    class ECSEntity;

    class ECSComponent : public CObjectBase
    {
    public:
        //all component must have
        enum
        {
            Type = ECS_COMPONENT_TYPE_DEFAULT
        };

        ECSComponent(ECSEntity* owner)
            :CObjectBase(GetObjectUid()), m_owner(owner)
        {
        }
        ~ECSComponent(){}

        virtual uint32_t GetType() = 0;

        ECSEntity* GetEntity() { return m_owner; }

    private:
        ECSEntity* m_owner;
    };

}

class TestComponent : public ECS::ECSComponent
{
public:
    enum
    {
        Type = ECS_COMPONENT_TYPE_TEST
    };

    TestComponent(ECS::ECSEntity* owner)
        :ECSComponent(owner)
    {
    }

    uint32_t GetType() override { return TestComponent::Type; }

private:

};



#endif

