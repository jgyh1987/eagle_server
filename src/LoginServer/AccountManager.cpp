#include "Defs.h"
#include "CommonType.h"
#include "AccountManager.h"
#include "LoginClientTask.h"

#define SERVERLIST_FILE_MAX_LEN    0xffff

SAccountInfo::~SAccountInfo()
{
    if (task)
        task->ClearAccountInfo();
}

CAccountManager::CAccountManager()
{

}

CAccountManager::~CAccountManager()
{
    for (auto &itr : m_accountMap)
    {
        SAFE_DELETE(itr.second);
    }
    m_accountMap.clear();
}

bool CAccountManager::Init()
{

    return true;
}

void CAccountManager::Update5Sec()
{

    return;
}

SAccountInfo *CAccountManager::AddAccountInfo(SAccountInfo *info)
{
    m_accountMap[info->account] = info;

    return NULL;
}

SAccountInfo* CAccountManager::GetAccountInfo(std::string &account)
{
    accountmap::iterator it = m_accountMap.find(account);
    if (it != m_accountMap.end())
        return it->second;

    return NULL;
}

void CAccountManager::RemoveAccountInfo(std::string &account)
{
    accountmap::iterator it = m_accountMap.find(account);
    if (it != m_accountMap.end())
    {
        SAFE_DELETE(it->second);
    }
        

    return;
}

char *CAccountManager::CreateSession(const char *account, const char *passwd)
{
    static char session[MAX_SESSION_LENGHT] = {0};

    bzero(session, MAX_SESSION_LENGHT);
    strncpy(session, account, MAX_SESSION_LENGHT - 1);

    return session;
}
