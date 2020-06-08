//#include "PollActivityManager.h"
//#include "TimeTick.h"
//#include "./LuaCpp/LuaScriptPollActivity.h"
//#include "Defs.h"
//#include "LuaScriptManager.h"
//#include "DBConnectClient.h"
//
//extern int tolua_LuaInit_open (lua_State* tolua_S);
//
////PollActivity
//PollActivity::PollActivity(const PollActivityConfigData *data)
//    :m_data(data), m_status(PollActivityStatus_None), m_startTime(0), m_init(false), m_needDel(false), m_needSave(false)
//{
//
//}
//
//bool PollActivity::Update(uint64_t curTime)
//{
//    if (!m_data)
//    {
//        //LuaScriptManager::instance()->CallRTVoid("TextActivityUpdate");
//        //int a = 0;
//        //LuaScriptManager::instance()->CallRT("GetPlayerMapValueById", 4, a);
//        //LOGE("PollActivity::Update a = " << a);
//    }
//    else
//    {
//        if (m_data->beginTime <= curTime && m_data->clearTime >= curTime)
//        {
//            //LuaScriptManager::instance()->CallRTVoid(m_data->updateFun.c_str());
//            do
//            {
//                if (curTime < m_data->endTime)
//                {
//                    if (!m_init && PollActivityStatus_None == m_status)
//                    {
//                        Init(curTime);
//                        break;
//                    }
//
//                    if (PollActivityStatus_Start == m_status)
//                        UpdateImp(curTime);
//                }
//
//                if (curTime >= m_data->endTime && m_status == PollActivityStatus_Start)
//                {
//                    EndImp(curTime);
//                    m_status = PollActivityStatus_End;
//                    Save();
//                }
//
//                if (curTime >= m_data->clearTime && m_status != PollActivityStatus_None)
//                {
//                    ClearImp(curTime);
//                    m_status = PollActivityStatus_None;
//                    m_needDel = true;
//                    Save();
//                }
//            }
//            while (false);
//        }
//
//        if (m_status == PollActivityStatus_Start && curTime >= m_data->endTime)
//        {
//            EndImp(curTime);
//            m_status = PollActivityStatus_End;
//            Save();
//        }
//
//        if (m_status != PollActivityStatus_None && curTime >= m_data->clearTime)
//        {
//            ClearImp(curTime);
//            m_status = PollActivityStatus_None;
//            m_needDel = true;
//            Save();
//        }
//    }
//
//    return true;
//}
//
//bool PollActivity::Update5Sec()
//{
//    //if (m_needSave)
//    //{
//    //    Save();
//    //}
//
//    return true;
//}
//
//bool PollActivity::Init(uint64_t curTime)
//{
//    if (m_init)
//        return true;
//
//    if (!m_data)
//    {
//        //LuaScriptManager::instance()->CallRTVoid("TextActivityInit");
//    }
//    else
//    {
//        if (m_data->beginTime <= curTime && m_data->clearTime >= curTime)
//        {
//            //LuaScriptManager::instance()->CallRTVoid(m_data->updateFun.c_str());
//            InitImp(curTime);
//            m_init = true;
//
//            Cmd::t_Data_Get_PollActivity_Data send;
//            send.activityId = m_data->id;
//            SendToDB(&send, sizeof(send));
//        }
//    }
//
//    return true;
//}
//
//void PollActivity::Start(uint64_t curTime)
//{
//    StartImp(curTime);
//    Save();
//
//    return;
//}
//
//bool PollActivity::SerializePlayer(uint8_t* buffer, uint32_t &size, LogicPlayer *player)
//{
//    BuffWriteInt(buffer, size, Id());
//    size -= UINT32_LEN;
//
//    BuffWriteInt(buffer, size, Type());
//    size -= UINT32_LEN;
//    
//    uint32_t *pLen = (uint32_t *)buffer;
//    BuffWriteMoveLen(buffer, size, UINT32_LEN);
//
//    SerializePlayerImp(buffer, size, player);
//
//    *pLen = size;
//
//    return true;
//
//}
//uint32_t PollActivity::UnSerializePlayer(uint8_t* buffer, LogicPlayer *player)
//{
//    uint32_t length = 0;
//    BuffLoadInt(buffer, length, length);
//    uint32_t ret = length + UINT32_LEN;
//
//    UnSerializePlayerImp(buffer, length, player);
//
//
//    return ret;
//}
//
//void PollActivity::DBGetPollActivityDataCallBack(Cmd::t_Data_Get_PollActivity_Data_Res *recv)
//{
//    if (!m_data)
//        return;
//
//    DBGetPollActivityDataCallBackImp(recv);
//
//    //if (CMD_LONG_MESSAGE_SIGN_END == recv->end)
//    {
//        m_status = recv->status;
//        m_startTime = recv->startTime;
//
//        uint64_t curTime = CImpServerTimeTick::currentTime.sec();
//        if (recv->startTime < m_data->beginTime)
//        {
//            if (curTime >= m_data->beginTime && curTime <= m_data->endTime)
//            {
//                m_status = PollActivityStatus_Start;
//                m_startTime = m_data->beginTime;
//                Start(curTime);
//            }
//        }
//    }
//    
//    return;
//}
//
////protected virtual 
//bool PollActivity::SerializePlayerImp(uint8_t* buffer, uint32_t &size, LogicPlayer *player)
//{
//    BuffWriteInt(buffer, size, POLLACTIVITYVERSION_1_1);
//
//    return true;
//}
//
//uint32_t PollActivity::UnSerializePlayerImp(uint8_t* buffer, uint32_t length, LogicPlayer *player)
//{
//    BuffLoadMoveLen(buffer, length, UINT32_LEN);    //version
//
//    return length;
//}
//
//void PollActivity::Save()
//{
//    Cmd::t_Data_Save_PollActivity_Data send;
//    send.activityId = Id();
//    send.startTime = m_startTime;
//    send.status = m_status;
//
//    SendToDB(&send, sizeof(send));
//    
//    return;
//}
//
////test code begin
//void PollActivity::TestCall()
//{
//    ScriptPollActivity playerproxy(this);
//    int ret = 0;
//    LuaScriptManager::instance()->CallRT("LuaTestActivity", &playerproxy, ret);
//
//    return;
//}
//
//void PollActivity::TestFun1()
//{
//    LOGE("PollActivity::TestFun1 !!!");
//
//    return;
//}
////test code end
//
////PollActivityManager
//bool PollActivityManager::Init()
//{
//    uint64_t curTime = CImpServerTimeTick::currentTime.sec();
//    m_pollActivitys.reserve(10);
//    DataManager<PollActivityConfigData, PollActivityConfig>::iterator itr = PollActivityConfigDataManager::instance()->begin();
//    for (; itr != PollActivityConfigDataManager::instance()->end(); ++itr)
//    {
//        if (itr->beginTime <= curTime + THIRTY_DAY_SEC && itr->clearTime + ONE_WEEK_SEC > curTime)
//        {
//            PollActivity *p = MakePollActivity(itr->type, &*itr);
//            if (p)
//                m_pollActivitys.push_back(p);
//        }
//    }
//
//    for (uint32_t i = 0; i < m_pollActivitys.size(); ++i)
//    {
//        m_pollActivitys[i]->Init(curTime);
//    }
//
//    return true;
//}
//
//bool PollActivityManager::Update()
//{
//    uint64_t curTime = CImpServerTimeTick::currentTime.sec();
//    for (uint32_t i = 0; i < m_pollActivitys.size(); ++i)
//    {
//        m_pollActivitys[i]->Update(curTime);
//    }
//
//    for (std::vector<PollActivity *>::iterator itr = m_pollActivitys.begin(); itr != m_pollActivitys.end();)
//    {
//        if ((*itr)->Delete())
//        {
//            itr = m_pollActivitys.erase(itr);
//        }
//        else
//            ++itr;
//    }
//
//    return true;
//}
//
//bool PollActivityManager::Update5Sec()
//{
//    for (uint32_t i = 0; i < m_pollActivitys.size(); ++i)
//    {
//        m_pollActivitys[i]->Update5Sec();
//    }
//
//    return true;
//}
//
//bool PollActivityManager::SerializePlayer(uint8_t* buffer, uint32_t &size, LogicPlayer *player)
//{
//    uint32_t *pLen = (uint32_t *)buffer;
//    BuffWriteMoveLen(buffer, size, UINT32_LEN);
//
//    BuffWriteInt(buffer, size, POLLACTIVITYMANAGERVERSION_1_1);
//
//    BuffWriteInt(buffer, size, (uint32_t)m_pollActivitys.size());
//    for (uint32_t i = 0; i < m_pollActivitys.size(); ++i)
//    {
//        uint32_t len = 0;
//        m_pollActivitys[i]->SerializePlayer(buffer, len, player);
//        BuffWriteMoveLen(buffer, size, len);
//    }
//
//    *pLen = size;
//
//    return true;
//}
//
//uint32_t PollActivityManager::UnSerializePlayer(uint8_t* buffer, LogicPlayer *player)
//{
//    uint32_t length = 0;
//
//    BuffLoadInt(buffer, length, length);
//    uint32_t ret = length + UINT32_LEN;
//
//    BuffLoadMoveLen(buffer, length, UINT32_LEN);    //version
//
//    uint32_t count = 0;
//    BuffLoadInt(buffer, length, count);
//    for (uint32_t i = 0; i < count; ++i)
//    {
//        uint32_t id = 0;
//        BuffLoadInt(buffer, length, id);
//        uint32_t type = 0;
//        BuffLoadInt(buffer, length, type);
//        uint32_t len = 0;
//        for (uint32_t i = 0; i < m_pollActivitys.size(); ++i)
//        {
//            if (m_pollActivitys[i]->Id() == id && m_pollActivitys[i]->Type() == type)
//                len = m_pollActivitys[i]->UnSerializePlayer(buffer, player);
//
//            break;
//        }
//
//        if (!len)
//        {
//            len = *(uint32_t *)buffer;
//        }
//
//        BuffLoadMoveLen(buffer, length, len);
//    }
//
//    return ret;
//}
//
//void PollActivityManager::DBGetPollActivityDataCallBack(Cmd::t_Data_Get_PollActivity_Data_Res *recv)
//{
//    for (uint32_t i = 0; i < m_pollActivitys.size(); ++i)
//    {
//        if (recv->activityId == m_pollActivitys[i]->Id())
//        {
//            m_pollActivitys[i]->DBGetPollActivityDataCallBack(recv);
//
//            return;
//        }
//    }
//
//    return;
//}
//
//PollActivity *PollActivityManager::FindPollActivityById(uint32_t id)
//{
//    for (uint32_t i = 0; i < m_pollActivitys.size(); ++i)
//    {
//        if (id == m_pollActivitys[i]->Id())
//        {
//            return m_pollActivitys[i];
//        }
//    }
//
//    return NULL;
//}
//
//PollActivity *PollActivityManager::MakePollActivity(uint32_t type, const PollActivityConfigData *data)
//{
//    if (type < m_createPollActivitys.size())
//        return m_createPollActivitys[type](data);
//
//    return NULL;
//}
//
//
