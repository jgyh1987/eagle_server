#ifndef _SINGLETON_H_
#define _SINGLETON_H_

namespace eagle
{

template <typename T>
class CSingletonFactory
{
    public:
    static T* instance()
    {
        return new T();
    }
 
};
template <typename T,typename MANA=CSingletonFactory<T> >
class CSingleton
{
    private:
    CSingleton(const CSingleton&);
    const CSingleton & operator=(const CSingleton &);
    protected:
    static T* ms_Singleton;
    CSingleton(void)
    {
    }
    ~CSingleton(void)
    {
    }
    public :
    static void delMe(void)
    {
        if(ms_Singleton)
        {
            delete ms_Singleton;
            ms_Singleton=0;
        }
    }
    static T* instance(void)
    {
        if(!ms_Singleton)
        {
            ms_Singleton =MANA::instance();
        }
        return ms_Singleton;
    }
    static T& getMe(void)
    {
        return *instance();
    }
};
template <typename T,typename MANA> T* CSingleton<T,MANA>::ms_Singleton=0;

};

#endif
