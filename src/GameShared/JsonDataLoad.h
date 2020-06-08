#ifndef _JSONDATALOAD_H_
#define _JSONDATALOAD_H_

#include "Logger.h"
#include "Stream.h"
#include "jsoncpp/include/json.h"
#include "DataManager.h"

template<class DataType, class DataBaseType = DataType, class KeyType = uint64_t >
class JsonDataManager  
{
    protected:
        std::auto_ptr< DataCreator<DataType, DataBaseType> > _creator;
        Json::Reader m_reader;

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
        JsonDataManager()
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

        virtual ~JsonDataManager(){
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
            char *data = new char[filesize];
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

            Json::Value value;
            std::string str(data);
            if (m_reader.parse(str, value))
            {
                for (uint32_t i = 0; i < value.size(); ++i)
                {
                    DataType *newData = _creator->Create(value[i]);
                    if (newData) {
                        if (!pushData(newData)) {
                            LOGFMTD("DataManager:: %s load data fail, key: %llu", filename.c_str(), (unsigned long long)newData->key());
                            delete[] data;
                            SAFE_DELETE(newData);
                            return false;
                        }
                    }
                }
            }

            //unsigned int len = 0;
            //unsigned char *pCurData = data;
            //while(pCurData + sizeof(len) <= data + filesize){
            //    len = *(unsigned int*)pCurData;
            //    len = eagle_ntohl(len) + sizeof(len);
            //    if (len > PACKET_ZIP_BUFFER)
            //    {
            //        LOGFMTD("DataManager:: %s data len so lang = %d.", filename.c_str(), len);
            //        delete[] data;
            //        return false;
            //    }
            //    BinaryReadStream stream((const char*)pCurData + sizeof(unsigned int), len);
            //    DataBaseType base;
            //    if(base.Unserialize(&stream) != 0){
            //        LOGFMTD("DataManager:: %s data unserialize fail len = %d.", filename.c_str(), len);
            //        delete[] data;
            //        return false;
            //    }
            //    //DataType *newData = new DataType(base);
            //    DataType *newData = _creator->Create(base);
            //    if (newData) {
            //        if (!pushData(newData)) {
            //            LOGFMTD("DataManager:: %s load data fail, key: %llu", filename.c_str(), (unsigned long long)newData->key());
            //            delete[] data;
            //            SAFE_DELETE(newData);
            //            return false;
            //        }
            //    }
            //    pCurData += len;
            //    //len = *(unsigned int*)pCurData;
            //    //len = ntohl(len) + sizeof(len);
            //}
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

template<class DataType>
bool JsonDataLoad(std::string &filename, DataType *&dataPtr)
{
    Json::Reader m_reader;

    FILE* fp = fopen(filename.c_str(), "rb");
    if (fp == NULL) {
        LOGFMTE("JsonDataLoad:fail to open data file %s", filename.c_str());
        return false;
    }
    fseek(fp, 0, SEEK_END);
    int filesize = ftell(fp);
    if (filesize > MAX_DATAFILESIZE || filesize < 4) {
        LOGFMTE("JsonDataLoad: %s invalid filesize", filename.c_str());
        fclose(fp);
        return false;
    }
    char *data = new char[filesize];
    fseek(fp, 0, SEEK_SET);
    if (fread(data, 1, filesize, fp) != (size_t)filesize) {
        LOGFMTE("JsonDataLoad: %s not correct,filesize:%d", filename.c_str(), filesize);
        fclose(fp);
        delete[] data;
        return false;
    }
    fclose(fp);

    Json::Value value;
    std::string str(data);
    if (!m_reader.parse(str, value))
    {
        std::string  error = m_reader.getFormatedErrorMessages();

        delete[] data;
        return false;
    }

    dataPtr = new DataType(value);    
    delete[] data;

    return true;
}

#endif

