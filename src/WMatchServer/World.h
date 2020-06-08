#ifndef _WORLD_H_
#define _WORLD_H_

#include "Sys.h"
#include "Singleton.h"
#include "parameters.h"
#include "ImpService.h"
#include "ServerCommand.h"
#include "ConstructInPlace.h"

// Common data
namespace game
{
    extern uint32_t g_leitaiMinPoint;
    extern uint32_t g_pvpWinCoin;
    extern uint32_t g_pvpLoseCoin;
    extern uint32_t g_dayMaxCoin;
    extern uint32_t g_pvpMatchTime;
    extern uint32_t g_pvpMatchPoint;
    void InitGameGlobalParameters();
};

class World : public CSingleton<World>
{
public:
    World();
    ~World();

    template<class cmd>
    unsigned char* ServerCmdBuffer(cmd* &name);

private:

    buffercmdqueue m_sendBuffer;
};

template<class cmd>
unsigned char* World::ServerCmdBuffer(cmd* &name) {
    m_sendBuffer.ReSet();
    m_sendBuffer.WrReserve(SERVER_COMMAND_MAX_LENGTH);
    name = (cmd *)(m_sendBuffer.WrBuf());
    constructInPlace(name);
    return m_sendBuffer.WrBuf();
}


#endif


