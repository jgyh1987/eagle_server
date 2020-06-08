#ifndef _LUASTATE_H_
#define _LUASTATE_H_

#include "Logger.h"
#include "Global.h"

class ScriptProxyBase;

extern "C"
{
#include "lualib.h"
#include "lua.h"
}
#include "tolua++.h"

#ifdef _DEBUG
#define LUA_DEBUG_STACK_NUM(L) LOGD("LUA STACK COUNT = " << lua_gettop(L))
#else
#define LUA_DEBUG_STACK_NUM(L)
#endif

class LuaState
{
public:
    LuaState()
    {
        L = lua_open(); 
        luaopen_base(L);  
        lua_checkstack(L,102400);
    }

    virtual ~LuaState()
    {
        Final();
    }

public:
    ///���¼��ؽű�
    bool Reset();

    void Final()
    {
        if(L)
            lua_close(L);
        L = NULL;
    }

    inline lua_State* const Handle() const
    {
        return L;
    }

    bool IsExistFunc(const char* func)
    {
        LUA_DEBUG_STACK_NUM(L);
        lua_getglobal(L, func);
        if(lua_type(L, -1) == LUA_TFUNCTION)
        {
            return true;
        }
        lua_pop(L, 1);

        LUA_DEBUG_STACK_NUM(L);
        return false;
    }

    bool DoFile(const char* filename)
    {
        LUA_DEBUG_STACK_NUM(L);
        int status = luaL_dofile(L, filename);
        if (status != 0)
        {
            if (lua_isstring(L,-1))
            {
                const char* err = lua_tostring(L,-1);
                if (err)
                    LOGE("DoFile script: " << err);
            }
            lua_pop(L,1);
            LUA_DEBUG_STACK_NUM(L);
            return false;
        }
        LUA_DEBUG_STACK_NUM(L);
        return true;
    }
    double GetGlobalNumber(const char* name)
    {
        LUA_DEBUG_STACK_NUM(L);
        if(!name) return 0;
        lua_getglobal(L,name);
        double ret = 0;
        if(lua_isnumber(L,-1))
        {
            ret = lua_tonumber(L,-1);
        }
        else
            LOGD("GetGlobalNumber ERROR NAME = " << name);

        lua_pop(L,1);
        LUA_DEBUG_STACK_NUM(L);
        return ret;
    }

    const char* GetGlobalString(const char* name)
    {
        LUA_DEBUG_STACK_NUM(L);
        static const char *defaultStr = "";
        const char *p = defaultStr;
        if(!name)
            return p;
        lua_getglobal(L,name);
        if(lua_isstring(L,-1))
        {
            p = lua_tostring(L,-1);
        }
        else
            LOGD("GetGlobalString ERROR NAME = " << name);

        lua_pop(L,1);
        LUA_DEBUG_STACK_NUM(L);
        return p;
    }

protected:
    lua_State* L;

private:
    /// ��lua��ջѹ��Ԫ��short,char,long,unsigned int/short/char/long,float,double,long double
    void PushValue( short value ){lua_pushnumber(L,(lua_Number)value);}
    void PushValue( unsigned short value ){lua_pushnumber(L,(lua_Number)value);}
    void PushValue( int value ){lua_pushnumber(L,(lua_Number)value);}
    void PushValue( unsigned int value ){lua_pushnumber(L,(lua_Number)value);}
    void PushValue( long value ){lua_pushnumber(L,(lua_Number)value);}
    void PushValue( unsigned long value ){lua_pushnumber(L,(lua_Number)value);}
    void PushValue( double value ){lua_pushnumber(L,(lua_Number)value);}
    void PushValue( float value ){lua_pushnumber(L,(lua_Number)value);}
    void PushValue( bool value ){lua_pushboolean(L, value);}
    void PushValue( const char* value ){ value ? lua_pushstring(L, value):lua_pushnil(L);}
    void PushValue( void* value ){lua_pushlightuserdata(L, value);}
    void pushValue( const ScriptProxyBase* scriptProxy );
    template <typename T>
        void pushValue(T* value)
        {
            pushValue((const ScriptProxyBase*)value);
        }

public:
    bool CallRTBool(const char* func)
    {
        if(IsExistFunc(func))
        {
            if(lua_pcall(L,0,0,0))
            {
                if(lua_isstring(L,-1))
                {
                    const char* err = lua_tostring(L,-1);
                    if( err )
                        LOGD("CallRTBool script: " << err);
                }
                lua_pop(L, 1);
                LUA_DEBUG_STACK_NUM(L);

                return false;
            }
            LUA_DEBUG_STACK_NUM(L);

            return true;
        }

        return false;
    }

    void CallRTVoid(const char* func)
    {
        if (IsExistFunc(func))
        {
            if (lua_pcall(L,0,0,0))
            {
                if (lua_isstring(L,-1))
                {
                    const char* err = lua_tostring(L,-1);
                    if (err)
                        LOGD("CallRTVoid script: " << err);
                }
                lua_pop(L, 1);
                LUA_DEBUG_STACK_NUM(L);

                return ;
            }
            LUA_DEBUG_STACK_NUM(L);

            return ;
        }

        return ;
    }

    template <typename T, typename P1>
    bool CallRT(const char* func, const P1 p1, T& value)
    {
        if (IsExistFunc(func))
        {
            PushValue(p1);
            if (lua_pcall(L,1,1,0))
            {
                if (lua_isstring(L,-1))
                {
                    const char* err = lua_tostring(L,-1);
                    if (err)
                        LOGD("CallRT <typename T, typename P1> script: " << err);
                }
                lua_pop(L,1);
                LUA_DEBUG_STACK_NUM(L);

                return false;
            }

            value = (T)lua_tonumber(L,-1);
            lua_pop(L,1);
            LUA_DEBUG_STACK_NUM(L);

            return true;
        }

        return false;
    }

    template <typename T, typename P1, typename P2>
    bool CallRT(const char* func, const P1 p1, const P2 p2, T& value)
    {
        if(IsExistFunc(func))
        {
            PushValue(p1);
            PushValue(p2);
            if(lua_pcall(L,2,1,0))
            {
                if(lua_isstring(L,-1))
                {
                    const char* err = lua_tostring(L,-1);
                    if( err )
                        LOGD("CallRT <typename T, typename P1, typename P2> script: " << err);
                }
                lua_pop(L,1);
                LUA_DEBUG_STACK_NUM(L);

                return false;
            }

            value = (T)lua_tonumber(L,-1);
            lua_pop(L,1);
            LUA_DEBUG_STACK_NUM(L);

            return true;
        }

        return false;
    }

    template <typename T, typename P1, typename P2, typename P3>
    bool CallRT(const char* func, const P1 p1, const P2 p2, const P3 p3, T& value)
    {
        if (IsExistFunc(func))
        {
            PushValue(p1);
            PushValue(p2);
            PushValue(p3);
            if (lua_pcall(L,3,1,0))
            {
                if (lua_isstring(L,-1))
                {
                    const char* err = lua_tostring(L,-1);
                    if (err)
                        LOGD("CallRT <typename T, typename P1, typename P2, typename P3> script: " << err);
                }
                lua_pop(L,1);
                LUA_DEBUG_STACK_NUM(L);

                return false;
            }

            value = (T)lua_tonumber(L,-1);
            lua_pop(L,1);
            LUA_DEBUG_STACK_NUM(L);

            return true;
        }

        return false;
    }

    template <typename P1>
    bool CallRT(const char* func, const P1 p1, char* value, const uint32_t size)
    {
        if (IsExistFunc(func))
        {
            PushValue(p1);
            if (lua_pcall(L,1,1,0))
            {
                if (lua_isstring(L,-1))
                {
                    const char* err = lua_tostring(L,-1);
                    if (err)
                        LOGD("CallRT <typename P1> script: " << err);
                }
                lua_pop(L,1);
                LUA_DEBUG_STACK_NUM(L);

                return false;
            }
            
            if (lua_isstring(L,-1))
            {
                const char* ret = lua_tostring(L,-1);
                if(ret)
                {
                    strncpy(value, ret, size);
                    lua_pop(L,1);
                    LUA_DEBUG_STACK_NUM(L);

                    return true;
                }
            }

            lua_pop(L,1);
            LUA_DEBUG_STACK_NUM(L);

            return false;
        }

        return false;
    }

    template <typename P1>
    bool CallRT(const char* func, const P1 p1, std::string& value)
    {
        if(IsExistFunc(func))
        {
            PushValue(p1);
            if(lua_pcall(L,1,1,0))
            {
                if(lua_isstring(L,-1))
                {
                    const char* err = lua_tostring(L,-1);
                    if( err )
                        LOGD("CallRT  <typename P1> script: " << err);
                }
                lua_pop(L,1);
                LUA_DEBUG_STACK_NUM(L);

                return false;
            }

            if (lua_isstring(L,-1))
            {
                const char* ret = lua_tostring(L,-1);
                if(ret != NULL)
                {
                    value = ret;
                    lua_pop(L,1);
                    LUA_DEBUG_STACK_NUM(L);

                    return true;
                }
            }

            lua_pop(L,1);
            LUA_DEBUG_STACK_NUM(L);
        }

        return false;
    }
};
#endif
