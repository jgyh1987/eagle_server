#include "LuaScriptLogicPlayer.h"
#include "TimeTick.h"
#include "../LuaScriptManager.h"

ScriptLogicPlayer::~ScriptLogicPlayer()
{
}

unsigned long long ScriptLogicPlayer::GetID()
{
    if( m_owner )
        return m_owner->Id();

    return 0;
}

void ScriptLogicPlayer::SendMail(char *title, char *content)
{
    if (m_owner)
    {
        //Cmd::t_Data_Send_Mail_Req send;
        //strncpy(send.account, m_owner->Account(), MAX_ACCOUNT_LENGHT - 1);
        //send.mailinfo.itemType = 3;
        //send.mailinfo.itemId = 1;
        //send.mailinfo.itemCount = 10;
        //send.mailinfo.createTime = CImpServerTimeTick::currentTime.sec();
        //strncpy(send.mailinfo.title, title, MAIL_TITLE_LENGTH - 1);
        //strncpy(send.mailinfo.content, content, MAIL_CONTENT_LENGTH - 1);
        //MailManager::instance()->SendMail(&send);
    }

    return ;
}

