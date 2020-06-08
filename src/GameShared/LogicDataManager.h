#ifndef _LOGICDATAMANAGER_H_
#define _LOGICDATAMANAGER_H_

#include "Design.h"
#include "Struct.h"
#include "StringTool.h"
#include "Singleton.h"
#include "DataManager.h"
#include "CommonType.h"
#include "Grid.h"
#include "EaglePos.h"
#include "JsonDataLoad.h"

void parsePos(const std::string& param, std::vector< Struct::MapPos >& posVec);

/**
 *  config data init
 */
class LogicDataManager : public CSingleton< LogicDataManager >, public CNoncopyable
{
    public:
        bool Init(std::string &str);

protected:
    
};
//
////PollActivityConfigData
//struct PollActivityConfig
//{};
//
//struct PollActivityConfigData
//{
//    uint64_t id;
//    uint32_t type;
//    uint64_t beginTime;
//    uint64_t endTime;
//    uint64_t clearTime;
//
//    PollActivityConfigData( const PollActivityConfig& base )
//    {
//        fill( base );
//    }
//
//    uint64_t key() const
//    {
//        return id;
//    }
//    void fill( const PollActivityConfig& base );
//
//};
//
//class PollActivityConfigDataManager : public DataManager<PollActivityConfigData, PollActivityConfig>, public CSingleton<PollActivityConfigDataManager>
//{
//};

/*
 * @brief Item
 */
struct ItemConfigData
{
    uint64_t id;
    std::string name;
    uint32_t type;
    uint32_t subtype;
    uint32_t maxStack;
    uint32_t quality;

    ItemConfigData( const design::ItemConfig& base )
    {
        fill( base );
    }

    uint64_t key() const
    {
        return id;
    }
    void fill( const design::ItemConfig& base );
};

class ItemConfigDataManager : public DataManager<ItemConfigData, design::ItemConfig>, public CSingleton<ItemConfigDataManager>
{
};

struct ItemsConfigData
{
    uint64_t id;
    std::string name;
    uint32_t type;
    uint32_t subtype;
    uint32_t maxStack;
    uint32_t quality;

    ItemsConfigData(Json::Value &value)
    {
        fill(value);
    }

    uint64_t key() const
    {
        return id;
    }
    void fill(Json::Value &value);
};

class ItemsConfigDataManager : public JsonDataManager<ItemsConfigData>, public CSingleton<ItemsConfigDataManager>
{
};

struct CommonDropSpecificInfo
{
    uint32_t rate;
    uint64_t id;
    uint32_t type;
    uint32_t minNum;
    uint32_t maxNum;

    CommonDropSpecificInfo()
    {
        memset(this, 0, sizeof(CommonDropSpecificInfo));
    }
};

struct CommonDropSubInfo
{
    uint32_t parentRate;
    uint32_t allRate;
    std::vector<CommonDropSpecificInfo> drops;

    CommonDropSubInfo()
    {
        parentRate = 0;
        allRate = 0;
    }
};

struct CommonDropConfigData
{
    uint64_t id;
    uint32_t randomNum;        //
    uint32_t allRate;
    std::vector<CommonDropSubInfo> drops;
    

    CommonDropConfigData( const design::CommonDropConfig& base )
    {
        fill( base );
    }

    uint64_t key() const
    {
        return id;
    }
    void fill( const design::CommonDropConfig& base );

    void Dump() const;
};

class CommonDropConfigDataManager : public DataManager<CommonDropConfigData, design::CommonDropConfig>, public CSingleton<CommonDropConfigDataManager>
{
};

/*
 * @brief map 
 */
struct MapConfigData
{
    uint64_t id;
	uint32_t type;

    MapConfigData( const design::MapConfig& base )
    {
        fill( base );
    }

    uint64_t key() const
    {
        return id;
    }
    void fill( const design::MapConfig& base );
};

class MapConfigDataManager : public DataManager<MapConfigData, design::MapConfig>, public CSingleton<MapConfigDataManager>
{
};

/*
* @brief Scene
*/

struct SceneConfigData
{
    uint64_t id;
    GridVec2Info gridInfo;

    SceneConfigData(const design::SceneConfig& base)
    {
        fill(base);
    }

    uint64_t key() const
    {
        return id;
    }
    void fill(const design::SceneConfig& base);
};

class SceneConfigDataManager : public DataManager<SceneConfigData, design::SceneConfig>, public CSingleton<SceneConfigDataManager>
{
};

/*
* @brief EagleLandmass
*/
struct LandmassConfigData
{
    uint64_t id;
	std::vector<uint64_t> maps;
	std::vector<uint64_t> scenes;
    GridVec2Info gridInfo;

    LandmassConfigData(const design::LandmassConfig& base)
    {
        fill(base);
    }

    uint64_t key() const
    {
        return id;
    }
    void fill(const design::LandmassConfig& base);
};

class LandmassConfigDataManager : public DataManager<LandmassConfigData, design::LandmassConfig>, public CSingleton<LandmassConfigDataManager>
{
public:

};

/*
 * @brief QuestInfoConfig
 */

struct QuestConfigData
{
    uint64_t id;
    uint32_t type;
	uint32_t client;
    uint32_t initAccept;

    std::vector<ConditionParm> vecCmpCondition;
    std::vector<ConditionParm> preCondition;
    uint64_t acceptQuest;
    uint32_t exp;
    std::vector<ConditionParm> appectActions;
    std::vector<ConditionParm> cmpActions;
    std::vector<ConditionParm> receiveActions;

    QuestConfigData(const design::QuestConfig& base)
    {
        fill(base);
    }

    uint64_t key() const
    {
        return id;
    }
    void fill(const design::QuestConfig& base);
};

class QuestConfigDataManager : public DataManager<QuestConfigData, design::QuestConfig>, public CSingleton<QuestConfigDataManager>
{
public:

};

/*
 * @brief BuffConfig
 */


struct BuffConfigData
{
    uint64_t id;
    uint32_t type;
    uint32_t isDebuff;
    uint32_t priority;
    uint32_t liftTime;
    uint32_t intervalTime;
    uint32_t overLayMax;
    std::vector<TypeValuesInfo> effects;
    std::vector<TypeValuesInfo> triggers;
    uint32_t takeEffectType;            //BUFF 
    std::vector<TypeValuesInfo> entryIntoForce;

    BuffConfigData( const design::BuffConfig& base )
    {
        fill( base );
    }

    uint64_t key() const
    {
        return id;
    }
    void fill( const design::BuffConfig& base );
};

class BuffConfigDataManager : public DataManager<BuffConfigData, design::BuffConfig>, public CSingleton<BuffConfigDataManager>
{
};

/*
 * @brief Skill
 */

struct SkillConfigData
{
    uint64_t id;
    uint32_t typeId;        //1 
    uint32_t groupId;
    double cd;
    TypeIdCount cost;    //
    std::vector<SkillData> skillsData;


    SkillConfigData( const design::SkillConfig& base )
    {
        fill( base );
    }

    uint64_t key() const
    {
        return id;
    }
    void fill( const design::SkillConfig& base );

};

class SkillConfigDataManager : public DataManager<SkillConfigData, design::SkillConfig>, public CSingleton<SkillConfigDataManager>
{
};

struct RoleConfigData
{
    uint64_t id;
    std::vector<uint32_t> skills;
    std::vector<uint32_t> biaoqing;
    uint32_t radius;
    uint64_t initMapId;
	EaglePos initMapPos;
	uint64_t initDungeonId;
    std::vector<TypeIdCount> items;

    RoleConfigData(const design::RoleConfig& base)
    {
        fill(base);
    }

    uint64_t key() const
    {
        return id;
    }
    void fill(const design::RoleConfig& base);
};

class RoleConfigDataManager : public DataManager<RoleConfigData, design::RoleConfig>, public CSingleton<RoleConfigDataManager>
{
};

struct DefineConfigData : public CSingleton<DefineConfigData>
{
    uint32_t coupon;
    uint32_t roleGrid;
    uint32_t buyRoleGridPrice;
    uint32_t bag;
    uint32_t bagBuy;
    uint32_t bagCount;
    uint32_t bagMax;

    DefineConfigData()
    {

    }

    bool Init(std::string str);
};

struct InitializesConfigData
{
    uint64_t id;
    int64_t x;
    int64_t z;
    std::vector<TypeIdCount> items;
    uint32_t mapId;
    uint32_t level;

    InitializesConfigData(Json::Value &value)
    {
        fill(value);
    }

    uint64_t key() const
    {
        return id;
    }
    void fill(Json::Value &value);
};

class InitializesConfigDataManager : public JsonDataManager<InitializesConfigData>, public CSingleton<InitializesConfigDataManager>
{
};


struct MapsConfigData
{
    uint64_t id;


    MapsConfigData(Json::Value &value)
    {
        fill(value);
    }

    uint64_t key() const
    {
        return id;
    }
    void fill(Json::Value &value);
};

class MapsConfigDataManager : public JsonDataManager<MapsConfigData>, public CSingleton<MapsConfigDataManager>
{
};

struct EquipsConfigData
{
    uint64_t id;
    uint32_t type;
    uint32_t subtype;
    uint32_t quality;

    EquipsConfigData(Json::Value &value)
    {
        fill(value);
    }

    uint64_t key() const
    {
        return id;
    }
    void fill(Json::Value &value);
};

class EquipsConfigDataManager : public JsonDataManager<EquipsConfigData>, public CSingleton<EquipsConfigDataManager>
{
};

struct DungeonConfigData
{
    uint64_t id;
    uint32_t type;
    std::vector<uint32_t> maps;
    uint32_t loadUIBP;
	std::vector<ConditionParm> vecCmpCondition;
	uint32_t autoTickTime;

    DungeonConfigData(const design::DungeonConfig& base)
    {
        fill(base);
    }

    uint64_t key() const
    {
        return id;
    }
    void fill(const design::DungeonConfig& base);
};

class DungeonConfigDataManager : public DataManager<DungeonConfigData, design::DungeonConfig>, public CSingleton<DungeonConfigDataManager>
{
};




#endif
