#ifndef _UNITOBJECT_H_
#define _UNITOBJECT_H_

#include "CObject.h"

class UnitObject : public CVtIdObject
{
public:
    UnitObject(uint64_t tempid);

    uint64_t Id(){return m_id;}

//need inherit
public:    
    virtual uint32_t Type() = 0;
    virtual bool IsType(uint32_t type) = 0;

protected:
    uint64_t m_id = 0;
};

void FreeUnitObject(UnitObject *ptr);

#endif


