#ifndef _COMMONDROP_H_ 
#define    _COMMONDROP_H_

#include "Sys.h"
#include "CommonType.h"

struct CommonDropConfigData;

class CommonDrop
{
public:
    static bool GetDommonDropItem(uint32_t id, std::vector<TypeIdCount> &);
    static std::vector<uint32_t>* GetDommonDropId(uint32_t id ,uint32_t createRoleId);

private:
    static bool GetDommonDropItemOnce(CommonDropConfigData *data, std::vector<TypeIdCount> &);
};



#endif    


