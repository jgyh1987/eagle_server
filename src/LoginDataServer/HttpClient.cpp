#include "HttpClient.h"
#include "Defs.h"

static int OnDebug(CURL *, curl_infotype itype, char * pData, size_t size, void *)
{
    if(itype == CURLINFO_TEXT)
    {
        LOGD("[TEXT]%s\n" << pData);
    }
    else if(itype == CURLINFO_HEADER_IN)
    {
        LOGD("[HEADER_IN]%s\n" << pData);
    }
    else if(itype == CURLINFO_HEADER_OUT)
    {
        LOGD("[HEADER_OUT]%s\n" << pData);
    }
    else if(itype == CURLINFO_DATA_IN)
    {
        LOGD("[DATA_IN]%s\n" << pData);
    }
    else if(itype == CURLINFO_DATA_OUT)
    {
        LOGD("[DATA_OUT]%s\n" << pData);
    }
    return 0;
}

static size_t OnWriteData(void* buffer, size_t size, size_t nmemb, void* lpVoid)
{
    std::string* str = dynamic_cast<std::string*>((std::string *)lpVoid);
    if( NULL == str || NULL == buffer )
    {
        return -1;
    }

    char* pData = (char*)buffer;
    str->append(pData, size * nmemb);
    return nmemb;
}

//static size_t OnHeadData(void* buffer, size_t size, size_t nmemb, void* lpVoid)
//{
//    std::string* str = dynamic_cast<std::string*>((std::string *)lpVoid);
//    if( NULL == str || NULL == buffer )
//    {
//        return -1;
//    }
//
//    char* pData = (char*)buffer;
//    str->append(pData, size * nmemb);
//    return nmemb;
//}

CHttpClient::CHttpClient(uint32_t req_type, bool bDebug)
    :m_bDebug(bDebug)
{
    struct curl_slist *headers=NULL; // init to NULL is important 
    std::ostringstream oss;
    curl_slist_append(headers, "Accept: application/json");  
    //curl_slist_append( headers, "Content-Type: application/json");
    //curl_slist_append( headers, "charsets: utf-8"); 

    m_curl = curl_easy_init();
    m_reqType = req_type;
    if (m_curl)
    {
        if(m_bDebug)
        {
            curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1);
            curl_easy_setopt(m_curl, CURLOPT_DEBUGFUNCTION, OnDebug);
        }

        curl_easy_setopt(m_curl, CURLOPT_READFUNCTION, NULL);
        //curl_easy_setopt(m_curl, CURLOPT_HEADERFUNCTION, OnHeadData);
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, OnWriteData);
        /**
        * ������̶߳�ʹ�ó�ʱ�����ʱ��ͬʱ���߳����sleepл��waitǵȲ��
        * �����������ѡ�libcurl���ᷢ�źŴ����wait�Ӷ��³����˳
        */
        curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1);
        curl_easy_setopt(m_curl, CURLOPT_CONNECTTIMEOUT, 10);
        curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, 10);

        //curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, headers);

        if (HTTP_REQ_TYPE_GET == m_reqType)
        {    
        }
        else if (HTTP_REQ_TYPE_POST == m_reqType)
        {
            curl_easy_setopt(m_curl, CURLOPT_POST, 1);
        }
        else
        {
            curl_easy_cleanup(m_curl);
            m_curl = NULL;
        }
    }
}

CHttpClient::~CHttpClient(void)
{
    if (m_curl)
        curl_easy_cleanup(m_curl);
}

int CHttpClient::Req(const std::string & strUrl, std::string & strResponse, const std::string *strPost, const char *pCaPath)
{
    if(NULL == m_curl)
    {
        return CURLE_FAILED_INIT;
    }
    
    int res;
    switch (m_reqType)
    {
    case HTTP_REQ_TYPE_GET:
        {
            if (NULL == pCaPath)
                res = Get(strUrl, strResponse);
            else
                res = Gets(strUrl, strResponse, pCaPath);
        }
        break;
    case HTTP_REQ_TYPE_POST:
        {
            if (NULL == pCaPath)
                res = Post(strUrl, *strPost, strResponse);
            else
                res = Posts(strUrl, *strPost, strResponse, pCaPath);
        }
        break;
    default:
        break;
    }

    return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////

int CHttpClient::Post(const std::string & strUrl, const std::string & strPost, std::string & strResponse)
{
    curl_easy_setopt(m_curl, CURLOPT_URL, strUrl.c_str());
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void *)&strResponse);
    curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, strPost.c_str());

    return curl_easy_perform(m_curl);
}

int CHttpClient::Get(const std::string & strUrl, std::string & strResponse)
{
    curl_easy_setopt(m_curl, CURLOPT_URL, strUrl.c_str()); 
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void *)&strResponse);
    

    return curl_easy_perform(m_curl);
}

int CHttpClient::Posts(const std::string & strUrl, const std::string & strPost, std::string & strResponse, const char * pCaPath)
{
    curl_easy_setopt(m_curl, CURLOPT_URL, strUrl.c_str());
    curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, strPost.c_str());
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void *)&strResponse);
    if(NULL == pCaPath)
    {
        curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, false);
    }
    else
    {
        //�ȱʡ�����PEMǣ������������ã�����֧�DER
        //curl_easy_setopt(m_curl,CURLOPT_SSLCERTTYPE,"PEM");
        curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, true);
        curl_easy_setopt(m_curl, CURLOPT_CAINFO, pCaPath);
    }

    return curl_easy_perform(m_curl);
}

int CHttpClient::Gets(const std::string & strUrl, std::string & strResponse, const char * pCaPath)
{
    curl_easy_setopt(m_curl, CURLOPT_URL, strUrl.c_str());
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void *)&strResponse);
    if(NULL == pCaPath)
    {
        curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, false);
    }
    else
    {
        curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, true);
        curl_easy_setopt(m_curl, CURLOPT_CAINFO, pCaPath);
    }

    return curl_easy_perform(m_curl);
}



