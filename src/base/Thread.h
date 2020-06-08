#ifndef _EAGLE_THREAD_H_
#define _EAGLE_THREAD_H_

#include "Sys.h"
#include "Noncopyable.h"
#include "Lock.h"
#include "Entry.h"

namespace eagle
{

class CThread
{
//static
public:
    /*
    * \brief 线程号
    * */
    static uint32_t GetCurrentThreadID()
    {
        return uv_thread_id();
    }

    /*
    * \brief 线程挂起一段时间
    * \param 单位s
    * */
    static void Sleep(const long sec)
    {
        uv_thread_sleep(sec * 1000); 
    }

    /*
    * \brief 线程挂起一段时间
    * \param 单位ms
    * */
    static void MSleep(const long msec)
    {
        uv_thread_sleep(msec);
    }

    /*
    * \brief 线程主回调函数 
    * */
    static void *ThreadFunc(void *arg);

public:
    CThread(const std::string&name=std::string("CThread"),bool joinable=true)
        :m_strThreadName(name),m_vbAlive(false),m_vbComplete(false),m_thread(0),m_bJoinable(joinable)
    {}

    virtual ~CThread(){}

    virtual bool Init() = 0;
    virtual void Final();
    virtual void SendFianl();
    virtual void Run()=0;

public:
    /*
    * \brief 是否已经启动 
    * */
    const bool IsAlive()const;

    /*
    * \brief 线程是否结束
    * */
    const bool IsFinal()const;

    /*
    * \brief 开启线程 
    * */
    bool Start();

    /*
    * \brief 关闭线程 
    * */
    void Close();

    bool operator == (const CThread &other) const
    {
        return (uv_thread_equal(&m_thread, &other.m_thread) != 0);
    }

    bool operator != (const CThread &other) const
    {
        return !operator==(other);
    }

    inline const std::string& GetThreadName()const
    {
        return m_strThreadName;
    }

protected:
    /*
    * \brief 是否可挂起 
    * */
    const bool IsJoinable()const;

    /*
    * \brief 挂起线程
    * */
    void Join();

protected:
    std::string m_strErrMsg;
    CMutex m_mLock;                        /// 互斥锁
    std::string m_strThreadName;        /// 线程名字

private:
    CCond m_cond;                        /// 条件变量
    volatile bool m_vbAlive;            // 是否已经启动
    volatile bool m_vbComplete;            /// 是否结束
    uv_thread_t m_thread;                /// 当前线程id
    bool m_bJoinable;                    /// 是否可挂起

    uv_thread_cb m_pThreadFun;
};


class CThreadGroup : private CNoncopyable
{
public:
    typedef std::vector<CThread*> Thread_Container;
    CThreadGroup();
    ~CThreadGroup();
        
    /*
        * \brief 添加线程
        * */
    void Add(CThread *thread);
        
    /*
        * \brief 获取线程
        * */
    CThread* GetByIndex(const Thread_Container::size_type index);
    CThread* operator[] (const Thread_Container::size_type index);

    /*
        * \brief 挂起所有线程 
        * */
    void JoinAll();
        
    /*
        * \brief 线程回调
        * */
    template< typename MyEntry >
    void ExecAll( CEntryCallback< MyEntry > &cb)
    {
        CRLock_Auto_Lock autoLock(&m_rwLock);
        for(Thread_Container::iterator it = m_vecThreads.begin(); it != m_vecThreads.end(); ++it)
            cb.exec(*it);
    }

    /*
        * \brief 线程数量 
        * */
    const Thread_Container::size_type size()
    {
        CRLock_Auto_Lock autoLock(&m_rwLock);
        return m_vecThreads.size();
    }
private:
    Thread_Container m_vecThreads;
    CRWLock m_rwLock;
};

};

#endif
