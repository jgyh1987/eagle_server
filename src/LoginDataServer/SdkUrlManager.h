/*
    ����ʱ�    : 2017-11-24 
    ��ļ����    : eagle
    ߹���˵�    : SDK ���Ϣ���ü��ع��

*/

#ifndef _SDKURLMANAGER_H_
#define _SDKURLMANAGER_H_

//�ͷ�ļ����Ŀ�����ͷ�ļ
#include "Sys.h"
#include "Singleton.h"
#include "XMLParser.h"
#include "MD5.h"
#include "CommonType.h"

struct SDKInfo
{
    std::string typeUrl;
    std::string appId;
    std::string gameTag;
    std::string gameSubTag;
    std::string secreat;
};

//���Ŀʹ��ʱ �Լ��滻�����
class CSDKUrlListManager : public CSingleton<CSDKUrlListManager>
{
public:
    CSDKUrlListManager();
    ~CSDKUrlListManager();

    //��ʼ�� �����ļ XML��ļ�ο��� SDKURLConfig.xml
    bool Init(char *configPath);
    bool ReLoadConfig();

    inline std::string GetUrlByType(uint32_t _type)
    {
        if (_type >= m_sdkInfo.size())
            return "";
        else
            return m_sdkInfo[_type].typeUrl;
    }
    inline std::string GetAppIdByType(uint32_t _type)
    {
        if (_type >= m_sdkInfo.size())
            return "";
        else
            return m_sdkInfo[_type].appId;
    }
    inline std::string GetGameTagByType(uint32_t _type)
    {
        if (_type >= m_sdkInfo.size())
            return "";
        else
            return m_sdkInfo[_type].gameTag;
    }
    inline std::string GetGameSubTagByType(uint32_t _type)
    {
        if (_type >= m_sdkInfo.size())
            return "";
        else
            return m_sdkInfo[_type].gameSubTag;
    }
    inline std::string GetSecreatByType(uint32_t _type)
    {
        if (_type >= m_sdkInfo.size())
            return "";
        else
            return m_sdkInfo[_type].secreat;
    }
private:
    bool LoadConfig();
    bool IsNeedReload();
    std::string GetFileMd5();

private:
    /// @brief    ������ļ���
    std::string m_filename;
    /// @brief ��ļmd5
    std::string m_fileMd5;
    std::vector<SDKInfo> m_sdkInfo;
  
};

#endif

