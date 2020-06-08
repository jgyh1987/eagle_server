#include "Stream.h"
#include "Design.h"

namespace design
{

using namespace Struct;

MapConfig::MapConfig()
{
	id = 0;
	type = 0;
	cameraLen = 0;
	cameraDefault = 0;
	cameraRange = 0;
}

int MapConfig::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->type)) return -1;
	}
	{
		if (!writeStream->Write(this->path.c_str(), this->path.size())) return -1;
	}
	{
		if (!writeStream->Write(this->stream_level_path.c_str(), this->stream_level_path.size())) return -1;
	}
	{
		if (!writeStream->Write(this->npcs.c_str(), this->npcs.size())) return -1;
	}
	{
		if (!writeStream->Write(this->monsters.c_str(), this->monsters.size())) return -1;
	}
	{
		if (!writeStream->Write(this->fighterEnterPos.c_str(), this->fighterEnterPos.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->cameraLen)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->cameraDefault)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->cameraRange)) return -1;
	}

	return 0;
}

int MapConfig::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->type)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->path.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->stream_level_path.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->npcs.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->monsters.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->fighterEnterPos.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->cameraLen)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->cameraDefault)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->cameraRange)) return -1;
	}

	return 0;
}

ItemConfig::ItemConfig()
{
	id = 0;
}

int ItemConfig::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write(this->name.c_str(), this->name.size())) return -1;
	}

	return 0;
}

int ItemConfig::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->name.assign(p, len);
	}

	return 0;
}

CommonDropConfig::CommonDropConfig()
{
	id = 0;
	randomnum = 0;
}

int CommonDropConfig::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write(this->randomproduce.c_str(), this->randomproduce.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->randomnum)) return -1;
	}

	return 0;
}

int CommonDropConfig::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->randomproduce.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->randomnum)) return -1;
	}

	return 0;
}

BuffConfig::BuffConfig()
{
	id = 0;
	buffType = 0;
}

int BuffConfig::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->buffType)) return -1;
	}

	return 0;
}

int BuffConfig::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->buffType)) return -1;
	}

	return 0;
}

SkillConfig::SkillConfig()
{
	id = 0;
	skillType = 0;
}

int SkillConfig::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->skillType)) return -1;
	}
	{
		if (!writeStream->Write(this->emitterPath.c_str(), this->emitterPath.size())) return -1;
	}
	{
		if (!writeStream->Write(this->emitterSockName.c_str(), this->emitterSockName.size())) return -1;
	}
	{
		if (!writeStream->Write(this->animId.c_str(), this->animId.size())) return -1;
	}
	{
		if (!writeStream->Write(this->beatkEmitterPath.c_str(), this->beatkEmitterPath.size())) return -1;
	}
	{
		if (!writeStream->Write(this->iconUrl.c_str(), this->iconUrl.size())) return -1;
	}

	return 0;
}

int SkillConfig::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->skillType)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->emitterPath.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->emitterSockName.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->animId.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->beatkEmitterPath.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->iconUrl.assign(p, len);
	}

	return 0;
}

DungeonConfig::DungeonConfig()
{
	id = 0;
	type = 0;
	loadUIBP = 0;
	autoTickTime = 0;
}

int DungeonConfig::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->type)) return -1;
	}
	{
		if (!writeStream->Write(this->maps.c_str(), this->maps.size())) return -1;
	}
	{
		if (!writeStream->Write(this->loadPath.c_str(), this->loadPath.size())) return -1;
	}
	{
		if (!writeStream->Write(this->loadImgPath.c_str(), this->loadImgPath.size())) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->loadUIBP)) return -1;
	}
	{
		if (!writeStream->Write(this->cmpCondition.c_str(), this->cmpCondition.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->autoTickTime)) return -1;
	}

	return 0;
}

int DungeonConfig::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->type)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->maps.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->loadPath.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->loadImgPath.assign(p, len);
	}
	{
		if (!readStream->Read((int64_t&)this->loadUIBP)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->cmpCondition.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->autoTickTime)) return -1;
	}

	return 0;
}

RoleConfig::RoleConfig()
{
	id = 0;
	roleBPId = 0;
	radius = 0;
	create = 0;
	initMapId = 0;
	initDungeonId = 0;
}

int RoleConfig::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write(this->skills.c_str(), this->skills.size())) return -1;
	}
	{
		if (!writeStream->Write(this->rightWeaponSockName.c_str(), this->rightWeaponSockName.size())) return -1;
	}
	{
		if (!writeStream->Write(this->leftWeaponSockName.c_str(), this->leftWeaponSockName.size())) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->roleBPId)) return -1;
	}
	{
		if (!writeStream->Write(this->mesh.c_str(), this->mesh.size())) return -1;
	}
	{
		if (!writeStream->Write(this->animBP.c_str(), this->animBP.size())) return -1;
	}
	{
		if (!writeStream->Write(this->material.c_str(), this->material.size())) return -1;
	}
	{
		if (!writeStream->Write(this->roleBP.c_str(), this->roleBP.size())) return -1;
	}
	{
		if (!writeStream->Write(this->roleTouxiangText.c_str(), this->roleTouxiangText.size())) return -1;
	}
	{
		if (!writeStream->Write(this->biaoqing.c_str(), this->biaoqing.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->radius)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->create)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->initMapId)) return -1;
	}
	{
		if (!writeStream->Write(this->initMapPos.c_str(), this->initMapPos.size())) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->initDungeonId)) return -1;
	}

	return 0;
}

int RoleConfig::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->skills.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->rightWeaponSockName.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->leftWeaponSockName.assign(p, len);
	}
	{
		if (!readStream->Read((int64_t&)this->roleBPId)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->mesh.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->animBP.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->material.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->roleBP.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->roleTouxiangText.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->biaoqing.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->radius)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->create)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->initMapId)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->initMapPos.assign(p, len);
	}
	{
		if (!readStream->Read((int64_t&)this->initDungeonId)) return -1;
	}

	return 0;
}

BPConfig::BPConfig()
{
	id = 0;
}

int BPConfig::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write(this->roleBP.c_str(), this->roleBP.size())) return -1;
	}

	return 0;
}

int BPConfig::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->roleBP.assign(p, len);
	}

	return 0;
}

MonsterConfig::MonsterConfig()
{
	id = 0;
	type = 0;
	roleBP = 0;
	isGravity = 0;
	isPoint = 0;
	hp = 0;
	radius = 0;
}

int MonsterConfig::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->type)) return -1;
	}
	{
		if (!writeStream->Write(this->skills.c_str(), this->skills.size())) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->roleBP)) return -1;
	}
	{
		if (!writeStream->Write(this->mesh.c_str(), this->mesh.size())) return -1;
	}
	{
		if (!writeStream->Write(this->meshRate.c_str(), this->meshRate.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->isGravity)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->isPoint)) return -1;
	}
	{
		if (!writeStream->Write(this->biaoqing.c_str(), this->biaoqing.size())) return -1;
	}
	{
		if (!writeStream->Write(this->animBP.c_str(), this->animBP.size())) return -1;
	}
	{
		if (!writeStream->Write(this->roleTouxiangText.c_str(), this->roleTouxiangText.size())) return -1;
	}
	{
		if (!writeStream->Write(this->material.c_str(), this->material.size())) return -1;
	}
	{
		if (!writeStream->Write(this->beAtkAnimName.c_str(), this->beAtkAnimName.size())) return -1;
	}
	{
		if (!writeStream->Write(this->beAtkGZName.c_str(), this->beAtkGZName.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->hp)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->radius)) return -1;
	}

	return 0;
}

int MonsterConfig::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->type)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->skills.assign(p, len);
	}
	{
		if (!readStream->Read((int64_t&)this->roleBP)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->mesh.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->meshRate.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->isGravity)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->isPoint)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->biaoqing.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->animBP.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->roleTouxiangText.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->material.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->beAtkAnimName.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->beAtkGZName.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->hp)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->radius)) return -1;
	}

	return 0;
}

MonsterGroupConfig::MonsterGroupConfig()
{
	id = 0;
	mapId = 0;
}

int MonsterGroupConfig::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->mapId)) return -1;
	}
	{
		if (!writeStream->Write(this->monsters.c_str(), this->monsters.size())) return -1;
	}

	return 0;
}

int MonsterGroupConfig::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->mapId)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->monsters.assign(p, len);
	}

	return 0;
}

AnimConfig::AnimConfig()
{
	id = 0;
}

int AnimConfig::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write(this->assetPath.c_str(), this->assetPath.size())) return -1;
	}

	return 0;
}

int AnimConfig::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->assetPath.assign(p, len);
	}

	return 0;
}

UIBPConfig::UIBPConfig()
{
	id = 0;
	clear = 0;
	mouseMode = 0;
}

int UIBPConfig::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write(this->loadUIBP.c_str(), this->loadUIBP.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->clear)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->mouseMode)) return -1;
	}

	return 0;
}

int UIBPConfig::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->loadUIBP.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->clear)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->mouseMode)) return -1;
	}

	return 0;
}

GuideConfig::GuideConfig()
{
	id = 0;
}

int GuideConfig::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write(this->preCondition.c_str(), this->preCondition.size())) return -1;
	}
	{
		if (!writeStream->Write(this->triggerCondition.c_str(), this->triggerCondition.size())) return -1;
	}

	return 0;
}

int GuideConfig::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->preCondition.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->triggerCondition.assign(p, len);
	}

	return 0;
}

QuestConfig::QuestConfig()
{
	id = 0;
	type = 0;
	client = 0;
	initAccept = 0;
	cmpAcceptQuest = 0;
	openWidget = 0;
	exp = 0;
}

int QuestConfig::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->type)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->client)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->initAccept)) return -1;
	}
	{
		if (!writeStream->Write(this->preCondition.c_str(), this->preCondition.size())) return -1;
	}
	{
		if (!writeStream->Write(this->cmpCondition.c_str(), this->cmpCondition.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->cmpAcceptQuest)) return -1;
	}
	{
		if (!writeStream->Write(this->autoPath.c_str(), this->autoPath.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->openWidget)) return -1;
	}
	{
		if (!writeStream->Write(this->context.c_str(), this->context.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->exp)) return -1;
	}
	{
		if (!writeStream->Write(this->appectActions.c_str(), this->appectActions.size())) return -1;
	}
	{
		if (!writeStream->Write(this->cmpActions.c_str(), this->cmpActions.size())) return -1;
	}
	{
		if (!writeStream->Write(this->receiveActions.c_str(), this->receiveActions.size())) return -1;
	}
	{
		if (!writeStream->Write(this->bindNpc.c_str(), this->bindNpc.size())) return -1;
	}

	return 0;
}

int QuestConfig::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->type)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->client)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->initAccept)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->preCondition.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->cmpCondition.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->cmpAcceptQuest)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->autoPath.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->openWidget)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->context.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->exp)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->appectActions.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->cmpActions.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->receiveActions.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->bindNpc.assign(p, len);
	}

	return 0;
}

LandmassConfig::LandmassConfig()
{
	id = 0;
	loadUIBP = 0;
}

int LandmassConfig::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write(this->maps.c_str(), this->maps.size())) return -1;
	}
	{
		if (!writeStream->Write(this->scenes.c_str(), this->scenes.size())) return -1;
	}
	{
		if (!writeStream->Write(this->range.c_str(), this->range.size())) return -1;
	}
	{
		if (!writeStream->Write(this->loadImgPath.c_str(), this->loadImgPath.size())) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->loadUIBP)) return -1;
	}

	return 0;
}

int LandmassConfig::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->maps.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->scenes.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->range.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->loadImgPath.assign(p, len);
	}
	{
		if (!readStream->Read((int64_t&)this->loadUIBP)) return -1;
	}

	return 0;
}

SceneConfig::SceneConfig()
{
	id = 0;
}

int SceneConfig::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write(this->range.c_str(), this->range.size())) return -1;
	}

	return 0;
}

int SceneConfig::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->range.assign(p, len);
	}

	return 0;
}

}

