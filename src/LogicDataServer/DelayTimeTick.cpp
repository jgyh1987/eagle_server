#include "DelayTimeTick.h"
#include "Defs.h"
#include "DelaySaveCmdQueue.h"

CRTime CDelayTimeTick::currentTime;

extern DelaySaveCmdQueue g_delaySaveDBCmdQueue;

bool CDelayTimeTick::Init()
{

    return true;
}

void CDelayTimeTick::Run()
{
    LOGI("DelayTimeTick Run!!!!!!!!!!!!!");

    while (!IsFinal())
    {
        currentTime.now();

        int _t=0;
        try
        {
            //bool ret = DelayDBConnection::instance()->connection()->ping();
            //if( !ret )
            //{
            //    LOGE("LogicDataServer DelayDBConnection mysql connect error try reconnect...");
            //    ret = DelayDBConnection::instance()->reconnect();
            //    if( !ret )
            //        LOGE("LogicDataServer DelayDBConnection mysql reconnect error");
            //    else
            //        LOGE("LogicDataServer DelayDBConnection mysql reconnect success");
            //}
        } 
        catch( const mysqlpp::BadQuery& e ) 
        {
            LOGFMTE("LogicDataServer DelayDBConnection mysql++ query error: %s errornum= %d", e.what(), e.errnum());
            LOGE("LogicDataServer DelayDBConnection mysql reconnect error");
        } 
        catch (const mysqlpp::BadConversion& e ) 
        {
            LOGFMTE("LogicDataServer DelayDBConnection mysql++ conversion error: %s, retrieved data size: %llu, actual size: %llu", e.what(), (unsigned long long)e.retrieved, (unsigned long long)e.actual_size);
            LOGE("LogicDataServer DelayDBConnection mysql reconnect error");
        } 
        catch (const mysqlpp::Exception& e) 
        {
            LOGFMTE("LogicDataServer DelayDBConnection mysql++ general error: %s", e.what());
            LOGE("LogicDataServer DelayDBConnection mysql reconnect error");
        } 
        catch (...) 
        {
            LOGE("LogicDataServer DelayDBConnection unknown error.");
            LOGE("LogicDataServer DelayDBConnection mysql reconnect error");
        }

        g_delaySaveDBCmdQueue.doCmd();

        if(m_one_sec(currentTime))
        {
            if(m_five_sec(currentTime))
            {
                g_delaySaveDBCmdQueue.Update();

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
            LOGFMTI("DelayTimeTick::Run %u ms", _t);
            uv_thread_sleep(1);
        }
        else
            uv_thread_sleep(50 - _t);

    }
    LOGI("DelayTimeTick finaled!!!!!!!!!!!!!");
}


