#include "DelaySaveCmdQueue.h"
#include "Defs.h"
#include "LogicDataCommand.h"
#include "DelayTimeTick.h"

bool DelaySaveCmdQueue::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
    try
    {
        Cmd::t_NullCmd *pNullCmd = (Cmd::t_NullCmd*)ptNull;
        switch (pNullCmd->cmd) 
        {
        case Cmd::CMD_LOGIC_PLAYERINFO:
            {
                switch (pNullCmd->para)
                {
                //case Cmd::PARA_DATA_SEND_MAIL_TO_ALL_REQ:
                //    {
                //        Cmd::t_Data_Send_Mail_To_All_Req *recv = (Cmd::t_Data_Send_Mail_To_All_Req *)ptNull;
                //        DBSendMailToAll(recv);
                //    }
                //    return true;
                //case Cmd::PARA_DATA_SEND_MAIL_REQ:
                //    {
                //        Cmd::t_Data_Send_Mail_Req *recv = (Cmd::t_Data_Send_Mail_Req *)ptNull;
                //        DBSendMail(recv);
                //    }
                //    return true;
                //case Cmd::PARA_DATA_DELETE_MAIL_REQ:
                //    {
                //        Cmd::t_Data_Delete_Mail_Req *recv = (Cmd::t_Data_Delete_Mail_Req *)ptNull;
                //        DBDeleteMail(recv);
                //    }
                //    return true;
                //case Cmd::PARA_DATA_GET_MAIL_LIST_REQ:
                //    {
                //        Cmd::t_Data_Get_Mail_List_Req *recv = (Cmd::t_Data_Get_Mail_List_Req *)ptNull;
                //        DBGetMailList(recv);
                //    }
                //    return true;
                default:break;
                }
            }
            break;
        default:break;
        }
    }
    catch( const mysqlpp::BadQuery& e )
    {
        LOGFMTD("DelaySaveCmdQueue::cmdMsgParse mysql++ query error: %s errornum= %d", e.what(), e.errnum());
    }
    catch (const mysqlpp::BadConversion& e )
    {
        LOGFMTD("DelaySaveCmdQueue::cmdMsgParse mysql++ conversion error: %s, retrieved data size: %llu, actual size: %llu", e.what(), (unsigned long long)e.retrieved, (unsigned long long)e.actual_size);
    }
    catch (const mysqlpp::Exception& e)
    {
        LOGFMTD("DelaySaveCmdQueue::cmdMsgParse mysql++ general error: %s", e.what());
    }
    catch (...)
    {
        LOGD("DelaySaveCmdQueue::cmdMsgParse unknown error.");
    }
    
    return false;
}

void DelaySaveCmdQueue::Update()
{


    return;
}

//
void DelaySaveCmdQueue::SendCmdMsgParse()
{
    uv_buf_t tempBuf;
    tempBuf.len = 0;
    while (GetSendBuf((unsigned char**)&tempBuf.base, (uint32_t*)&tempBuf.len))
    {
        Cmd::t_NullCmd *pNullCmd = (Cmd::t_NullCmd*)tempBuf.base;
        switch (pNullCmd->cmd) 
        {
        case Cmd::CMD_LOGIC_PLAYERINFO:
            {
                switch (pNullCmd->para)
                {
                //case Cmd::PARA_DATA_SEND_MAIL_TO_ALL_RES:
                //case Cmd::PARA_DATA_SEND_MAIL_RES:
                //case Cmd::PARA_DATA_GET_MAIL_LIST_RES:
                //    {
                //        SendToLogicServer((void *)tempBuf.base, (uint32_t)tempBuf.len);
                //    }
                //    break;
                default:break;
                }
            }
            break;
        default:break;
        }
        g_mt_alloc_char.deallocate((unsigned char *)tempBuf.base, tempBuf.len);
    }

    return;
}

//
//bool DelaySaveCmdQueue::DBSendMailToAll(Cmd::t_Data_Send_Mail_To_All_Req *recv)
//{
//    mysqlpp::Query query = DelayDBConnection::instance()->query();
//    query << "insert into MAIL(PLAYERID, ACCOUNT, CREATETIME, ITEMTYPE, ITEMID, ITEMCOUNT, TITLE, CONTENT, SENDNAME, SENDACCOUNT) select PLAYERID, ACCOUNT, " << recv->mailinfo.createTime << ", " <<  recv->mailinfo.itemType << ", " << recv->mailinfo.itemId << ", " << recv->mailinfo.itemCount << ", '" << recv->mailinfo.title << "', '" << recv->mailinfo.content << "', '" << recv->mailinfo.sendName << "', '" << recv->mailinfo.sendAccount << "' from PLAYER_CREATE_INFO;";
//    mysqlpp::SimpleResult res = query.execute();
//
//    Cmd::t_Data_Send_Mail_To_All_Res send;
//    send.ret = 1;
//    if (!res)
//    {
//        send.ret = 0;
//        LOGE(" DBSendMailToAll " << query.str().c_str());
//    }
//
//    PutSendBuf(&send, sizeof(send));
//
//    return true;
//}
//
//bool DelaySaveCmdQueue::DBSendMail(Cmd::t_Data_Send_Mail_Req *recv)
//{
//    Cmd::t_Data_Send_Mail_Res send;
//    send.ret = 1;
//    send.isGM = recv->isGM;
//    send.sendPlayerId = recv->sendPlayerId;
//    strncpy(send.mailinfo.sendAccount, recv->mailinfo.sendAccount, MAX_ACCOUNT_LENGHT - 1);
//    mysqlpp::Query query = DelayDBConnection::instance()->query();
//    if (recv->playerId)
//        query << "select PLAYERID, ACCOUNT from PLAYER_CREATE_INFO where PLAYERID  =  " << recv->playerId << ";";
//    else if (strlen(recv->account))
//        query << "select PLAYERID, ACCOUNT from PLAYER_CREATE_INFO where ACCOUNT  =  '" << recv->account << "' ;";
//    else if (strlen(recv->name))
//        query << "select PLAYERID, ACCOUNT from PLAYER_CREATE_INFO where NAME  =  '" << recv->name << "' ;";
//    else
//        send.ret = 0;
//    LOGT("Cmd::PARA_DATA_SEND_MAIL_REQ " << query.str().c_str());
//
//    if (!send.ret)
//    {
//        PutSendBuf(&send, sizeof(send));
//        return true;
//    }
//
//    std::vector<SqlPlayerInfo> result;
//    query.storein(result);
//
//    if (result.empty())
//    {
//        send.ret = 0;
//    }
//    else
//    {        
//        recv->playerId = result[0].playerId;
//        send.playerId = recv->playerId;
//        strncpy(recv->account, result[0].account.c_str(), MAX_ACCOUNT_LENGHT - 1);
//    }
//
//    if (!send.ret)
//    {
//        PutSendBuf(&send, sizeof(send));
//        return true;
//    }
//
//    mysqlpp::Query querymail = DelayDBConnection::instance()->query();
//    SqlMail mailinfo;
//    mailinfo.playerId = recv->playerId;
//    mailinfo.account = recv->account;
//    mailinfo.createTime = recv->mailinfo.createTime;
//    mailinfo.itemType = recv->mailinfo.itemType;
//    mailinfo.itemId = recv->mailinfo.itemId;
//    mailinfo.itemCount = recv->mailinfo.itemCount;
//    mailinfo.title = recv->mailinfo.title;
//    mailinfo.content = recv->mailinfo.content;
//    mailinfo.sendName = recv->mailinfo.sendName;
//    mailinfo.sendAccount = recv->mailinfo.sendAccount;
//
//    std::vector<bool> vb(SqlMail_NULL, true);    
//    vb[SqlMail_id] = false;
//
//    DelayDBConnection::makeInsertQuery(querymail, mailinfo, vb);
//    LOGT("CLogicDataTask::DBSendMail  " << querymail.str().c_str());
//    mysqlpp::SimpleResult res = querymail.execute();
//    if(!res)
//    {
//        send.ret = 3;
//    }
//    else
//    {
//        send.mailinfo = recv->mailinfo;
//        send.mailinfo.mailId = (uint32_t)res.insert_id();
//    }
//    PutSendBuf(&send, sizeof(send));
//
//    return true;
//}
//
//bool DelaySaveCmdQueue::DBDeleteMail(Cmd::t_Data_Delete_Mail_Req *recv)
//{
//    mysqlpp::Query query = DelayDBConnection::instance()->query();
//    query << "delete from MAIL where PLAYERID  =  " << recv->playerId << " and ( ID = " << recv->mailId[0];
//    for (uint32_t i = 1; i < recv->num; ++i)
//    {
//        query << " or ID = " << recv->mailId[i];
//    }
//    query << " );";
//
//    LOGT("DelaySaveCmdQueue::DBDeleteMail " << query.str().c_str());
//
//    mysqlpp::SimpleResult res = query.execute();
//    if (!res)
//    {
//        LOGF(" CLogicDataTask::DBDeleteMail" << query.str().c_str());
//        m_delMailErrorCmdQueue[recv->playerId].push_back(*recv);
//    }
//
//    return true;
//}
//
//bool DelaySaveCmdQueue::DBGetMailList(Cmd::t_Data_Get_Mail_List_Req *recv)
//{
//    mysqlpp::Query query = DelayDBConnection::instance()->query();
//    query << "select * from MAIL where PLAYERID  =  " << recv->playerId << " ;";
//    LOGT("Cmd::PARA_DATA_GET_MAIL_LIST_REQ " << query.str().c_str());
//
//    std::vector<SqlMail> result;
//    query.storein(result);
//    uint32_t more = 0;
//    Cmd::t_Data_Delete_Mail_Req deletemail;
//    deletemail.playerId = recv->playerId;
//    if (result.empty())
//    {
//        Cmd::t_Data_Get_Mail_List_Res send;
//        send.playerId = recv->playerId;
//        send.num = 0;
//        PutSendBuf(&send, send.Size());
//    }
//    else
//    {        
//        Cmd::t_Data_Get_Mail_List_Res *send = NULL;
//        ServerCmdBuffer(send);
//        send->playerId = recv->playerId;
//        uint32_t i = 0;
//        if (result.size() > MAIL_MAX_COUNT)
//        {
//            more = i = (uint32_t)result.size() - MAIL_MAX_COUNT;
//        }
//        for (uint32_t j = 0; i < result.size(); ++i, ++j)
//        {
//            if (CDelayTimeTick::currentTime.sec() - (uint32_t)result[i].createTime > MAIL_MAX_LEFT_TIME && deletemail.num < MAIL_MAX_COUNT)
//            {
//                deletemail.mailId[deletemail.num++] = result[i].id;
//            }
//            else
//            {
//                ++send->num;
//                ((Cmd::ServerMailInfo*)send->data)[j].mailId = result[i].id;
//                ((Cmd::ServerMailInfo*)send->data)[j].itemType = result[i].itemType;
//                ((Cmd::ServerMailInfo*)send->data)[j].itemId = result[i].itemId;
//                ((Cmd::ServerMailInfo*)send->data)[j].itemCount = result[i].itemCount;
//                ((Cmd::ServerMailInfo*)send->data)[j].createTime = result[i].createTime;
//                strncpy(((Cmd::ServerMailInfo*)send->data)[j].title, result[i].title.c_str(), MAIL_TITLE_LENGTH - 1);
//                strncpy(((Cmd::ServerMailInfo*)send->data)[j].content, result[i].content.c_str(), MAIL_CONTENT_LENGTH - 1);
//                strncpy(((Cmd::ServerMailInfo*)send->data)[j].sendName, result[i].sendName.c_str(), MAX_PLAYER_NAME - 1);
//                strncpy(((Cmd::ServerMailInfo*)send->data)[j].sendAccount, result[i].sendAccount.c_str(), MAX_ACCOUNT_LENGHT - 1);
//            }
//        }
//        PutSendBuf(send, send->Size());
//    }
//
//    if (more)
//    {
//        for (uint32_t j = 0; j < more && deletemail.num < MAIL_MAX_COUNT; ++j)
//        {
//            deletemail.mailId[deletemail.num++] = result[j].id;
//        }
//    }
//    if (deletemail.num)
//        DBDeleteMail(&deletemail);
//
//    return true;
//}

