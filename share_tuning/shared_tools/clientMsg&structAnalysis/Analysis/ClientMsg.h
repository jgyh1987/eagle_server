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

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct LoginCommand : public Message 
{
	static const uint32_t MAJOR_CMD = 2;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MapCommand : public Message 
{
	static const uint32_t MAJOR_CMD = 3;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FightCommand : public Message 
{
	static const uint32_t MAJOR_CMD = 4;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PVEDungeosCommand : public Message 
{
	static const uint32_t MAJOR_CMD = 5;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerInfoCommand : public Message 
{
	static const uint32_t MAJOR_CMD = 6;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChatMessageCommand : public Message 
{
	static const uint32_t MAJOR_CMD = 7;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct WorldMessageCommand : public Message 
{
	static const uint32_t MAJOR_CMD = 8;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendMessageCommand : public Message 
{
	static const uint32_t MAJOR_CMD = 9;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GuildMessageCommand : public Message 
{
	static const uint32_t MAJOR_CMD = 10;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ClientExInfoMessageCommand : public Message 
{
	static const uint32_t MAJOR_CMD = 99;

	();

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

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct RegistAccountRes : public LoginCommand
{
	static const uint32_t MINOR_CMD = 2;
	static const uint32_t CMD = 2002;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct LoginAccountReq : public LoginCommand
{
	static const uint32_t MINOR_CMD = 3;
	static const uint32_t CMD = 2003;

	std::string account;
	std::string passwd;
	std::string mac;
	std::string model;
	uint32_t sdkType;

	();

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

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct LoginSessionAccountRes : public LoginCommand
{
	static const uint32_t MINOR_CMD = 5;
	static const uint32_t CMD = 2005;

	uint32_t ret;
	std::string session;
	std::vector<::Struct::ServerInfo> data;
	uint32_t commonServerID;
	std::vector<uint32_t> roleServerID;
	std::string account;
	uint32_t accountId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetServerListReq : public LoginCommand
{
	static const uint32_t MINOR_CMD = 8;
	static const uint32_t CMD = 2008;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetServerListRes : public LoginCommand
{
	static const uint32_t MINOR_CMD = 9;
	static const uint32_t CMD = 2009;

	std::vector<::Struct::ServerInfo> data;
	uint32_t commonServerID;
	std::vector<uint32_t> roleServerID;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SelectServerReq : public LoginCommand
{
	static const uint32_t MINOR_CMD = 10;
	static const uint32_t CMD = 2010;

	std::string account;
	uint32_t serverID;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SelectServerRes : public LoginCommand
{
	static const uint32_t MINOR_CMD = 11;
	static const uint32_t CMD = 2011;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SelectLogicReq : public LoginCommand
{
	static const uint32_t MINOR_CMD = 12;
	static const uint32_t CMD = 2012;

	std::string account;
	std::string session;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SelectLogicRes : public LoginCommand
{
	static const uint32_t MINOR_CMD = 13;
	static const uint32_t CMD = 2013;

	uint32_t ret;
	uint32_t characterNum;
	::Struct::PlayerInfoBase playerInfo;
	std::string serverIP;
	uint32_t serverPort;
	std::string serverName;
	uint32_t updateDelayTime;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CreatePlayerReq : public LoginCommand
{
	static const uint32_t MINOR_CMD = 14;
	static const uint32_t CMD = 2014;

	std::string name;
	uint32_t job;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CreatePlayerRes : public LoginCommand
{
	static const uint32_t MINOR_CMD = 15;
	static const uint32_t CMD = 2015;

	uint32_t ret;
	uint32_t characterNum;
	::Struct::PlayerInfoBase playerInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SessionOverSync : public LoginCommand
{
	static const uint32_t MINOR_CMD = 16;
	static const uint32_t CMD = 2016;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ServerHreatSync : public LoginCommand
{
	static const uint32_t MINOR_CMD = 17;
	static const uint32_t CMD = 2017;

	uint64_t time;
	uint32_t id;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ServerHreatRes : public LoginCommand
{
	static const uint32_t MINOR_CMD = 18;
	static const uint32_t CMD = 2018;

	uint64_t time;
	uint32_t id;
	uint64_t serverTime;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PackageCodeReq : public LoginCommand
{
	static const uint32_t MINOR_CMD = 19;
	static const uint32_t CMD = 2019;

	std::string code;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PackageCodeRes : public LoginCommand
{
	static const uint32_t MINOR_CMD = 20;
	static const uint32_t CMD = 2020;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChangeNameReq : public LoginCommand
{
	static const uint32_t MINOR_CMD = 21;
	static const uint32_t CMD = 2021;

	std::string name;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChangeNameRes : public LoginCommand
{
	static const uint32_t MINOR_CMD = 22;
	static const uint32_t CMD = 2022;

	uint32_t ret;
	std::string name;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct NotifyOtherLogin : public LoginCommand
{
	static const uint32_t MINOR_CMD = 23;
	static const uint32_t CMD = 2023;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct NotifyMoudleFun : public LoginCommand
{
	static const uint32_t MINOR_CMD = 24;
	static const uint32_t CMD = 2024;

	uint32_t funBitMap;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EnterMapReq : public MapCommand
{
	static const uint32_t MINOR_CMD = 1;
	static const uint32_t CMD = 3001;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EnterMapRes : public MapCommand
{
	static const uint32_t MINOR_CMD = 2;
	static const uint32_t CMD = 3002;

	std::vector<::Struct::DungeonsPlayerInfo> team1info;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EnterMapNotify : public MapCommand
{
	static const uint32_t MINOR_CMD = 3;
	static const uint32_t CMD = 3003;

	std::vector<::Struct::DungeonsPlayerInfo> playerinfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MulPVEEnterReq : public MapCommand
{
	static const uint32_t MINOR_CMD = 4;
	static const uint32_t CMD = 3004;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MulPVEEnterRes : public MapCommand
{
	static const uint32_t MINOR_CMD = 5;
	static const uint32_t CMD = 3005;

	uint32_t dungeonId;
	::Struct::DungeonsPlayerInfo playerInfo;
	::Struct::MulPveMapInfo mapInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MulPVEPlayerInfoNotify : public MapCommand
{
	static const uint32_t MINOR_CMD = 6;
	static const uint32_t CMD = 3006;

	std::vector<::Struct::DungeonsPlayerInfo> playerInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MulPVEChangeMapReq : public MapCommand
{
	static const uint32_t MINOR_CMD = 7;
	static const uint32_t CMD = 3007;

	uint32_t mapId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MulPVEChangeMapRes : public MapCommand
{
	static const uint32_t MINOR_CMD = 8;
	static const uint32_t CMD = 3008;

	::Struct::MulPveMapInfo mapInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MulPVEEndReq : public MapCommand
{
	static const uint32_t MINOR_CMD = 9;
	static const uint32_t CMD = 3009;

	uint32_t endType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MulPVEEndRes : public MapCommand
{
	static const uint32_t MINOR_CMD = 10;
	static const uint32_t CMD = 3010;

	uint32_t endType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MulPVEChangeCaptainNotify : public MapCommand
{
	static const uint32_t MINOR_CMD = 11;
	static const uint32_t CMD = 3011;

	uint64_t fighterUid;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MulPVEChangeCaptainRes : public MapCommand
{
	static const uint32_t MINOR_CMD = 12;
	static const uint32_t CMD = 3012;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MulPVENpcDieReq : public MapCommand
{
	static const uint32_t MINOR_CMD = 13;
	static const uint32_t CMD = 3013;

	uint64_t npcUid;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MulPVENpcDieRes : public MapCommand
{
	static const uint32_t MINOR_CMD = 14;
	static const uint32_t CMD = 3014;

	uint64_t npcUid;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MulPVESyncPlayerAttr : public MapCommand
{
	static const uint32_t MINOR_CMD = 15;
	static const uint32_t CMD = 3015;

	std::vector<::Struct::FightAttrInfo> fightersInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MulPVEPlayerQuitNotify : public MapCommand
{
	static const uint32_t MINOR_CMD = 16;
	static const uint32_t CMD = 3016;

	uint64_t fighterUid;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MulPVECreateNpc : public MapCommand
{
	static const uint32_t MINOR_CMD = 17;
	static const uint32_t CMD = 3017;

	std::vector<::Struct::DungeonsNpcInfo> npcInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MulPVECreateNpcRes : public MapCommand
{
	static const uint32_t MINOR_CMD = 18;
	static const uint32_t CMD = 3018;

	std::vector<::Struct::CreateNpcClientKey> npcUid;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SyncMainCityPlayerPos : public MapCommand
{
	static const uint32_t MINOR_CMD = 19;
	static const uint32_t CMD = 3019;

	std::vector<::Struct::FighterPos> players;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerEnterMainCityNotify : public MapCommand
{
	static const uint32_t MINOR_CMD = 20;
	static const uint32_t CMD = 3020;

	::Struct::MainCityPlayerAttrInfo player;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerEnterMainCityNotifyOther : public MapCommand
{
	static const uint32_t MINOR_CMD = 21;
	static const uint32_t CMD = 3021;

	std::vector<::Struct::MainCityPlayerAttrInfo> player;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerLeaveMainCityNotify : public MapCommand
{
	static const uint32_t MINOR_CMD = 22;
	static const uint32_t CMD = 3022;

	uint64_t playerUid;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UpdateMainCityPos : public MapCommand
{
	static const uint32_t MINOR_CMD = 23;
	static const uint32_t CMD = 3023;

	::Struct::FighterPos pos;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerInfoChangeMainCityNotify : public MapCommand
{
	static const uint32_t MINOR_CMD = 24;
	static const uint32_t CMD = 3024;

	::Struct::MainCityPlayerAttrInfo player;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EnterJobTitleDungeonMapReq : public MapCommand
{
	static const uint32_t MINOR_CMD = 25;
	static const uint32_t CMD = 3025;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EnterJobTitleDungeonMapRes : public MapCommand
{
	static const uint32_t MINOR_CMD = 26;
	static const uint32_t CMD = 3026;

	uint32_t dungeonId;
	::Struct::DungeonsPlayerInfo playerInfo;
	::Struct::MulPveMapInfo mapInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JobTitleDungeonPlayerInfoNotify : public MapCommand
{
	static const uint32_t MINOR_CMD = 27;
	static const uint32_t CMD = 3027;

	std::vector<::Struct::DungeonsPlayerInfo> playerInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JobTitleDungeonNpcDieReq : public MapCommand
{
	static const uint32_t MINOR_CMD = 28;
	static const uint32_t CMD = 3028;

	uint64_t npcUid;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JobTitleDungeonNpcDieRes : public MapCommand
{
	static const uint32_t MINOR_CMD = 29;
	static const uint32_t CMD = 3029;

	uint64_t npcUid;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JobTitleDungeonSyncPlayerAttr : public MapCommand
{
	static const uint32_t MINOR_CMD = 30;
	static const uint32_t CMD = 3030;

	std::vector<::Struct::FightAttrInfo> fightersInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JobTitleDungeonPlayerQuitNotify : public MapCommand
{
	static const uint32_t MINOR_CMD = 31;
	static const uint32_t CMD = 3031;

	uint64_t fighterUid;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JobTitleDungeonCreateNpc : public MapCommand
{
	static const uint32_t MINOR_CMD = 32;
	static const uint32_t CMD = 3032;

	std::vector<::Struct::DungeonsNpcInfo> npcInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JobTitleDungeonCreateNpcRes : public MapCommand
{
	static const uint32_t MINOR_CMD = 33;
	static const uint32_t CMD = 3033;

	std::vector<::Struct::CreateNpcClientKey> npcUid;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EndJobTitleDungeonReq : public MapCommand
{
	static const uint32_t MINOR_CMD = 34;
	static const uint32_t CMD = 3034;

	uint32_t endType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EndJobTitleDungeonRes : public MapCommand
{
	static const uint32_t MINOR_CMD = 35;
	static const uint32_t CMD = 3035;

	uint32_t endType;
	uint32_t jobTitleId;
	std::vector<::Struct::DropItem> rewards;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JobTitleDungeonChangeMapReq : public MapCommand
{
	static const uint32_t MINOR_CMD = 36;
	static const uint32_t CMD = 3036;

	uint32_t mapId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JobTitleDungeonChangeMapRes : public MapCommand
{
	static const uint32_t MINOR_CMD = 37;
	static const uint32_t CMD = 3037;

	::Struct::MulPveMapInfo mapInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerMoveReq : public FightCommand
{
	static const uint32_t MINOR_CMD = 1;
	static const uint32_t CMD = 4001;

	std::vector<::Struct::FighterPos> pos;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerMoveNotify : public FightCommand
{
	static const uint32_t MINOR_CMD = 2;
	static const uint32_t CMD = 4002;

	std::vector<::Struct::FighterPos> fightpos;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UseSkillReq : public FightCommand
{
	static const uint32_t MINOR_CMD = 3;
	static const uint32_t CMD = 4003;

	::Struct::FighterPos pos;
	uint32_t skillId;
	::Struct::FighterPos targetPos;
	std::vector<BYTE> data;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UseSkillNotify : public FightCommand
{
	static const uint32_t MINOR_CMD = 4;
	static const uint32_t CMD = 4004;

	uint32_t skillId;
	uint64_t skillUid;
	::Struct::FighterPos pos;
	::Struct::FighterPos targetPos;
	std::vector<BYTE> data;
	uint32_t anger;
	uint32_t manual;
	uint32_t weapon1anger;
	uint32_t weapon2anger;
	uint32_t ret;
	uint32_t isBuff;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SkillHurtReq : public FightCommand
{
	static const uint32_t MINOR_CMD = 5;
	static const uint32_t CMD = 4005;

	::Struct::FighterPos pos;
	uint32_t skillId;
	uint64_t skillUid;
	uint32_t hitIndex;
	std::vector<uint64_t> hurt;
	::Struct::MapPos effectPos;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SkillHurtNotify : public FightCommand
{
	static const uint32_t MINOR_CMD = 6;
	static const uint32_t CMD = 4006;

	::Struct::SkillHurtListInfo hurtlist;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ClientMsgFightReq : public FightCommand
{
	static const uint32_t MINOR_CMD = 7;
	static const uint32_t CMD = 4007;

	std::string data;
	std::vector<::Struct::ClientFightInfo> dataInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ClientMsgFightNotify : public FightCommand
{
	static const uint32_t MINOR_CMD = 8;
	static const uint32_t CMD = 4008;

	std::string data;
	std::vector<::Struct::ClientFightInfo> dataInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ClientMsgDumpReq : public FightCommand
{
	static const uint32_t MINOR_CMD = 9;
	static const uint32_t CMD = 4009;

	std::string data;
	::Struct::ClientDumpInfo dataInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ClientMsgDumpNotify : public FightCommand
{
	static const uint32_t MINOR_CMD = 10;
	static const uint32_t CMD = 4010;

	std::string data;
	::Struct::ClientDumpInfo dataInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ResurrectionReq : public FightCommand
{
	static const uint32_t MINOR_CMD = 11;
	static const uint32_t CMD = 4011;

	uint32_t count;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ResurrectionRes : public FightCommand
{
	static const uint32_t MINOR_CMD = 12;
	static const uint32_t CMD = 4012;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct AddResurrectionReq : public FightCommand
{
	static const uint32_t MINOR_CMD = 13;
	static const uint32_t CMD = 4013;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct LastResurCountNotify : public FightCommand
{
	static const uint32_t MINOR_CMD = 14;
	static const uint32_t CMD = 4014;

	uint32_t count;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DungeonsListReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 4;
	static const uint32_t CMD = 5004;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DungeonsListRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 5;
	static const uint32_t CMD = 5005;

	std::vector<::Struct::DungeonsStatus> info;
	std::vector<::Struct::ChapterRewards> chapterRewards;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DungeonsEnterReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 6;
	static const uint32_t CMD = 5006;

	uint32_t id;
	uint32_t intervalId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DungeonsEnterRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 7;
	static const uint32_t CMD = 5007;

	uint32_t ret;
	::Struct::CopyMapInfo info;
	uint32_t haveBlackShopNpc;
	::Struct::DungeonsPlayerInfo intervalPlayer;
	uint32_t intervalId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DungeonsEndReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 8;
	static const uint32_t CMD = 5008;

	uint32_t id;
	uint32_t endType;
	::Struct::DungeonsStatus star;
	std::string data;
	std::vector<::Struct::DropItem> dropItem;
	std::vector<::Struct::CopyMapMonsterInfo> killMonster;
	BYTE blackShop;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DungeonsEndRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 9;
	static const uint32_t CMD = 5009;

	std::string data;
	::Struct::DungeonsStatus star;
	std::vector<::Struct::DropItem> starLoot;
	uint32_t endType;
	uint32_t exp;
	uint32_t money;
	uint32_t intervalId;
	uint32_t daymapCount;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DungeonsSweepReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 10;
	static const uint32_t CMD = 5010;

	uint32_t id;
	uint32_t count;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DungeonsSweepRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 11;
	static const uint32_t CMD = 5011;

	uint32_t count;
	std::vector<::Struct::CopyMapInfo> loots;
	uint32_t ret;
	uint32_t daymapCount;
	std::vector<uint32_t> exp;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UpdateDungeonsNotify : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 12;
	static const uint32_t CMD = 5012;

	::Struct::DungeonsStatus info;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UpdatePveCommonNotify : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 13;
	static const uint32_t CMD = 5013;

	::Struct::SweepEnergyInfo sweepInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SweepMaxBuyReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 14;
	static const uint32_t CMD = 5014;

	uint32_t id;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SweepMaxBuyRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 15;
	static const uint32_t CMD = 5015;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DungeonsStrategyReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 16;
	static const uint32_t CMD = 5016;

	uint32_t dungeonId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DungeonsStrategyRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 17;
	static const uint32_t CMD = 5017;

	std::vector<::Struct::DungeonsStrategyInfo> strategys;
	uint32_t dungeonId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DungeonsStrategyAddReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 18;
	static const uint32_t CMD = 5018;

	uint32_t dungeonId;
	std::string strategy;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DungeonsStrategyAddRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 19;
	static const uint32_t CMD = 5019;

	uint32_t ret;
	std::vector<::Struct::DungeonsStrategyInfo> strategys;
	uint32_t dungeonId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DaymapInfoReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 20;
	static const uint32_t CMD = 5020;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DaymapInfoRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 21;
	static const uint32_t CMD = 5021;

	uint32_t daymapCount;
	uint32_t discountChapterId;
	uint32_t energy;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ClimbTowerInfoReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 22;
	static const uint32_t CMD = 5022;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ClimbTowerInfoRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 23;
	static const uint32_t CMD = 5023;

	uint32_t curSubId;
	uint32_t curLayer;
	uint32_t maxLayer;
	uint32_t maxSubId;
	uint32_t reward;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ClimbTowerEnterReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 24;
	static const uint32_t CMD = 5024;

	uint32_t layer;
	uint32_t subId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ClimbTowerEnterRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 25;
	static const uint32_t CMD = 5025;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ClimbTowerEndReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 26;
	static const uint32_t CMD = 5026;

	uint32_t layer;
	uint32_t subId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ClimbTowerEndRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 27;
	static const uint32_t CMD = 5027;

	uint32_t layer;
	uint32_t subId;
	uint32_t ret;
	uint32_t endType;
	std::vector<::Struct::DropItem> loot;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ClimbTowerRewardReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 28;
	static const uint32_t CMD = 5028;

	uint32_t layer;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ClimbTowerRewardRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 29;
	static const uint32_t CMD = 5029;

	uint32_t reward;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetChapterRewardReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 32;
	static const uint32_t CMD = 5032;

	uint32_t index;
	uint32_t reward;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetChapterRewardRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 33;
	static const uint32_t CMD = 5033;

	uint32_t ret;
	::Struct::ChapterRewards info;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UpdateDungeonsDoubleNotify : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 34;
	static const uint32_t CMD = 5034;

	std::vector<::Struct::DungeonDoubleInfo> doubleInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DungeonsStrategyClikeReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 35;
	static const uint32_t CMD = 5035;

	uint32_t dungeonId;
	uint32_t strategyId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DungeonsStrategyClikeRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 36;
	static const uint32_t CMD = 5036;

	uint32_t selfClike;
	uint32_t strategyId;
	uint32_t dungeonId;
	uint32_t clike;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CreateJobTitleDungeonReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 37;
	static const uint32_t CMD = 5037;

	uint32_t mapType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CreateJobTitleDungeonRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 38;
	static const uint32_t CMD = 5038;

	uint32_t ret;
	::Struct::JobTitleDungeonSimpleInfo room;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct InvitationJobTitleDungeonReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 39;
	static const uint32_t CMD = 5039;

	uint32_t playerId;
	::Struct::JobTitleDungeonSimpleInfo room;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct InvitationJobTitleDungeonRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 40;
	static const uint32_t CMD = 5040;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct InvitationJobTitleDungeonNotify : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 41;
	static const uint32_t CMD = 5041;

	::Struct::JobTitleDungeonSimpleInfo room;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EnterJobTitleDungeonReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 42;
	static const uint32_t CMD = 5042;

	std::string captainName;
	uint64_t roomUid;
	uint32_t mapType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EnterJobTitleDungeonRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 43;
	static const uint32_t CMD = 5043;

	uint64_t roomUid;
	uint32_t ret;
	uint32_t mapType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChangeJobTitleDungeonPlayersNotify : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 44;
	static const uint32_t CMD = 5044;

	::Struct::JobTitleDungeonRoomInfo roomInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ReadyJobTitleDungeonReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 45;
	static const uint32_t CMD = 5045;

	uint32_t ready;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ReadyJobTitleDungeonRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 46;
	static const uint32_t CMD = 5046;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ReadyJobTitleDungeonNotify : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 47;
	static const uint32_t CMD = 5047;

	std::vector<uint32_t> ready;
	uint32_t playerMaxCount;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct OpenJobTitleDungeonPosReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 48;
	static const uint32_t CMD = 5048;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct OpenJobTitleDungeonPosRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 49;
	static const uint32_t CMD = 5049;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct OpenJobTitleDungeonPosNotify : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 50;
	static const uint32_t CMD = 5050;

	uint32_t playerMaxCount;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct StartJobTitleDungeonReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 51;
	static const uint32_t CMD = 5051;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct StartJobTitleDungeonRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 52;
	static const uint32_t CMD = 5052;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct StartJobTitleDungeonNotify : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 53;
	static const uint32_t CMD = 5053;

	::Struct::MulPveInfo info;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct LevelJobTitleDungeonReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 54;
	static const uint32_t CMD = 5054;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct LevelJobTitleDungeonRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 55;
	static const uint32_t CMD = 5055;

	uint32_t ret;
	uint32_t levelType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct TickJobTitleDungeonReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 56;
	static const uint32_t CMD = 5056;

	uint32_t index;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct TickJobTitleDungeonRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 57;
	static const uint32_t CMD = 5057;

	uint32_t ret;
	uint32_t index;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BossRushInfoReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 58;
	static const uint32_t CMD = 5058;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BossRushInfoRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 59;
	static const uint32_t CMD = 5059;

	std::vector<::Struct::BossRushGateInfo> info;
	uint32_t stars;
	uint32_t rewards;
	uint32_t freeRefresh;
	uint32_t jionCount;
	uint32_t buyRefreshCount;
	uint32_t buyJionCount;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BossRushRewardReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 60;
	static const uint32_t CMD = 5060;

	uint32_t index;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BossRushRewardRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 61;
	static const uint32_t CMD = 5061;

	uint32_t rewards;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BossRushRefreshReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 62;
	static const uint32_t CMD = 5062;

	uint32_t free;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BossRushRefreshRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 63;
	static const uint32_t CMD = 5063;

	std::vector<::Struct::BossRushGateInfo> info;
	uint32_t freeRefresh;
	uint32_t buyRefreshCount;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BossRushBuyJoinReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 64;
	static const uint32_t CMD = 5064;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BossRushBuyJoinRes : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 65;
	static const uint32_t CMD = 5065;

	uint32_t ret;
	uint32_t jionCount;
	uint32_t buyJionCount;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ClimbTowerCloseReq : public PVEDungeosCommand
{
	static const uint32_t MINOR_CMD = 66;
	static const uint32_t CMD = 5066;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct NewMailNotify : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 1;
	static const uint32_t CMD = 6001;

	uint32_t count;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SendMailReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 2;
	static const uint32_t CMD = 6002;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SendMailRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 3;
	static const uint32_t CMD = 6003;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct RecvMailReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 4;
	static const uint32_t CMD = 6004;

	uint32_t mailid;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct RecvMailRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 5;
	static const uint32_t CMD = 6005;

	uint32_t ret;
	std::vector<uint32_t> mails;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetMailListReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 6;
	static const uint32_t CMD = 6006;

	uint32_t page;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetMailListRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 7;
	static const uint32_t CMD = 6007;

	uint32_t page;
	std::vector<::Struct::MailInfo> mails;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GMReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 8;
	static const uint32_t CMD = 6008;

	std::string str;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GMRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 9;
	static const uint32_t CMD = 6009;

	std::string str;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetBagInfoReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 10;
	static const uint32_t CMD = 6010;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetBagInfoRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 11;
	static const uint32_t CMD = 6011;

	std::vector<::Struct::ItemInfo> itemList;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetEquipBagInfoReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 12;
	static const uint32_t CMD = 6012;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetEquipBagInfoRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 13;
	static const uint32_t CMD = 6013;

	std::vector<::Struct::EquipInfo> equipList;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UpdateEquipStarReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 14;
	static const uint32_t CMD = 6014;

	uint64_t uid;
	uint32_t exp;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UpdateEquipStarRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 15;
	static const uint32_t CMD = 6015;

	::Struct::EquipInfo equip;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UpdateEquipLevelReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 16;
	static const uint32_t CMD = 6016;

	uint64_t uid;
	uint32_t level;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UpdateEquipLevelRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 17;
	static const uint32_t CMD = 6017;

	::Struct::EquipInfo equip;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UpdateEquipQualityReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 18;
	static const uint32_t CMD = 6018;

	uint64_t uid;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UpdateEquipQualityRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 19;
	static const uint32_t CMD = 6019;

	::Struct::EquipInfo equip;
	uint32_t ret;
	uint64_t uid;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SetRoleToTeamReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 20;
	static const uint32_t CMD = 6020;

	uint32_t id;
	BYTE index;
	BYTE teamIndex;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SetRoleToTeamRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 21;
	static const uint32_t CMD = 6021;

	uint32_t ret;
	::Struct::PartnerTeamInfo partnerteam;
	uint32_t id;
	BYTE index;
	BYTE teamIndex;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetPartnerTeamReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 22;
	static const uint32_t CMD = 6022;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetPartnerTeamRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 23;
	static const uint32_t CMD = 6023;

	std::vector<::Struct::PartnerTeamInfo> partnerteams;
	uint32_t curIndex;
	std::vector<::Struct::MsgRoleInfo> haveRoles;
	std::vector<uint32_t> havePhotos;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SetEquipToTeamReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 24;
	static const uint32_t CMD = 6024;

	uint64_t uid;
	BYTE index;
	BYTE teamIndex;
	BYTE pos;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SetEquipToTeamRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 25;
	static const uint32_t CMD = 6025;

	uint32_t ret;
	::Struct::PartnerTeamInfo partnerteam;
	uint32_t id;
	BYTE index;
	BYTE teamIndex;
	BYTE pos;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChangeIndexToTeamReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 26;
	static const uint32_t CMD = 6026;

	BYTE teamIndex;
	std::vector<uint32_t> changePos;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChangeIndexToTeamRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 27;
	static const uint32_t CMD = 6027;

	uint32_t ret;
	BYTE teamIndex;
	::Struct::PartnerTeamInfo partnerteam;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SetUsePartnerTeamIndexReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 28;
	static const uint32_t CMD = 6028;

	uint32_t index;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SetUsePartnerTeamIndexRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 29;
	static const uint32_t CMD = 6029;

	uint32_t index;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct OpenMagicShopReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 30;
	static const uint32_t CMD = 6030;

	uint32_t shoptype;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct OpenMagicShopRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 31;
	static const uint32_t CMD = 6031;

	uint32_t shoptype;
	uint32_t ret;
	std::vector<::Struct::ShopItemInfo> items;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BuyMagicShopReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 33;
	static const uint32_t CMD = 6033;

	uint32_t shoptype;
	uint32_t index;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BuyMagicShopRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 34;
	static const uint32_t CMD = 6034;

	uint32_t shoptype;
	uint32_t ret;
	uint32_t index;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct OpenRunBusinessReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 37;
	static const uint32_t CMD = 6037;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct OpenRunBusinessRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 38;
	static const uint32_t CMD = 6038;

	std::vector<uint32_t> levelTime;
	std::vector<uint32_t> waitUnload;
	std::vector<::Struct::DropItem> items;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetRunBusinessRewardReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 39;
	static const uint32_t CMD = 6039;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetRunBusinessRewardRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 40;
	static const uint32_t CMD = 6040;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct NotifyPlayerBaseInfo : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 41;
	static const uint32_t CMD = 6041;

	uint32_t sweepEnergy;
	uint32_t energy;
	uint32_t gold;
	uint32_t money;
	uint32_t exp;
	std::vector<::Struct::DropItem> commonCion;
	uint32_t level;
	uint32_t fight;
	uint32_t vipLevel;
	uint32_t recoverEnergyTime;
	uint32_t jjcTicket;
	std::vector<::Struct::PlayerGiftInfo> giftTreeList;
	uint32_t worldChatFreeTimes;
	uint32_t juedouChangCount;
	uint32_t buyMoneyCount;
	uint32_t buyJJCTicketCount;
	uint32_t guildQiandao;
	uint32_t guildReward;
	uint32_t guildWeekHuoyueReward;
	uint32_t guildMulPveCount;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetBaptizeEnergyReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 42;
	static const uint32_t CMD = 6042;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetBaptizeEnergyRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 43;
	static const uint32_t CMD = 6043;

	uint32_t baptizeenergy;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BaptizeReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 44;
	static const uint32_t CMD = 6044;

	uint64_t uid;
	uint32_t index;
	uint32_t baptizeType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BaptizeRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 45;
	static const uint32_t CMD = 6045;

	::Struct::EquipInfo equip;
	uint32_t ret;
	uint32_t index;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PartnerPassiveReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 46;
	static const uint32_t CMD = 6046;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PartnerPassiveRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 47;
	static const uint32_t CMD = 6047;

	std::vector<::Struct::TeamPassiveInfo> passiveList;
	std::vector<::Struct::GuildSkill> guildSkills;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PartnerPassiveUpReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 48;
	static const uint32_t CMD = 6048;

	uint32_t subid;
	uint32_t level;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PartnerPassiveUpRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 49;
	static const uint32_t CMD = 6049;

	uint32_t ret;
	uint32_t subid;
	uint32_t level;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EquipGiftUpReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 50;
	static const uint32_t CMD = 6050;

	uint32_t subid;
	uint32_t level;
	uint32_t oprType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EquipGiftUpRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 51;
	static const uint32_t CMD = 6051;

	uint32_t ret;
	uint32_t subid;
	uint32_t level;
	uint32_t oprType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChangeItemNotify : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 52;
	static const uint32_t CMD = 6052;

	std::vector<::Struct::ItemInfo> changeItems;
	std::vector<uint64_t> removeItems;
	std::vector<::Struct::EquipInfo> addEquips;
	std::vector<::Struct::DropItem> changeCoins;
	uint32_t clientType;
	std::vector<::Struct::GemInfo> changeGems;
	std::vector<::Struct::FateGuardInfo> changeFateGuards;
	std::vector<uint32_t> addPartners;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct NotifySimpleInfo : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 53;
	static const uint32_t CMD = 6053;

	::Struct::DropItem value1;
	::Struct::DropItem value2;
	::Struct::DropItem value3;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ComposeItemReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 54;
	static const uint32_t CMD = 6054;

	uint32_t composeId;
	uint32_t clientFuncType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ComposeItemRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 55;
	static const uint32_t CMD = 6055;

	uint32_t ret;
	uint32_t clientFuncType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChestInfoReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 56;
	static const uint32_t CMD = 6056;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct NotifyChestInfo : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 57;
	static const uint32_t CMD = 6057;

	uint32_t PartnerNextFreeTime;
	uint32_t PartnerNextProtect;
	uint32_t PartnerLastCounts;
	uint32_t FateNextFreeTime;
	uint32_t FateNextProtect;
	uint32_t FateLastCounts;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct NotifyChestOffsetInfo : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 58;
	static const uint32_t CMD = 6058;

	uint32_t PartnerOnceCost;
	uint32_t PartnerTenCost;
	uint32_t FateOnceCost;
	uint32_t FateTenCost;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChestExtractReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 59;
	static const uint32_t CMD = 6059;

	uint32_t extractType;
	uint32_t isFree;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChestExtractRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 60;
	static const uint32_t CMD = 6060;

	std::vector<::Struct::DropItem> items;
	uint32_t ret;
	uint32_t extractType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct NotifyQuestInfo : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 61;
	static const uint32_t CMD = 6061;

	std::vector<::Struct::QuestInfo> normals;
	std::vector<::Struct::QuestInfo> days;
	std::vector<uint32_t> completeQuests;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct NotifyQuestChangeInfo : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 62;
	static const uint32_t CMD = 6062;

	::Struct::QuestInfo info;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct QuestReceiveReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 63;
	static const uint32_t CMD = 6063;

	uint32_t id;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EquipMeltingReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 74;
	static const uint32_t CMD = 6074;

	std::vector<uint64_t> equipUid;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EquipMeltingRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 75;
	static const uint32_t CMD = 6075;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SetPhotoReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 82;
	static const uint32_t CMD = 6082;

	uint32_t id;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SetPhotoRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 83;
	static const uint32_t CMD = 6083;

	uint32_t ret;
	uint32_t id;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BuyCoinReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 84;
	static const uint32_t CMD = 6084;

	uint32_t coinId;
	uint32_t BuyCount;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BuyCoinRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 85;
	static const uint32_t CMD = 6085;

	uint32_t ret;
	uint32_t coinId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ActiveValueReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 86;
	static const uint32_t CMD = 6086;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ActiveValueRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 87;
	static const uint32_t CMD = 6087;

	uint32_t activeValue;
	std::vector<::Struct::AvtiveValueReward> reward;
	std::vector<::Struct::AvtiveValueEvent> activeEvent;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ActiveValueRewardReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 88;
	static const uint32_t CMD = 6088;

	uint32_t index;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ActiveValueRewardRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 89;
	static const uint32_t CMD = 6089;

	uint32_t rewards;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ActiveValueNotify : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 90;
	static const uint32_t CMD = 6090;

	uint32_t rewards;
	uint32_t activeValue;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DaySignReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 91;
	static const uint32_t CMD = 6091;

	uint32_t sign;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct DaySignRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 92;
	static const uint32_t CMD = 6092;

	uint32_t signId;
	uint32_t isSign;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct NewPlayerGuideReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 93;
	static const uint32_t CMD = 6093;

	uint32_t guideId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct NewPlayerGuideRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 94;
	static const uint32_t CMD = 6094;

	uint32_t guideId;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerMonthCardInfo : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 95;
	static const uint32_t CMD = 6095;

	std::vector<::Struct::MonthCardsInfo> monthCards;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetMonthCardRewardReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 96;
	static const uint32_t CMD = 6096;

	uint32_t cardType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetMonthCardRewardRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 97;
	static const uint32_t CMD = 6097;

	uint32_t ret;
	uint32_t cardType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct RedIconNotify : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 98;
	static const uint32_t CMD = 6098;

	std::vector<::Struct::RedIconInfo> redIcons;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ActivityGiftReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 99;
	static const uint32_t CMD = 6099;

	uint32_t activityType;
	uint32_t id;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ActivityGiftRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 100;
	static const uint32_t CMD = 6100;

	uint32_t ret;
	::Struct::ActivityTypeInfo activityTypes;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ActivityInfoReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 101;
	static const uint32_t CMD = 6101;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ActivityInfoRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 102;
	static const uint32_t CMD = 6102;

	std::vector<::Struct::ActivityTypeInfo> activityTypes;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ClientQuestCompReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 103;
	static const uint32_t CMD = 6103;

	uint32_t questId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetRoleNotify : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 104;
	static const uint32_t CMD = 6104;

	::Struct::MsgRoleInfo roleInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UseBagItemReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 113;
	static const uint32_t CMD = 6113;

	uint64_t uid;
	uint32_t count;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UseBagItemRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 114;
	static const uint32_t CMD = 6114;

	uint32_t ret;
	uint64_t uid;
	uint32_t count;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SetGiftTreeReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 115;
	static const uint32_t CMD = 6115;

	uint32_t subid;
	uint32_t oprType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SetGiftTreeRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 116;
	static const uint32_t CMD = 6116;

	uint32_t ret;
	uint32_t subid;
	uint32_t oprType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UpdatePartnerLevelReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 117;
	static const uint32_t CMD = 6117;

	uint32_t id;
	::Struct::DropItem itemId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UpdatePartnerLevelRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 118;
	static const uint32_t CMD = 6118;

	::Struct::PartnerInfo partner;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PartnersBagReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 119;
	static const uint32_t CMD = 6119;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PartnersBagRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 120;
	static const uint32_t CMD = 6120;

	std::vector<::Struct::PartnerInfo> partners;
	uint32_t curPartnerId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UpdatePartnerStarsReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 121;
	static const uint32_t CMD = 6121;

	uint32_t id;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UpdatePartnerStarsRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 122;
	static const uint32_t CMD = 6122;

	::Struct::PartnerInfo partner;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PartnerSetFightReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 123;
	static const uint32_t CMD = 6123;

	uint32_t id;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PartnerSetFightRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 124;
	static const uint32_t CMD = 6124;

	uint32_t ret;
	uint32_t id;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PartnerUpSkillReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 125;
	static const uint32_t CMD = 6125;

	uint32_t id;
	uint32_t subid;
	uint32_t level;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PartnerUpSkillRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 126;
	static const uint32_t CMD = 6126;

	uint32_t ret;
	uint32_t subid;
	uint32_t level;
	uint32_t id;
	::Struct::PartnerInfo partner;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PartnerComposeReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 127;
	static const uint32_t CMD = 6127;

	uint32_t id;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PartnerComposeRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 128;
	static const uint32_t CMD = 6128;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PartnerRecoverReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 129;
	static const uint32_t CMD = 6129;

	uint32_t id;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PartnerRecoverRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 130;
	static const uint32_t CMD = 6130;

	uint32_t ret;
	::Struct::PartnerInfo partner;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PartnerReNameReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 131;
	static const uint32_t CMD = 6131;

	uint32_t id;
	std::string name;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PartnerReNameRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 132;
	static const uint32_t CMD = 6132;

	uint32_t ret;
	::Struct::PartnerInfo partner;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PartnerGetNotify : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 133;
	static const uint32_t CMD = 6133;

	::Struct::PartnerInfo partner;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EquipGridUpReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 134;
	static const uint32_t CMD = 6134;

	uint32_t index;
	uint32_t oprType;
	uint32_t level;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EquipGridUpRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 135;
	static const uint32_t CMD = 6135;

	uint32_t ret;
	uint32_t oprType;
	::Struct::EquipGridInfo equipGrids;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EquipGridUpNotify : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 136;
	static const uint32_t CMD = 6136;

	std::vector<::Struct::EquipGridInfo> equipGrids;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GemStonesBagReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 137;
	static const uint32_t CMD = 6137;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GemStonesBagRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 138;
	static const uint32_t CMD = 6138;

	std::vector<::Struct::GemInfo> GemStones;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GemStonesInlayReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 139;
	static const uint32_t CMD = 6139;

	uint32_t inlayType;
	uint32_t equipPos;
	uint32_t equipGemSolt;
	uint32_t gemSolt;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GemStonesInlayRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 140;
	static const uint32_t CMD = 6140;

	::Struct::EquipGridInfo equip;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FateGuardBagReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 141;
	static const uint32_t CMD = 6141;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FateGuardBagRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 142;
	static const uint32_t CMD = 6142;

	std::vector<::Struct::FateGuardInfo> fateGuards;
	std::vector<::Struct::FateGuardInfo> playerFateGuards;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FateGuardInlayReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 143;
	static const uint32_t CMD = 6143;

	uint32_t inlayType;
	uint32_t pos;
	uint64_t fateGuardUid;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FateGuardInlayRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 144;
	static const uint32_t CMD = 6144;

	::Struct::FateGuardInfo fateGuard;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetFashionArmorReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 145;
	static const uint32_t CMD = 6145;

	uint32_t preType;
	uint32_t id;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetFashionArmorRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 146;
	static const uint32_t CMD = 6146;

	uint32_t ret;
	uint32_t id;
	uint32_t preType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SetFashionArmorReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 147;
	static const uint32_t CMD = 6147;

	uint32_t id;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SetFashionArmorRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 148;
	static const uint32_t CMD = 6148;

	uint32_t ret;
	uint32_t id;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FashionArmorNotify : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 149;
	static const uint32_t CMD = 6149;

	uint32_t id;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FashionArmorBagReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 150;
	static const uint32_t CMD = 6150;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FashionArmorBagRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 151;
	static const uint32_t CMD = 6151;

	std::vector<uint32_t> fashionArmors;
	uint32_t curFashionArmor;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FateGuardDevourReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 152;
	static const uint32_t CMD = 6152;

	std::vector<uint64_t> devourFateGuardUids;
	uint32_t desFateGuardSolt;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FateGuardDevourRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 153;
	static const uint32_t CMD = 6153;

	uint32_t ret;
	::Struct::FateGuardInfo fateGuardInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JobTitleInfoNotify : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 154;
	static const uint32_t CMD = 6154;

	uint32_t maxJobTitleId;
	uint32_t curJobTitleId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetVipGiftReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 155;
	static const uint32_t CMD = 6155;

	uint32_t giftId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetVipGiftRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 156;
	static const uint32_t CMD = 6156;

	uint32_t ret;
	uint32_t vipGiftList;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct VipInfoNotify : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 157;
	static const uint32_t CMD = 6157;

	uint32_t rechargeAmount;
	uint32_t vipLevel;
	uint32_t vipGiftList;
	uint32_t rewardState;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UpdatePlayerLevelNotify : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 158;
	static const uint32_t CMD = 6158;

	uint32_t exp;
	uint32_t level;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetRechargeRewardReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 159;
	static const uint32_t CMD = 6159;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetRechargeRewardRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 160;
	static const uint32_t CMD = 6160;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BuyGoldFundReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 170;
	static const uint32_t CMD = 6170;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BuyGoldFundRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 171;
	static const uint32_t CMD = 6171;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GoldFundInfoReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 172;
	static const uint32_t CMD = 6172;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GoldFundInfoRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 173;
	static const uint32_t CMD = 6173;

	uint32_t stage;
	std::vector<::Struct::GoldFundInfo> itemInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ReceiveGoldFundReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 174;
	static const uint32_t CMD = 6174;

	uint32_t id;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ReceiveGoldFundRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 175;
	static const uint32_t CMD = 6175;

	uint32_t ret;
	uint32_t id;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct OffLineExpInfoReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 176;
	static const uint32_t CMD = 6176;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct OffLineExpInfoRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 177;
	static const uint32_t CMD = 6177;

	uint32_t offlineTime;
	uint32_t baseExp;
	uint32_t timesExp;
	uint32_t refreshTime;
	uint32_t freeTime;
	uint32_t chargeTime;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BuyOffLineChargeTimeReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 178;
	static const uint32_t CMD = 6178;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BuyOffLineChargeTimeRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 179;
	static const uint32_t CMD = 6179;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ReceiveOffLineExpReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 180;
	static const uint32_t CMD = 6180;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ReceiveOffLineExpRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 181;
	static const uint32_t CMD = 6181;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ActiveOpenReq : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 182;
	static const uint32_t CMD = 6182;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ActiveOpenRes : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 183;
	static const uint32_t CMD = 6183;

	std::vector<::Struct::CloseActiveInfo> closeActives;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerInfoCommandMax : public PlayerInfoCommand
{
	static const uint32_t MINOR_CMD = 184;
	static const uint32_t CMD = 6184;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChatMessageReq : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 1;
	static const uint32_t CMD = 7001;

	std::string str;
	std::string channeltype;
	::Struct::ChatPlayerInfo playerInfo;
	uint32_t nowTime;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChatMessageRes : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 2;
	static const uint32_t CMD = 7002;

	std::string str;
	std::string channeltype;
	::Struct::ChatPlayerInfo playerInfo;
	uint32_t nowTime;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct RegisterChannelReq : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 3;
	static const uint32_t CMD = 7003;

	std::vector<std::string> channeltype;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct RegisterChannelRes : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 4;
	static const uint32_t CMD = 7004;

	std::vector<std::string> channeltype;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GMCMDReq : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 5;
	static const uint32_t CMD = 7005;

	std::string str;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GMCMDRes : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 6;
	static const uint32_t CMD = 7006;

	std::string cmdStr;
	std::string resStr;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChaterInfoReq : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 7;
	static const uint32_t CMD = 7007;

	std::string chaterName;
	uint32_t playerID;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChaterInfoRes : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 8;
	static const uint32_t CMD = 7008;

	uint32_t ret;
	::Struct::FindPlayerAttrInfo playerInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PMReq : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 9;
	static const uint32_t CMD = 7009;

	uint32_t playerId;
	std::string chatMessage;
	uint32_t nowTime;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PMRes : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 10;
	static const uint32_t CMD = 7010;

	std::string chatMessage;
	::Struct::ChatPlayerInfo playerInfo;
	uint32_t nowTime;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct WorldOldMessageReq : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 11;
	static const uint32_t CMD = 7011;

	std::string channeltype;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct WorldOldMessageRes : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 12;
	static const uint32_t CMD = 7012;

	std::vector<std::string> chatMessage;
	std::string channeltype;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UnRegisterChannelReq : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 13;
	static const uint32_t CMD = 7013;

	std::string channeltype;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct UnRegisterChannelRes : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 14;
	static const uint32_t CMD = 7014;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct AnnounceNotify : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 15;
	static const uint32_t CMD = 7015;

	std::string content;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct WorldChatMessageReq : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 16;
	static const uint32_t CMD = 7016;

	std::string str;
	::Struct::ChatPlayerInfo playerInfo;
	uint32_t nowTime;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct WorldChatMessageRes : public ChatMessageCommand
{
	static const uint32_t MINOR_CMD = 17;
	static const uint32_t CMD = 7017;

	std::string str;
	::Struct::ChatPlayerInfo playerInfo;
	uint32_t nowTime;
	uint32_t freeTimes;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetGatewayAddrReq : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 1;
	static const uint32_t CMD = 8001;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetGatewayAddrRes : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 2;
	static const uint32_t CMD = 8002;

	std::string ip;
	uint32_t port;
	uint32_t serverId;
	std::string session;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct LoginWGatewayReq : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 3;
	static const uint32_t CMD = 8003;

	std::string account;
	std::string session;
	uint32_t serverId;
	uint32_t playerId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct LoginWGatewayRes : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 4;
	static const uint32_t CMD = 8004;

	uint32_t ret;
	std::string worldChatIp;
	uint32_t worldChatPort;
	std::vector<::Struct::MulDungeonPlayerInfo> otherPlayer;
	uint32_t isReconnectFight;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BackLogicReq : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 5;
	static const uint32_t CMD = 8005;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct BackLogicRes : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 6;
	static const uint32_t CMD = 8006;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ReconnectWorldServerNotify : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 7;
	static const uint32_t CMD = 8007;

	std::string ip;
	uint32_t port;
	uint32_t serverId;
	std::string session;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CreateMulPveRoomReq : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 8;
	static const uint32_t CMD = 8008;

	uint32_t mapId;
	uint32_t mapType;
	uint32_t passwd;
	std::string title;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CreateMulPveRoomRes : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 9;
	static const uint32_t CMD = 8009;

	uint32_t ret;
	uint32_t passwd;
	::Struct::MulDungeonSimpleInfo room;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetMulPveRoomReq : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 10;
	static const uint32_t CMD = 8010;

	uint32_t page;
	uint32_t mapId;
	uint32_t mapType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetMulPveRoomRes : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 11;
	static const uint32_t CMD = 8011;

	std::vector<::Struct::MulDungeonSimpleInfo> rooms;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SearchMulPveRoomReq : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 12;
	static const uint32_t CMD = 8012;

	uint32_t roomId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SearchMulPveRoomRes : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 13;
	static const uint32_t CMD = 8013;

	::Struct::MulDungeonSimpleInfo room;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EnterMulPveRoomReq : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 14;
	static const uint32_t CMD = 8014;

	uint32_t roomId;
	uint32_t passwd;
	uint32_t mapId;
	uint32_t isInvitation;
	uint64_t roomUid;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EnterMulPveRoomRes : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 15;
	static const uint32_t CMD = 8015;

	uint32_t roomId;
	uint32_t ret;
	uint64_t roomUid;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct LeaveMulPveRoomReq : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 16;
	static const uint32_t CMD = 8016;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct LeaveMulPveRoomRes : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 17;
	static const uint32_t CMD = 8017;

	uint32_t ret;
	uint32_t leaveType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct StartMulPveRoomReq : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 18;
	static const uint32_t CMD = 8018;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct StartMulPveRoomRes : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 19;
	static const uint32_t CMD = 8019;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct WGateChatReq : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 20;
	static const uint32_t CMD = 8020;

	std::string chatMsg;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct WGateChatRes : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 21;
	static const uint32_t CMD = 8021;

	std::string chatMsg;
	uint32_t serverId;
	uint32_t playerId;
	std::string playerName;
	uint32_t vipLevel;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct RoomPlayerChangeNotify : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 22;
	static const uint32_t CMD = 8022;

	::Struct::MulDungeonInfo roomInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct TickPlayerReq : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 23;
	static const uint32_t CMD = 8023;

	uint32_t index;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct TickPlayerRes : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 24;
	static const uint32_t CMD = 8024;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct WGateChangePasswdReq : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 25;
	static const uint32_t CMD = 8025;

	uint32_t passwd;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct WGateChangePasswdRes : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 26;
	static const uint32_t CMD = 8026;

	uint32_t ret;
	uint32_t passwd;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct QuickEnterMulPveRoomReq : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 27;
	static const uint32_t CMD = 8027;

	uint32_t mapType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct QuickEnterMulPveRoomRes : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 28;
	static const uint32_t CMD = 8028;

	uint32_t roomId;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CreateMulPveRoomNotify : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 29;
	static const uint32_t CMD = 8029;

	uint32_t playerId;
	uint32_t playerServerId;
	uint32_t photoId;
	::Struct::MulDungeonSimpleInfo room;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct WGateChangeMapIdReq : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 30;
	static const uint32_t CMD = 8030;

	uint32_t mapId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct WGateChangeMapIdRes : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 31;
	static const uint32_t CMD = 8031;

	uint32_t ret;
	uint32_t mapId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ReadyMulPveRoomReq : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 32;
	static const uint32_t CMD = 8032;

	uint32_t ready;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ReadyMulPveRoomNotify : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 33;
	static const uint32_t CMD = 8033;

	std::vector<uint32_t> ready;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ConfirmMulPveListReq : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 34;
	static const uint32_t CMD = 8034;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ConfirmMulPveListRes : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 35;
	static const uint32_t CMD = 8035;

	std::vector<::Struct::MulDungeonPlayerInfo> playerList;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct InvitationMulPveReq : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 36;
	static const uint32_t CMD = 8036;

	uint32_t playerId;
	uint32_t serverId;
	::Struct::MulDungeonSimpleInfo invitation;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct InvitationMulPveRes : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 37;
	static const uint32_t CMD = 8037;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct InvitationMulPveNotify : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 38;
	static const uint32_t CMD = 8038;

	::Struct::MulDungeonSimpleInfo invitation;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SyncEquipChangeReq : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 39;
	static const uint32_t CMD = 8039;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SyncEquipChangeRes : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 40;
	static const uint32_t CMD = 8040;

	uint32_t sync;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct MulDungeonEnterNotify : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 41;
	static const uint32_t CMD = 8041;

	::Struct::MulPveInfo info;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ReadyMulPveRoomRes : public WorldMessageCommand
{
	static const uint32_t MINOR_CMD = 42;
	static const uint32_t CMD = 8042;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendListReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 1;
	static const uint32_t CMD = 9001;

	uint32_t page;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendListRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 2;
	static const uint32_t CMD = 9002;

	std::vector<::Struct::FriendInfo> friends;
	uint32_t haveReq;
	uint32_t friendGiftDayCount;
	uint32_t friendGetDayCount;
	std::vector<uint32_t> intimacyRewards;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendReqListReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 3;
	static const uint32_t CMD = 9003;

	uint32_t page;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendReqListRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 4;
	static const uint32_t CMD = 9004;

	std::vector<::Struct::FriendReqInfo> friendReqs;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendSearchReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 5;
	static const uint32_t CMD = 9005;

	uint32_t playerId;
	std::string playerName;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendSearchRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 6;
	static const uint32_t CMD = 9006;

	::Struct::FriendReqInfo playerInfo;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendAddReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 7;
	static const uint32_t CMD = 9007;

	uint32_t playerId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendAddRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 8;
	static const uint32_t CMD = 9008;

	uint32_t ret;
	uint32_t playerId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendDelReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 9;
	static const uint32_t CMD = 9009;

	uint32_t playerId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendDelRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 10;
	static const uint32_t CMD = 9010;

	uint32_t ret;
	uint32_t playerId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendConfirmReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 11;
	static const uint32_t CMD = 9011;

	uint32_t playerId;
	uint32_t oper;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendConfirmRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 12;
	static const uint32_t CMD = 9012;

	uint32_t ret;
	uint32_t playerId;
	uint32_t oper;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendRecommendReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 13;
	static const uint32_t CMD = 9013;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendRecommendRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 14;
	static const uint32_t CMD = 9014;

	std::vector<::Struct::FriendReqInfo> recommends;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendGiftReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 15;
	static const uint32_t CMD = 9015;

	uint32_t playerId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendGiftRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 16;
	static const uint32_t CMD = 9016;

	uint32_t ret;
	::Struct::DropItem items;
	uint32_t playerId;
	uint32_t friendGiftDayCount;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendGetReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 17;
	static const uint32_t CMD = 9017;

	uint32_t playerId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct FriendGetRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 18;
	static const uint32_t CMD = 9018;

	uint32_t ret;
	::Struct::DropItem items;
	uint32_t playerId;
	uint32_t friendGetDayCount;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct IntervalListReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 19;
	static const uint32_t CMD = 9019;

	uint32_t needFriends;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct IntervalListRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 20;
	static const uint32_t CMD = 9020;

	uint32_t needFriends;
	std::vector<::Struct::FriendInfo> friends;
	std::vector<::Struct::FriendReqInfo> strangers;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JJCRankListReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 21;
	static const uint32_t CMD = 9021;

	uint32_t page;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JJCRankListRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 22;
	static const uint32_t CMD = 9022;

	std::vector<::Struct::JJCPlayerInfo> rankList;
	uint32_t page;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JJCDuelListReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 23;
	static const uint32_t CMD = 9023;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JJCDuelListRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 24;
	static const uint32_t CMD = 9024;

	std::vector<::Struct::JJCPlayerInfo> dualList;
	uint32_t ret;
	uint32_t ticket;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JJCDuelReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 25;
	static const uint32_t CMD = 9025;

	uint32_t playerId;
	uint32_t dualType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JJCDuelRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 26;
	static const uint32_t CMD = 9026;

	uint32_t winType;
	::Struct::JJCPlayerFightInfo target;
	uint32_t point;
	uint32_t winComboCount;
	uint32_t changePoint;
	uint32_t JJCClass;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JJCBaseInfoReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 27;
	static const uint32_t CMD = 9027;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JJCBaseInfoRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 28;
	static const uint32_t CMD = 9028;

	uint32_t rank;
	uint32_t point;
	uint32_t jjcCoin;
	uint32_t jjcTicket;
	uint32_t continuity;
	std::vector<::Struct::JJCPlayerInfo> dualList;
	uint32_t canRefDualList;
	uint32_t winCount;
	uint32_t jjcClass;
	uint32_t jjcClassPercent;
	uint32_t updateTicketTime;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JJCRefBuffReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 29;
	static const uint32_t CMD = 9029;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JJCRefBuffRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 30;
	static const uint32_t CMD = 9030;

	std::vector<uint32_t> buffIds;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JJCChangeEquipBeginReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 35;
	static const uint32_t CMD = 9035;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JJCChangeEquipBeginRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 36;
	static const uint32_t CMD = 9036;

	::Struct::PartnerTeamInfo partnerteams;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JJCChangeEquipSaveReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 37;
	static const uint32_t CMD = 9037;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct JJCChangeEquipSaveRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 38;
	static const uint32_t CMD = 9038;

	::Struct::PartnerTeamInfo partnerteams;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetFightRankReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 39;
	static const uint32_t CMD = 9039;

	uint32_t page;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetFightRankRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 40;
	static const uint32_t CMD = 9040;

	std::vector<::Struct::FriendReqInfo> playerInfo;
	uint32_t page;
	uint32_t rank;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetLevelRankReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 41;
	static const uint32_t CMD = 9041;

	uint32_t page;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetLevelRankRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 42;
	static const uint32_t CMD = 9042;

	std::vector<::Struct::FriendReqInfo> playerInfo;
	uint32_t page;
	uint32_t rank;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct IntimacyChangeNotify : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 43;
	static const uint32_t CMD = 9043;

	::Struct::FriendInfo friendInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetIntimacyRewardReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 44;
	static const uint32_t CMD = 9044;

	uint32_t rewardId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetIntimacyRewardRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 45;
	static const uint32_t CMD = 9045;

	uint32_t rewardId;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerDumpInfoReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 46;
	static const uint32_t CMD = 9046;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerDumpInfoRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 47;
	static const uint32_t CMD = 9047;

	uint32_t rewardCount;
	std::vector<uint32_t> dumpPlayerId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerDumpRecommendReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 48;
	static const uint32_t CMD = 9048;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerDumpRecommendRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 49;
	static const uint32_t CMD = 9049;

	std::vector<::Struct::FriendReqInfo> recommends;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerDumpInvitationReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 50;
	static const uint32_t CMD = 9050;

	uint32_t playerId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerDumpInvitationNotify : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 51;
	static const uint32_t CMD = 9051;

	::Struct::PlayerSimpleInfo invitationPlayer;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerDumpApplyReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 52;
	static const uint32_t CMD = 9052;

	uint32_t targetId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerDumpApplyNotify : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 53;
	static const uint32_t CMD = 9053;

	uint64_t dumpUid;
	::Struct::PlayerSimpleInfo targetPlayer;
	uint32_t ret;
	uint32_t isReconnect;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerDumpStartReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 54;
	static const uint32_t CMD = 9054;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerDumpStartRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 55;
	static const uint32_t CMD = 9055;

	uint32_t ret;
	uint32_t targetId;
	uint32_t criCount;
	uint64_t endTime;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerDumpEndReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 56;
	static const uint32_t CMD = 9056;

	uint32_t comob;
	uint32_t badEnd;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerDumpEndRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 57;
	static const uint32_t CMD = 9057;

	uint32_t ret;
	uint32_t rewardCount;
	std::vector<uint32_t> dumpPlayerId;
	std::vector<::Struct::DropItem> dropItem;
	uint32_t comob;
	uint32_t intimacyReward;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerDumpJujueReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 58;
	static const uint32_t CMD = 9058;

	std::vector<uint32_t> playerIds;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PlayerDumpJujueNotify : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 59;
	static const uint32_t CMD = 9059;

	std::string playerName;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct AddFriendNotify : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 60;
	static const uint32_t CMD = 9060;

	::Struct::PlayerSimpleInfo player;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetPartnerRankReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 61;
	static const uint32_t CMD = 9061;

	uint32_t page;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetPartnerRankRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 62;
	static const uint32_t CMD = 9062;

	std::vector<::Struct::PartnerSimpleInfo> playerInfo;
	uint32_t page;
	uint32_t rank;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PVPInvitationReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 63;
	static const uint32_t CMD = 9063;

	uint32_t playerId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PVPInvitationNotify : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 64;
	static const uint32_t CMD = 9064;

	::Struct::PlayerSimpleInfo invitationPlayer;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PVPApplyReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 65;
	static const uint32_t CMD = 9065;

	uint32_t targetId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PVPApplyNotify : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 66;
	static const uint32_t CMD = 9066;

	uint64_t pkUid;
	::Struct::JJCPlayerFightInfo targetPlayer;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PVPEndReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 67;
	static const uint32_t CMD = 9067;

	uint32_t endType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct PVPEndRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 68;
	static const uint32_t CMD = 9068;

	uint32_t endType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetTowerRankReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 69;
	static const uint32_t CMD = 9069;

	uint32_t page;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetTowerRankRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 70;
	static const uint32_t CMD = 9070;

	std::vector<::Struct::TowerSimpleInfo> playerInfo;
	uint32_t page;
	uint32_t rank;
	uint32_t maxLayer;
	uint32_t maxSubId;
	uint32_t time;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct RefusePVPInvitationReq : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 71;
	static const uint32_t CMD = 9071;

	uint32_t playerId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct RefusePVPInvitationRes : public FriendMessageCommand
{
	static const uint32_t MINOR_CMD = 72;
	static const uint32_t CMD = 9072;

	uint32_t playerId;
	uint32_t ret;
	std::string playerName;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CreateGuildReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 1;
	static const uint32_t CMD = 10001;

	std::string guildName;
	uint32_t guildPhotoId;
	std::string guildDeclaration;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CreateGuildRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 2;
	static const uint32_t CMD = 10002;

	::Struct::GuildInfo info;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ApplyGuildReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 3;
	static const uint32_t CMD = 10003;

	uint32_t guildId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ApplyGuildRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 4;
	static const uint32_t CMD = 10004;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetGuildsReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 5;
	static const uint32_t CMD = 10005;

	uint32_t page;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetGuildsRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 6;
	static const uint32_t CMD = 10006;

	std::vector<::Struct::GuildSimpleInfo> guildList;
	uint32_t page;
	uint32_t guildCount;
	std::vector<uint32_t> applys;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ConfirmGuildApplyReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 7;
	static const uint32_t CMD = 10007;

	uint32_t playerId;
	uint32_t oper;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ConfirmGuildApplyRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 8;
	static const uint32_t CMD = 10008;

	uint32_t ret;
	uint32_t oper;
	uint32_t playerId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetGuildApplysReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 9;
	static const uint32_t CMD = 10009;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetGuildApplysRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 10;
	static const uint32_t CMD = 10010;

	std::vector<::Struct::GuildPlayerInfo> players;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GuildInfoReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 11;
	static const uint32_t CMD = 10011;

	uint32_t guildId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GuildInfoRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 12;
	static const uint32_t CMD = 10012;

	::Struct::GuildInfo guildInfo;
	std::vector<::Struct::GuildPlayerInfo> players;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct QuitGuildReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 13;
	static const uint32_t CMD = 10013;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct QuitGuildRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 14;
	static const uint32_t CMD = 10014;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct TickPlayerGuildReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 15;
	static const uint32_t CMD = 10015;

	uint32_t playerId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct TickPlayerGuildRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 16;
	static const uint32_t CMD = 10016;

	uint32_t ret;
	uint32_t playerId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetGuildRankReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 17;
	static const uint32_t CMD = 10017;

	uint32_t page;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetGuildRankRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 18;
	static const uint32_t CMD = 10018;

	std::vector<::Struct::GuildSimpleInfo> guildList;
	uint32_t page;
	uint32_t guildRank;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CreateGuildPVPRoomReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 19;
	static const uint32_t CMD = 10019;

	uint32_t passwd;
	std::string title;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CreateGuildPVPRoomRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 20;
	static const uint32_t CMD = 10020;

	uint32_t ret;
	uint32_t passwd;
	::Struct::GuildRoomSimpleInfo room;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetGuildPVPRoomReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 21;
	static const uint32_t CMD = 10021;

	uint32_t page;
	uint32_t oprType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetGuildPVPRoomRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 22;
	static const uint32_t CMD = 10022;

	std::vector<::Struct::GuildRoomSimpleInfo> rooms;
	uint32_t page;
	uint32_t oprType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SearchGuildPVPRoomReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 23;
	static const uint32_t CMD = 10023;

	uint32_t roomId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SearchGuildPVPRoomRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 24;
	static const uint32_t CMD = 10024;

	::Struct::GuildRoomSimpleInfo room;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EnterGuildPVPRoomReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 25;
	static const uint32_t CMD = 10025;

	uint32_t roomId;
	uint32_t passwd;
	uint32_t isInvitation;
	uint64_t roomUid;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EnterGuildPVPRoomRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 26;
	static const uint32_t CMD = 10026;

	uint32_t roomId;
	uint32_t ret;
	uint64_t roomUid;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GuildPVPRoomPlayerChangeNotify : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 27;
	static const uint32_t CMD = 10027;

	::Struct::GuildRoomInfo roomInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ReadyGuildPVPRoomReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 28;
	static const uint32_t CMD = 10028;

	uint32_t ready;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ReadyGuildPVPRoomRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 29;
	static const uint32_t CMD = 10029;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ReadyGuildPVPRoomNotify : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 30;
	static const uint32_t CMD = 10030;

	std::vector<uint32_t> ready;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct InvitationGuildPVPReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 31;
	static const uint32_t CMD = 10031;

	uint32_t playerId;
	::Struct::GuildRoomSimpleInfo invitation;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct InvitationGuildPVPRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 32;
	static const uint32_t CMD = 10032;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct InvitationGuildPVPNotify : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 33;
	static const uint32_t CMD = 10033;

	::Struct::GuildRoomSimpleInfo invitation;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct QuickEnterGuildPVPRoomReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 34;
	static const uint32_t CMD = 10034;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct QuickEnterGuildPVPRoomRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 35;
	static const uint32_t CMD = 10035;

	uint32_t roomId;
	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct LeaveGuildPVPRoomReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 36;
	static const uint32_t CMD = 10036;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct LeaveGuildPVPRoomRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 37;
	static const uint32_t CMD = 10037;

	uint32_t ret;
	uint32_t leaveType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct TickGuildPVPRoomPlayerReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 38;
	static const uint32_t CMD = 10038;

	uint32_t index;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct TickGuildPVPRoomPlayerRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 39;
	static const uint32_t CMD = 10039;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GuildPVPRoomEnterNotify : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 40;
	static const uint32_t CMD = 10040;

	::Struct::GuildRoomInfo info;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GuildPVPRoomChangePasswdReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 41;
	static const uint32_t CMD = 10041;

	uint32_t passwd;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GuildPVPRoomChangePasswdRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 42;
	static const uint32_t CMD = 10042;

	uint32_t ret;
	uint32_t passwd;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CreateGuildPVPRoomNotify : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 43;
	static const uint32_t CMD = 10043;

	uint32_t playerId;
	uint32_t photoId;
	::Struct::GuildRoomSimpleInfo room;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct StartGuildPVPRoomReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 44;
	static const uint32_t CMD = 10044;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct StartGuildPVPRoomNotify : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 45;
	static const uint32_t CMD = 10045;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct StartGuildPVPRoomRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 46;
	static const uint32_t CMD = 10046;

	uint32_t ret;
	uint32_t roomId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CloseGuildPVPRoomReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 47;
	static const uint32_t CMD = 10047;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct CloseGuildPVPRoomNotify : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 48;
	static const uint32_t CMD = 10048;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct EndGuildPVPRoomNotify : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 49;
	static const uint32_t CMD = 10049;

	uint32_t ret;
	std::vector<::Struct::DropItem> items;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChangeGuildDeclarationReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 50;
	static const uint32_t CMD = 10050;

	std::string declaration;
	uint32_t guildId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChangeGuildDeclarationRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 51;
	static const uint32_t CMD = 10051;

	uint32_t ret;
	std::string declaration;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SreachGuildReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 52;
	static const uint32_t CMD = 10052;

	std::string guildName;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct SreachGuildRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 53;
	static const uint32_t CMD = 10053;

	uint32_t ret;
	::Struct::GuildSimpleInfo info;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct NotifyJoinGuild : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 54;
	static const uint32_t CMD = 10054;

	uint32_t guildClass;
	std::string guildName;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChangeGuildAuthReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 55;
	static const uint32_t CMD = 10055;

	uint32_t playerId;
	uint32_t auth;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChangeGuildAuthRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 56;
	static const uint32_t CMD = 10056;

	uint32_t ret;
	uint32_t playerId;
	uint32_t auth;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChangeGuildLeaderReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 57;
	static const uint32_t CMD = 10057;

	uint32_t playerId;
	uint32_t oper;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ChangeGuildLeaderRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 58;
	static const uint32_t CMD = 10058;

	uint32_t ret;
	uint32_t desPlayerId;
	uint32_t desAuth;
	uint32_t auth;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GuildQiandaoReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 59;
	static const uint32_t CMD = 10059;

	uint32_t qiandaoType;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GuildQiandaoRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 60;
	static const uint32_t CMD = 10060;

	uint32_t ret;
	uint32_t guildMoney;
	uint32_t gongxian;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GuildQiandaoRewardReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 61;
	static const uint32_t CMD = 10061;

	uint32_t index;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GuildQiandaoRewardRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 62;
	static const uint32_t CMD = 10062;

	uint32_t ret;
	uint32_t rewardMask;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GuildSkillUpReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 63;
	static const uint32_t CMD = 10063;

	::Struct::GuildSkill skillInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GuildSkillUpRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 64;
	static const uint32_t CMD = 10064;

	uint32_t ret;
	::Struct::GuildSkill skillInfo;
	uint32_t guildMoney;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GuildPlayerSkillUpReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 65;
	static const uint32_t CMD = 10065;

	::Struct::GuildSkill skillInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GuildPlayerSkillUpRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 66;
	static const uint32_t CMD = 10066;

	uint32_t ret;
	::Struct::GuildSkill skillInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GuildWeekHuoyueRewardReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 67;
	static const uint32_t CMD = 10067;

	uint32_t rewardId;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GuildWeekHuoyueRewardRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 68;
	static const uint32_t CMD = 10068;

	uint32_t ret;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetGuildFirtKillReq : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 69;
	static const uint32_t CMD = 10069;


	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct GetGuildFirtKillRes : public GuildMessageCommand
{
	static const uint32_t MINOR_CMD = 70;
	static const uint32_t CMD = 10070;

	std::vector<::Struct::GuildFirstKillInfo> info;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

struct ClientErrorMsgNotify : public ClientExInfoMessageCommand
{
	static const uint32_t MINOR_CMD = 1;
	static const uint32_t CMD = 99001;

	std::string errorInfo;

	();

	virtual int Serialize(WriteStream *) const;
	virtual int Unserialize(ReadStream *);
};

};

#endif
