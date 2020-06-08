#include "LoginDataService.h"
#include "Defs.h"
#include "QQSdk.h"

CLoginDataServer::CLoginDataServer(const std::string &name)
    :CImpServer(SERVER_TYPE_MAX, name)
{

}
    
CLoginDataServer::~CLoginDataServer()
{

}

void CLoginDataServer::Update()
{

    CQQSdkManager::instance()->doCmd();

    return;
}

void CLoginDataServer::UpdateSec()
{
	try
	{
		bool ret = DataDBConnection::instance()->connection()->ping();
		if (!ret)
		{
			LOGE("LoginDataServer DataDBConnection mysql connect error try reconnect...");
			ret = DataDBConnection::instance()->reconnect();
			if (!ret)
				LOGE("LoginDataServer DataDBConnection mysql reconnect error");
			else
				LOGE("LoginDataServer DataDBConnection mysql reconnect success");
		}
	}
	catch (const mysqlpp::BadQuery& e)
	{
		LOGFMTE("LoginDataServer DataDBConnection mysql++ query error: %s errornum= %d", e.what(), e.errnum());
		LOGE("LoginDataServer DataDBConnection mysql reconnect error");
	}
	catch (const mysqlpp::BadConversion& e)
	{
		LOGFMTE("LoginDataServer DataDBConnection mysql++ conversion error: %s, retrieved data size: %llu, actual size: %llu", e.what(), (unsigned long long)e.retrieved, (unsigned long long)e.actual_size);
		LOGE("LoginDataServer DataDBConnection mysql reconnect error");
	}
	catch (const mysqlpp::Exception& e)
	{
		LOGFMTE("LoginDataServer DataDBConnection mysql++ general error: %s", e.what());
		LOGE("LoginDataServer DataDBConnection mysql reconnect error");
	}
	catch (...)
	{
		LOGE("LoginDataServer DataDBConnection unknown error.");
		LOGE("LoginDataServer DataDBConnection mysql reconnect error");
	}

    CQQSdkManager::instance()->UpdateSec();

    return;
}


