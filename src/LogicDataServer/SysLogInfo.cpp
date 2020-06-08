#include "SysLogInfo.h"
#include "ServerCommand.h"
#include "LogDBConnection.h"
#include "Defs.h"

SysLogInfo::SysLogInfo()
{
    m_bufsize = atoi(eagle::global["logBatchNum"].c_str());
    if(m_bufsize <= 0)
        m_bufsize = 50;
    m_logBuffer.reserve(m_bufsize);
}

bool SysLogInfo::FlushLog()
{
    if (!m_logBuffer.size())
        return true;

    mysqlpp::SimpleResult result; 
    mysqlpp::Query query = LogDBConnection::instance()->query();
    std::vector<bool> vb(SqlLogActionInfo_NULL,false); 
    vb[SqlLogActionInfo_account] = true;   
    vb[SqlLogActionInfo_playerId] = true;    
    vb[SqlLogActionInfo_type] = true;   
    vb[SqlLogActionInfo_playerLevel] = true;    
    vb[SqlLogActionInfo_playerName] = true;     
    vb[SqlLogActionInfo_time] = true; 
    vb[SqlLogActionInfo_info] = true;   
    LogDBConnection::makeInsertQuery(query, m_logBuffer, vb); 
    LOGT("SysLogInfo::FlushLog" << query.str().c_str());  
    result = query.execute();  

    m_logBuffer.clear();

    if(result)
        return true;
    else 
    {
        LOGD("log write fail.");
        return false;
    }

}

void SysLogInfo::AddLog(Cmd::t_SendCmdToData_LogInfo* rev, bool flush )
{
    //m_lock.Lock;
    SqlLogActionInfo info;
    info.playerId = rev->playerId;
    info.account = rev->account;
    info.playerName = rev->name;
    info.type = rev->type;
    info.playerLevel = rev->level;
    info.time = rev->time;
    info.info = rev->info;

    m_logBuffer.push_back(info);

    if(m_logBuffer.size() >= m_bufsize && flush)
        FlushLog();
    //m_lock.UnLock();
}

void SysLogInfo::Loop()
{
    FlushLog();
}

