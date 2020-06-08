#ifndef _LUASCRIPTMANAGER_H_
#define _LUASCRIPTMANAGER_H_

#include "LuaState.h"
#include "Singleton.h"
#include "Noncopyable.h"
 
class LuaScriptManager : public LuaState, public CSingleton< LuaScriptManager >, public CNoncopyable
{
public:
    LuaScriptManager(){}
    ~LuaScriptManager(){}

public:
    bool Init();
    bool Reset();

};
#endif

