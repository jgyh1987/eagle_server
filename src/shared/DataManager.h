#ifndef _DATAMANAGER_H_
#define _DATAMANAGER_H_

#include "Logger.h"
#include "Stream.h"

#define DATABASE_ASSIGN(DATATYPE, DATABASETYPE, VALNAME) \
    (DATATYPE).VALNAME = (DATABASETYPE).VALNAME;

#define DATABASE_ASSIGN_TOSELF(DATABASETYPE, VALNAME) \
    VALNAME = (DATABASETYPE).VALNAME;

const int MAX_DATAFILESIZE = 1024*1024*256;

template<class DataType, class KeyType = DWORD>
class DataIterator
{
    private:
        typename std::map< KeyType, DataType* >::iterator __dataIterator;
    public:
        DataIterator( typename std::map< KeyType, DataType* >::iterator iter ): __dataIterator(iter){

        }

        inline DataIterator& operator++(){
            ++__dataIterator;
            return *this;
        }

        inline DataIterator& operator--(){
            --__dataIterator;
            return *this;
        }

        inline DataIterator operator++(int i){
            DataIterator ret = *this;
            ++__dataIterator;
            return ret;
        }

        inline const DataType& operator*() const {
            return (*(__dataIterator->second));
        }

        inline const DataType* operator->() const {
            return __dataIterator->second;
        }

        inline bool operator==(const DataIterator& iter) const {
            return __dataIterator == iter.__dataIterator;
        }

        inline bool operator!=(const DataIterator& iter)const{
            return !(*this == iter);
        }

};

template<class DataType, class DataBaseType>
class DataCreator
{
    public:
        virtual ~DataCreator() {}

        virtual DataType* Create(const DataBaseType& base) = 0;
};

template<class DataType, class DataBaseType>
class DefaultDataCreator: public DataCreator<DataType, DataBaseType>
{
    public:
        DataType* Create(const DataBaseType& base)
        {
            return new DataType(base);
        }
};

template<class DataType, class DataBaseType = DataType, class KeyType = uint64_t >
class DataManager  
{
    protected:
        std::auto_ptr< DataCreator<DataType, DataBaseType> > _creator;

        std::map< KeyType, DataType* > _data;

        typedef typename std::map< KeyType, DataType* >::iterator ElemIter;

        bool pushData(DataType* entry){
            std::pair< ElemIter, bool > res = _data.insert(std::make_pair(entry->key(), entry));
            return res.second;
        }

        DataType* getData(KeyType id){
            ElemIter it = _data.find(id);
            if(it == _data.end())
                return NULL;
            else 
                return it->second;
        }

    public:
        DataManager()
        {
            _creator.reset(new DefaultDataCreator<DataType, DataBaseType>());
        }

        typedef DataIterator<DataType, KeyType> iterator;

        iterator begin(){
            return iterator(_data.begin());
        }

        iterator end(){
            return iterator(_data.end());
        }

        virtual ~DataManager(){
            for(ElemIter it = _data.begin(); it != _data.end(); it++)
                delete it->second;
        }

        bool load(std::string filename){
            FILE* fp = fopen(filename.c_str(), "rb");
            if(fp == NULL){
                LOGFMTE("DataManager:fail to open data file %s", filename.c_str());
                return false;
            }
            fseek(fp, 0, SEEK_END);
            int filesize = ftell(fp);
            if(filesize > MAX_DATAFILESIZE || filesize < 4){
                LOGFMTE("DataManager: %s invalid filesize", filename.c_str());
                fclose(fp);
                return false;
            }
            unsigned char *data = new unsigned char[filesize];
            fseek(fp, 0, SEEK_SET);
            if( fread(data, 1, filesize, fp) != (size_t)filesize ){
                LOGFMTE("DataManager: %s not correct,filesize:%d", filename.c_str(), filesize);
                fclose(fp);
                delete[] data;
                return false;
            }
            fclose(fp);
            //int len = *(unsigned int*)data;
            //len = ntohl(len) + sizeof(len);
            unsigned int len = 0;
            unsigned char *pCurData = data;
            while(pCurData + sizeof(len) <= data + filesize){
                len = *(unsigned int*)pCurData;
                len = eagle_ntohl(len) + sizeof(len);
                if (len > PACKET_ZIP_BUFFER)
                {
                    LOGFMTD("DataManager:: %s data len so lang = %d.", filename.c_str(), len);
                    delete[] data;
                    return false;
                }
                BinaryReadStream stream((const char*)pCurData + sizeof(unsigned int), len);
                DataBaseType base;
                if(base.Unserialize(&stream) != 0){
                    LOGFMTD("DataManager:: %s data unserialize fail len = %d.", filename.c_str(), len);
                    delete[] data;
                    return false;
                }
                //DataType *newData = new DataType(base);
                DataType *newData = _creator->Create(base);
                if (newData) {
                    if (!pushData(newData)) {
                        LOGFMTD("DataManager:: %s load data fail, key: %llu", filename.c_str(), (unsigned long long)newData->key());
                        delete[] data;
                        SAFE_DELETE(newData);
                        return false;
                    }
                }
                pCurData += len;
                //len = *(unsigned int*)pCurData;
                //len = ntohl(len) + sizeof(len);
            }
            delete[] data;
            return true;
        }

        inline DataType* get(KeyType id){
            return getData(id);
        }

        inline int size() const {
            return (int)_data.size(); 
        }
};

#endif

