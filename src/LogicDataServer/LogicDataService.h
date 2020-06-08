#ifndef _LOGICDATASERVICE_H_
#define _LOGICDATASERVICE_H_

#include "ImpService.h"

class CLogicDataServer : public CImpServer
{
public:
    CLogicDataServer(const std::string &name);
    ~CLogicDataServer();

    void Update();
    void Update5Sec();

    void Close();

private:
};

CLogicDataServer *ServerImp();


#endif

