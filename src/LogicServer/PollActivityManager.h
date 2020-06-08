#ifndef _POLLACTIVITY_H_ 
#define    _POLLACTIVITY_H_

#include "StringTool.h"
#include "LogicDataManager.h"
#include "LuaState.h"
#include "Singleton.h"
#include "Noncopyable.h"
#include "LogicDataCommand.h"

class LogicPlayer;
class FriendManager;

#define POLLACTIVITYMANAGERVERSION_1_1        1
#define POLLACTIVITYVERSION_1_1        1

enum PollActivityType
{
    PollActivityType_None = 0,
    PollActivityType_Test = 1,


    PollActivityType_Max
};

enum PollActivityStatus
{
    PollActivityStatus_None = 0,
    PollActivityStatus_Start,

    PollActivityStatus_End,        //活动结束 排行榜和领奖仍然持续
};

class PollActivity
{
public:
//    PollActivity(const PollActivityConfigData *);
//    static PollActivity *NewPollActivity(const PollActivityConfigData *data)
//    {
//        return new PollActivity(data);
//    }
//
//    bool Update(uint64_t curTime);
//    bool Update5Sec();
//    bool Init(uint64_t curTime);
//    void Start(uint64_t curTime);
//    bool SerializePlayer(uint8_t* buffer, uint32_t &size, LogicPlayer *player);
//    uint32_t UnSerializePlayer(uint8_t* buffer, LogicPlayer *player); 
//    void DBGetPollActivityDataCallBack(Cmd::t_Data_Get_PollActivity_Data_Res *recv);
//    void Save();
//
//    //test code begin
//    void TestCall();
//    void TestFun1();
//    //test code end
//
//public:
//    inline uint32_t Status()
//    {
//        return m_status;
//    }
//
//    inline bool Delete()
//    {
//        return m_needDel;
//    }
//
//    inline uint64_t Id()
//    {
//        if (m_data)
//            return m_data->id;
//
//        return 0;
//    }
//
//    inline uint32_t Type()
//    {
//        if (m_data)
//            return m_data->type;
//
//        return 0;
//    }
//
//protected:
//    virtual void StartImp(uint64_t curTime){}
//    virtual bool InitImp(uint64_t curTime){return true;}
//    virtual void UpdateImp(uint64_t curTime){}
//    virtual void EndImp(uint64_t curTime){}
//    virtual void ClearImp(uint64_t curTime){}
//    virtual bool SerializePlayerImp(uint8_t* buffer, uint32_t &size, LogicPlayer *player);
//    virtual uint32_t UnSerializePlayerImp(uint8_t* buffer, uint32_t len, LogicPlayer *player); 
//    virtual void DBGetPollActivityDataCallBackImp(Cmd::t_Data_Get_PollActivity_Data_Res *recv){}
//
//protected:
//    const PollActivityConfigData *m_data;
//    uint32_t m_status;
//    uint64_t m_startTime;
//    bool m_init;
//    bool m_needDel;
//    bool m_needSave;
};

class PollActivityManager : public CSingleton< PollActivityManager >, public CNoncopyable
{
public:
//    PollActivityManager()
//    {
//        m_createPollActivitys.resize(PollActivityType_Max);
//        m_createPollActivitys[PollActivityType_None] = &PollActivity::NewPollActivity;
//        m_createPollActivitys[PollActivityType_Test] = &PollActivity::NewPollActivity;
//    }
//    ~PollActivityManager()
//    {
//        for (uint32_t i = 0; i < m_pollActivitys.size(); ++i)
//        {
//            delete m_pollActivitys[i];
//        }
//        m_pollActivitys.clear();
//        
//    }
//
//    bool Init();
//    bool Update();
//    bool Update5Sec();
//    bool SerializePlayer(uint8_t* buffer, uint32_t &size, LogicPlayer *player);
//    uint32_t UnSerializePlayer(uint8_t* buffer, LogicPlayer *player); 
//    void DBGetPollActivityDataCallBack(Cmd::t_Data_Get_PollActivity_Data_Res *recv);
//    PollActivity *FindPollActivityById(uint32_t id);
//
//private:
//    PollActivity *MakePollActivity(uint32_t type, const PollActivityConfigData *data);
//
//private:
//    typedef PollActivity *(* CreatePollActivity)(const PollActivityConfigData *);
//
//    std::vector<PollActivity *> m_pollActivitys;
//    std::vector<CreatePollActivity> m_createPollActivitys;
};


#endif    


