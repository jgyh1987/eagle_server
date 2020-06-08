#ifndef _LUASCRIPTLOGICPLAYER_H
#define _LUASCRIPTLOGICPLAYER_H

#include "../LogicPlayer.h"
#include "ScriptProxyBase.h"
#include "../LuaScriptManager.h"

class ScriptLogicPlayer : public ScriptProxy< LogicPlayer >
{ 
public:
    ScriptLogicPlayer( LogicPlayer* player )
        :ScriptProxy< LogicPlayer >(player, LuaScriptManager::instance())
    {
    }
   
    ~ScriptLogicPlayer();

    unsigned long long GetID();
    void SendMail(char *title, char *content);

private:

};

#endif
