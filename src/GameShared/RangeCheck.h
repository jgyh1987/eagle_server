#ifndef _RANGE_CHECK_H_
#define _RANGE_CHECK_H_

#include "CommonType.h"

class WorldObject;

struct RangeObject
{
	WorldObject *caster;
    WorldObject *checkObject;
    HitRangeInfo *rangeInfo;
    double x1;
    double y1;
    double x2;
    double y2;
    double range;

    RangeObject(WorldObject *, WorldObject *c, HitRangeInfo *);
    
    bool IsTarget(WorldObject *);

    bool IsInRange(WorldObject *);
    bool IsInRecRange(WorldObject* target);
    bool IsInCylRange(WorldObject* target);
    bool IsInSectorRange(WorldObject* target);
    bool IsInSphereRange(WorldObject* target);
};



#endif
