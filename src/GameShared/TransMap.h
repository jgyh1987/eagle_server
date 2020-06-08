#ifndef _CENTRAL_TRANSMAP_H_
#define _CENTRAL_TRANSMAP_H_

#include "Sys.h"
#include "Singleton.h"
#include "GameBaseTask.h"
#include "ServerCommand.h"
#include "ConstructInPlace.h"

class CTransMapManager : public CSingleton<CTransMapManager>
{
public:
    CTransMapManager();
    ~CTransMapManager();

    bool Init(const char *);
    void UpdataMin();

    std::vector<uint32_t> *GetNotifyServerType(uint32_t index);
    std::vector<uint32_t> *GetNeedServerType(uint32_t index);

    void AddTask(CServerTaskEx *);
    void RemoveTask(CServerTaskEx *);
    void SendCmdToTask(void *ptr, uint32_t len, uint32_t serverType);

    void TransNotifyServers(CServerTaskEx *task);
    void TransRemoveServers(CServerTaskEx *);

    template<class cmd>
    unsigned char* ServerCmdBuffer(cmd* &name);

private:
    bool LoadConfig();

private:
    buffercmdqueue m_sendBuffer;
    /// @brief   
    std::string m_filename;
    ///
    std::vector< std::vector<uint32_t> > m_notifyMap;
    std::vector< std::vector<uint32_t> > m_needMap;

    std::map< uint32_t, std::map< uint32_t, std::map<uint32_t, CServerTaskEx *> > > m_serverTasks;
};

template<class cmd>
unsigned char* CTransMapManager::ServerCmdBuffer(cmd* &name) {
    m_sendBuffer.ReSet();
    m_sendBuffer.WrReserve(SERVER_COMMAND_MAX_LENGTH);
    name = (cmd *)(m_sendBuffer.WrBuf());
    constructInPlace(name);
    return m_sendBuffer.WrBuf();
}

#endif
