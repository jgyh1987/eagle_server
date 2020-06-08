#ifndef _DATAS_SQLSDATA_H_
#define _DATAS_SQLSDATA_H_ 

#include "datetime.h"
#include "mystring.h"
#include "row.h"
#include <ssqls.h>

//server list to start
sql_create_complete_7(SqlPackageCode,     
        1,        
        0,
        mysqlpp::sql_int,    id,        "ID",            
        mysqlpp::sql_char,    code,        "CODE",    
        mysqlpp::sql_char,    package_items,        "PACKAGE_ITEMS",    
        mysqlpp::sql_int,    package_type,        "PACKAGE_TYPE",    
        mysqlpp::sql_int,    package_time,        "PACKAGE_TIME",        
        mysqlpp::sql_char,    mail_title,            "MAIL_TITLE",        
        mysqlpp::sql_char,    mail_context,        "MAIL_CONTEXT"        
        );

//logic player info
sql_create_complete_4(SqlAccount,
        1,
        0,
        mysqlpp::sql_int,            id,                "ID",
        mysqlpp::sql_char,            account,        "ACCOUNT",    
        mysqlpp::sql_char,            sdkId,            "SDKID",    
        mysqlpp::sql_char,            passwd,            "PASSWD"
        );

class DataSsqls
{    
    public:        
        static bool init()        
        {            
            SqlPackageCode::table("PACKAGE_CODE");     
            SqlAccount::table("ACCOUNT_INFO");
            return true;
        }
};

#endif

