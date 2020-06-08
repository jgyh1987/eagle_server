#ifndef _EAGLE_ALLOC_H_
#define _EAGLE_ALLOC_H_

namespace eagle
{

template<class TYPE>
class CEagle_Alloc_Pool
{
public:
    typedef TYPE* return_type;
    return_type allocate (unsigned long nLen);
    void deallocate(TYPE *ptr,  unsigned long nLen);

private:

};

};

#endif
