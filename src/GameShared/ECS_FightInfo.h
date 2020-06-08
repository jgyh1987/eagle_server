#ifndef _ECS_FIGHTINFO_H_
#define _ECS_FIGHTINFO_H_

#include "Sys.h"
#include "Singleton.h"
#include "CObject.h"
#include "ECS_Component.h"
#include "ECS_Entity.h"
#include "CommonType.h"

class FightComponent : public ECS::ECSComponent
{
public:
    enum
    {
        Type = ECS_CHAR_COMPONENT_TYPE_FIGHT
    };

	FightComponent(ECS::ECSEntity* owner)
        :ECSComponent(owner)
    {
    }

    uint32_t GetType() override { return FightComponent::Type; }

public:

};




#endif

