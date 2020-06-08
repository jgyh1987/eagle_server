#include "LogicDataService.h"
#include "DelaySaveCmdQueue.h"
#include "Defs.h"
#include "LogicDataPlayer.h"

extern DelaySaveCmdQueue g_delaySaveDBCmdQueue;

CLogicDataServer *ServerImp()
{
    return (CLogicDataServer *)g_pServerImp;
}


CLogicDataServer::CLogicDataServer(const std::string &name)
    :CImpServer(SERVER_TYPE_MAX, name)
{

}
    
CLogicDataServer::~CLogicDataServer()
{

}

void CLogicDataServer::Update()
{
    try
    {
        g_delaySaveDBCmdQueue.SendCmdMsgParse();
    }
    catch (const mysqlpp::BadQuery& e)
    {
        LOGFMTE("LogicDataServer DataDBConnection mysql++ query error: %s errornum= %d", e.what(), e.errnum());
        LOGE("LogicDataServer DataDBConnection mysql reconnect error");
    }
    catch (const mysqlpp::BadConversion& e)
    {
        LOGFMTE("LogicDataServer DataDBConnection mysql++ conversion error: %s, retrieved data size: %llu, actual size: %llu", e.what(), (unsigned long long)e.retrieved, (unsigned long long)e.actual_size);
        LOGE("LogicDataServer DataDBConnection mysql reconnect error");
    }
    catch (const mysqlpp::Exception& e)
    {
        LOGFMTE("LogicDataServer DataDBConnection mysql++ general error: %s", e.what());
        LOGE("LogicDataServer DataDBConnection mysql reconnect error");
    }
    catch (...)
    {
        LOGE("LogicDataServer DataDBConnection unknown error.");
        LOGE("LogicDataServer DataDBConnection mysql reconnect error");
    }

    

    return;
}

void CLogicDataServer::Update5Sec()
{
    try
    {
        bool ret = DataDBConnection::instance()->connection()->ping();
        if (!ret)
        {
            LOGE("LogicDataServer DataDBConnection mysql connect error try reconnect...");
            ret = DataDBConnection::instance()->reconnect();
            if (!ret)
                LOGE("LogicDataServer DataDBConnection mysql reconnect error");
            else
                LOGE("LogicDataServer DataDBConnection mysql reconnect success");
        }

        DataPlayerManager::instance()->Update5Sec();
    }
    catch (const mysqlpp::BadQuery& e)
    {
        LOGFMTE("LogicDataServer DataDBConnection mysql++ query error: %s errornum= %d", e.what(), e.errnum());
        LOGE("LogicDataServer DataDBConnection mysql reconnect error");
    }
    catch (const mysqlpp::BadConversion& e)
    {
        LOGFMTE("LogicDataServer DataDBConnection mysql++ conversion error: %s, retrieved data size: %llu, actual size: %llu", e.what(), (unsigned long long)e.retrieved, (unsigned long long)e.actual_size);
        LOGE("LogicDataServer DataDBConnection mysql reconnect error");
    }
    catch (const mysqlpp::Exception& e)
    {
        LOGFMTE("LogicDataServer DataDBConnection mysql++ general error: %s", e.what());
        LOGE("LogicDataServer DataDBConnection mysql reconnect error");
    }
    catch (...)
    {
        LOGE("LogicDataServer DataDBConnection unknown error.");
        LOGE("LogicDataServer DataDBConnection mysql reconnect error");
    }


    return;
}

void CLogicDataServer::Close()
{
    DataPlayerManager::instance()->SaveAllPlayer();

    return;
}


