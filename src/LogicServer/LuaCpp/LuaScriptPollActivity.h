#ifndef _LUASCRIPTPOLLACTIVITY_H_
#define _LUASCRIPTPOLLACTIVITY_H_

#include "../PollActivityManager.h"
#include "ScriptProxyBase.h"
#include "../LuaScriptManager.h"

class ScriptPollActivity : public ScriptProxy< PollActivity >
{ 
public:
    ScriptPollActivity( PollActivity* pollActivity )
        :ScriptProxy< PollActivity >(pollActivity, LuaScriptManager::instance())
    {
        
    }
   
    ~ScriptPollActivity();
    void TestFun1(int num);

private:
};


#endif
