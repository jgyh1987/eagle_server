#include "GM.h"
#include "Defs.h"
#include "ClientMsg.h"
#include "LogicService.h"
#include "ECS_Bag.h"

//GMCommendManager

GMCommandManager::GMCommandManager()
{
    m_commands["SendServerNotify"] = new SendServerNotify;    //{"name":"SendServerNotify"}
    m_commands["SendSystemMail"] = new SendSystemMail;            //{"name":"SendSystemMail", "title":"asdf", "content":"asdfasdfasdf", ""all":1, "type":101, "id":101, "count":1000, "playername":"eagle"}
    m_commands["UpdatePlayerLevel"] = new UpdatePlayerLevel;        //{"name":"UpdatePlayerLevel", "level":10, "playername":"eagle"}
    m_commands["OpenGate"] = new OpenGate;                            //{"name":"OpenGate", "id":101, "star":3, "playername":"eagle"}    0 ����ȫ��
    m_commands["AddItem"] = new AddItem;                            //{"name":"AddItem", "type":101, "id":101, "count":1000, "playername":"eagle"}
    m_commands["WhosYourDaddy"] = new WhosYourDaddy;                            //{"name":"WhosYourDaddy", "playername":"eagle"}
    m_commands["GetAllItems"] = new GetAllItems;                            //{"name":"GetAllItems", "type":101, "playername":"eagle"}
    m_commands["UpdateVipLevel"] = new UpdateVipLevel;                            //{"name":"UpdateVipLevel", "level":10, "playername":"eagle"}
}

GMCommandManager::~GMCommandManager()
{
    for (CommandIter it = m_commands.begin(); it != m_commands.end(); it++) 
    {
        SAFE_DELETE(it->second);
    }

    m_commands.clear();
}


bool GMCommandManager::parse(std::string jsonstring, std::string &out)
{
    Json::Value value;
    Json::Value root;

    if (jsonstring.size() && jsonstring.c_str()[0] == '[')
    {
        root["name"] = "GMCOMMEND_RET_ENUM_PARSE_ERROR";
        root["ret"] = GMCOMMEND_RET_ENUM_PARSE_ERROR;
        out = root.toStyledString();
        LOGE("gmCMD Parse Error " << jsonstring.c_str());
        return false;
    }

    if (m_reader.parse(jsonstring.c_str(), value))
    {
        std::string name = value["name"].asString();
        CommandIter itr = m_commands.find(name);
        if (itr != m_commands.end())
        {
            return itr->second->execute(value, out);
        }

        root["name"] = value["name"];
        root["ret"] = GMCOMMEND_RET_ENUM_NO_COMMEND;    
        LOGE("gmCMD Parse No Commend " << jsonstring.c_str());
    }
    else
    {
        root["name"] = "GMCOMMEND_RET_ENUM_PARSE_ERROR";
        root["ret"] = GMCOMMEND_RET_ENUM_PARSE_ERROR;
        LOGE("gmCMD Parse Error " << jsonstring.c_str());
    }
    out = root.toStyledString();
    
    return false;
}


void GMCommandManager::SendAllMailRecv(int ret)
{
    Json::Value root;
    root["name"] = "SendSystemMail";
    if (ret == 1)
        root["ret"] = GMCOMMEND_RET_ENUM_SUCCESS;
    else
        root["ret"] = GMCOMMEND_RET_ENUM_PARSE_ERROR;

    std::string out = root.toStyledString();

    return;
}

////GMCOMMEND IMP
bool SendServerNotify::execute(Json::Value &value, std::string &out)
{

    return true;
}

bool SendSystemMail::execute(Json::Value &value, std::string &out)
{
    //Json::Value root;
    //root["name"] = value["name"];
    //int isAll = value["all"].asInt();
    //uint32_t type = value["type"].asInt();
    //uint32_t id = value["id"].asInt();
    //uint32_t count = value["count"].asInt();
    //std::string title = value["title"].asString();
    //std::string content = value["content"].asString();
    //if (isAll)
    //{
    //    MailManager::instance()->SendMailToAll(type, id, count, title.c_str(), content.c_str(), "system", "");
    //}
    //else
    //{
    //    std::string playername = value["playername"].asString();
    //    LogicPlayer *player = World::instance()->GetPlayerByName(playername);
    //    if (!player)
    //    {
    //        root["ret"] = GMCOMMEND_RET_ENUM_NO_PLAYER;
    //        out = root.toStyledString();
    //        return false;
    //    }
    //    MailManager::instance()->SendMail(player->Id(), "", "", type, id, count, title.c_str(), content.c_str(), "system", "", 0, 1);
    //}

    //root["ret"] = GMCOMMEND_RET_ENUM_SUCCESS;
    //out = root.toStyledString();

    return true;
}

bool UpdatePlayerLevel::execute(Json::Value &value, std::string &out)
{


    return true;
}

bool OpenGate::execute(Json::Value &value, std::string &out)
{

    return true;
}

bool AddItem::execute(Json::Value &value, std::string &out)
{
    Json::Value root;
    root["name"] = value["name"];
    int isAll = value["all"].asInt();
    uint32_t type = value["type"].asInt();
    uint64_t id = value["id"].asInt();
    uint64_t count = value["count"].asInt();
    std::string playerName = value["playername"].asString();

    LogicPlayer *player = World::instance()->GetPlayerByName(playerName);
    if (!player)
    {
        root["ret"] = GMCOMMEND_RET_ENUM_NO_PLAYER;
    }
    else
    {
        //Cmd::t_Data_Update_Item_Req* send = player->BeginUpdateItem();

        //uint8_t* ptr = send->data;
        //TypeIdCount item = { type, id, count };
        //if (BagSystem::instance()->AddItem(player->GetEntity(), item, ptr, send->itemsCount, send->itemsDataLen))
        //{
        //    player->EndUpdateItem(send);
        //}

        root["ret"] = GMCOMMEND_RET_ENUM_SUCCESS;
    }

    
    out = root.toStyledString();

    return true;
}

bool WhosYourDaddy::execute(Json::Value &value, std::string &out)
{

    return true;
}

bool GetAllItems::execute(Json::Value &value, std::string &out)
{

    return true;
}

bool UpdateVipLevel::execute(Json::Value &value, std::string &out)
{

    return true;
}

