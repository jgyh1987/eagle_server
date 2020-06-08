#include "LogicDataManager.h"
#include "ToolsFun.h"
#include "WorldObject.h"
#include "Effect.h"
#include "TimeTick.h"

#ifdef DATA_LOAD
#undef DATA_LOAD
#endif

#define DATA_LOAD( STR, FILESTR, PATH) \
    if( STR##DataManager::instance()->load(PATH + FILESTR) ) \
{\
    LOGFMTD("%s Loading Success", FILESTR);\
}\
else\
{\
    LOGFMTD("%s Loading Error", FILESTR);\
    return false;\
}

bool LogicDataManager::Init(std::string &str)
{
    std::string fileStr = "";

    fileStr = "Data/ItemConfig.dat";
    DATA_LOAD(ItemConfig, fileStr.c_str(), str);

    fileStr = "Data/CommonDropConfig.dat";
    DATA_LOAD(CommonDropConfig, fileStr.c_str(), str);

    fileStr = "Data/MapConfig.dat";
    DATA_LOAD(MapConfig, fileStr.c_str(), str);

    fileStr = "Data/SceneConfig.dat";
    DATA_LOAD(SceneConfig, fileStr.c_str(), str);

    fileStr = "Data/LandmassConfig.dat";
    DATA_LOAD(LandmassConfig, fileStr.c_str(), str);

    fileStr = "Data/QuestConfig.dat";
    DATA_LOAD(QuestConfig, fileStr.c_str(), str);

    fileStr = "Data/BuffConfig.dat";
    DATA_LOAD(BuffConfig, fileStr.c_str(), str);

    fileStr = "Data/SkillConfig.dat";
    DATA_LOAD(SkillConfig, fileStr.c_str(), str);

    fileStr = "Data/RoleConfig.dat";
    DATA_LOAD( RoleConfig, fileStr.c_str(), str);

	fileStr = "Data/DungeonConfig.dat";
	DATA_LOAD(DungeonConfig, fileStr.c_str(), str);

    //fileStr = "Data/ProfessionInfo.dat";
    //DATA_LOAD(ProfessionInfo, fileStr.c_str(), str);

    //test code begin
    //fileStr = "Data/ItemsConfig.json";
    //DATA_LOAD(ItemsConfig, fileStr.c_str(), str);

    //fileStr = "Data/InitializesConfig.json";
    //DATA_LOAD(InitializesConfig, fileStr.c_str(), str);

    //fileStr = "Data/MapsConfig.json";
    //DATA_LOAD(MapsConfig, fileStr.c_str(), str);

    //fileStr = "Data/DefineConfig.json";
    //if (!DefineConfigData::instance()->Init(str + fileStr))
    //    return false;

    //fileStr = "Data/EquipsConfig.json";
    //DATA_LOAD(EquipsConfig, fileStr.c_str(), str);


    //test code end
    
    return true;
}


// @brief
void parsePos(const std::string& param, std::vector< Struct::MapPos >& posVec)
{
    std::vector< std::string > temp;
    CStringTool::split(param, ';', temp);
    for (uint32_t i = 0; i < temp.size(); ++i)
    {
        std::vector< std::string > vec;
        CStringTool::split(temp[i], '-', vec);
        if (vec.size() >= 2)
        {
            Struct::MapPos pos;
            pos.x = (uint32_t)CStringTool::integer(vec[0]);
            pos.y = (uint32_t)CStringTool::integer(vec[1]);
            posVec.push_back(pos);
        }
    }

    return;
}

//void PollActivityConfigData::fill( const PollActivityConfig& base )
//{
//
//    return;
//}

void ItemConfigData::fill( const design::ItemConfig& base )
{
    id = base.id;
    type = OBJECT_TYPE_NORMAL;
    subtype = 0;
    maxStack = ITEMSTACKMAXCOUNT;
    quality = 0;

    return ;
}

void ItemsConfigData::fill(Json::Value &value)
{
    id = value["id"].asInt();
    subtype = value["subType"].asInt();
    maxStack = value["overlay"].asInt();

    return;
}

void CommonDropConfigData::fill( const design::CommonDropConfig& base )
{
    id = base.id;
    randomNum = base.randomnum;

    std::vector< std::string > temp;
    CStringTool::split( base.randomproduce, ';', temp);
    if (temp.size() > 1)
        allRate = ( uint32_t )CStringTool::integer( temp[0] );

    for( uint32_t i = 1; i < temp.size(); ++i )
    {
        std::vector< std::string > temp1;
        CStringTool::split( temp[i], ':', temp1);

        if (temp1.size() > 1)
        {
            CommonDropSubInfo tempinfo;
            tempinfo.parentRate = ( uint32_t )CStringTool::integer( temp1[0] );

            for (uint32_t j = 1; j < temp1.size(); ++j)
            {
                std::vector< std::string > temp2;
                CStringTool::split( temp1[j], '-', temp2);

                if (5 == temp2.size())
                {
                    CommonDropSpecificInfo tempinfo1;
                    tempinfo1.rate = ( uint32_t )CStringTool::integer( temp2[0] );
                    tempinfo1.id = ( uint32_t )CStringTool::integer( temp2[2] );
                    tempinfo1.type = ( uint32_t )CStringTool::integer( temp2[1] );
                    tempinfo1.minNum = ( uint32_t )CStringTool::integer( temp2[3] );
                    tempinfo1.maxNum = ( uint32_t )CStringTool::integer( temp2[4] );

                    tempinfo.allRate += tempinfo1.rate;
                    tempinfo.drops.push_back(tempinfo1);
                }
            }

            drops.push_back(tempinfo);
        }
    }
 
    return ;
}

void CommonDropConfigData::Dump() const
{
    LOGD("CommonDropConfigData::Dump Begin AllRate = " << allRate << " Count = " << randomNum);
    for (uint32_t i = 0; i < drops.size(); ++i)
    {
        LOGD("CommonDropConfigData::Dump DropNum = " << i + 1 << " AllRate = " << drops[i].allRate << " ParentRate = " << drops[i].parentRate);
    }
    LOGD("CommonDropConfigData::Dump End");
 
    return ;
}

void MapConfigData::fill( const design::MapConfig& base )
{
    id = base.id;
	type = base.type;

    return ;
}

void SceneConfigData::fill(const design::SceneConfig& base)
{
    id = base.id;

    std::vector< std::vector<double> > rangs;
    parseStrToVecVecDouble(base.range, rangs, ',');
    gridInfo.m_size = EYE_RANG_SIZE;
    if (2 == rangs.size())
    {
        if (rangs[0].size() >= 2)
        {
            gridInfo.m_xMin = (int64_t)rangs[0][0];
            gridInfo.m_yMin = (int64_t)rangs[0][1];

        }
        if (rangs[1].size() >= 2)
        {
            gridInfo.m_xMax = (int64_t)rangs[1][0];
            gridInfo.m_yMax = (int64_t)rangs[1][1];

        }
    }
    else
    {
        gridInfo.m_xMin = -20000;
        gridInfo.m_xMax = 20000;
        gridInfo.m_yMin = -20000;
        gridInfo.m_yMax = 20000;
    }
    

    return;
}

void LandmassConfigData::fill(const design::LandmassConfig& base)
{
    id = base.id;

	parseStrToVecInt64(base.maps, maps);
	parseStrToVecInt64(base.scenes, scenes);

    std::vector< std::vector<double> > rangs;
    parseStrToVecVecDouble(base.range, rangs, ',');
    gridInfo.m_size = EYE_RANG_SIZE;
    if (2 == rangs.size())
    {
        if (rangs[0].size() >= 2)
        {
            gridInfo.m_xMin = (int64_t)rangs[0][0];
            gridInfo.m_yMin = (int64_t)rangs[0][1];

        }
        if (rangs[1].size() >= 2)
        {
            gridInfo.m_xMax = (int64_t)rangs[1][0];
            gridInfo.m_yMax = (int64_t)rangs[1][1];

        }
    }
    else
    {
        gridInfo.m_xMin = -20000;
        gridInfo.m_xMax = 20000;
        gridInfo.m_yMin = -20000;
        gridInfo.m_yMax = 20000;
    }


    return;
}

void QuestConfigData::fill( const design::QuestConfig& base )
{
    id = base.id;
    type = base.type;
	client = base.client;
    initAccept = base.initAccept;

    //parseStrToIntAndString(base.cmpCondition, condition.key, condition.value, '|');
    acceptQuest = base.cmpAcceptQuest;


	std::vector< std::string > temp1;
	CStringTool::split(base.preCondition, ';', temp1);
	for (uint32_t i = 0; i < temp1.size(); ++i)
	{
		ConditionParm tempparm;
		parseStrToIntAndString(temp1[i], tempparm.type, tempparm.value, '|');

		preCondition.push_back(tempparm);
	}

	temp1.clear();
	CStringTool::split(base.cmpCondition, ';', temp1);
	for (uint32_t i = 0; i < temp1.size(); ++i)
	{
		ConditionParm tempparm;
		parseStrToIntAndString(temp1[i], tempparm.type, tempparm.value, '|');

		vecCmpCondition.push_back(tempparm);
	}

	temp1.clear();
    CStringTool::split(base.appectActions, ';', temp1);
    appectActions.resize(temp1.size());
    for (uint32_t i = 0; i < temp1.size(); ++i)
    {
        parseStrToIntAndString(temp1[i], appectActions[i].type, appectActions[i].value, '|');
    }

    temp1.clear();
    CStringTool::split(base.cmpActions, ';', temp1);
    cmpActions.resize(temp1.size());
    for (uint32_t i = 0; i < temp1.size(); ++i)
    {
        parseStrToIntAndString(temp1[i], cmpActions[i].type, cmpActions[i].value, '|');
    }

    temp1.clear();
    CStringTool::split(base.receiveActions, ';', temp1);
    receiveActions.resize(temp1.size());
    for (uint32_t i = 0; i < temp1.size(); ++i)
    {
        parseStrToIntAndString(temp1[i], receiveActions[i].type, receiveActions[i].value, '|');
    }

    exp = base.exp;

    return ;
}

void CheckEffectType(uint32_t id, std::vector<TypeValuesInfo> &effectType, std::vector<TypeValuesInfo> &trigger)
{
    
    return;
}

void BuffConfigData::fill( const design::BuffConfig& base )
{
    id = base.id;

    return ;
}


void SkillConfigData::fill( const design::SkillConfig& base )
{

    id = base.id;

    return ;
}

bool DefineConfigData::Init(std::string filename)
{
    FILE* fp = fopen(filename.c_str(), "rb");
    if (fp == NULL) {
        LOGFMTE("DefineConfigData:fail to open data file %s", filename.c_str());
        return false;
    }
    fseek(fp, 0, SEEK_END);
    int filesize = ftell(fp);
    if (filesize > MAX_DATAFILESIZE || filesize < 4) {
        LOGFMTE("DefineConfigData: %s invalid filesize", filename.c_str());
        fclose(fp);
        return false;
    }
    char *data = new char[filesize];
    fseek(fp, 0, SEEK_SET);
    if (fread(data, 1, filesize, fp) != (size_t)filesize) {
        LOGFMTE("DefineConfigData: %s not correct,filesize:%d", filename.c_str(), filesize);
        fclose(fp);
        delete[] data;
        return false;
    }
    fclose(fp);
    //int len = *(unsigned int*)data;
    //len = ntohl(len) + sizeof(len);

    Json::Reader reader;
    Json::Value value;
    std::string str(data);
    if (!reader.parse(str, value))
    {
        return false;
    }

    coupon = value["coupon"].asInt();
    roleGrid = value["RoleGrid"].asInt();
    buyRoleGridPrice = value["buyRoleGridPrice"].asInt();

    bag = value["bagInitialNum"].asInt();
    bagBuy = value["bagCost"].asInt();
    bagCount = value["bagAddNum"].asInt();
    bagMax = value["bagMaxNum"].asInt();

    return true;
}

void InitializesConfigData::fill(Json::Value &value)
{
    id = value["id"].asInt();

    Json::Value rebornPoint = value["rebornPoint"];
    x = (int64_t)rebornPoint["x"].asDouble() * 1000;
    z = (int64_t)rebornPoint["z"].asDouble() * 1000;

    Json::Value goods = value["goodss"];
    items.reserve(goods.size());
    for (uint32_t i = 0; i < goods.size(); ++i)
    {
        TypeIdCount info;
        info.type = goods[i]["type"].asInt();
        info.id = goods[i]["id"].asInt();
        info.count = goods[i]["count"].asInt();
        items.push_back(info);
    }

    mapId = value["map"].asInt();
    level = value["level"].asInt();

    return;
}

void MapsConfigData::fill(Json::Value &value)
{
    id = value["id"].asInt();


    return;
}

void EquipsConfigData::fill(Json::Value &value)
{
    id = value["id"].asInt();


    return;
}

void RoleConfigData::fill(const design::RoleConfig& base)
{
    id = base.id;
    parseStrToVecInt(base.skills, skills);

    parseStrToVecInt(base.biaoqing, biaoqing);
    radius = base.radius;
	initMapId = base.initMapId;
	parseStrToPosDir(base.initMapPos, initMapPos);
	initDungeonId = base.initDungeonId;

	items.resize(2);
	items[0].type = OBJECT_TYPE_COIN;
	items[0].id = COIN_TYPE_DIAMOND;
	items[0].count = 1000;
	items[1].type = OBJECT_TYPE_COIN;
	items[1].id = COIN_TYPE_MONEY;
	items[1].count = 1000;


    return;
}

void DungeonConfigData::fill(const design::DungeonConfig& base)
{
	id = base.id;
	type = base.type;
	autoTickTime = base.autoTickTime;

	std::vector< std::string > temp1;
	CStringTool::split(base.cmpCondition, ';', temp1);
	for (uint32_t i = 0; i < temp1.size(); ++i)
	{
		ConditionParm tempparm;
		parseStrToIntAndString(temp1[i], tempparm.type, tempparm.value, '|');

		vecCmpCondition.push_back(tempparm);
	}


	return;
}

