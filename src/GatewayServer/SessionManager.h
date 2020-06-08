#ifndef _ACCOUNT_SESSION_MANAGER_H_
#define _ACCOUNT_SESSION_MANAGER_H_

#include "Singleton.h"
#include "Session.h"

class AccountSessionManager : public CSingleton<AccountSessionManager>
{
public:    
    AccountSession* GetAccountSession(const std::string& account);
    
    void AddSessionAccount(AccountSession* connect);
    
    void RemoveSessionAccount(AccountSession* connect);
    void RemoveSessionAccount(const std::string& account);

    uint32_t Size()const;

private:
    eagle_hash_map<std::string, AccountSession *> m_accounts;
};

#endif

