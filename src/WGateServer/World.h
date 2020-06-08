#ifndef _WORLD_H_
#define _WORLD_H_

#include "Sys.h"
#include "Singleton.h"
#include "parameters.h"

// Common data
namespace game
{


    void InitGameGlobalParameters();
};


class World : public CSingleton<World>
{
public:
    World();
    ~World();

    bool Init();


private:
};


#endif


