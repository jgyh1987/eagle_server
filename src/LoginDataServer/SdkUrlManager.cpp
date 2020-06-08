#include "SdkUrlManager.h"

#define SDKURL_FILE_MAX_LEN    0xffffff

std::vector<SDKInfo> g_sdkInfo;

CSDKUrlListManager::CSDKUrlListManager()
{
    m_sdkInfo.resize(SDK_TYPE_MAX);
}

CSDKUrlListManager::~CSDKUrlListManager()
{
}

bool CSDKUrlListManager::Init(char *configPath)
{
    m_filename = configPath;
    m_fileMd5 = GetFileMd5();
    LoadConfig();

    return true;
}

bool CSDKUrlListManager::LoadConfig()
{
    CXMLParser xml;    
    if (!xml.loadFile(m_filename.c_str()))
    {
        return false;
    }

    if (!xml.setCurNode("Config"))
    {
        return false;
    }

    if (xml.setChildNode("server"))
    {
        do
        {
            std::string _url = "";
            uint32_t _type = 0;
            std::string appId = "";
            std::string gameTag = "";
            std::string gameSubTag = "";
            std::string key = "";

            xml.getNodeAttrInt( "type", &_type );
            xml.getNodeAttrStr( "url", _url );
            xml.getNodeAttrStr( "appId", appId );
            xml.getNodeAttrStr( "gameTag", gameTag );
            xml.getNodeAttrStr( "gameSubTag", gameSubTag );
            xml.getNodeAttrStr( "secreat", key );
            if (_type > 0 && _type < SDK_TYPE_MAX)
            {
                m_sdkInfo[_type].typeUrl = _url;
                m_sdkInfo[_type].appId = appId;
                m_sdkInfo[_type].gameTag = gameTag;
                m_sdkInfo[_type].gameSubTag = gameSubTag;
                m_sdkInfo[_type].secreat = key;
            }
        }
        while ( xml.setNextNode() );
    }

    return true;
}

bool CSDKUrlListManager::ReLoadConfig()
{
    if (IsNeedReload())
    {
        LoadConfig();
    }

    return true;
}

bool CSDKUrlListManager::IsNeedReload()
{
    std::string newMd5 = GetFileMd5();

    if (m_fileMd5.compare(newMd5))
    {
        m_fileMd5 = newMd5;
        return true;
    }

    return false;
}

std::string CSDKUrlListManager::GetFileMd5()
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
        if (nLen > SDKURL_FILE_MAX_LEN)
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
