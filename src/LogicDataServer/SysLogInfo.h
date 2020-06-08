#ifndef _SYSLOGINFO_H_
#define _SYSLOGINFO_H_

#include "CommonType.h"
#include "LogicDataCommand.h"
#include "Singleton.h"
#include "Defs.h"
#include "Lock.h"

struct SqlLogActionInfo;

class SysLogInfo: public CSingleton<SysLogInfo>
{
public:
    SysLogInfo();

    void AddLog(Cmd::t_SendCmdToData_LogInfo* rev , bool flush = true );
        
    void Final() 
    {
        FlushLog();
    }
        
    void Loop();

private:
        
    std::vector<SqlLogActionInfo> m_logBuffer;
    uint32_t m_bufsize;
        
    bool FlushLog();
private:
    CMutex m_lock;
};

#endif
