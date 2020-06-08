#ifndef _PLAYER_MANAGER_H_
#define _PLAYER_MANAGER_H_

#include "Singleton.h"
#include "LogicPlayer.h"

//CObjectSession 
class PlayerManager : public CObjectManager<LogicPlayer, CObjectTempID, CObjectID, CObjectSession, CObjectName>, public CSingleton<PlayerManager>
{
public:
    LogicPlayer* GetPlayerByID(uint64_t id);
    
    LogicPlayer* GetPlayerByTempID(uint64_t tempid);
    
    LogicPlayer* GetPlayerByName(const std::string& name);

    LogicPlayer* GetPlayerByAccount(const std::string& account);
    
    bool AddPlayer(LogicPlayer* player);
    
    void RemovePlayer(LogicPlayer* player);

    bool ExecEveryPlayer(CEntryCallback<LogicPlayer>& execPlayer);

    int Size()const;

    LogicPlayer* GetFirstPlayer() const;

};

#endif

