#ifndef _ECS_MAIL_H_
#define _ECS_MAIL_H_

#include "Sys.h"
#include "Singleton.h"
#include "CObject.h"
#include "ECS_Component.h"
#include "ECS_Entity.h"
#include "CommonType.h"
#include "ECS_System.h"

class MailComponent : public ECS::ECSComponent
{
public:
    enum
    {
        Type = ECS_PLAYER_COMPONENT_TYPE_PLAYER
    };

    MailComponent(ECS::ECSEntity* owner)
        :ECSComponent(owner)
    {
    }

    uint32_t GetType() override { return MailComponent::Type; }

public:

};


class MailSystem : public ECS::ECSSystem, public CSingleton<MailSystem>
{
public:
	void Clear(ECS::ECSEntity* entity) override {}

    void SystemSendMail(ECS::ECSEntity * entity, TypeIdCount& item, const char* title, const char* content);


};

#endif

