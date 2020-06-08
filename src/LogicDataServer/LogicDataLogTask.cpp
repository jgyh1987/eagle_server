#include "LogicDataLogTask.h"
#include "Defs.h"
#include "CommonType.h"
#include "DelaySaveCmdQueue.h"
#include "SysLogInfo.h"
#include "ServerCommand.h"

extern DelaySaveCmdQueue g_delaySaveDBCmdQueue;

bool CLogicDataLogTask::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
    try
    {
        Cmd::t_NullCmd *pNullCmd = (Cmd::t_NullCmd*)ptNull;
        switch (pNullCmd->cmd) 
        {
            case Cmd::CMD_SERVER_INIT:
                return DBServerInitMessageParase(pNullCmd, nCmdLen);
            case Cmd::CMD_LOGIC_PLAYERINFO:
                return DBLogicPlayerInfoMessageParase(pNullCmd, nCmdLen);
            default:break;
        }
    }
    catch( const mysqlpp::BadQuery& e ) 
    {
        LOGFMTE("LogicDataServer LogicDataLogTask mysql++ query error: %s errornum= %d", e.what(), e.errnum());
    } 
    catch (const mysqlpp::BadConversion& e ) 
    {
        LOGFMTE("LogicDataServer LogicDataLogTask mysql++ conversion error: %s, retrieved data size: %llu, actual size: %llu", e.what(), (unsigned long long)e.retrieved, (unsigned long long)e.actual_size);
    } 
    catch (const mysqlpp::Exception& e) 
    {
        LOGFMTE("LogicDataServer LogicDataLogTask mysql++ general error: %s", e.what());
    } 
    catch (...) 
    {
        LOGE("LogicDataServer LogicDataLogTask unknown error.");
    }
    
    return false;
}

//DBServerInitMessageParase begin
bool CLogicDataLogTask::DBServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch ( pNullCmd->para )
    {
    case Cmd::PARA_SERVER_REGIST_REQ:
        {
            Cmd::t_Server_Regist_Res send;
            send.res = SUCCESS;
            SendCmd(&send, sizeof(send));
        }
        return true;
    default:
        return false;
    }

    return false;
}
//DBServerInitMessageParase end

bool CLogicDataLogTask::DBLogicPlayerInfoMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch ( pNullCmd->para )
    {
    case Cmd::PARA_DATA_SAVE_RECOUNT_LOGINFO:
        {
            Cmd::t_SendCmdToData_LogInfo *recv = (Cmd::t_SendCmdToData_LogInfo *)pNullCmd;
            DBRecvLog(recv);
        }
        return true;
    default:
        return false;
    }

    return false;
}

bool CLogicDataLogTask::DBRecvLog(Cmd::t_SendCmdToData_LogInfo * recv)
{
    SysLogInfo::instance()->AddLog(recv);

    return true;
}

