#include "LuaState.h"
#include "ScriptProxyBase.h"

bool LuaState::Reset()
{
    Final();
    L = lua_open(); 
    luaopen_base(L); 
    lua_checkstack(L,102400);
    
    return true;
}

void LuaState::pushValue(const ScriptProxyBase* scriptProxy)
{
    lua_getref(L, scriptProxy->getRef());
}

