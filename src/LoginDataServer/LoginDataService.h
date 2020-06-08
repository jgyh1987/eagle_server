#ifndef _LOGICDATASERVICE_H_
#define _LOGICDATASERVICE_H_

#include "ImpService.h"

class CLoginDataServer : public CImpServer
{
public:
    CLoginDataServer(const std::string &name);
    ~CLoginDataServer();

    void Update();
    void UpdateSec();

private:
};


#endif

