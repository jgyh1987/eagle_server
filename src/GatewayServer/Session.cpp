#include "Session.h"
#include "GatewayTaskManager.h"
#include "PlayerManager.h"

AccountSession::AccountSession(char *s, char *a)
    :session(s), account(a), player(NULL), task(NULL)
{

}
  
AccountSession::~AccountSession()
{

}

void AccountSession::TickOldPlayer()
{
    if (player)
    {
        player->NotifyBeTick(REPEATED_LOGIN_LOGIC);
        PlayerManager::instance()->RemovePlayer(player);
    }

    return;
}

