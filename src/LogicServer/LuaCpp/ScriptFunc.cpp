#include "../LuaScriptManager.h"
#include "LuaScriptPollActivity.h"

/// @brief ��ȡ�ű���·��
const char* c_getRootDir()
{
    return eagle::global["LuaInit"].c_str();
}

/// @brief �����ļ
bool c_doFile( const char* filename )
{
    LuaScriptManager::instance()->DoFile( filename );

    return true;
}

/// test code begin
ScriptPollActivity GetNewPollActivity()
{
    return ScriptPollActivity(NULL);
}
/// test code end

