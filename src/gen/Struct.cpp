#include "Stream.h"
#include "Struct.h"

namespace Struct
{

MapPos::MapPos()
{
	x = 0;
	y = 0;
	z = 0;
	dirx = 0;
	diry = 0;
	dirz = 0;
	move = 0;
	time = 0;
}

int MapPos::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write(this->x)) return -1;
	}
	{
		if (!writeStream->Write(this->y)) return -1;
	}
	{
		if (!writeStream->Write(this->z)) return -1;
	}
	{
		if (!writeStream->Write(this->dirx)) return -1;
	}
	{
		if (!writeStream->Write(this->diry)) return -1;
	}
	{
		if (!writeStream->Write(this->dirz)) return -1;
	}
	{
		if (!writeStream->Write(this->move)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->time)) return -1;
	}

	return 0;
}

int MapPos::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read(this->x)) return -1;
	}
	{
		if (!readStream->Read(this->y)) return -1;
	}
	{
		if (!readStream->Read(this->z)) return -1;
	}
	{
		if (!readStream->Read(this->dirx)) return -1;
	}
	{
		if (!readStream->Read(this->diry)) return -1;
	}
	{
		if (!readStream->Read(this->dirz)) return -1;
	}
	{
		if (!readStream->Read(this->move)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->time)) return -1;
	}

	return 0;
}

TypeIdCount::TypeIdCount()
{
	id = 0;
	count = 0;
	type = 0;
}

int TypeIdCount::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->count)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->type)) return -1;
	}

	return 0;
}

int TypeIdCount::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->count)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->type)) return -1;
	}

	return 0;
}

ItemBaseInfo::ItemBaseInfo()
{
	id = 0;
	count = 0;
	type = 0;
	uid = 0;
}

int ItemBaseInfo::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->count)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->type)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->uid)) return -1;
	}

	return 0;
}

int ItemBaseInfo::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->count)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->type)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->uid)) return -1;
	}

	return 0;
}

ConditionInfo::ConditionInfo()
{
	type = 0;
	value = 0;
}

int ConditionInfo::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int32_t)this->type)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->value)) return -1;
	}

	return 0;
}

int ConditionInfo::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int32_t&)this->type)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->value)) return -1;
	}

	return 0;
}

AttrInfo::AttrInfo()
{
	type = 0;
	value = 0;
}

int AttrInfo::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int32_t)this->type)) return -1;
	}
	{
		if (!writeStream->Write(this->value)) return -1;
	}

	return 0;
}

int AttrInfo::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int32_t&)this->type)) return -1;
	}
	{
		if (!readStream->Read(this->value)) return -1;
	}

	return 0;
}

ServerInfo::ServerInfo()
{
	serverType = 0;
	gameId = 0;
	serverId = 0;
	portTcp = 0;
	portUdp = 0;
}

int ServerInfo::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int32_t)this->serverType)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->gameId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->serverId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->portTcp)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->portUdp)) return -1;
	}
	{
		if (!writeStream->Write(this->ip.c_str(), this->ip.size())) return -1;
	}

	return 0;
}

int ServerInfo::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int32_t&)this->serverType)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->gameId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->serverId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->portTcp)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->portUdp)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->ip.assign(p, len);
	}

	return 0;
}

PlayerSimpleInfo::PlayerSimpleInfo()
{
	playerId = 0;
	playerUid = 0;
	vipLevel = 0;
}

int PlayerSimpleInfo::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->playerId)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->playerUid)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->vipLevel)) return -1;
	}

	return 0;
}

int PlayerSimpleInfo::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->playerId)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->playerUid)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->vipLevel)) return -1;
	}

	return 0;
}

RoleSimpleInfo::RoleSimpleInfo()
{
	roleId = 0;
	photoId = 0;
	jobId = 0;
	level = 0;
	mapId = 0;
	sex = 0;
	shape = 0;
	fight = 0;
}

int RoleSimpleInfo::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->roleId)) return -1;
	}
	{
		if (!writeStream->Write(this->playerName.c_str(), this->playerName.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->photoId)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->jobId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->level)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->mapId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->sex)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->shape)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->fight)) return -1;
	}

	return 0;
}

int RoleSimpleInfo::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->roleId)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->playerName.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->photoId)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->jobId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->level)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->mapId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->sex)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->shape)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->fight)) return -1;
	}

	return 0;
}

ItemInfo::ItemInfo()
{
}

int ItemInfo::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (this->baseInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ItemInfo::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (this->baseInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

EquipInfo::EquipInfo()
{
}

int EquipInfo::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (this->baseInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int EquipInfo::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (this->baseInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

MailInfo::MailInfo()
{
	mailId = 0;
	leftTime = 0;
}

int MailInfo::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->mailId)) return -1;
	}
	{
		if (this->item.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->leftTime)) return -1;
	}
	{
		if (!writeStream->Write(this->title.c_str(), this->title.size())) return -1;
	}
	{
		if (!writeStream->Write(this->content.c_str(), this->content.size())) return -1;
	}
	{
		if (!writeStream->Write(this->sendName.c_str(), this->sendName.size())) return -1;
	}

	return 0;
}

int MailInfo::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->mailId)) return -1;
	}
	{
		if (this->item.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->leftTime)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->title.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->content.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->sendName.assign(p, len);
	}

	return 0;
}

QuestInfo::QuestInfo()
{
	id = 0;
	status = 0;
}

int QuestInfo::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->status)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->conditions.size())) return -1;
		for (std::vector< Struct::ConditionInfo >::const_iterator it=this->conditions.begin(); it!=this->conditions.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int QuestInfo::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->status)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->conditions.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			Struct::ConditionInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->conditions.push_back(__inner__);
		}
	}

	return 0;
}

RoleInfo::RoleInfo()
{
	exp = 0;
	money = 0;
	gold = 0;
}

int RoleInfo::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (this->baseInfo.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->exp)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->money)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->gold)) return -1;
	}

	return 0;
}

int RoleInfo::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (this->baseInfo.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int64_t&)this->exp)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->money)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->gold)) return -1;
	}

	return 0;
}

FighterBaseInfo::FighterBaseInfo()
{
	fightUid = 0;
}

int FighterBaseInfo::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->fightUid)) return -1;
	}
	{
		if (this->pos.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int FighterBaseInfo::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->fightUid)) return -1;
	}
	{
		if (this->pos.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

FighterCompleteInfo::FighterCompleteInfo()
{
	status = 0;
}

int FighterCompleteInfo::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (this->baseInfo.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->status)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->curAttr.size())) return -1;
		for (std::vector< uint64_t >::const_iterator it=this->curAttr.begin(); it!=this->curAttr.end(); ++it) {
			if (!writeStream->Write((int64_t)(*it))) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->buffId.size())) return -1;
		for (std::vector< uint32_t >::const_iterator it=this->buffId.begin(); it!=this->buffId.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}
	{
		if (this->playerInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int FighterCompleteInfo::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (this->baseInfo.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int64_t&)this->status)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->curAttr.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint64_t __inner__;
			{
				if (!readStream->Read((int64_t&)__inner__)) return -1;
			}
			this->curAttr.push_back(__inner__);
		}
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->buffId.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint32_t __inner__;
			{
				if (!readStream->Read((int32_t&)__inner__)) return -1;
			}
			this->buffId.push_back(__inner__);
		}
	}
	{
		if (this->playerInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

SkillInfo::SkillInfo()
{
	skillId = 0;
}

int SkillInfo::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int32_t)this->skillId)) return -1;
	}

	return 0;
}

int SkillInfo::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int32_t&)this->skillId)) return -1;
	}

	return 0;
}

BuffInfo::BuffInfo()
{
	buffUid = 0;
	buffId = 0;
	endTime = 0;
	layer = 0;
	triggerEffectId = 0;
}

int BuffInfo::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->buffUid)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->buffId)) return -1;
	}
	{
		if (this->caster.Serialize(writeStream) != 0) return -1;
	}
	{
		if (this->target.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->endTime)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->layer)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->triggerEffectId)) return -1;
	}

	return 0;
}

int BuffInfo::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->buffUid)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->buffId)) return -1;
	}
	{
		if (this->caster.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (this->target.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int64_t&)this->endTime)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->layer)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->triggerEffectId)) return -1;
	}

	return 0;
}

WFightDungeonBaseInfo::WFightDungeonBaseInfo()
{
	dungeonUid = 0;
}

int WFightDungeonBaseInfo::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	{
		if (!writeStream->Write((int64_t)this->dungeonUid)) return -1;
	}
	{
		if (this->serverInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int WFightDungeonBaseInfo::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	{
		if (!readStream->Read((int64_t&)this->dungeonUid)) return -1;
	}
	{
		if (this->serverInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

};

