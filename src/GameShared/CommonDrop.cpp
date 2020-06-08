#include "CommonDrop.h"
#include "Random.h"
#include "LogicDataManager.h"

bool CommonDrop::GetDommonDropItem(uint32_t id, std::vector<TypeIdCount> &items)
{
    CommonDropConfigData *data = CommonDropConfigDataManager::instance()->get(id);
    if (!data)
        return false;

    for (uint32_t i = 0; i < data->randomNum; ++i)
    {
        CommonDrop::GetDommonDropItemOnce(data, items);
    }

    return true;
}

std::vector<uint32_t> *CommonDrop::GetDommonDropId(uint32_t id ,uint32_t createRoleId)
{
    //GuideUniqueItemConfigData *jobData = GuideUniqueItemConfigDataManager::instance()->get(id);
    //if (jobData)
    //{

    //    std::map< uint32_t, std::vector<uint32_t> >::iterator iter = jobData->guideReward.find(createRoleId);
    //    if (iter != jobData->guideReward.end() && iter->second.size())
    //    {
    //        return &iter->second;
    //    }
    //        

    //    std::map< uint32_t, std::vector<uint32_t> >::iterator alliter = jobData->guideReward.find(JOB_TYPE_NONE);
    //    if (alliter != jobData->guideReward.end() && alliter->second.size())
    //    {
    //        return &alliter->second;
    //    }
    //}
    return NULL;
}

bool CommonDrop::GetDommonDropItemOnce(CommonDropConfigData *data, std::vector<TypeIdCount> &items)
{
    uint32_t random = CRandom::RandomBetween(0, data->allRate);
    for (uint32_t i = 0; i < data->drops.size(); ++i)
    {
        if (random < data->drops[i].parentRate)
        {
            uint32_t random1 = CRandom::RandomBetween(0, data->drops[i].allRate);
            for (uint32_t j = 0; j < data->drops[i].drops.size(); ++j)
            {
                if (random1 < data->drops[i].drops[j].rate)
                {
                    TypeIdCount info;
                    info.id = data->drops[i].drops[j].id;
                    info.type = data->drops[i].drops[j].type;
                    info.count = CRandom::RandomBetween(data->drops[i].drops[j].minNum, data->drops[i].drops[j].maxNum + 1);

                    if (!info.count)
                        return false;

                    items.push_back(info);
                
                    return true;
                }

                random1 -= data->drops[i].drops[j].rate;
            }
        }

        random -= data->drops[i].parentRate;
    }

    return false;
}




