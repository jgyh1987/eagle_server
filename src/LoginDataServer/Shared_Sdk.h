/*
    ����ʱ�    : 2017-11-24 
    ��ļ����    : eagle
    ߹���˵�    : SDK ��ַ�ϳ

*/

#ifndef _SHARED_SDK_H_
#define _SHARED_SDK_H_

//�ͷ�ļ����Ŀ�����ͷ�ļ
#include "Sys.h"
#include "Singleton.h"
#include "SdkUrlManager.h"

#define MAX_OPENID_LENGHT 128
#define MAX_OPENKEY_LENGHT 512

struct Sdk_ReqInfo
{
    char openid[MAX_OPENID_LENGHT];
    char openkey[MAX_OPENKEY_LENGHT];
    unsigned int sdkType;
    unsigned long long time;
    unsigned int vistor;
};

typedef bool (*SDKSTRFUN)(Sdk_ReqInfo *info, std::string &url, std::string &post);
extern std::vector<SDKSTRFUN> g_getSdkStrFuns;
bool InitSdkStrFuns();
bool GetSdkStr(Sdk_ReqInfo *info, std::string &url, std::string &postUrl);
bool TryResStr(std::string &res, uint32_t sdkType);


#endif
