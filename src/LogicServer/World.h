#ifndef _WORLD_H_
#define _WORLD_H_

#include "Singleton.h"
#include "PlayerManager.h"
#include "ClientMsg.h"
#include "ImpService.h"
#include "Command.h"
#include "ConstructInPlace.h"
#include "ECS_Entity.h"

//Logic Common data
namespace game
{
    //初始金币
    extern uint32_t g_initDiamond;
    //技能装备数量
    extern uint32_t g_skillEquipNum;

    void InitGameGlobalParameters();
};

class CLogicTask;
class Character;
class LogicRole;

class ECSWorldManager : public CSingleton<ECSWorldManager>
{
public:
    ECSWorldManager()
    {

    }

    bool Init();

    ECS::ECSEntity * CreatePlayerEntity(LogicPlayer *player, LogicRole *role);
	void DestroyPlayerEntrty(ECS::ECSEntity*&);

};


class World : public CSingleton<World>
{
public:
    World();
    ~World();

    bool Init();
    void Clear();
    void Update();
    void UpdateSec();
    void Update5Sec();
    void UpdateMin();
    void UpdateHour();
    void Update24();

    LogicPlayer *CreatePlayer(const PlayerInfoBase &playerInfo);
    void FreePlayer(LogicPlayer*);
    inline LogicPlayer *GetPlayerByID(uint64_t id);
    inline LogicPlayer *GetPlayerByUID(uint64_t uid);
    inline LogicPlayer *GetPlayerByName(std::string &name);
    inline LogicPlayer *GetPlayerByAccount(std::string &account);
    bool AddPlayer(LogicPlayer *player);
    bool RemovePlayer(LogicPlayer *player);
    //玩家离线
    void AddRecoveryPlayer(LogicPlayer *player);
    void DelRecoveryPlayer(LogicPlayer *player);
    void SendClientMsgToAllPlayer(ClientMsg::Message *msg);

    template<class cmd>
    unsigned char* ServerCmdBuffer(cmd* &name);
    template<class cmd>
    unsigned char* ServerItemCmdBuffer(cmd* &name);
    
private:
    std::map<uint64_t, uint32_t> m_recoveryPlayers;

    buffercmdqueue m_sendBuffer;
    buffercmdqueue m_sendItemBuffer;
};

//inline 
inline LogicPlayer *World::GetPlayerByID(uint64_t id)
{
    return PlayerManager::instance()->GetPlayerByID(id);
}

inline LogicPlayer *World::GetPlayerByUID(uint64_t uid)
{
    return PlayerManager::instance()->GetPlayerByTempID(uid);
}

inline LogicPlayer *World::GetPlayerByName(std::string &name)
{
    return PlayerManager::instance()->GetPlayerByName(name);
}

inline LogicPlayer *World::GetPlayerByAccount(std::string &account)
{
    return PlayerManager::instance()->GetPlayerByAccount(account);
}

template<class cmd>
unsigned char* World::ServerCmdBuffer(cmd* &name) {
    m_sendBuffer.ReSet();
    m_sendBuffer.WrReserve(SERVER_COMMAND_MAX_LENGTH);
    name = (cmd *)(m_sendBuffer.WrBuf());
    constructInPlace(name);
    return m_sendBuffer.WrBuf();
}

template<class cmd>
unsigned char* World::ServerItemCmdBuffer(cmd* &name) {
    m_sendItemBuffer.ReSet();
    m_sendItemBuffer.WrReserve(SERVER_COMMAND_MAX_LENGTH);
    name = (cmd *)(m_sendItemBuffer.WrBuf());
    constructInPlace(name);
    return m_sendItemBuffer.WrBuf();
}

#endif


