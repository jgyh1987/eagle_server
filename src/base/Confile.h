#ifndef _CPP_CONFIG_FILE_H_
#define _CPP_CONFIG_FILE_H_

#include "XMLParser.h"

namespace eagle
{

/// @brief    Configuration file parser
class CConfigFile
{
    public:
        /// @param    filename
        CConfigFile(const char *filename="./Config/ZoneConfig.xml.template");
        ~CConfigFile();

        /// @brief    start parse
        /// @param    node name 
        /// @return    
        bool parse(const char *name);
        /// @brief    start parse
        /// @param    node name 
        /// @param    ignore_false 
        /// @return    
        bool parseNode(const char *name,bool ignore_false=false);

    private:
        /// @brief    Normal parameter parsing simply puts the parameter into the global container
        /// @param    node 
        /// @return 
        bool parseNormal();

    private:
        /// @brief    
        CXMLParser _parser;
        /// @brief
        std::string _filename;
};

};

#endif
