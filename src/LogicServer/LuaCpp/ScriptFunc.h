#ifndef _SCRIPTFUNC_H_
#define _SCRIPTFUNC_H_
//tolua_begin

/// @brief ��ȡ�ű���·��
const char* c_getRootDir();

/// @brief �����ļ�
bool c_doFile( const char* filename );

/// test code begin
class ScriptPollActivity;
ScriptPollActivity GetNewPollActivity();
/// test code end

//tolua_end
#endif
