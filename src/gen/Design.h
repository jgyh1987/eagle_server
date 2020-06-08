#ifndef _DESIGN_H_
#define _DESIGN_H_

#include <string>
#include <vector>
#include <list>
#include <map>
#include "Streamable.h"
#include "CommonType.h"
#include "Struct.h"

namespace design
{

using namespace Struct;

struct MapConfig : public Streamable
{
	uint64_t id;
	uint32_t type;
	std::string path;
	std::string stream_level_path;
	std::string npcs;
	std::string monsters;
	std::string fighterEnterPos;
	uint32_t cameraLen;
	uint32_t cameraDefault;
	uint32_t cameraRange;

	MapConfig();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ItemConfig : public Streamable
{
	uint64_t id;
	std::string name;

	ItemConfig();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CommonDropConfig : public Streamable
{
	uint64_t id;
	std::string randomproduce;
	uint32_t randomnum;

	CommonDropConfig();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BuffConfig : public Streamable
{
	uint64_t id;
	uint32_t buffType;

	BuffConfig();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SkillConfig : public Streamable
{
	uint64_t id;
	uint32_t skillType;
	std::string emitterPath;
	std::string emitterSockName;
	std::string animId;
	std::string beatkEmitterPath;
	std::string iconUrl;

	SkillConfig();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DungeonConfig : public Streamable
{
	uint64_t id;
	uint32_t type;
	std::string maps;
	std::string loadPath;
	std::string loadImgPath;
	uint64_t loadUIBP;
	std::string cmpCondition;
	uint32_t autoTickTime;

	DungeonConfig();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct RoleConfig : public Streamable
{
	uint64_t id;
	std::string skills;
	std::string rightWeaponSockName;
	std::string leftWeaponSockName;
	uint64_t roleBPId;
	std::string mesh;
	std::string animBP;
	std::string material;
	std::string roleBP;
	std::string roleTouxiangText;
	std::string biaoqing;
	uint32_t radius;
	uint32_t create;
	uint64_t initMapId;
	std::string initMapPos;
	uint64_t initDungeonId;

	RoleConfig();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BPConfig : public Streamable
{
	uint64_t id;
	std::string roleBP;

	BPConfig();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MonsterConfig : public Streamable
{
	uint64_t id;
	uint32_t type;
	std::string skills;
	uint64_t roleBP;
	std::string mesh;
	std::string meshRate;
	uint32_t isGravity;
	uint32_t isPoint;
	std::string biaoqing;
	std::string animBP;
	std::string roleTouxiangText;
	std::string material;
	std::string beAtkAnimName;
	std::string beAtkGZName;
	int32_t hp;
	uint32_t radius;

	MonsterConfig();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MonsterGroupConfig : public Streamable
{
	uint64_t id;
	uint64_t mapId;
	std::string monsters;

	MonsterGroupConfig();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct AnimConfig : public Streamable
{
	uint64_t id;
	std::string assetPath;

	AnimConfig();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UIBPConfig : public Streamable
{
	uint64_t id;
	std::string loadUIBP;
	uint32_t clear;
	uint32_t mouseMode;

	UIBPConfig();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GuideConfig : public Streamable
{
	uint64_t id;
	std::string preCondition;
	std::string triggerCondition;

	GuideConfig();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct QuestConfig : public Streamable
{
	uint64_t id;
	uint32_t type;
	uint32_t client;
	uint32_t initAccept;
	std::string preCondition;
	std::string cmpCondition;
	uint32_t cmpAcceptQuest;
	std::string autoPath;
	uint32_t openWidget;
	std::string context;
	uint32_t exp;
	std::string appectActions;
	std::string cmpActions;
	std::string receiveActions;
	std::string bindNpc;

	QuestConfig();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct LandmassConfig : public Streamable
{
	uint64_t id;
	std::string maps;
	std::string scenes;
	std::string range;
	std::string loadImgPath;
	uint64_t loadUIBP;

	LandmassConfig();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SceneConfig : public Streamable
{
	uint64_t id;
	std::string range;

	SceneConfig();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

}

#endif
