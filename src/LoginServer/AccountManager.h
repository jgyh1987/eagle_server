#ifndef _ACCOUNTMANAGER_H_
#define _ACCOUNTMANAGER_H_

#include "Singleton.h"
#include "ClientMsg.h"

class CLoginClientTask;

struct SAccountInfo
{
    sockaddr_storage addr;
    std::string account;
    std::string skdId;
    std::string token;
    std::string session;
    uint32_t m_lastLoginReq;
    CLoginClientTask *task;
    bool isVerify;

    SAccountInfo()
    {
        m_lastLoginReq = 0;
        task = NULL;
        isVerify = false;
    }

    ~SAccountInfo();
};

typedef eagle_hash_map<std::string, SAccountInfo *> accountmap;

class CAccountManager : public CSingleton<CAccountManager>
{
public:
    CAccountManager();
    ~CAccountManager();

    bool Init();
    void Update5Sec();

    SAccountInfo *AddAccountInfo(SAccountInfo *);
    SAccountInfo* GetAccountInfo(std::string &account);
    void RemoveAccountInfo(std::string &account);

private:
    //not thread safe
    char *CreateSession(const char *account, const char *passwd);

private:
    accountmap m_accountMap;

};

#endif

