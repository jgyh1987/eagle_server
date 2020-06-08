#ifndef _STRUCT_H_
#define _STRUCT_H_

#include <string>
#include <vector>
#include <list>
#include <map>
#include "Streamable.h"
#include "CommonType.h"

namespace Struct{

struct MapPos : public Streamable{
	double x;
	double y;
	double z;
	double dirx;
	double diry;
	double dirz;
	double move;
	uint64_t time;

	MapPos();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct TypeIdCount : public Streamable{
	uint64_t id;
	uint64_t count;
	uint32_t type;

	TypeIdCount();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ItemBaseInfo : public Streamable{
	uint64_t id;
	uint64_t count;
	uint32_t type;
	uint64_t uid;

	ItemBaseInfo();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ConditionInfo : public Streamable{
	uint32_t type;
	uint64_t value;

	ConditionInfo();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct AttrInfo : public Streamable{
	uint32_t type;
	double value;

	AttrInfo();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ServerInfo : public Streamable{
	uint32_t serverType;
	uint32_t gameId;
	uint32_t serverId;
	uint32_t portTcp;
	uint32_t portUdp;
	std::string ip;

	ServerInfo();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerSimpleInfo : public Streamable{
	uint64_t playerId;
	uint64_t playerUid;
	uint32_t vipLevel;

	PlayerSimpleInfo();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct RoleSimpleInfo : public Streamable{
	uint64_t roleId;
	std::string playerName;
	uint32_t photoId;
	uint64_t jobId;
	uint32_t level;
	uint64_t mapId;
	uint32_t sex;
	uint32_t shape;
	uint64_t fight;

	RoleSimpleInfo();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ItemInfo : public Streamable{
	Struct::ItemBaseInfo baseInfo;

	ItemInfo();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EquipInfo : public Streamable{
	Struct::ItemBaseInfo baseInfo;

	EquipInfo();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MailInfo : public Streamable{
	uint64_t mailId;
	Struct::TypeIdCount item;
	uint32_t leftTime;
	std::string title;
	std::string content;
	std::string sendName;

	MailInfo();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct QuestInfo : public Streamable{
	uint64_t id;
	uint32_t status;
	std::vector< Struct::ConditionInfo > conditions;

	QuestInfo();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct RoleInfo : public Streamable{
	Struct::RoleSimpleInfo baseInfo;
	uint64_t exp;
	uint64_t money;
	uint64_t gold;

	RoleInfo();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FighterBaseInfo : public Streamable{
	uint64_t fightUid;
	Struct::MapPos pos;

	FighterBaseInfo();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FighterCompleteInfo : public Streamable{
	Struct::FighterBaseInfo baseInfo;
	uint64_t status;
	std::vector< uint64_t > curAttr;
	std::vector< uint32_t > buffId;
	Struct::PlayerSimpleInfo playerInfo;

	FighterCompleteInfo();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SkillInfo : public Streamable{
	uint32_t skillId;

	SkillInfo();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BuffInfo : public Streamable{
	uint64_t buffUid;
	uint32_t buffId;
	Struct::FighterBaseInfo caster;
	Struct::FighterBaseInfo target;
	uint64_t endTime;
	uint32_t layer;
	uint32_t triggerEffectId;

	BuffInfo();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct WFightDungeonBaseInfo : public Streamable{
	uint64_t dungeonUid;
	Struct::ServerInfo serverInfo;

	WFightDungeonBaseInfo();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

}

#endif
