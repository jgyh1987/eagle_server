#ifndef _SCRIPTPROXYBASE_H_
#define _SCRIPTPROXYBASE_H_

extern "C"
{
#include "lualib.h"
#include "lua.h"
}

#include "tolua++.h"
#include "LuaState.h"

class ScriptProxyBase
{
protected:
    ScriptProxyBase(LuaState* luaState)
        :pLuaState(luaState), ref(LUA_NOREF)
    {

    }
    virtual ~ScriptProxyBase(){}
public:
    int getRef() const
    {
        return ref;
    }
  
protected:
    LuaState* pLuaState;
    int ref;
};

template<typename ProxyT>
class ScriptProxy : public ScriptProxyBase
{
public:
    ScriptProxy(ProxyT* me, LuaState* luaState)
        :ScriptProxyBase(luaState), m_owner(me)
    {}

protected:
    ProxyT* m_owner;
};

#endif

