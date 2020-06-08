#ifndef __HTTP_CURL_H__
#define __HTTP_CURL_H__

#include "Sys.h"
#include "curl/curl.h"

enum HTTP_REQ_TYPE
{
    HTTP_REQ_TYPE_GET = 0,
    HTTP_REQ_TYPE_POST = 1,
};

class CHttpClient
{
public:
    CHttpClient(uint32_t req_type = HTTP_REQ_TYPE_GET, bool bDebug = false);
    ~CHttpClient();

    int Req(const std::string & strUrl, std::string & strResponse, const std::string * strPost = NULL, const char * pCaPath = NULL);
    inline CURL *GetCurl()
    {
        return m_curl;
    }

    

private:
    /**
    * @brief HTTP POST请求
    * @param strUrl 输入参数,请求的Url地址,如:http://www.baidu.com
    * @param strPost 输入参数,使用如下格式para1=val1¶2=val2&…
    * @param strResponse 输出参数,返回的内容
    * @return 返回是否Post成功
    */
    int Post(const std::string & strUrl, const std::string & strPost, std::string & strResponse);

    /**
    * @brief HTTP GET请求
    * @param strUrl 输入参数,请求的Url地址,如:http://www.baidu.com
    * @param strResponse 输出参数,返回的内容
    * @return 返回是否Post成功
    */
    int Get(const std::string & strUrl, std::string & strResponse);

    /**
    * @brief HTTPS POST请求,无证书版本
    * @param strUrl 输入参数,请求的Url地址,如:https://www.alipay.com
    * @param strPost 输入参数,使用如下格式para1=val1¶2=val2&…
    * @param strResponse 输出参数,返回的内容
    * @param pCaPath 输入参数,为CA证书的路径.如果输入为NULL,则不验证服务器端证书的有效性.
    * @return 返回是否Post成功
    */
    int Posts(const std::string & strUrl, const std::string & strPost, std::string & strResponse, const char * pCaPath = NULL);

    /**
    * @brief HTTPS GET请求,无证书版本
    * @param strUrl 输入参数,请求的Url地址,如:https://www.alipay.com
    * @param strResponse 输出参数,返回的内容
    * @param pCaPath 输入参数,为CA证书的路径.如果输入为NULL,则不验证服务器端证书的有效性.
    * @return 返回是否Post成功
    */
    int Gets(const std::string & strUrl, std::string & strResponse, const char * pCaPath = NULL);    

private:
    bool m_bDebug;
    CURL* m_curl;
    uint32_t m_reqType;
};

#endif
