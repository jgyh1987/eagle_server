#include "SessionManager.h"



AccountSession* AccountSessionManager::GetAccountSession(const std::string& account)
{
    auto itr = m_accounts.find(account);
    if (itr != m_accounts.end())
    {
        return itr->second;
    }

    return NULL;
}

void AccountSessionManager::AddSessionAccount(AccountSession* connect)
{
    m_accounts[connect->account] = connect;

    return;
}

void AccountSessionManager::RemoveSessionAccount(AccountSession* account)
{
    return RemoveSessionAccount(account->account);
}

void AccountSessionManager::RemoveSessionAccount(const std::string& account)
{
    auto itr = m_accounts.find(account);
    if (itr != m_accounts.end())
    {
        SAFE_DELETE(itr->second);
        m_accounts.erase(itr);
    }

    return;
}

uint32_t AccountSessionManager::Size()const
{
    return (uint32_t)m_accounts.size();
}


