#ifndef _MAPPOS_H_
#define _MAPPOS_H_

#include "Sys.h"

#define POS_DENOMINATOR 1000.0

struct EaglePos;
struct CmdPos
{
    int64_t x;
    int64_t y;
    int64_t z;
    int64_t dirx;
    int64_t diry;
    int64_t dirz;
    uint32_t move;

    CmdPos()
    {
        bzero(this, sizeof(*this));
    }
};

struct EaglePos
{
    double x;
    double y;
    double z;
    double dirx;
    double diry;
    double dirz;
    double range;
    
    EaglePos()
        :x(0), y(0), z(0), dirx(0), diry(0), dirz(0)
    {
    }
    
    EaglePos(double _x, double _y, double _z = 0, double _dirx = 0, double _diry = 0, double _dirz = 0)
        :x(_x), y(_y), z(_z), dirx(_dirx), diry(_diry), dirz(_dirz)
    {
    }
    
    EaglePos(const EaglePos& pos)
    {
        x = pos.x;
        y = pos.y;
        z = pos.z;
        dirx = pos.dirx;
        diry = pos.diry;
        dirz = pos.dirz;
    }

	EaglePos(const CmdPos& pos)
	{
		x = (double)pos.x / POS_DENOMINATOR;
		y = (double)pos.y / POS_DENOMINATOR;
		z = (double)pos.z / POS_DENOMINATOR;
		dirx = (double)pos.dirx / POS_DENOMINATOR;
		diry = (double)pos.diry / POS_DENOMINATOR;
		dirz = (double)pos.dirz / POS_DENOMINATOR;
	}
    
    double Distance(const EaglePos& pos) const
    {
        return sqrt( (x - pos.x) * ( x - pos.x ) + (y - pos.y) * (y - pos.y) );
    }

	double DistanceNoSqrt(const EaglePos& pos) const
	{
		return (x - pos.x) * (x - pos.x) + (y - pos.y) * (y - pos.y);
	}
    
    const EaglePos& operator= (const EaglePos& pos)
    {
        x = pos.x;
        y = pos.y;
        z = pos.z;
        dirx = pos.dirx;
        diry = pos.diry;
        dirz = pos.dirz;

        return *this;
    }

	const EaglePos& operator= (const CmdPos& pos)
	{
		x = (double)pos.x / POS_DENOMINATOR;
		y = (double)pos.y / POS_DENOMINATOR;
		z = (double)pos.z / POS_DENOMINATOR;
		dirx = (double)pos.dirx / POS_DENOMINATOR;
		diry = (double)pos.diry / POS_DENOMINATOR;
		dirz = (double)pos.dirz / POS_DENOMINATOR;

		return *this;
	}
    
    bool operator == (const EaglePos& pos) const
    {
        return x == pos.x && y == pos.y;
    }
    
    bool operator != (const EaglePos& pos) const
    {
        return !this->operator ==(pos);
    }

    void PosClear()
    {
        x = 0;
        y = 0;
        z = 0;
        dirx = 0;
        diry = 0;
        dirz = 0;
    }

    void RefRange()
    {
        range = atan2(diry, dirx);
    }

	void EagleToCmdPos(CmdPos &pos)
	{
		pos.x = (int64_t)(x * POS_DENOMINATOR);
		pos.y = (int64_t)(y * POS_DENOMINATOR);
		pos.z = (int64_t)(z * POS_DENOMINATOR);
		pos.dirx = (int64_t)(dirx * POS_DENOMINATOR);
		pos.diry = (int64_t)(diry * POS_DENOMINATOR);
		pos.dirz = (int64_t)(dirz * POS_DENOMINATOR);
	}
    
};



#endif

