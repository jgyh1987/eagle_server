function LuaSendMail(e)
    etemp = GetScriptLogicPlayer(e);
    etemp:SendMail("luatesttitle1", "luatestcontent1");

    return 1;
end
