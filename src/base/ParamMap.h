#ifndef _CM_PARAM_MAP_H_
#define _CM_PARAM_MAP_H_

#include "Sys.h"
#include "StringTool.h"

namespace eagle
{

/// @brief    Parameter correlation class container
//             All parameter keys and values are represented by strings that are case-insensitive
class CParamMap
{
    public:
        /// @brief    
        /// @param    key 
        /// @return    
        const std::string &Get(const std::string &key)
        {
            return m_param_map[key];
        }

        /// @brief    
        /// @param    key 
        /// @return    
        const uint32_t GetInt(const std::string &key)
        {
            return atoi(m_param_map[key].c_str());
        }

        /// @brief    
        /// @param    key 
        /// @return    
        const double GetFloat(const std::string &key)
        {
            return atof(m_param_map[key].c_str());
        }

        /// @brief    
        /// @param    key 
        /// @param    value 
        void Set(const std::string &key, const std::string &value)
        {
            m_param_map[key] = value;
        }

        /// @brief    
        /// @param    key 
        /// @return    
        std::string & operator[] (const std::string &key)
        {
            return m_param_map[key];
        }



        /// @brief    
        /// @param    out 
        void Dump(std::ostream &out) const
        {
            for(ParamMap_ConstIter it = m_param_map.begin(); it != m_param_map.end(); it++)
                out << it->first << " = " << it->second<< std::endl;
        }

        /// @brief    
        /// @param    cmdLine    
        /// @return    
        unsigned int ParseCmdLine(const std::string &cmdLine);

        /// @brief    
        /// @param    cmdLine    
        /// @return    
        unsigned int ParseCmdLine(const char *cmdLine);

    private:
        /// @brief    hash
        struct key_hash : public std::unary_function<const std::string, size_t>
        {
            /// @brief    
            /// @param    x 
            /// @return    hash
            size_t operator()(const std::string &x) const
            {
                std::string s = x;
                eagle_hash<const char *> H;
                //
                return H(CStringTool::tolower(s).c_str());
            }
        };

        /// @brief    
        struct key_equal : public std::binary_function<const std::string, const std::string, bool>
        {
            /// @brief    
            /// @param    s1 1
            /// @param    s2 2
            /// @return    true s1��s2��
            bool operator()(const std::string &s1, const std::string &s2) const
            {
                return eagle_strcasecmp(s1.c_str(), s2.c_str()) == 0;
            }
        };
        /// @brief    hash_map
        typedef std::map<std::string, std::string> ParamMap;
        /// @brief    
        typedef ParamMap::iterator ParamMap_Iter;
        /// @brief    
        typedef ParamMap::const_iterator ParamMap_ConstIter;

        /// @brief    hash_map,
        ParamMap m_param_map;

};

};

#endif

