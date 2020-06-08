#ifndef _GM_H_
#define _GM_H_

#include "Sys.h"
#include "Singleton.h"
#include "jsoncpp/include/json.h"

enum GMCOMMEND_RET_ENUM
{

    GMCOMMEND_RET_ENUM_PARSE_ERROR = 0,
    GMCOMMEND_RET_ENUM_SUCCESS = 1,
    GMCOMMEND_RET_ENUM_NO_COMMEND = 2,
    GMCOMMEND_RET_ENUM_NO_PLAYER = 3,


};

class GMCommandBase 
{
public:
    virtual ~GMCommandBase()
    {
    }

    virtual bool execute(Json::Value &value, std::string &out) = 0;
};

class SendServerNotify : public GMCommandBase
{
public:

    bool execute(Json::Value &value, std::string &out);
};

class SendSystemMail : public GMCommandBase
{
public:

    bool execute(Json::Value &value, std::string &out);
};

class UpdatePlayerLevel : public GMCommandBase
{
public:

    bool execute(Json::Value &value, std::string &out);
};

class OpenGate : public GMCommandBase
{
public:

    bool execute(Json::Value &value, std::string &out);
};

class AddItem : public GMCommandBase
{
public:

    bool execute(Json::Value &value, std::string &out);
};

class WhosYourDaddy : public GMCommandBase
{
public:

    bool execute(Json::Value &value, std::string &out);
};

class GetAllItems : public GMCommandBase
{
public:

    bool execute(Json::Value &value, std::string &out);
};

class UpdateVipLevel : public GMCommandBase
{
public:

    bool execute(Json::Value &value, std::string &out);
};

//////////GMCommandManager

class GMCommandManager : public CSingleton<GMCommandManager> 
{
private:

    Json::Reader m_reader;

    std::map<std::string, GMCommandBase*> m_commands;

    typedef std::map<std::string, GMCommandBase*>::iterator CommandIter;

public:

    GMCommandManager();

    ~GMCommandManager();

    bool parse(std::string jsonstring, std::string &out);

    void SendAllMailRecv(int ret);
};

#endif

