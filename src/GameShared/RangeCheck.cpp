#include "RangeCheck.h"
#include "WorldObject.h"
#include "Map.h"

#define PLAYER_RADIUS_VAL 50.0
#define PLAYER_RADIUS_VAL_PINGFANG 2500.0

//RangeObject
RangeObject::RangeObject(WorldObject *o, WorldObject *c, HitRangeInfo *i)
    :caster(o), checkObject(c), rangeInfo(i)
{
    x1 = 0;
    y1 = 0;
    x2 = 0;
    y2 = 0;

    range = atan2(checkObject->diry, checkObject->dirx);

    switch (rangeInfo->rangeType)
    {
    case 1:
    {
        x1 = checkObject->x + rangeInfo->para1;
        x2 = checkObject->x + rangeInfo->para1 + rangeInfo->para3;
        y1 = checkObject->y + rangeInfo->para2 - rangeInfo->para4 / 2;
        y2 = checkObject->y + rangeInfo->para2 + rangeInfo->para4 / 2;

        range = -range;
    }
    break;
    case 2:
    {
        x1 = checkObject->x + rangeInfo->para1;
        y1 = checkObject->y + rangeInfo->para2;
        x2 = rangeInfo->para3 * rangeInfo->para3;
    }
    break;
    case 3:
    {
        x2 = rangeInfo->para1 * rangeInfo->para1;
        y2 = rangeInfo->para2 / 180 / 2 * 3.1415926;
    }
    break;
    case 4:
    {
        x2 = rangeInfo->para1 * rangeInfo->para1;
    }        
    break;
    default:
        break;
    }

    return;
}

bool RangeObject::IsTarget(WorldObject*target)
{
    if (HIT_TARGET_TYPE_OWNER == rangeInfo->targetType)
    {
        if (target == caster)
            return  true;
        else
            return false;
    }
    else if (HIT_TARGET_TYPE_SELECT == rangeInfo->targetType)
    {

    }
    else if (HIT_TARGET_TYPE_AREA_TEAM == rangeInfo->targetType)
    {

    }
    else if (HIT_TARGET_TYPE_AREA_ENEMY == rangeInfo->targetType)
    {
		if (!caster->GetWorld())
			return false;

		//仇恨系统判断是否敌人
		if (target == caster)
		{
			return false;
		}

		if (!caster->GetWorld()->IsEnemy(caster, target))
			return false;

        return IsInRange(target);
    }

    return false;
}

bool RangeObject::IsInRange(WorldObject *target)
{
    switch (rangeInfo->rangeType)
    {
    case 1:
        return IsInRecRange(target);
        break;
    case 2:
        return IsInCylRange(target);
        break;
    case 3:
        return IsInSectorRange(target);
        break;
    case 4:
        return IsInSphereRange(target);
        break;
    default:
        break;    
    }

    return false;
}

//
bool RangeObject::IsInRecRange(WorldObject* target)
{
    //if (abs(target->z - checkObject->z) > rangeInfo->para5)
    //    return false;

    double x = target->x - checkObject->x;
    double y = target->y - checkObject->y;

    double x4 = cos(range) * x - sin(range) * y + checkObject->x;
    double y4 = sin(range) * x + cos(range) * y + checkObject->y;

    //LOGD("IsInRecRange checkObject x = " << checkObject->x << " y = " << checkObject->y << " dirx = " << checkObject->dirx << " diry = " << checkObject->diry << " range = " << range << " target x = " << target->x << " y = " << target->y << " x1 = " << x1 << " y1 = " << y1 << " x2 = " << x2 << " y2 = " << y2 << " x4 = " << x4 << " y4 = " << y4 << "   !!!");


    if (x4 + PLAYER_RADIUS_VAL >= x1 && x4 - PLAYER_RADIUS_VAL <= x2 && y4 + PLAYER_RADIUS_VAL >= y1 && y4 - PLAYER_RADIUS_VAL <= y2)
    {
        return true;
    }

    return false;
}

//
bool RangeObject::IsInCylRange(WorldObject* target)
{
    //if (abs(target->z - checkObject->z) > rangeInfo->para4)
    //    return false;

    double x = target->x - x1;
    double y = target->y - y1;

    if ((x * x + y * y) <= x2 + PLAYER_RADIUS_VAL_PINGFANG)
    {
        return true;
    }

    return false;
}

//
bool RangeObject::IsInSphereRange(WorldObject* target)
{
    double x = target->x - checkObject->x;
    double y = target->y - checkObject->y;

    if ((x * x + y * y) <= x2 + PLAYER_RADIUS_VAL_PINGFANG)
    {
        return true;
    }

    return false;
}

//
bool RangeObject::IsInSectorRange(WorldObject* target)
{
    //if (abs(target->z - checkObject->z) > rangeInfo->para3)
    //    return false;

    double x = target->x - checkObject->x;
    double y = target->y - checkObject->y;

    if ((x * x + y * y) <= x2 + PLAYER_RADIUS_VAL_PINGFANG)
    {
        double range1 = atan2(y, x);
        
        //LOGD("IsInSectorRange checkObject x = " << checkObject->x << " y = " << checkObject->y << " dirx = " << checkObject->dirx << " diry = " << checkObject->diry << " range = " << range << " range1 = " << range1 <<  " target x = " << target->x << " y = " << target->y << " x2 = " << x2 << " y2 = " << y2  << "   !!!");

        range1 = range1 - range;

        if (abs(range1) <= y2)
            return true;
    }

    return false;
}

