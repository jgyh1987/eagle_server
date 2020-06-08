function LuaTestActivity(e)
    etemp = GetScriptPollActivity(e);
    etemp:TestFun1(3);

    return 1;
end

function TextActivityUpdate()
    temp = GetNewPollActivity();

    temp:TestFun1(1);

end


local g_playerMap = {};

function TextActivityInit()

    for i = 0, 1000 do
        g_playerMap[i] = i * 4;
    end
end

function GetPlayerMapValueById(id)

    for i = 0, 1000 do
        if id == i then
            return g_playerMap[i];
        end
    end

    return 0;
end

