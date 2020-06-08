#include "ChatService.h"
#include "Defs.h"
#include "Command.h"

CChatServer::CChatServer(const std::string &name)
	:CImpServer(SERVER_TYPE_MAX, name)
{

}
	
CChatServer::~CChatServer()
{

}


