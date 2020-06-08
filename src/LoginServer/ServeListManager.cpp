#include "Defs.h"
#include "XMLParser.h"
#include "MD5.h"
#include "ServeListManager.h"
#include "TimeTick.h"
#include "LoginTask.h"
#include "LoginTaskManager.h"
#include "LoginService.h"

#define SERVERLIST_FILE_MAX_LEN    0xffff

CServeListManager::CServeListManager()
    :m_filename(eagle::global["ServerListConfigPath"].c_str()), m_refTime(0), m_refStep(300)
{

}

CServeListManager::~CServeListManager()
{
}

bool CServeListManager::Init()
{
    m_fileMd5 = GetFileMd5();
    LOGD("CServeListManager::Init FILE MD5 = " << m_fileMd5.c_str());
    LoadConfig();
    m_refTime = CImpServerTimeTick::currentTime.sec();
    m_refStep = eagle::global.GetInt("ServerListRefTime");

    return true;
}

bool CServeListManager::ReLoadConfig(uint64_t curtime)
{
    if (curtime > m_refTime + m_refStep)
    {
        LoadConfig();
        m_refTime = curtime;
    }

    return true;
}

bool CServeListManager::ReLoadConfig()
{
    if (IsNeedReload())
    {
        LOGD("CServeListManager::ReLoadConfig FILE MD5 = " << m_fileMd5.c_str());
        Clear();
        LoadConfig();
    }

    return true;
}

bool CServeListManager::LoadConfig()
{
    CXMLParser xml;
    if (!xml.loadFile(m_filename.c_str()))
    {
        LOGE("CServeListManager::LoadConfig m_parser.loadFile ERROR");
        return false;
    }

    if (!xml.setCurNode("serverconfig"))
    {
        LOGE("CServeListManager::LoadConfig serverconfig ERROR");
        return false;
    }

    if (xml.setChildNode("servertype"))
    {
        std::string strType = xml.getNodeContentStr();
        std::vector<uint32_t> servertype;
        ParseStringToVectorUint32(strType, servertype, '-', ';', 1);
        if (servertype.size())
        {
            for (uint32_t i = 0; i < servertype.size(); ++i)
            {
                m_serverType.insert(servertype[i]);
            }
        }

        for (uint32_t i = 0; i < servertype.size(); ++i)
        {
            LOGT("ClientMsg::GetServerListReq m_serverType" << servertype[i]);
        }
    }
    xml.setUpNode();

    if (xml.setChildNode("serverlist"))
    {
        if (xml.setChildNode("activelist"))
        {
            do
            {
                uint32_t type = 0;
                Struct::ServerInfo temp;
                LOGT("CServeListManager::LoadConfig activelist begin ");
                CheckCondition( xml.getNodeAttrInt( "type", &type ), false );
                LOGT("CServeListManager::LoadConfig activelist type " << type);
                if (ActiveType(type))
                {
                    LOGT("CServeListManager::LoadConfig activelist data ");
                    temp.serverType = type;
                    CheckCondition( xml.getNodeAttrInt( "id", &temp.gameId), false );
                    //CheckCondition( xml.getNodeAttrInt( "serverindex", &temp.serverindex), false );
                    //CheckCondition( xml.getNodeAttrStr( "servertitle", temp.areaName ), false );
                    //CheckCondition( xml.getNodeAttrStr( "servername", temp.serverName ), false );
                    //CheckCondition( xml.getNodeAttrStr( "title", temp.title ), false );

                    m_serverInfo.push_back(temp);
                }
            }
            while ( xml.setNextNode() );
        }
        else
        {
            LOGD("CServeListManager::LoadConfig activelist NULL");
        }
    }
    else
    {
        LOGE("CServeListManager::LoadConfig serverlist NULL");
    }

    LOGD("CServeListManager::LoadConfig End");


    return true;
}

void CServeListManager::UpdateServerStatus()
{
    for (uint32_t i = 0; i < m_serverInfo.size(); ++i)
    {
        CLoginTask *server = GetServerImp()->FindLoginTask(m_serverInfo[i].gameId);
        //if (server)
        //{
        //    m_serverInfo[i].status = server->GetPlayerCount();
        //    //set server status
        //}
    }

    return;
}

std::string CServeListManager::GetFileMd5()
{
    std::string newMd5;
    FILE *fp = fopen(m_filename.c_str(), "rb");
    if (!fp)
        return newMd5;

    char *buff = NULL;
    
    do
    {
        fseek(fp, 0, SEEK_END);
        uint32_t nLen = ftell(fp);
        if (nLen > SERVERLIST_FILE_MAX_LEN)
            break;
        buff = new char[nLen + 1];
        if (!buff)
            break;

        fseek(fp, 0, SEEK_SET);
        fread(buff, 1, nLen, fp);
        buff[nLen] = 0;

        newMd5 = md5(buff);
    }
    while(false);
    
    if (buff)
        delete [] buff;
    fclose(fp);

    return newMd5;
}

bool CServeListManager::IsNeedReload()
{
    std::string newMd5 = GetFileMd5();

    if (m_fileMd5.compare(newMd5))
    {
        m_fileMd5 = newMd5;
        return true;
    }

    return false;
}

