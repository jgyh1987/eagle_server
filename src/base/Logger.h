#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "log4z.h"
#include "Singleton.h"
#include "Noncopyable.h"

namespace eagle
{

class CLogger : public CSingleton<CLogger>, private CNoncopyable
{
public:
    CLogger();
    ~CLogger();

    void LoadConfigByFile(std::string &path);
    void LoadConfitByStr(std::string &config);

    void Init();

    // @brief 
    void SetPath(const char *);
    /// @brief  
    void SetConsole(bool set = false);
    /// @brief  
    void SetLogFile(bool set);
    // @brief 
    void SetLevel(ENUM_LOG_LEVEL level);

private:
    bool m_console;
    ENUM_LOG_LEVEL m_level;
    std::string m_path;
};

};

#endif

