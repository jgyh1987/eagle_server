ROOT_DIR = c_getRootDir()

function GetScriptPollActivity(e)
    return tolua.cast(e, "ScriptPollActivity");
end

function GetScriptLogicPlayer(e)
    return tolua.cast(e, "ScriptLogicPlayer");
end

c_doFile(ROOT_DIR.."ActivityInit.lua");
c_doFile(ROOT_DIR.."PlayerInit.lua");

