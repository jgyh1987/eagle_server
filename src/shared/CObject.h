#ifndef _COBJECT_H_
#define _COBJECT_H_

#include "Entry.h"
#include "Noncopyable.h"

class CObjectBase  : private CNoncopyable
{
public:
    uint64_t m_tempid;
    
    CObjectBase(uint64_t uid)
        :m_tempid(uid)
    {
    };

    virtual ~CObjectBase()=0;

    inline uint64_t Uid(){return m_tempid;}
    
};

class CVtIdObject : public CObjectBase
{
public:
    CVtIdObject(uint64_t uid)
        :CObjectBase(uid)
    {}

    ~CVtIdObject() = 0;

    virtual uint64_t Id(){return 0;}
};

class CIdNameSessionObject : public CVtIdObject
{
public:
    uint64_t m_id;
    std::string m_session;
    std::string m_name;

    CIdNameSessionObject(uint64_t uid)
        :CVtIdObject(uid), m_id(0)
    {
    }

    ~CIdNameSessionObject();

    inline uint64_t Id(){return m_id;}
    inline const char *Name(){return m_name.c_str();}
    inline const char *Session(){return m_session.c_str();}
};

template<int i>
class CObjectNone
{
protected:
        inline bool Push(CObjectBase *e){return true;}
        inline void Remove(CObjectBase *e){}
        inline void Clear(){}
};

template <class keyT,class valueT>
class CObjectMap : private CNoncopyable
{
protected:
    typedef eagle_hash_map<keyT, valueT> hashmap;
    typedef typename hashmap::iterator iter;
    typedef typename hashmap::const_iterator const_iter;
    hashmap ets;
    inline bool Insert(const keyT &key,valueT &value)
    {
        if (Find(key, value))
            return false;

        ets[key]=value;
        return true;
    }
    inline bool Find(const keyT &key,valueT &value) const
    {
        const_iter it = ets.find(key);
        if (it != ets.end())
        {
            value = it->second;
            return true;
        }
        else
            return false;
    }

    inline bool FindOne(valueT &value) const
    {
        if (!ets.empty())
        {
            value=ets.begin()->second;
            return true;
        }
        return false;
    }

    CObjectMap()
    {
    }

    virtual ~CObjectMap()
    {
        Clear();
    }

    inline void Remove(const keyT &key)
    {
        ets.erase(key);
    }

    inline void Clear()
    {
        ets.clear();
    }

    inline uint32_t Size() const
    {
        return (uint32_t)ets.size();
    }

    inline bool Empty() const
    {
        return ets.empty();
    }
};

class CObjectTempID : public CObjectMap<uint64_t, CObjectBase *>
{
protected:
        bool Push(CObjectBase * e);
        void Remove(CObjectBase * e);
        CObjectBase * GetObjectByTempID(const uint64_t tempid) const;

private:

};

class CObjectID: public CObjectMap<uint64_t, CVtIdObject *>
{
protected:
        bool Push(CVtIdObject * e);
        void Remove(CVtIdObject * e);
        CVtIdObject * GetObjectByID(const uint64_t id) const;
};

class CObjectSession: public CObjectMap<std::string, CIdNameSessionObject *>
{
protected:
        bool Push(CIdNameSessionObject * e);
        void Remove(CIdNameSessionObject * e);
        CIdNameSessionObject * GetObjectBySession(const char * session) const;
        CIdNameSessionObject * GetObjectBySession(const std::string  &session) const;
};

class CObjectName: public CObjectMap<std::string, CIdNameSessionObject *>
{
protected:
        bool Push(CIdNameSessionObject * e);
        void Remove(CIdNameSessionObject * e);
        CIdNameSessionObject * GetObjectByName(const char * name) const;
        CIdNameSessionObject * GetObjectByName(const std::string  &name) const;
};

template< typename T, typename e1, typename e2 = CObjectNone<1>, typename e3 = CObjectNone<2>, typename e4 = CObjectNone<3> >
class CObjectManager : protected e1, protected e2, protected e3, protected e4
{
protected:

    inline bool AddObject(T *e)
    {
        if(e1::Push(e))
        {
            if(e2::Push(e))
            {
                if(e3::Push(e))
                {
                    if (e4::Push(e))
                    {
                        return true;
                    }
                    else
                    {
                        e3::Remove(e);
                        e2::Remove(e);
                        e1::Remove(e);
                    }
                }
                else
                {
                    e2::Remove(e);
                    e1::Remove(e);
                }
            }
            else
            {
                e1::Remove(e);
            }
        }
        return false;
    }

    inline void RemoveObject(T *e)
    {
        e1::Remove(e);
        e2::Remove(e);
        e3::Remove(e);
        e4::Remove(e);
    }

    virtual ~CObjectManager(){};

    inline int Size()const
    {
        return e1::Size();
    }

    inline bool Empty() const
    {
        return e1::Empty();
    }

    inline void Clear()
    {
        e1::Clear();
        e2::Clear();
        e3::Clear();
        e4::Clear();
    }

    inline bool ExecEveryEntry(CEntryCallback<T> &exec)
    {
        typedef typename e1::iter my_iter;
        for (my_iter it = e1::ets.begin();it != e1::ets.end(); ++it)
        {
            exec.exec((T*)it->second);
        }
        return true;
    }
};

uint64_t GetObjectUid();

#endif
