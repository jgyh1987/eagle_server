#ifndef _LOGDBCONNECTION_H_
#define    _LOGDBCONNECTION_H_

#include "DBConnection.h"
#include "Singleton.h"

class LogDBConnection : public DBConnection, public CSingleton<LogDBConnection>
{
    
};

#endif    /* LOGDBCONNECTION_H */

