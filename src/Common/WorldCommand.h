#ifndef _WORLDCOMMAND_H_
#define _WORLDCOMMAND_H_

#include "ServerCommand.h"
#include "PlayerInfo.h"


namespace Cmd 
{
    /////////////////////////////////////////////////////////////
    //跨服消息 START CMD_WORLD_MESSAGE
    //////////////////////////////////////////////////////////////

    struct t_WorldNullCmd : public t_NullCmd
    {
        t_WorldNullCmd(const uint32_t para = PARA_NULL)
            :t_NullCmd(CMD_WORLD_MESSAGE, para)
        {
        }
    };

    const uint32_t PARA_WORLD_CMD_TEST_REQ = WORLDCOMMAND + 1;

	struct t_Scene_ChangeOrBroatcast : t_NullCmd {
		uint32_t change = 0;    //1 change 0 broatcast

		t_Scene_ChangeOrBroatcast(uint32_t para) : t_NullCmd(CMD_WORLD_MESSAGE, para)
		{
		}
	};

	const uint32_t PARA_SERVER_SEND_SCENE_BROADCAST_MOVE_TOCLIENT = WORLDCOMMAND + 1;

	struct t_Server_Send_Scene_Broadcast_Move_ToClient : t_NullCmd {
		SceneCharactorPos pos;

		t_Server_Send_Scene_Broadcast_Move_ToClient() : t_NullCmd(CMD_WORLD_MESSAGE, PARA_SERVER_SEND_SCENE_BROADCAST_MOVE_TOCLIENT)
		{

		}
	};

	const uint32_t PARA_SERVER_SEND_SCENE_BROADCAST_TOCLIENT = WORLDCOMMAND + 2;

	struct t_Server_Send_Scene_Broadcast_ToClient : t_NullCmd {
		uint64_t sceneId = 0;
		uint64_t x = 0;
		uint64_t y = 0;
		uint64_t z = 0;
		uint32_t dataLen = 0;
		uint8_t data[1];

		t_Server_Send_Scene_Broadcast_ToClient() : t_NullCmd(CMD_WORLD_MESSAGE, PARA_SERVER_SEND_SCENE_BROADCAST_TOCLIENT)
		{
		}

		uint32_t Size()
		{
			return sizeof(t_Server_Send_Scene_Broadcast_ToClient) + dataLen;
		}
	};

	const uint32_t PARA_SCENE_AGENT_LOCK = WORLDCOMMAND + 3;

	struct t_Scene_Agent_Lock_Req : t_NullCmd {
		uint64_t playerUid = 0;
		uint32_t lock = 0;
		uint32_t serverId = 0;

		t_Scene_Agent_Lock_Req() : t_NullCmd(CMD_WORLD_MESSAGE, PARA_SCENE_AGENT_LOCK)
		{
		}
	};

	const uint32_t PARA_SCENE_AGENT_LOCK_RES = WORLDCOMMAND + 4;

	struct t_Scene_Agent_Lock_Res : t_NullCmd {
		uint64_t playerUid = 0;
		uint32_t ret = 0;
		uint32_t serverId = 0;
		uint32_t lock = 0;

		t_Scene_Agent_Lock_Res() : t_NullCmd(CMD_WORLD_MESSAGE, PARA_SCENE_AGENT_LOCK_RES)
		{
		}
	};

	const uint32_t PARA_REQ_SCENESERVER = WORLDCOMMAND + 5;

	enum Req_SceneServer_FunType
	{
		Req_SceneServer_FunType_None = 0,
		Req_SceneServer_FunType_EnterLandmass = 1,
	};

	struct t_Req_SceneServer : t_NullCmd {
		uint32_t funType = Req_SceneServer_FunType_None;	//
		uint64_t mapId = 0;
		CmdPos pos;
		uint32_t serverType = 0;
		uint32_t serverId = 0;
		uint64_t playerUid = 0;

		t_Req_SceneServer() : t_NullCmd(CMD_WORLD_MESSAGE, PARA_REQ_SCENESERVER)
		{
		}
	};

	const uint32_t PARA_RES_SCENESERVER = WORLDCOMMAND + 6;

	struct t_Res_SceneServer : t_NullCmd {
		uint32_t funType = Req_SceneServer_FunType_None;	//
		uint32_t serverId = 0;
		uint64_t playerUid = 0;

		t_Res_SceneServer() : t_NullCmd(CMD_WORLD_MESSAGE, PARA_RES_SCENESERVER)
		{
		}
	};

	//业务逻辑
	const uint32_t PARA_ENTER_WORD_REQ = WORLDCOMMAND + 10;

	struct t_Enter_World_Req : t_NullCmd {

		PlayerInfoBase playerinfo;
		RoleInfoBase roleInfo;
		uint32_t enterType = 0;	//1 login 
		uint32_t itemsLen = 0;
		uint32_t itemsCount = 0;
		uint32_t playerDataLen = 0;
		uint32_t allBinarrayLength = 0;
		uint8_t data[1];

		t_Enter_World_Req() : t_NullCmd(CMD_WORLD_MESSAGE, PARA_ENTER_WORD_REQ)
		{
		}

		uint32_t Size()
		{
			return sizeof(t_Enter_World_Req) + allBinarrayLength + itemsLen;
		}
	};

	const uint32_t PARA_SCENE_MOVE = WORLDCOMMAND + 11;

	struct t_Scene_Move : t_Scene_ChangeOrBroatcast {
		SceneCharactorPos pos;

		t_Scene_Move() : t_Scene_ChangeOrBroatcast(PARA_SCENE_MOVE)
		{

		}


	};

	const uint32_t PARA_SCENE_CHARACTOR_DOACTION = WORLDCOMMAND + 12;

	struct t_Scene_Charactor_DoAction : t_Scene_ChangeOrBroatcast {


		t_Scene_Charactor_DoAction() : t_Scene_ChangeOrBroatcast(PARA_SCENE_CHARACTOR_DOACTION)
		{

		}


	};

	const uint32_t PARA_SCENE_CAST_SKILL = WORLDCOMMAND + 13;

	struct t_Scene_Cast_Skill : t_Scene_ChangeOrBroatcast {
		SceneCharactorPos src;
		TargetPos target;
		uint64_t skillId = 0;
		uint32_t actionId = 0;

		t_Scene_Cast_Skill() : t_Scene_ChangeOrBroatcast(PARA_SCENE_CAST_SKILL)
		{
		}


	};

	const uint32_t PARA_SCENE_FIGHT_PEACE = WORLDCOMMAND + 14;

	struct t_Scene_Fight_Peace : t_Scene_ChangeOrBroatcast {
		uint64_t fighterUid = 0;
		uint32_t peace = 0;

		t_Scene_Fight_Peace() : t_Scene_ChangeOrBroatcast(PARA_SCENE_FIGHT_PEACE)
		{
		}


	};

	const uint32_t PARA_SCENE_ATTR_SYNC = WORLDCOMMAND + 15;

	struct t_Scene_Attr_Sync : t_Scene_ChangeOrBroatcast {
		SceneCharactorPos fighter;
		CharacterFightInfo fighterInfo;

		t_Scene_Attr_Sync() : t_Scene_ChangeOrBroatcast(PARA_SCENE_ATTR_SYNC)
		{
		}


	};

	//skill buff effect
	const uint32_t PARA_SCENE_HURT_EFFECT = WORLDCOMMAND + 30;

	//t_Scene_Change_HP
	struct t_Scene_HurtEffect : t_Scene_ChangeOrBroatcast {
		uint64_t src = 0;
		uint64_t target = 0;
		int64_t hurt = 0;
		uint32_t actionId = 0;
		uint64_t skillId = 0;

		t_Scene_HurtEffect() : t_Scene_ChangeOrBroatcast(PARA_SCENE_HURT_EFFECT)
		{
		}


	};

	const uint32_t PARA_SCENE_ADDSTATUS_EFFECT = WORLDCOMMAND + 31;

	//
	struct t_Scene_AddStatus_Effect : t_Scene_ChangeOrBroatcast {
		uint64_t src = 0;
		uint64_t target = 0;
		uint32_t triggerEffectId = 0;
		uint32_t type = 0;
		int64_t param1 = 0;
		int64_t param2 = 0;
		int64_t param3 = 0;
		int64_t param4 = 0;

		t_Scene_AddStatus_Effect() : t_Scene_ChangeOrBroatcast(PARA_SCENE_ADDSTATUS_EFFECT)
		{
		}
	};

	const uint32_t PARA_SCENE_ADDBUFF_EFFECT = WORLDCOMMAND + 32;
	//
	struct t_Scene_AddBuff_Effect : t_Scene_ChangeOrBroatcast {
		uint64_t src = 0;
		uint64_t target = 0;
		uint64_t buffId = 0;
		uint64_t time = 0;
		uint32_t triggerEffectId = 0;
		int64_t param1 = 0;
		int64_t param2 = 0;
		int64_t param3 = 0;
		int64_t param4 = 0;

		t_Scene_AddBuff_Effect() : t_Scene_ChangeOrBroatcast(PARA_SCENE_ADDBUFF_EFFECT)
		{
		}
	};

    const uint32_t PARA_WORLD_MATCH_REQ = WORLDCOMMAND + 103;

    struct t_World_Match_Req : t_WorldNullCmd
    {
        uint32_t matchType = 0;
        uint64_t dungeonId = 0;
        uint32_t count = 0;
        uint32_t len = 0;
        uint8_t data[1];
        //WorldPlayerInfo info;

        t_World_Match_Req() : t_WorldNullCmd(PARA_WORLD_MATCH_REQ)
        {
        }

        uint32_t Size()
        {
            return sizeof(t_World_Match_Req) + len;
        }
    };

    const uint32_t PARA_WORLD_MATCH_RES = WORLDCOMMAND + 104;

    struct t_World_Match_Res : t_WorldNullCmd
    {
        uint32_t ret = 0;
        WorldPlayerBaseInfo playerInfo;
        WDungeonBaseInfo wdungeonInfo;

        t_World_Match_Res() : t_WorldNullCmd(PARA_WORLD_MATCH_RES)
        {
        }
    };

    const uint32_t PARA_WORLD_CREATE_FIGHT_REQ = WORLDCOMMAND + 105;

    struct t_World_Create_Fight_Req : t_WorldNullCmd
    {
        MatchBaseInfo matchInfo;
        uint64_t dungeonId = 0;
        uint32_t playerCount = 0;
        uint32_t len = 0;
        uint8_t data[1];

        t_World_Create_Fight_Req() : t_WorldNullCmd(PARA_WORLD_CREATE_FIGHT_REQ)
        {
        }

        uint32_t Size()
        {
            return len + sizeof(t_World_Create_Fight_Req);
        }
    };

    const uint32_t PARA_WORLD_CREATE_FIGHT_RES = WORLDCOMMAND + 106;

    struct t_World_Create_Fight_Res : t_WorldNullCmd
    {
        MatchBaseInfo matchInfo;
        WDungeonBaseInfo wdungeonInfo;
        uint32_t ret = 0;

        t_World_Create_Fight_Res() : t_WorldNullCmd(PARA_WORLD_CREATE_FIGHT_RES)
        {
        }
    };

    /////////////////////////////////////////////////////////////
    //跨服消息 END CMD_WORLD_MESSAGE
    //////////////////////////////////////////////////////////////

};

#endif

