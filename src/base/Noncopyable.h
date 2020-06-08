#ifndef _NONCOPYABLE_H_
#define _NONCOPYABLE_H_

namespace eagle
{

//ban of copying 
class CNoncopyable
{
    protected:
        CNoncopyable() {};
        ~CNoncopyable() {};

    private:
        CNoncopyable(const CNoncopyable&);

        const CNoncopyable & operator= (const CNoncopyable &);
};

};

#endif

