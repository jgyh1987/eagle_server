#ifndef _BASESERVICE_H_
#define _BASESERVICE_H_

#include "Sys.h"
#include "Noncopyable.h"
#include "Thread.h"

namespace eagle
{

enum EBaseServerStutas
{
    BASESERVER_NONE,
    BASESERVER_SYNC,
    BASESERVER_VERIFY,
    BASESERVER_FINAL
};

class CBaseServer : private CNoncopyable, public CThread
{
//static
public:
    static void idle_cb(uv_idle_t* handle);
    static void AsyncCB(uv_async_t* handle);//async 

public:
    CBaseServer(const std::string &name);
    virtual ~CBaseServer();

    bool Init();
    void Final();
    void SendFianl();
    void Run();

    //
    bool Start();

public:
    virtual bool Verify();
    //return false do exit run
    virtual bool CallBack();

public:
    void SetVerify(EBaseServerStutas status){m_eIsVerify = status;}
    inline EBaseServerStutas GetVerify(){return m_eIsVerify;}
    //one sec step and GetVerify() == BASESERVER_SYNC  do  call
    
protected:
    void CloseInl();

private:
    uv_loop_t m_loop;
    uv_idle_t m_idle_handle;
    uv_signal_t m_sig_int; 
    uv_signal_t m_sig_kill; 
    uv_signal_t m_sig_pipe;
    uv_async_t m_async_handle;

    int m_loopStatus;
    bool m_bIsClosed;
    EBaseServerStutas m_eIsVerify;
    bool m_bIsUserAskForClosed;
};

};

#endif

