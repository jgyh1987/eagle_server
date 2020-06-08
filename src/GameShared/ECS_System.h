#ifndef _ECS_SYSTEM_H_
#define _ECS_SYSTEM_H_

#include "Sys.h"
#include "Singleton.h"


namespace ECS
{
	class ECSEntity;

	class ECSSystem
	{
	public:
		virtual ~ECSSystem()
		{}
		//system init
		virtual void Init() {}
		//role first entity
		virtual bool InitEntityData(ECS::ECSEntity*) { return true; }
		//role entity server
		virtual bool OnEnterServer(ECS::ECSEntity* entity) { return true; }
		virtual void Clear(ECS::ECSEntity* entity) = 0;
		virtual uint32_t Serialize(ECS::ECSEntity*, uint8_t* buffer) { return 0; }
		virtual uint32_t UnSerialize(ECS::ECSEntity*, uint8_t* buffer) { return 0; }
	};
}


#endif

