#ifndef _PLAYER_MANAGER_H_
#define _PLAYER_MANAGER_H_

#include "CObject.h"
#include "Singleton.h"
#include "GatewayPlayer.h"
#include "ClientMsg.h"

//CObjectSession  
class PlayerManager : public CObjectManager<GatewayPlayer, CObjectTempID, CObjectID>, public CSingleton<PlayerManager>
{
public:
    GatewayPlayer* GetPlayerByID(uint64_t id);
    
    GatewayPlayer* GetPlayerByTempID(uint64_t tempid);
    
    bool AddPlayer(GatewayPlayer* player);
    
    void RemovePlayer(GatewayPlayer* &player, bool notifyLogic = true);

    bool ExecEveryPlayer(CEntryCallback<GatewayPlayer>& execPlayer);

    void SendAllPlayer(void *, uint32_t len);

    int Size()const;

    void AddKcpPlayer(uint32_t, GatewayPlayer *);
    void RemoveKcpPlayer(uint32_t);
    GatewayPlayer *FindKcpPlayer(uint32_t);

private:
    std::map<uint32_t, GatewayPlayer *> m_kcpPlayer;
};

#endif

