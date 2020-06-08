#ifndef _WORLD_H_
#define _WORLD_H_

#include "Sys.h"
#include "Singleton.h"
#include "parameters.h"
#include "ImpService.h"
#include "Command.h"
#include "ConstructInPlace.h"
#include "ECS_Entity.h"
#include "PlayerInfo.h"

class WGamePlayer;
class EagleWorld;

// Common data
namespace game
{

    void InitGameGlobalParameters();
};

class ECSWorldManager : public CSingleton<ECSWorldManager>
{
public:
	ECSWorldManager()
	{

	}

	bool Init();

	void DestroyEntity(ECS::ECSEntity *&);
	ECS::ECSEntity* CreatePlayerEntity(WGamePlayer* player);
	ECS::ECSEntity* CreateFighterEntity(WGamePlayer* player);
	ECS::ECSEntity* CreateNpcEntity(EagleWorld *);

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

	WGamePlayer *CreatePlayer(const PlayerInfoBase &playerInfo, uint32_t gateServerType);
	void AddPlayer(WGamePlayer *);
	void RemovePlayer(WGamePlayer*& );
	void RemovePlayer(uint64_t uid);
	WGamePlayer* FindPlayerByUid(uint64_t playerUid);

    template<class cmd>
    unsigned char* ServerCmdBuffer(cmd* &name);
    template<class cmd>
    unsigned char* ServerItemCmdBuffer(cmd* &name);

private:
    buffercmdqueue m_sendBuffer;
    buffercmdqueue m_sendItemBuffer;

	eagle_hash_map<uint64_t, WGamePlayer*> m_players;
};

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


