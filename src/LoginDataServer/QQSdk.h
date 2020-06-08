#ifndef _QQSDK_H_
#define _QQSDK_H_

#include "Thread.h"
#include "Singleton.h"
#include "CmdQueue.h"
#include "HttpClient.h"
#include "InnerCommand.h"
#include "Shared_Sdk.h"

class CSdkClient : public CThread, public CConCmdQueue
{
public:
    CSdkClient();
    ~CSdkClient();

    bool Init();
    void Run();

    bool cmdMsgParse(void *ptNull,const uint32_t nCmdLen);

    void SendCmd(void *ptNull, uint32_t nCmdLen);

private:
    CHttpClient m_httpClient;
};


class CQQSdkManager : public CSingleton<CQQSdkManager>, public CConCmdQueue
{
public:
    CQQSdkManager();
    ~CQQSdkManager();

    bool Init();
    void Start();
    void Close();

    bool cmdMsgParse(void *ptNull,const uint32_t nCmdLen);

    void PushRecvCmd(void *ptNullCmd ,const unsigned int cmdLen);
    void PushSendCmd(void *ptNullCmd ,const unsigned int cmdLen);

    //test code begin
    void UpdateSec();
    //test code end

private:
    std::vector<CSdkClient *> m_httpClients;

    uint64_t m_index;

    CMutex m_mLock;    
};

#endif
