#include "Shared_Sdk.h"

std::vector<SDKSTRFUN> g_getSdkStrFuns;

bool JiaziSdkStr(Sdk_ReqInfo *info, std::string &url, std::string &postUrl);

bool InitSdkStrFuns()
{
    g_getSdkStrFuns.resize(SDK_TYPE_MAX, NULL);
    g_getSdkStrFuns[SDK_TYPE_EAGLE] = JiaziSdkStr;

    return true;
}

bool GetSdkStr(Sdk_ReqInfo *info, std::string &url, std::string &postUrl)
{
    if (info->sdkType < g_getSdkStrFuns.size() && g_getSdkStrFuns[info->sdkType])
        return g_getSdkStrFuns[info->sdkType](info, url, postUrl);

    return false;
}

bool TryResStr(std::string &res, uint32_t sdkType)
{
    switch (sdkType)
    {
    case SDK_TYPE_EAGLE:
        {
            if (strstr(res.c_str(), "\"code\":0"))
                return true;
            else
                return false;
        }
        break;
    default:
        break;
    }

    return false;
}

//SDK STR �������

bool JiaziSdkStr(Sdk_ReqInfo *info, std::string &url, std::string &postUrl)
{
    char typeUrl[1024] = {0};
    char post[1024] = {0};
    sprintf(typeUrl, CSDKUrlListManager::instance()->GetUrlByType(info->sdkType).c_str());
    char md5Src[1024] = {0};
    sprintf(md5Src, "%s|%s|%s|%u|%s", info->openkey, CSDKUrlListManager::instance()->GetAppIdByType(info->sdkType).c_str(), CSDKUrlListManager::instance()->GetGameTagByType(info->sdkType).c_str(), info->vistor, CSDKUrlListManager::instance()->GetSecreatByType(info->sdkType).c_str());
    sprintf(post, "httpType=%s&gameToken=%s&appId=%s&gameTag=%s&vistor=%u&sign=%s", "GameTokenCheck", info->openkey, CSDKUrlListManager::instance()->GetAppIdByType(info->sdkType).c_str(), CSDKUrlListManager::instance()->GetGameTagByType(info->sdkType).c_str(), info->vistor, md5(md5Src).c_str());

    url = typeUrl;
    postUrl = post;

    return true;
}


