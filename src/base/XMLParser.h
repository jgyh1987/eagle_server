#ifndef _XMLPARSE_H_
#define _XMLPARSE_H_

#include "Sys.h"
#include "tinyxml.h"

namespace eagle
{

/// @brief    Simple encapsulation of XML, primarily for loading configuration files
//            Tinyxml is currently used in XML parsers
class CXMLParser
{
    public:
        CXMLParser();
        ~CXMLParser();

        /// @brief    
        /// @param    
        /// @return    
        bool loadFile(const char *xmlFile);
        /// @brief    
        /// @param    
        /// @return    
        bool parseString(const char* xmlString);
        /// @brief    
        /// @param    nodeString 
        /// @return    
        bool getCurrentNodeString(std::string& nodeString);
        /// @brief    
        void freeFile();
        /// @brief
        void printFile();
        /// @brief    
        /// @return    
        bool setChildNode();
        /// @brief    
        /// @param    name 
        /// @return
        bool setChildNode(const char* name);
        /// @brief    
        /// @param    name 
        /// @return
        bool setCurNode(const char *name,bool needlog=true);
        /// @brief    
        /// @param    name1 
        /// @param    name2 
        /// @return    
        bool setCurNode(const char *name1, const char *name2,bool needlog=true);
        /// @brief    
        /// @param    name1 
        /// @param    name2 
        /// @param    name3 
        /// @return    
        bool setCurNode(const char *name1, const char *name2, const char *name3,bool needlog=true);
        /// @brief    
        /// @param    name1 
        /// @param    name2 
        /// @param    name3 
        /// @param    name4 
        /// @return    
        bool setCurNode(const char *name1, const char *name2, const char *name3, const char *name4,bool needlog=true);
        /// @brief    
        /// @param    name1 
        /// @param    name2 
        /// @param    name3 
        /// @param    name4 
        /// @param    name5 
        /// @return    
        bool setCurNode(const char *name1, const char *name2, const char *name3, const char *name4, const char *name5,bool needlog=true);
        /// @brief    
        /// @return    
        bool setNextNode();
        /// @brief    
        /// @return    
        bool setUpNode();
        /// @brief    
        /// @param    nodeName 
        /// @return
        bool setUpNode(const char *nodeName);
        /// @brief    
        /// @return    
        bool isNoneNode();
        /// @brief    
        /// @param    attrName 
        /// @param    prop 
        /// @return
        bool getNodeAttrInt(const char *attrName,int *prop) const;
        /// @brief    
        /// @param    attrName 
        /// @param    prop 
        /// @return    
        bool setNodeAttrInt(const char *attrName, int prop);
        /// @brief    
        /// @param    attrName 
        /// @param    prop 
        /// @return    
        template<typename T>
            bool getNodeAttrInt(const char *attrName, T *prop) const;
        /// @brief    
        /// @param    attrName 
        /// @param    prop 
        /// @param    defaultValue 
        /// @return    
        bool getNodeAttrInt(const char *attrName,int *prop,const int &defaultValue) const;
        /// @brief    
        /// @param    attrName 
        /// @param    prop 
        /// @param    defaultValue 
        /// @return    
        template<typename T>
            bool getNodeAttrInt(const char *attrName, T *prop,const int &defaultValue) const;
        /// @brief    
        /// @param    attrName 
        /// @param    prop 
        /// @return    
        bool getNodeAttrDouble(const char *attrName,void *prop) const;
        /// @brief    
        /// @param    attrName 
        /// @param    prop 
        /// @param    propSize 
        /// @return    
        bool getNodeAttrStr(const char *attrName,void *prop,int propSize,bool needLog=true) const;
        /// @brief    
        /// @param    attrName 
        /// @param    prop 
        /// @return    
        bool getNodeAttrStr(const char *attrName,std::string &prop,bool needLog = true) const;

        /// @brief    
        /// @param    content 
        /// @return    
        template<typename T>
            bool getNodeContentInt(T *content) const;
        /// @brief
        /// @param    content 
        /// @return    
        bool getNodeContentDouble(void *content) const;
        /// @brief    
        /// @return    
        const char* getNodeContentStr() const;
        /// @brief    
        /// @param    content 
        /// @param    contentSize 
        /// @return    
        bool getNodeContentStr(void *content, int contentSize) const;
        /// @brief
        /// @param    content 
        /// @return    
        bool setNodeContentStr(std::string &content);
        /// @brief    
        /// @return    
        const char *getNodeName() const;
        /// @brief    
        /// @param    nodeName 
        /// @return
        bool isAtNode(const char* nodeName) const;
    
    bool setRootNode( );
    
    std::string getFirstAttribute();
    std::string getNextAttribute();

    private:
        /// @brief    XML
        TiXmlDocument  _doc;
        /// @brief    
        TiXmlElement *_cur_node;
        /// @brief    
        std::list<TiXmlElement*> _up_node_stack;
    
    TiXmlAttribute* _attribute;
};

template<typename T>
inline bool CXMLParser::getNodeAttrInt(const char *attrName, T *prop) const
{
    if(!attrName || !prop || !_cur_node) 
    {
        return false;
    }
    int tmp=0;
    if(getNodeAttrInt(attrName, &tmp))
    {
        *prop = (T)tmp;
        return true;
    }

    return false;
}
template<typename T>
inline bool CXMLParser::getNodeAttrInt(const char *attrName, T *prop, const int &defaultValue) const
{
    if(!attrName || !prop || !_cur_node) 
    {
        return false;
    }
    int tmp=0;
    if(getNodeAttrInt(attrName, &tmp, defaultValue))
    {
        *prop = (T)tmp;
        return true;
    }

    return false;
}
template<typename T>
inline bool CXMLParser::getNodeContentInt(T *content) const
{
    if(!content || !_cur_node) 
    {
        return false;
    }
    const char *tmp = _cur_node->GetText();
    if(!tmp)
    {
        return false;
    }
    int temp = atoi(tmp);
    (*content) = (T)temp;
    return true;
}

};

#endif
