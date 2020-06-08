#include "QQSdk.h"
#include "Defs.h"
#include "TimeTick.h"
#include "LoginDataTaskManager.h"
#include "LoginDataTask.h"
#include "LoginServerCommand.h"

#define QQSDK_THREAD_COUNT 50
#define QQSDK_CMD_QUEUE_COUNT 1024

//CSdkClient
CSdkClient::CSdkClient()
    :CThread("CSdkClient"), CConCmdQueue(QQSDK_CMD_QUEUE_COUNT)
{

}
    
CSdkClient::~CSdkClient()
{

}

bool CSdkClient::Init()
{


    return true;
}

void CSdkClient::Run()
{
    while (!IsFinal())
    {
        doCmd();

        //std::string str;
        //char url[1024] = {0};
        //char strt1[1024] = {0};
        //uint32_t t1 = CImpServerTimeTick::currentTime.sec();
        //sprintf(strt1, "%s%ul", g_appQQKEY.c_str(), t1);
        //sprintf(url, "http://ysdktest.qq.com/auth/qq_check_token?appid=%s&openid=1B3C4822236840403571E30922A8F088&openkey=9F2806884C8703F7FEA1490B474940F4&userip=&sig=%s&timestamp=%ul", g_appQQID.c_str(), md5(strt1).c_str(), t1);
        //m_httpClient.Req(url, str);
        //LOGE("CSdkClient::Run " << str.c_str());

        uv_thread_sleep(100);
    }
}

bool CSdkClient::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
    Cmd::t_NullCmd *pNullCmd = (Cmd::t_NullCmd*)ptNull;
    switch (pNullCmd->cmd)
    {
    case Cmd::CMD_INNER_MESSAGE:
        {
            switch (pNullCmd->para)
            {
            case Cmd::PARA_VERIFY_SESSOIN_REQ:
            {
                Cmd::t_Verify_Session_Req *recv = (Cmd::t_Verify_Session_Req *)ptNull;
                Sdk_ReqInfo info;
                memcpy(info.openid, recv->openid, MAX_OPENID_LENGHT);
                memcpy(info.openkey, recv->openkey, MAX_OPENKEY_LENGHT);
                info.sdkType = recv->sdkType;
                info.time = CImpServerTimeTick::currentTime.sec();
                info.vistor = recv->vistor;

                Cmd::t_Login_SessionAccount_Res send;
                strncpy(send.account, recv->account, MAX_ACCOUNT_LENGHT - 1);

                std::string url;
                std::string postUrl;
                std::string str;
                if (GetSdkStr(&info, url, postUrl))
                {
                    int ret = m_httpClient.Req(url, str, &postUrl);

                    LOGD("CSdkClient::Run " << url << " || postUrl = " << postUrl << "  || res = " << str.c_str() << " || ret = " << ret);

                    if (TryResStr(str, recv->sdkType))
                        send.ret = SUCCESS;
                    else
                    {
                        send.ret = SESSION_ERROR;
                        LOGE("CSdkClient::Run " << url << " || postUrl = " << postUrl << "  || res = " << str.c_str() << " || ret = " << ret);
                    }

                }

                SendCmd(&send, sizeof(send));
            }
            break;
            default:break;
            }
        }
        break;
    default:break;
    }

    return true;
}

void CSdkClient::SendCmd(void *ptNull, uint32_t nCmdLen)
{
    CQQSdkManager::instance()->PushSendCmd(ptNull, nCmdLen);

    return;
}

//CQQSdkManager
CQQSdkManager::CQQSdkManager()
    :CConCmdQueue(QQSDK_CMD_QUEUE_COUNT * QQSDK_THREAD_COUNT)
{
    m_httpClients.resize(QQSDK_THREAD_COUNT, NULL);
    m_index = 0;
}

CQQSdkManager::~CQQSdkManager()
{
    Close();
}

bool CQQSdkManager::Init()
{
    for (uint32_t i = 0; i < m_httpClients.size(); ++i)
    {
        m_httpClients[i] = new CSdkClient;
        m_httpClients[i]->Init();
    }

    return true;
}

void CQQSdkManager::Start()
{
    for (uint32_t i = 0; i < m_httpClients.size(); ++i)
    {
        m_httpClients[i]->Start();
    }

    return;
}
    
void CQQSdkManager::Close()
{
    for (uint32_t i = 0; i < m_httpClients.size(); ++i)
    {
        m_httpClients[i]->Close();
        delete m_httpClients[i];
    }

    m_httpClients.clear();

    return;
}

void CQQSdkManager::UpdateSec()
{

}

bool CQQSdkManager::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
    SendToLoginServer(ptNull, nCmdLen);

    return true;
}

void CQQSdkManager::PushRecvCmd(void *ptNullCmd ,const unsigned int cmdLen)
{
    uint32_t index = (uint32_t)(m_index % QQSDK_THREAD_COUNT);
    ++m_index;

    m_httpClients[index]->msgParase(ptNullCmd, cmdLen);

    return;
}

void CQQSdkManager::PushSendCmd(void *ptNullCmd ,const unsigned int cmdLen)
{
    m_mLock.Lock();
    msgParase(ptNullCmd, cmdLen);
    m_mLock.UnLock();
    
    return;
}


