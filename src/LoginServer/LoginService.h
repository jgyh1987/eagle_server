#ifndef _LOGINSERVICE_H_
#define _LOGINSERVICE_H_

#include "ImpService.h"


class CLoginClientTask;
class CLoginTask;

class CLoginServer : public CImpServer
{
public:
    CLoginServer(const std::string &name);
    ~CLoginServer();

    bool CallBack();

    void Update();
    void Update5Sec();
    void UpdateMin();

public:
    void AddClientTask(CLoginClientTask *task);
    void RemoveClientTask(CLoginClientTask *task);
    CLoginClientTask *FindPlayer(uint32_t clientId);

    CLoginTask *FindLoginTask(uint32_t gameServerId);
    void AddLoginTask(CLoginTask *);
    void RemoveLoginTask(CLoginTask *);

private:
    typedef std::map<uint32_t, CLoginClientTask *> T_PlayerMap;
    T_PlayerMap m_players;

    std::map<uint32_t, std::map<uint32_t, CLoginTask *> > m_servers;
};

CLoginServer *GetServerImp();

#endif

