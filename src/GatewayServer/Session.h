#ifndef _SESSIONACCOUNT_H_ 
#define    _SESSIONACCOUNT_H_

#include "CObject.h"

class GatewayPlayer;
class CGatewayTask;

struct AccountSession
{
public:
    AccountSession(char *session, char *account);
    ~AccountSession();

    void TickOldPlayer();
public:
    std::string account;
    std::string session;
    GatewayPlayer *player;
    CGatewayTask *task;
};



#endif    


