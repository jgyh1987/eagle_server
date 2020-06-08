#ifndef _RANDOM_H_
#define _RANDOM_H_

#include "Sys.h"

class CRandom
{

    public:

        static void Init()
        {
            srand((unsigned int)time(NULL));
        }

        static unsigned int RandomBetween(unsigned int down, unsigned int up) 
        {
            if(down > up)
                return 0;
            else if(down == up)
                return down;
            return down + rand() % (up - down);
        }

        static bool SelectByPercent(unsigned int upNum, unsigned int downNum) 
        {
            if (upNum > downNum - 1) return true;
            if (downNum < 1) return false;
            if (upNum < 1) return false;
            unsigned int m_rand = RandomBetween(0, downNum);
            return (m_rand <= upNum);
        }

        static bool SelectByPercent(unsigned int num)
        {
            return num >= RandomBetween(0, 100);
        }

        static bool SelectByThousandPercent(unsigned int num)
        {
            return num >= RandomBetween(0, 1000);
        }

        static bool SelectByTenThousandPercent(unsigned int num)
        {
            return num >= RandomBetween(0, 10000);
        }

private:
};

#endif
