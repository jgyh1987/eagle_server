#include "Defs.h"
#include "TimeTick.h"
#include "LogicDataManager.h"
#include "LogicPlayer.h"
#include "LogicTask.h"
#include "ServerCommand.h"
#include "parameters.h"
#include "LuaScriptManager.h"
#include "LogicService.h"
#include "AIBehaviac.h"
#include "ECS_AIBehaviac.h"
#include "GameServerManager.h"

#ifdef WIN32

bool is_str_utf8(const char* str)
{
    unsigned int nBytes = 0;//UFT8可用1-6个字节编码,ASCII用一个字节
    unsigned char chr = *str;
    bool bAllAscii = true;
    for (unsigned int i = 0; str[i] != '\0'; ++i) {
        chr = *(str + i);
        //判断是否ASCII编码,如果不是,说明有可能是UTF8,ASCII用7位编码,最高位标记为0,0xxxxxxx
        if (nBytes == 0 && (chr & 0x80) != 0) {
            bAllAscii = false;
        }
        if (nBytes == 0) {
            //如果不是ASCII码,应该是多字节符,计算字节数
            if (chr >= 0x80) {
                if (chr >= 0xFC && chr <= 0xFD) {
                    nBytes = 6;
                }
                else if (chr >= 0xF8) {
                    nBytes = 5;
                }
                else if (chr >= 0xF0) {
                    nBytes = 4;
                }
                else if (chr >= 0xE0) {
                    nBytes = 3;
                }
                else if (chr >= 0xC0) {
                    nBytes = 2;
                }
                else {
                    return false;
                }
                nBytes--;
            }
        }
        else {
            //多字节符的非首字节,应为 10xxxxxx
            if ((chr & 0xC0) != 0x80) {
                return false;
            }
            //减到为零为止
            nBytes--;
        }
    }
    //违返UTF8编码规则
    if (nBytes != 0) {
        return false;
    }
    if (bAllAscii) { //如果全部都是ASCII, 也是UTF8
        return true;
    }
    return true;
}


bool is_str_gbk(const char* str)
{
    unsigned int nBytes = 0;//GBK可用1-2个字节编码,中文两个 ,英文一个
    unsigned char chr = *str;
    bool bAllAscii = true; //如果全部都是ASCII,
    for (unsigned int i = 0; str[i] != '\0'; ++i) {
        chr = *(str + i);
        if ((chr & 0x80) != 0 && nBytes == 0) {// 判断是否ASCII编码,如果不是,说明有可能是GBK
            bAllAscii = false;
        }
        if (nBytes == 0) {
            if (chr >= 0x80) {
                if (chr >= 0x81 && chr <= 0xFE) {
                    nBytes = +2;
                }
                else {
                    return false;
                }
                nBytes--;
            }
        }
        else {
            if (chr < 0x40 || chr>0xFE) {
                return false;
            }
            nBytes--;
        }//else end
    }
    if (nBytes != 0) {   //违返规则
        return false;
    }
    if (bAllAscii) { //如果全部都是ASCII, 也是GBK
        return true;
    }
    return true;
}

std::string GBKToUTF8(const std::string& strGBK)
{
    std::string strOutUTF8 = "";
    WCHAR * str1;
    int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
    str1 = new WCHAR[n + 1];
    MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
    n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
    char * str2 = new char[n + 1];
    n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
    strOutUTF8 = str2;
    delete[]str1;
    str1 = NULL;
    delete[]str2;
    str2 = NULL;
    return strOutUTF8;
}

std::string UTF8ToGBK(const std::string& strUTF8)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
    unsigned short * wszGBK = new unsigned short[len + 1];
    memset(wszGBK, 0, len * 2 + 2);
    MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUTF8.c_str(), -1, (LPWSTR)wszGBK, len);

    len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
    char *szGBK = new char[len + 1];
    memset(szGBK, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, szGBK, len, NULL, NULL);
    //strUTF8 = szGBK;
    std::string strTemp(szGBK);
    delete[]szGBK;
    delete[]wszGBK;
    return strTemp;
}

#endif

//Logic Common data
namespace game
{
    uint32_t g_initDiamond;
    uint32_t g_skillEquipNum;

    void InitGameGlobalParameters()
    {
        g_initDiamond = (uint32_t)paramNumbers["InitDiamond"];
        g_skillEquipNum = (uint32_t)paramNumbers["SkillEquipNum"];

#ifdef WIN32
        auto tempStr = paramStrs["TestUTF8"];

        auto tempStr1 = UTF8ToGBK(tempStr);

        auto tempStr2 = GBKToUTF8(tempStr1);

        if (tempStr1 == tempStr2) 
        {
            int a = 1;
        }
#endif

        return;
    }
};

//ECSWorldManager
bool ECSWorldManager::Init()
{
	return ECS::ECSManager::instance()->Init(ECS_ENTITY_TYPE_MAX);
}

ECS::ECSEntity* ECSWorldManager::CreatePlayerEntity(LogicPlayer* player, LogicRole* role)
{
	auto entity = ECS::ECSManager::instance()->CreateEntity(ECS_ENTITY_TYPE_PLAYER, ECS_PLAYER_COMPONENT_TYPE_MAX);
	if (entity)
	{
		auto playerCmp = ECS::ECSManager::instance()->CreateComponent<LogicPlayerComponent>(entity);
		playerCmp->m_player = player;
		playerCmp->m_role = role;
		ECS::ECSManager::instance()->CreateComponent<CounterComponent>(entity);
		ECS::ECSManager::instance()->CreateComponent<BagComponent>(entity);
		ECS::ECSManager::instance()->CreateComponent<MailComponent>(entity);
	}

	return entity;
}

void ECSWorldManager::DestroyPlayerEntrty(ECS::ECSEntity*& entity)
{
	if (entity)
	{
		ECS::ECSManager::instance()->DestroyEntrty(entity);
		entity = NULL;
	}

	return;
}

//world

class CallbackGetPlayerUpdate : public CEntryCallback<LogicPlayer>
{
public:
     bool exec(LogicPlayer* player)
     {
         player->Update();
         return true;
     }
};

class CallbackGetPlayerUpdateSec : public CEntryCallback<LogicPlayer>
{
public:
     bool exec(LogicPlayer* player)
     {
         player->UpdateSec();
         return true;
     }
};

class CallbackGetPlayerUpdate5Sec : public CEntryCallback<LogicPlayer>
{
public:
     bool exec(LogicPlayer* player)
     {
         player->Update5Sec();
         return true;
     }
};

class CallbackGetPlayerUpdateMin : public CEntryCallback<LogicPlayer>
{
public:
     bool exec(LogicPlayer* player)
     {
         player->UpdateMin();
         return true;
     }
};

class CallbackGetPlayerUpdateHour : public CEntryCallback<LogicPlayer>
{
public:
     bool exec(LogicPlayer* player)
     {
         player->UpdateHour();
         return true;
     }
};

class CallbackGetPlayerUpdate24 : public CEntryCallback<LogicPlayer>
{
public:
     bool exec(LogicPlayer* player)
     {
         player->Update24();
         return true;
     }
};

//world
World::World()
{
}

World::~World()
{
}

//BehaviacComponent* g_aicmp = NULL;

bool World::Init()
{
    ECSWorldManager::instance()->Init();

    CRandom::Init();
    //
    PlayerManager::instance();
    LuaScriptManager::instance()->Init();

    InitConditionToEventArray();
    InitEffectFuncs();
    InitBuffTiggerToEventArray();

	BehaviacConfigManager::instance()->LoadConfig(eagle::global["ConfigPath"], "BehaviorList.xml");
	//g_aicmp = new BehaviacComponent(NULL);
	//BehaviacSystem::instance()->SetTree(g_aicmp, "behavior_test_1");
    

    if (!LogicDataManager::instance()->Init(eagle::global["ConfigPath"]))
        return false;

    //
	GameServerManager::instance()->Init();
    InitParasePlayerInfoMsgFun();

    return true;
}

//
void World::Clear()
{

    return;
}

void World::Update()
{
    CallbackGetPlayerUpdate playerupdate;
    PlayerManager::instance()->ExecEveryPlayer(playerupdate);

    return;
}

void World::UpdateSec()
{
    CallbackGetPlayerUpdateSec playerupdate;
    PlayerManager::instance()->ExecEveryPlayer(playerupdate);

	//BehaviacSystem::instance()->RunBehaviac(g_aicmp);

    return;
}

void World::Update5Sec()
{
    CallbackGetPlayerUpdate5Sec playerupdate;
    PlayerManager::instance()->ExecEveryPlayer(playerupdate);

    uint32_t curTime = (uint32_t)CImpServerTimeTick::currentTime.sec();
    for (std::map<uint64_t, uint32_t>::iterator itr = m_recoveryPlayers.begin(); itr != m_recoveryPlayers.end();)
    {
        if (curTime - itr->second > UNLOGIN_DEL_PLAYER_TIME)
        {
            LogicPlayer *player = GetPlayerByID(itr->first);
            if (player)
            {
                if (player->CanFree())
                {
                    RemovePlayer(player);
                    m_recoveryPlayers.erase(itr++);
                }
                else
                    ++itr;
            }
            else
                m_recoveryPlayers.erase(itr++);
        }
        else
            ++itr;
    }

    return;
}

void World::UpdateMin()
{

    CallbackGetPlayerUpdateMin playerupdate;
    PlayerManager::instance()->ExecEveryPlayer(playerupdate);


    return;
}

void World::UpdateHour()
{
    CallbackGetPlayerUpdateHour playerupdate;
    PlayerManager::instance()->ExecEveryPlayer(playerupdate);

    return;
}

void World::Update24()
{
	CallbackGetPlayerUpdate24 playerupdate;
	PlayerManager::instance()->ExecEveryPlayer(playerupdate);

	return;
}


//// world player
LogicPlayer* World::CreatePlayer(const PlayerInfoBase &playerInfo)
{
    return new LogicPlayer(playerInfo);
}

void World::FreePlayer(LogicPlayer *player)
{
    delete player;

    return ;
}

bool World::AddPlayer(LogicPlayer *player)
{
    if (PlayerManager::instance()->AddPlayer(player) && player->OnLogin())
    {
        return true;
    }

    return false;
}

bool World::RemovePlayer(LogicPlayer *player)
{
    player->OnUnLogin();
    PlayerManager::instance()->RemovePlayer(player);
    FreePlayer(player);

    return true;
}

//
void World::AddRecoveryPlayer(LogicPlayer *player)
{
    m_recoveryPlayers[player->Id()] = (uint32_t)CImpServerTimeTick::currentTime.sec();

    return;
}

void World::DelRecoveryPlayer(LogicPlayer *player)
{
    std::map<uint64_t, uint32_t>::iterator itr = m_recoveryPlayers.find(player->Id());
    if (itr != m_recoveryPlayers.end())
    {
        m_recoveryPlayers.erase(itr);
    }
    
    return;
}

void World::SendClientMsgToAllPlayer(ClientMsg::Message *msg)
{
	ServerImp()->SendClientMsg(msg, 0, 0);

    return;
}

