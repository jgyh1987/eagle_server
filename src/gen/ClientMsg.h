#ifndef _CLIENT_MSG_H_
#define _CLIENT_MSG_H_
#include <string>
#include <vector>
#include <list>
#include <map>
#include "CommonType.h"
#include "Struct.h"
#include "Streamable.h"

namespace ClientMsg
{

using namespace Struct;

struct __BaseMessage__  : public Streamable
{
	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct Message : public __BaseMessage__
{
	uint32_t majorCmd;
	uint32_t minorCmd;
	uint32_t type;

	Message();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct LoginCommand : public Message 
{
	static const uint32_t MAJOR_CMD = 2;

	LoginCommand();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MapCommand : public Message 
{
	static const uint32_t MAJOR_CMD = 3;

	MapCommand();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FightCommand : public Message 
{
	static const uint32_t MAJOR_CMD = 4;

	FightCommand();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerInfoCommand : public Message 
{
	static const uint32_t MAJOR_CMD = 6;

	PlayerInfoCommand();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChatMessageCommand : public Message 
{
	static const uint32_t MAJOR_CMD = 7;

	ChatMessageCommand();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct WorldMessageCommand : public Message 
{
	static const uint32_t MAJOR_CMD = 8;

	WorldMessageCommand();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendMessageCommand : public Message 
{
	static const uint32_t MAJOR_CMD = 9;

	FriendMessageCommand();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ClientExInfoMessageCommand : public Message 
{
	static const uint32_t MAJOR_CMD = 99;

	ClientExInfoMessageCommand();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct RegistAccountReq : public LoginCommand
{
	static const uint32_t MINOR_CMD = 1;
	static const uint32_t CMD = 2001;

	std::string account;
	std::string passwd;
	std::string model;
	uint32_t sdkType;
	std::string mac;
	std::string platfrom;

	RegistAccountReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct RegistAccountRes : public LoginCommand
{
	static const uint32_t MINOR_CMD = 2;
	static const uint32_t CMD = 2002;

	uint32_t ret;
	std::string account;

	RegistAccountRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct LoginSessionReq : public LoginCommand
{
	static const uint32_t MINOR_CMD = 4;
	static const uint32_t CMD = 2004;

	std::string openid;
	std::string openkey;
	uint32_t sdkType;
	std::string mac;
	std::string model;
	uint32_t vistor;
	std::string platfrom;

	LoginSessionReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct LoginSessionAccountRes : public LoginCommand
{
	static const uint32_t MINOR_CMD = 5;
	static const uint32_t CMD = 2005;

	uint32_t ret;
	std::string session;
	std::vector< Struct::ServerInfo > data;
	uint32_t commonServerID;
	std::vector< uint32_t > roleServerID;
	std::string account;
	uint64_t accountId;

	LoginSessionAccountRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SelectServerReq : public LoginCommand
{
	static const uint32_t MINOR_CMD = 10;
	static const uint32_t CMD = 2010;

	std::string account;
	uint32_t gameServerID;

	SelectServerReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SelectServerRes : public LoginCommand
{
	static const uint32_t MINOR_CMD = 11;
	static const uint32_t CMD = 2011;

	uint32_t ret;
	Struct::ServerInfo gateServerInfo;
	std::string session;

	SelectServerRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SelectLogicReq : public LoginCommand
{
	static const uint32_t MINOR_CMD = 12;
	static const uint32_t CMD = 2012;

	std::string account;
	std::string session;

	SelectLogicReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SelectLogicRes : public LoginCommand
{
	static const uint32_t MINOR_CMD = 13;
	static const uint32_t CMD = 2013;

	uint32_t ret;
	Struct::PlayerSimpleInfo playerInfo;
	std::vector< Struct::RoleSimpleInfo > roleInfo;
	Struct::ServerInfo chatServerInfo;
	std::string serverName;
	uint32_t updateDelayTime;

	SelectLogicRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CreateRoleReq : public LoginCommand
{
	static const uint32_t MINOR_CMD = 14;
	static const uint32_t CMD = 2014;

	std::string name;
	uint64_t jobId;
	uint32_t sex;
	uint32_t shape;

	CreateRoleReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CreateRoleRes : public LoginCommand
{
	static const uint32_t MINOR_CMD = 15;
	static const uint32_t CMD = 2015;

	uint32_t ret;
	Struct::PlayerSimpleInfo playerInfo;
	Struct::RoleSimpleInfo roleInfo;

	CreateRoleRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SessionOverSync : public LoginCommand
{
	static const uint32_t MINOR_CMD = 16;
	static const uint32_t CMD = 2016;


	SessionOverSync();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ServerHreatSync : public LoginCommand
{
	static const uint32_t MINOR_CMD = 17;
	static const uint32_t CMD = 2017;

	uint64_t time;
	uint64_t uid;

	ServerHreatSync();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ServerHreatRes : public LoginCommand
{
	static const uint32_t MINOR_CMD = 18;
	static const uint32_t CMD = 2018;

	uint64_t time;
	uint64_t uid;

	ServerHreatRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PackageCodeReq : public LoginCommand
{
	static const uint32_t MINOR_CMD = 19;
	static const uint32_t CMD = 2019;

	std::string code;

	PackageCodeReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PackageCodeRes : public LoginCommand
{
	static const uint32_t MINOR_CMD = 20;
	static const uint32_t CMD = 2020;

	uint32_t ret;

	PackageCodeRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EnterWorldReq : public LoginCommand
{
	static const uint32_t MINOR_CMD = 21;
	static const uint32_t CMD = 2021;

	uint64_t roleId;

	EnterWorldReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EnterWorldRes : public LoginCommand
{
	static const uint32_t MINOR_CMD = 22;
	static const uint32_t CMD = 2022;

	uint32_t ret;
	Struct::RoleInfo roleInfo;

	EnterWorldRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DeleteRoleReq : public LoginCommand
{
	static const uint32_t MINOR_CMD = 23;
	static const uint32_t CMD = 2023;

	std::string account;
	uint64_t roleId;

	DeleteRoleReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DeleteRoleRes : public LoginCommand
{
	static const uint32_t MINOR_CMD = 24;
	static const uint32_t CMD = 2024;

	uint32_t ret;
	uint64_t roleId;

	DeleteRoleRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct KickPlayerNotify : public LoginCommand
{
	static const uint32_t MINOR_CMD = 25;
	static const uint32_t CMD = 2025;

	uint32_t ret;

	KickPlayerNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EnterMapReq : public MapCommand
{
	static const uint32_t MINOR_CMD = 1;
	static const uint32_t CMD = 3001;


	EnterMapReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EnterMapRes : public MapCommand
{
	static const uint32_t MINOR_CMD = 2;
	static const uint32_t CMD = 3002;

	Struct::FighterBaseInfo pos;
	uint32_t sceneId;
	uint32_t mapId;
	uint32_t ret;
	Struct::ServerInfo server;

	EnterMapRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EnterMapNotify : public MapCommand
{
	static const uint32_t MINOR_CMD = 3;
	static const uint32_t CMD = 3003;

	std::vector< Struct::FighterCompleteInfo > players;

	EnterMapNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MoveReq : public MapCommand
{
	static const uint32_t MINOR_CMD = 4;
	static const uint32_t CMD = 3004;

	Struct::MapPos pos;

	MoveReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MoveRes : public MapCommand
{
	static const uint32_t MINOR_CMD = 5;
	static const uint32_t CMD = 3005;

	Struct::MapPos pos;
	uint32_t ret;

	MoveRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MoveNotify : public MapCommand
{
	static const uint32_t MINOR_CMD = 6;
	static const uint32_t CMD = 3006;

	std::vector< Struct::FighterBaseInfo > msgs;

	MoveNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DoHurtTestReq : public MapCommand
{
	static const uint32_t MINOR_CMD = 7;
	static const uint32_t CMD = 3007;

	Struct::FighterBaseInfo target;
	uint64_t hurt;

	DoHurtTestReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DoHurtTestRes : public MapCommand
{
	static const uint32_t MINOR_CMD = 8;
	static const uint32_t CMD = 3008;

	uint32_t ret;
	Struct::FighterBaseInfo target;
	uint64_t hurt;

	DoHurtTestRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DoHurtTestNotify : public MapCommand
{
	static const uint32_t MINOR_CMD = 9;
	static const uint32_t CMD = 3009;

	Struct::FighterBaseInfo figher;
	Struct::FighterBaseInfo target;
	uint64_t hurt;

	DoHurtTestNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DoActionReq : public MapCommand
{
	static const uint32_t MINOR_CMD = 10;
	static const uint32_t CMD = 3010;

	Struct::FighterBaseInfo target;
	uint32_t action;
	uint32_t undo;

	DoActionReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DoActionRes : public MapCommand
{
	static const uint32_t MINOR_CMD = 11;
	static const uint32_t CMD = 3011;

	uint32_t ret;
	Struct::FighterBaseInfo target;
	uint32_t action;
	uint32_t undo;

	DoActionRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DoActionNotify : public MapCommand
{
	static const uint32_t MINOR_CMD = 12;
	static const uint32_t CMD = 3012;

	Struct::FighterBaseInfo figher;
	Struct::FighterBaseInfo target;
	uint32_t action;
	uint32_t undo;

	DoActionNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct LeaveMapNotify : public MapCommand
{
	static const uint32_t MINOR_CMD = 13;
	static const uint32_t CMD = 3013;

	std::vector< Struct::FighterBaseInfo > charactors;

	LeaveMapNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EnterDungeonReq : public MapCommand
{
	static const uint32_t MINOR_CMD = 14;
	static const uint32_t CMD = 3014;

	uint64_t playerUid;
	uint64_t dungeonUid;

	EnterDungeonReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EnterDungeonRes : public MapCommand
{
	static const uint32_t MINOR_CMD = 15;
	static const uint32_t CMD = 3015;

	Struct::FighterBaseInfo fighter;
	uint64_t dungeonId;
	uint64_t mapId;
	uint32_t ret;

	EnterDungeonRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct LeaveMapRes : public MapCommand
{
	static const uint32_t MINOR_CMD = 16;
	static const uint32_t CMD = 3016;


	LeaveMapRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct LeaveDungeonReq : public MapCommand
{
	static const uint32_t MINOR_CMD = 17;
	static const uint32_t CMD = 3017;


	LeaveDungeonReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct LeaveDungeonRes : public MapCommand
{
	static const uint32_t MINOR_CMD = 18;
	static const uint32_t CMD = 3018;

	uint32_t ret;

	LeaveDungeonRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct KillNpcReq : public MapCommand
{
	static const uint32_t MINOR_CMD = 19;
	static const uint32_t CMD = 3019;

	uint64_t id;

	KillNpcReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DungeonEndNotify : public MapCommand
{
	static const uint32_t MINOR_CMD = 20;
	static const uint32_t CMD = 3020;


	DungeonEndNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EnterLandNotify : public MapCommand
{
	static const uint32_t MINOR_CMD = 21;
	static const uint32_t CMD = 3021;

	Struct::FighterBaseInfo fighter;
	uint64_t mapId;

	EnterLandNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EnterFinish : public MapCommand
{
	static const uint32_t MINOR_CMD = 22;
	static const uint32_t CMD = 3022;


	EnterFinish();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FightTestReq : public FightCommand
{
	static const uint32_t MINOR_CMD = 1;
	static const uint32_t CMD = 4001;


	FightTestReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FightErrorNotify : public FightCommand
{
	static const uint32_t MINOR_CMD = 2;
	static const uint32_t CMD = 4002;

	uint32_t ret;

	FightErrorNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CastSkillReq : public FightCommand
{
	static const uint32_t MINOR_CMD = 3;
	static const uint32_t CMD = 4003;

	uint32_t skillId;
	uint32_t actionId;
	Struct::FighterBaseInfo targetPos;
	Struct::FighterBaseInfo caster;

	CastSkillReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CastSkillRes : public FightCommand
{
	static const uint32_t MINOR_CMD = 4;
	static const uint32_t CMD = 4004;

	uint32_t ret;
	uint32_t skillId;
	uint32_t actionId;
	Struct::FighterBaseInfo targetPos;
	Struct::FighterBaseInfo caster;

	CastSkillRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CastSkilNotify : public FightCommand
{
	static const uint32_t MINOR_CMD = 5;
	static const uint32_t CMD = 4005;

	Struct::FighterBaseInfo caster;
	uint32_t skillId;
	uint32_t actionId;
	Struct::FighterBaseInfo targetPos;

	CastSkilNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DoHurtNotify : public FightCommand
{
	static const uint32_t MINOR_CMD = 6;
	static const uint32_t CMD = 4006;

	Struct::FighterBaseInfo caster;
	uint32_t skillId;
	uint32_t actionId;
	Struct::FighterBaseInfo target;
	double hurt;

	DoHurtNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DoHitNotify : public FightCommand
{
	static const uint32_t MINOR_CMD = 7;
	static const uint32_t CMD = 4007;

	Struct::FighterBaseInfo caster;
	uint32_t skillId;
	uint32_t actionId;
	std::vector< Struct::FighterBaseInfo > target;
	uint32_t index;
	uint32_t triggerEffectId;

	DoHitNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SkillEndNotify : public FightCommand
{
	static const uint32_t MINOR_CMD = 8;
	static const uint32_t CMD = 4008;

	Struct::FighterBaseInfo caster;
	uint32_t skillId;
	uint32_t actionId;

	SkillEndNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct AddBuffNotify : public FightCommand
{
	static const uint32_t MINOR_CMD = 9;
	static const uint32_t CMD = 4009;

	Struct::BuffInfo buff;

	AddBuffNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EndBuffNotify : public FightCommand
{
	static const uint32_t MINOR_CMD = 10;
	static const uint32_t CMD = 4010;

	Struct::BuffInfo buff;

	EndBuffNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ReviveReq : public FightCommand
{
	static const uint32_t MINOR_CMD = 11;
	static const uint32_t CMD = 4011;


	ReviveReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ReviveRes : public FightCommand
{
	static const uint32_t MINOR_CMD = 12;
	static const uint32_t CMD = 4012;

	uint32_t ret;

	ReviveRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FightInfoNotify : public FightCommand
{
	static const uint32_t MINOR_CMD = 13;
	static const uint32_t CMD = 4013;

	Struct::FighterBaseInfo fighter;
	uint64_t status;
	std::vector< uint64_t > curAttr;

	FightInfoNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct AttrChangeNotify : public FightCommand
{
	static const uint32_t MINOR_CMD = 14;
	static const uint32_t CMD = 4014;

	Struct::FighterBaseInfo fighter;
	uint64_t status;
	std::vector< Struct::AttrInfo > curAttr;

	AttrChangeNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CreateEffectObjectNotify : public FightCommand
{
	static const uint32_t MINOR_CMD = 15;
	static const uint32_t CMD = 4015;

	Struct::FighterBaseInfo caster;
	Struct::FighterBaseInfo effectObject;
	uint32_t skillId;
	uint32_t actionId;
	uint32_t longDisId;

	CreateEffectObjectNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct RemoveEffectObjectNotify : public FightCommand
{
	static const uint32_t MINOR_CMD = 16;
	static const uint32_t CMD = 4016;

	Struct::FighterBaseInfo effectObject;

	RemoveEffectObjectNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct NewMailNotify : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 1;
	static const uint32_t CMD = 6001;

	uint32_t count;

	NewMailNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SendMailReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 2;
	static const uint32_t CMD = 6002;


	SendMailReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SendMailRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 3;
	static const uint32_t CMD = 6003;

	uint32_t ret;

	SendMailRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct RecvMailReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 4;
	static const uint32_t CMD = 6004;

	uint32_t mailid;

	RecvMailReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct RecvMailRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 5;
	static const uint32_t CMD = 6005;

	uint32_t ret;
	std::vector< uint32_t > mails;

	RecvMailRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetMailListReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 6;
	static const uint32_t CMD = 6006;

	uint32_t page;

	GetMailListReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetMailListRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 7;
	static const uint32_t CMD = 6007;

	uint32_t page;
	std::vector< Struct::MailInfo > mails;

	GetMailListRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct NotifyQuestInfo : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 10;
	static const uint32_t CMD = 6010;

	std::vector< Struct::QuestInfo > normals;
	std::vector< Struct::QuestInfo > days;
	std::vector< uint64_t > canAccepts;

	NotifyQuestInfo();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct NotifyQuestChangeInfo : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 11;
	static const uint32_t CMD = 6011;

	Struct::QuestInfo info;

	NotifyQuestChangeInfo();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct QuestReceiveReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 12;
	static const uint32_t CMD = 6012;

	uint64_t id;

	QuestReceiveReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CommonErrorNotify : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 13;
	static const uint32_t CMD = 6013;

	uint32_t ret;

	CommonErrorNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ClientNotifyCmpQuestReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 14;
	static const uint32_t CMD = 6014;

	uint64_t id;

	ClientNotifyCmpQuestReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct NotifyLevelInfo : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 15;
	static const uint32_t CMD = 6015;

	uint32_t level;

	NotifyLevelInfo();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChatMessageReq : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 1;
	static const uint32_t CMD = 7001;

	std::string str;
	std::string channeltype;
	uint32_t vipLevel;
	std::string playerName;

	ChatMessageReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChatMessageRes : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 2;
	static const uint32_t CMD = 7002;

	std::string str;
	std::string channeltype;
	uint32_t vipLevel;
	std::string playerName;

	ChatMessageRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct RegisterChannelReq : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 3;
	static const uint32_t CMD = 7003;

	std::vector< std::string > channeltype;

	RegisterChannelReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct RegisterChannelRes : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 4;
	static const uint32_t CMD = 7004;

	std::vector< std::string > channeltype;
	uint32_t ret;

	RegisterChannelRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GMCMDReq : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 5;
	static const uint32_t CMD = 7005;

	std::string str;

	GMCMDReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GMCMDRes : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 6;
	static const uint32_t CMD = 7006;


	GMCMDRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChaterInfoReq : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 7;
	static const uint32_t CMD = 7007;

	std::string chaterName;

	ChaterInfoReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChaterInfoRes : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 8;
	static const uint32_t CMD = 7008;

	uint32_t ret;
	std::string chaterName;
	uint32_t level;
	uint32_t playerId;
	uint32_t vipLevel;
	uint32_t photoId;

	ChaterInfoRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PMReq : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 9;
	static const uint32_t CMD = 7009;

	uint32_t playerId;
	std::string chatMessage;

	PMReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PMRes : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 10;
	static const uint32_t CMD = 7010;

	uint32_t playerId;
	std::string chatMessage;
	std::string chaterName;

	PMRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct WorldOldMessageReq : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 11;
	static const uint32_t CMD = 7011;

	std::string channeltype;

	WorldOldMessageReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct WorldOldMessageRes : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 12;
	static const uint32_t CMD = 7012;

	std::vector< std::string > chatMessage;
	std::string channeltype;

	WorldOldMessageRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UnRegisterChannelReq : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 13;
	static const uint32_t CMD = 7013;

	std::string channeltype;

	UnRegisterChannelReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UnRegisterChannelRes : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 14;
	static const uint32_t CMD = 7014;

	uint32_t ret;

	UnRegisterChannelRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct WorldTestReq : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 1;
	static const uint32_t CMD = 8001;


	WorldTestReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct WorldTestRes : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 2;
	static const uint32_t CMD = 8002;


	WorldTestRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct WorldMatchReq : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 3;
	static const uint32_t CMD = 8003;

	uint32_t type;

	WorldMatchReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct WorldMatchRes : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 4;
	static const uint32_t CMD = 8004;

	uint32_t ret;
	Struct::WFightDungeonBaseInfo dungeonBaseInfo;

	WorldMatchRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendTestReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 1;
	static const uint32_t CMD = 9001;


	FriendTestReq();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendTestRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 2;
	static const uint32_t CMD = 9002;


	FriendTestRes();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ClientErrorMsgNotify : public ClientExInfoMessageCommand
{
	static const uint32_t MINOR_CMD = 1;
	static const uint32_t CMD = 99001;

	std::string errorInfo;

	ClientErrorMsgNotify();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

}

#endif
