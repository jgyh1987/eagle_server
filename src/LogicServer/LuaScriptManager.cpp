#include "LuaScriptManager.h"

extern int tolua_LuaInit_open (lua_State* tolua_S);

bool LuaScriptManager::Init()
{
    tolua_LuaInit_open( Handle() );
    std::string str = eagle::global["LuaInit"].c_str();
    str += "Init.lua";
    if (!DoFile(str.c_str()))
    {
        return false;
    }

    return true;
}

bool LuaScriptManager::Reset()
{
    if (LuaState::Reset())
    {
        return Init();
    }

    Final();

    return false;
}

