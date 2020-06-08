/*
** Lua binding: LuaInit
** Generated automatically by tolua++-1.0.92 on 09/19/18 14:23:39.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_LuaInit_open (lua_State* tolua_S);

#include "ScriptFunc.h"
#include "LuaInit.h"
#include "ActivityLuaInit.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_ScriptPollActivity (lua_State* tolua_S)
{
 ScriptPollActivity* self = (ScriptPollActivity*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_ScriptLogicPlayer (lua_State* tolua_S)
{
 ScriptLogicPlayer* self = (ScriptLogicPlayer*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"ScriptProxy");
 tolua_usertype(tolua_S,"ScriptPollActivity");
 tolua_usertype(tolua_S,"ScriptLogicPlayer");
}

/* function: c_getRootDir */
#ifndef TOLUA_DISABLE_tolua_LuaInit_c_getRootDir00
static int tolua_LuaInit_c_getRootDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   const char* tolua_ret = (const char*)  c_getRootDir();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'c_getRootDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: c_doFile */
#ifndef TOLUA_DISABLE_tolua_LuaInit_c_doFile00
static int tolua_LuaInit_c_doFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  c_doFile(filename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'c_doFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ScriptPollActivity */
#ifndef TOLUA_DISABLE_tolua_LuaInit_ScriptPollActivity_delete00
static int tolua_LuaInit_ScriptPollActivity_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScriptPollActivity",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScriptPollActivity* self = (ScriptPollActivity*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TestFun1 of class  ScriptPollActivity */
#ifndef TOLUA_DISABLE_tolua_LuaInit_ScriptPollActivity_TestFun100
static int tolua_LuaInit_ScriptPollActivity_TestFun100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScriptPollActivity",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScriptPollActivity* self = (ScriptPollActivity*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TestFun1'",NULL);
#endif
  {
   self->TestFun1(num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TestFun1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetNewPollActivity */
#ifndef TOLUA_DISABLE_tolua_LuaInit_GetNewPollActivity00
static int tolua_LuaInit_GetNewPollActivity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ScriptPollActivity tolua_ret = (ScriptPollActivity)  GetNewPollActivity();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((ScriptPollActivity)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"ScriptPollActivity");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(ScriptPollActivity));
     tolua_pushusertype(tolua_S,tolua_obj,"ScriptPollActivity");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNewPollActivity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ScriptLogicPlayer */
#ifndef TOLUA_DISABLE_tolua_LuaInit_ScriptLogicPlayer_delete00
static int tolua_LuaInit_ScriptLogicPlayer_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScriptLogicPlayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScriptLogicPlayer* self = (ScriptLogicPlayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetID of class  ScriptLogicPlayer */
#ifndef TOLUA_DISABLE_tolua_LuaInit_ScriptLogicPlayer_GetID00
static int tolua_LuaInit_ScriptLogicPlayer_GetID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScriptLogicPlayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScriptLogicPlayer* self = (ScriptLogicPlayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetID'",NULL);
#endif
  {
   unsigned long long tolua_ret = (unsigned long long)  self->GetID();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendMail of class  ScriptLogicPlayer */
#ifndef TOLUA_DISABLE_tolua_LuaInit_ScriptLogicPlayer_SendMail00
static int tolua_LuaInit_ScriptLogicPlayer_SendMail00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScriptLogicPlayer",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScriptLogicPlayer* self = (ScriptLogicPlayer*)  tolua_tousertype(tolua_S,1,0);
  char* title = ((char*)  tolua_tostring(tolua_S,2,0));
  char* content = ((char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendMail'",NULL);
#endif
  {
   self->SendMail(title,content);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendMail'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_LuaInit_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_function(tolua_S,"c_getRootDir",tolua_LuaInit_c_getRootDir00);
  tolua_function(tolua_S,"c_doFile",tolua_LuaInit_c_doFile00);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ScriptPollActivity","ScriptPollActivity","ScriptProxy",tolua_collect_ScriptPollActivity);
  #else
  tolua_cclass(tolua_S,"ScriptPollActivity","ScriptPollActivity","ScriptProxy",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ScriptPollActivity");
   tolua_function(tolua_S,"delete",tolua_LuaInit_ScriptPollActivity_delete00);
   tolua_function(tolua_S,"TestFun1",tolua_LuaInit_ScriptPollActivity_TestFun100);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"GetNewPollActivity",tolua_LuaInit_GetNewPollActivity00);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ScriptLogicPlayer","ScriptLogicPlayer","ScriptProxy",tolua_collect_ScriptLogicPlayer);
  #else
  tolua_cclass(tolua_S,"ScriptLogicPlayer","ScriptLogicPlayer","ScriptProxy",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ScriptLogicPlayer");
   tolua_function(tolua_S,"delete",tolua_LuaInit_ScriptLogicPlayer_delete00);
   tolua_function(tolua_S,"GetID",tolua_LuaInit_ScriptLogicPlayer_GetID00);
   tolua_function(tolua_S,"SendMail",tolua_LuaInit_ScriptLogicPlayer_SendMail00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_LuaInit (lua_State* tolua_S) {
 return tolua_LuaInit_open(tolua_S);
};
#endif

