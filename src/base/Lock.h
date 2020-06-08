#ifndef _MUTEX_H_
#define _MUTEX_H_

#include "Noncopyable.h"
#include "Sys.h"

namespace eagle
{

//����� 
class CMutex : private CNoncopyable
{
    public:

        CMutex()
        {
            uv_mutex_init(&m_mutex);
        }

        ~CMutex() 
        { 
            uv_mutex_destroy(&m_mutex); 
        }

        void Lock() 
        { 
            uv_mutex_lock(&m_mutex); 
        }

        void UnLock() 
        { 
            uv_mutex_unlock(&m_mutex); 
        }

        bool TryLock() 
        { 
            return (uv_mutex_trylock(&m_mutex) == 0); 
        }

        uv_mutex_t * GetMutex()
        {
            return &m_mutex;
        }

    private:

        uv_mutex_t m_mutex;

};

//��Զ������ 
class CMutex_Auto_Lock : private CNoncopyable
{
    public:

        CMutex_Auto_Lock(CMutex *m) 
            : m_pLock(m) 
        { 
            m_pLock->Lock(); 
        }

        ~CMutex_Auto_Lock() 
        { 
            m_pLock->UnLock(); 
        }

    private:
        CMutex *m_pLock;

};

//����� 
class CMutex_Try_Lock : private CNoncopyable
{
    public:
        CMutex_Try_Lock(CMutex *m) 
            : m_pLock(m), m_bLocked(false) 
        { 
            m_bLocked = m_pLock->TryLock(); 
        }

        ~CMutex_Try_Lock() 
        { 
            if (m_bLocked) 
                m_pLock->UnLock(); 
        }

        bool IsLocked() const 
        { 
            return m_bLocked; 
        }

    private:

        CMutex *m_pLock;

        bool m_bLocked;
};

template <bool locker = true>
class CMutexT
{
    public:

        void Lock() 
        { 
            m_lock.Lock(); 
        }


        void UnLock() 
        { 
            m_lock.UnLock(); 
        }
    private:
        CMutex m_lock;
};


template <>
class CMutexT<false>
{
    public:

        void Lock() 
        { 
        }

        void UnLock() 
        { 
        }
};

//����� 
class CCond : private CNoncopyable
{
    public:
        CCond()
        {
            uv_cond_init(&m_cond);
        }

        ~CCond(void)
        {
            uv_cond_destroy(&m_cond);
        }

        void Signal()
        {
            uv_cond_signal(&m_cond);
        }

        void BroadCast()
        {
            uv_cond_broadcast(&m_cond);
        }

        void Wait(CMutex* pMutex)
        {
            uv_cond_wait(&m_cond, pMutex->GetMutex());
        }

        int Wait(CMutex* pMutex, uint64_t timeout)
        {
            return uv_cond_timedwait(&m_cond, pMutex->GetMutex(), timeout);
        }

    private:
        uv_cond_t m_cond;
};

//��ź�� 
class CSem : private CNoncopyable
{
    public:
        CSem(int initValue = 0)
        {
            uv_sem_init(&m_sem, initValue);
        }

        ~CSem(void)
        {
            uv_sem_destroy(&m_sem);
        }

        void Post()
        {
            uv_sem_post(&m_sem);
        }

        void Wait()
        {
            uv_sem_wait(&m_sem);
        }

        bool TryWait()
        {
            return uv_sem_trywait(&m_sem) == 0;
        }

    private:
        uv_sem_t m_sem;
};

//��д� 
class CRWLock : private CNoncopyable
{
    public:
        CRWLock()
        {
            uv_rwlock_init(&m_rwLock);
        }

        ~CRWLock(void)
        {
            uv_rwlock_destroy(&m_rwLock);
        }

        void ReadLock()
        {
            uv_rwlock_rdlock(&m_rwLock);
        }

        void ReadUnLock()
        {
            uv_rwlock_rdunlock(&m_rwLock);
        }

        bool ReadTryLock()
        {
            return uv_rwlock_tryrdlock(&m_rwLock) == 0;
        }

        void WriteLock()
        {
            uv_rwlock_wrlock(&m_rwLock);
        }

        void WriteUnLock()
        {
            uv_rwlock_wrunlock(&m_rwLock);
        }

        bool WriteTryLock()
        {
            return uv_rwlock_trywrlock(&m_rwLock) == 0;
        }

    private:
        uv_rwlock_t m_rwLock;
};

//��Զ���д  ��� 
class CRLock_Auto_Lock : private CNoncopyable
{
        public:

                CRLock_Auto_Lock(CRWLock *m)
                        : m_pLock(m)
                {
                        m_pLock->ReadLock();
                }

                ~CRLock_Auto_Lock()
                {
                        m_pLock->ReadUnLock();
                }

        private:

                CRWLock *m_pLock;

};

//��Զ���д д� 
class CWLock_Auto_Lock : private CNoncopyable
{
        public: 

                CWLock_Auto_Lock(CRWLock *m)
                        : m_pLock(m)
                {
                        m_pLock->WriteLock();
                }

                ~CWLock_Auto_Lock()
                {
                        m_pLock->WriteUnLock();
                }

        private:
                CRWLock *m_pLock;

};

//�դ� 
class CBarrier : private CNoncopyable
{
    public:
        CBarrier(int count)
        {
            uv_barrier_init(&m_barrier, count);
        }

        ~CBarrier(void)
        {
            uv_barrier_destroy(&m_barrier);
        }

        void Wait()
        {
            uv_barrier_wait(&m_barrier);
        }

    private:
        uv_barrier_t m_barrier;
};

};

#endif

