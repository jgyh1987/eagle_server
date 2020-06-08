#ifndef _INFOLOGSYS_H_
#define _INFOLOGSYS_H_

#include "Sys.h"
#include "LogicDataCommand.h"
#include "ConstructInPlace.h"
#include "TimeTick.h"

static const int sock_userdata_maxsize = 60 * 1024;

enum SYSLOG_TYPE
{
    SYSLOG_TYPE_TEST = 0,
    SYSLOG_TYPE_ADDGOLD = 1,
};

template <typename TO>
class SysLogInfo
{
    public:
        SysLogInfo( int type, TO* p );

        void operator() (TO* p);

        SysLogInfo& operator()( const char* pszLogStr )
        {
            if ( !pszLogStr || strcmp(pszLogStr, "") == 0 )
            {
                return *this;
            }

            if ( _os.str().empty())
            {
                _os << "{";
            }
            else
            {
                _os << ",";
            }

            _os << pszLogStr ;
            return *this;
        }

        template <class T>
            SysLogInfo& operator()( const char* name, T val)
            {
                if ( _os.str().empty())
                {
                    _os << "{";
                }
                else
                {
                    _os << ",";
                }
                _os << '\"' << name << "\":\"" << val << "\"";
                return *this;
            }
        SysLogInfo& operator()( const char* name, unsigned char val)
        {
            if ( _os.str().empty())
            {
                _os << "{";
            }
            else
            {
                _os << ",";
            }
            _os << '\"' << name << "\":\"" << (uint32_t)val << "\"";
            return *this; 
        }
        SysLogInfo& operator()( const char* name, char val)
        {
            if ( _os.str().empty())
            {
                _os << "{";
            }
            else
            {
                _os << ",";
            }
            _os << '\"' << name << "\":\"" << (uint32_t)val << "\"";
            return *this; 
        }

    private:
        std::ostringstream _os;

        char _send_buff[sock_userdata_maxsize];
};


template <typename TO>
SysLogInfo<TO>::SysLogInfo(int type, TO* p)
{
    bzero(_send_buff, sizeof(_send_buff));
    Cmd::t_SendCmdToData_LogInfo* _send = (Cmd::t_SendCmdToData_LogInfo*)_send_buff;
    constructInPlace(_send);

    _send->type = type;
    if (p)
    {
        _send->level = p->Level();
        _send->playerId = p->Id();
        strncpy(_send->name, p->Name(), MAX_PLAYER_NAME - 1);
        strncpy(_send->account, p->Account(), MAX_ACCOUNT_LENGHT - 1);
        _os << "{";
        _os << '\"' << "ip" << "\":\"" << p->GetIp() << "\"";
    }
}

template <typename TO>
void SysLogInfo<TO>::operator() (TO* p)
{
    if (!_os.str().empty())
    {
        _os << "}";
    }
    Cmd::t_SendCmdToData_LogInfo* _send = (Cmd::t_SendCmdToData_LogInfo*)_send_buff;
    _send->time = CImpServerTimeTick::dayTime.sec();
    strncpy(_send->info, _os.str().c_str(), _os.str().length());
    _send->len = (uint32_t)_os.str().length() + 1;
    _send->info[_send->len - 1] = 0;
    p->SendToLogDB(_send, _send->Size());
}


class SysLogString
{
    public:
        SysLogString(){}

        std::string operator()()
        {
            return _os.str();
        }

        template <class T>
            SysLogString& operator()( const char* name, T val)
            {
                if ( !_os.str().empty())
                {
                    _os << ",";
                }
                _os << '\"' << name << "\":\"" << val << "\"";
                return *this;
            }

    private:
        std::ostringstream _os;
};

#endif

