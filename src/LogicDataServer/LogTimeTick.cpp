#include "LogTimeTick.h"
#include "ListenServer.h"
#include "Defs.h"

CRTime CLogicDataLogTimeTick::currentTime;

extern CListenTCPServer *g_pListenTcpLogServer;

bool CLogicDataLogTimeTick::Init()
{

    return true;
}

void CLogicDataLogTimeTick::Run()
{
    LOGI("LoginDataLogTimeTick Run!!!!!!!!!!!!!");

    while (!IsFinal())
    {
        currentTime.now();

        int _t=0;
        try
        {
            bool ret = LogDBConnection::instance()->connection()->ping();
            if( !ret )
            {
                LOGE("LogicDataServer LogDBConnection mysql connect error try reconnect...");
                ret = LogDBConnection::instance()->reconnect();
                if( !ret )
                    LOGE("LogicDataServer LogDBConnection mysql reconnect error");
                else
                    LOGE("LogicDataServer LogDBConnection mysql reconnect success");
            }
        } 
        catch( const mysqlpp::BadQuery& e ) 
        {
            LOGFMTE("LogicDataServer LogDBConnection mysql++ query error: %s errornum= %d", e.what(), e.errnum());
            LOGE("LogicDataServer LogDBConnection mysql reconnect error");
        } 
        catch (const mysqlpp::BadConversion& e ) 
        {
            LOGFMTE("LogicDataServer LogDBConnection mysql++ conversion error: %s, retrieved data size: %llu, actual size: %llu", e.what(), (unsigned long long)e.retrieved, (unsigned long long)e.actual_size);
            LOGE("LogicDataServer LogDBConnection mysql reconnect error");
        } 
        catch (const mysqlpp::Exception& e) 
        {
            LOGFMTE("LogicDataServer LogDBConnection mysql++ general error: %s", e.what());
            LOGE("LogicDataServer LogDBConnection mysql reconnect error");
        } 
        catch (...) 
        {
            LOGE("LogicDataServer LogDBConnection mysql unknown error.");
            LOGE("LogicDataServer LogDBConnection mysql reconnect error");
        }

        g_pListenTcpLogServer->GetTaskManager()->ExecAll();

        if(m_one_sec(currentTime))
        {
            if(m_five_sec(currentTime))
            {
                if(m_one_min(currentTime))
                {
                    if(m_five_min(currentTime))
                    {
                        if (m_thirty_min(currentTime))
                        {
                            if (m_one_hour(currentTime))
                            {
                        
                            }
                        }
                    }
                }
            }

        }

        CRTime e;
        _t = (int)currentTime.elapse(e);
        if (_t > 50)
        {   
            LOGFMTD("LogicDataLogTimeTick::Run %u ms", _t);
            uv_thread_sleep(1);
        }
        else
            uv_thread_sleep(50 - _t);

    }
    LOGI("LogicDataLogTimeTick finaled!!!!!!!!!!!!!");
}


