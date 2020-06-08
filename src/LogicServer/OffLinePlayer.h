#ifndef _OFFLINEPLAYER_H_
#define _OFFLINEPLAYER_H_

#include "Lock.h"
#include "Singleton.h"
//
class LogicPlayer;

class COffLinePLayerManager : public CSingleton<COffLinePLayerManager>
{
public:
    inline void Lock()
    {
        m_lock.Lock();
    }
    inline void UnLock()
    {
        m_lock.UnLock();
    }

    void AddOffPlayer(LogicPlayer *);
    void RemoveOffPlayer(LogicPlayer *);
    void RemoveOffPlayer(uint64_t);
    LogicPlayer *GetOffPlayerById(uint64_t id);

private:

private:
    std::map<uint64_t, LogicPlayer *> m_offPlayers;

    CMutex m_lock;
};


#endif
