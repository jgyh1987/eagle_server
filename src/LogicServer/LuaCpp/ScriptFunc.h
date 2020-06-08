#ifndef _SCRIPTFUNC_H_
#define _SCRIPTFUNC_H_
//tolua_begin

/// @brief 获取脚本跟路径
const char* c_getRootDir();

/// @brief 加载文件
bool c_doFile( const char* filename );

/// test code begin
class ScriptPollActivity;
ScriptPollActivity GetNewPollActivity();
/// test code end

//tolua_end
#endif
