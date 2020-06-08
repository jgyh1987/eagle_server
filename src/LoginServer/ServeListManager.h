#ifndef _SERVERLISTMANAGER_H_
#define _SERVERLISTMANAGER_H_

#include "Singleton.h"
#include "Struct.h"
#include "ClientMsg.h"

typedef std::vector<Struct::ServerInfo> serverlist;

class CServeListManager : public CSingleton<CServeListManager>
{
public:
    CServeListManager();
    ~CServeListManager();

    bool Init();
    bool ReLoadConfig(uint64_t curtime);
    //默认5分钟更新
    bool ReLoadConfig();

    void UpdateServerStatus();

private:
    bool LoadConfig();
    inline bool ActiveType(uint32_t type);
    inline void Clear();
    bool IsNeedReload();
    std::string GetFileMd5();

private:
    /// @brief    配置文件名称
    std::string m_filename;
    /// @brief 文件md5
    std::string m_fileMd5;

    //LAST LOAD TIME
    uint64_t m_refTime;
    //REF STEP
    uint32_t m_refStep;

    std::set<uint32_t> m_serverType;
    serverlist m_serverInfo;
};

inline bool CServeListManager::ActiveType(uint32_t type)
{
    std::set<uint32_t>::iterator itr = m_serverType.find(type);
    if (itr != m_serverType.end())
        return true;

    return false;
}

inline void CServeListManager::Clear()
{
    m_serverType.clear();
    m_serverInfo.clear();

    return;
}

#endif

