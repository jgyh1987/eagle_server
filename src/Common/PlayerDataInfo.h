#ifndef _PLAYER_DATA_INFO_H_
#define _PLAYER_DATA_INFO_H_

#include "CommonType.h"

enum ITEM_CHANGE_STATUS
{
    ITEM_CHANGE_STATUS_LOAD,
    ITEM_CHANGE_STATUS_NEW,
    ITEM_CHANGE_STATUS_ADD,
    ITEM_CHANGE_STATUS_SUB,
    ITEM_CHANGE_STATUS_DEL,
    ITEM_CHANGE_STATUS_MOVE,
    ITEM_CHANGE_STATUS_UPDATE
    
};

struct ItemChangeData
{
    uint32_t len;
    uint64_t itemId;
    uint64_t roleId;
    uint32_t type;
    uint64_t configId;
    uint64_t count;
    uint64_t uid;
    uint32_t bagType;
    uint32_t change;//ITEM_CHANGE_STATUS 
    char data[1];

    ItemChangeData()
    {
        uid = 0;
        type = 0;
        configId = 0;
        count = 0;
        itemId = 0;
        roleId = 0;
        len = 0;
        bagType = OBJECT_BAG;
        change = ITEM_CHANGE_STATUS_LOAD;
    }

    uint32_t Size()
    {
        return sizeof(ItemChangeData) + len;
    }
};

//Send Mail
struct ServerMailInfo
{
    uint32_t mailId;
    //uint64_t playerId;
    uint32_t itemType;
    uint64_t itemId;
    uint32_t itemCount;
    uint64_t createTime;
    char title[MAIL_TITLE_LENGTH];
    char content[MAIL_CONTENT_LENGTH];
    char sendName[MAX_PLAYER_NAME];
    char sendAccount[MAX_ACCOUNT_LENGHT];

    ServerMailInfo()
    {
        memset(this, 0, sizeof(ServerMailInfo));
    }
};



#endif

