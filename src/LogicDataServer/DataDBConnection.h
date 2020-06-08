#ifndef _DATADBCONNECTION_H_
#define    _DATADBCONNECTION_H_

#include "DBConnection.h"
#include "Singleton.h"

class DataDBConnection : public DBConnection, public CSingleton<DataDBConnection>
{
public:

private:

};

#endif    /* DATADBCONNECTION_H */

