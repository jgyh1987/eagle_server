#ifndef _STRING_TOOL_H_
#define _STRING_TOOL_H_

#include "Sys.h"

namespace eagle
{

/// @brief An extension of STL's string providing additional functionality that is often availiable in
///        higher-level languages such as C#, php, Python.
/// @ref Reference is made to the ext_string implementation ��http://www.gotroot.ca/ext_string/
class CStringTool
{
    public:
        static const std::string WHITE_SPACE;            ///< White space characters in turn are: space, horizontal tab, enter, newline, paper wrap, vertical tab
        static const int DEFAULT_BUFFER_SIZE = 1024;    ///<
    public:
        /// @brief 
        static std::string& format(std::string& resultOUT, const char* fmt, ...);
        /// @brief 
        static std::string format(const char* fmt, ...);
        /// @brief 
        /// @param default_size The default buffer size, and if the buffer size is not sufficient, it will double until the buffer is sufficient
        static std::string& vformat(std::string& resultOUT, const char *fmt, va_list argptr, int default_size = DEFAULT_BUFFER_SIZE);
        /// @brief �ַ��ʽ��
        /// @param default_size The default buffer size, and if the buffer size is not sufficient, it will double until the buffer is sufficient
        static inline std::string vformat(const char *fmt, va_list argptr, int default_size = DEFAULT_BUFFER_SIZE);

        /// @brief C#-like string formatting by subscript index
        static bool format_index(std::string& resultOUT, const char* fmt, const std::vector<std::string>& argList);
        /// @brief C#-like string formatting by subscript index
        static inline bool format_index(std::string& resultOUT, const char* fmt);
        /// @brief C#-like string formatting by subscript index
        template<typename Arg0>
            static bool format_index(std::string& resultOUT, const char* fmt, Arg0 arg0);
        /// @brief C#-like string formatting by subscript index
        template<typename Arg0, typename Arg1>
            static bool format_index(std::string& resultOUT, const char* fmt, Arg0 arg0, Arg1 arg1);
        /// @brief C#-like string formatting by subscript index
        template<typename Arg0, typename Arg1, typename Arg2>
            static bool format_index(std::string& resultOUT, const char* fmt, Arg0 arg0, Arg1 arg1, Arg2 arg2);
        /// @brief C#-like string formatting by subscript index
        template<typename Arg0, typename Arg1, typename Arg2, typename Arg3>
            static bool format_index(std::string& resultOUT, const char* fmt, Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3);
        /// @brief C#-like string formatting by subscript index
        template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
            static bool format_index(std::string& resultOUT, const char* fmt, Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4);
        /// @brief C#-like string formatting by subscript index
        template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
            static bool format_index(std::string& resultOUT, const char* fmt, Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5);
        /// @brief C#-like string formatting by subscript index
        template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
            static bool format_index(std::string& resultOUT, const char* fmt, Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6);
        /// @brief C#-like string formatting by subscript index
        template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
            static bool format_index(std::string& resultOUT, const char* fmt, Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7);

        /// @brief Converting data to string format
        static inline std::string& tostring(std::string& resultOUT, char c);
        /// @brief Converting data to string format
        static inline std::string& tostring(std::string& resultOUT, const char* pstr);
        /// @brief Converting data to string format
        static inline std::string& tostring(std::string& resultOUT, const std::string& str);
        /// @brief Converting data to string format
        static inline std::string& tostring(std::string& resultOUT, bool value);
        /// @brief Converting data to string format
        template<typename ValueType>
            static inline std::string& tostring(std::string& resultOUT, ValueType value);

        /// @brief 
        /// @return 
        static std::string& append(std::string& str, const char* fmt, ...);
        /// @brief 
        /// @return 
        static inline std::string& append(std::string& str, const std::string& cat);
        /// @brief 
        /// @return
        static inline std::string& append(std::string& str, char c);
        /// @brief 
        /// @return 
        static inline std::string& append(std::string& str, bool value);
        /// @brief 
        /// @return 
        template<typename ValueType>
            static inline std::string& append(std::string& str, ValueType value);

        /// @brief Filter out the white space at the beginning of a string
        static inline std::string trimbegin(std::string& str, const std::string& whiteSpace = WHITE_SPACE);
        /// @brief Filter out the white space at the beginning of a string
        static inline std::string trimend(std::string& str, const std::string& whiteSpace = WHITE_SPACE);
        /// @brief Filter out the white space at the beginning of a string
        static inline std::string trim(std::string& str, const std::string& whiteSpace = WHITE_SPACE);

        /// @brief Determines whether a string contains a given string
        static inline bool contains(const std::string& str, const std::string& tosearch);
        /// @brief Determines whether a string contains a given string
        static inline bool contains(const std::string& str, const char* tosearch);
        /// @brief Determines whether a string begins with a given string
        static inline bool startwith(const std::string& str, const std::string& needle);
        /// @brief Determine whether a string ends with a given string
        static inline bool endwith(const std::string& str, const std::string& needle);

        /// @brief String left fill
        static inline std::string& padleft(std::string& str, std::string::size_type size, std::string::value_type paddingchar = ' ');
        /// @brief String right fill
        static inline std::string& padright(std::string& str, std::string::size_type size, std::string::value_type paddingchar = ' ');

        /// @brief Resetting the string container
        /// @remark StringListContainer can be std::list<std::string> or std::vector<std::string>
        template <typename StringListContainerFrom, typename StringListContainerTo>
            static void unique(const StringListContainerFrom& strList, StringListContainerTo& resultOUT);
        /// @brief Resetting the string container
        /// @remark StringListContainer can be std::list<std::string> or std::vector<std::string>
        template<typename StringListContainer>
            static void unique(StringListContainer& strList);

        /// @brief Converts a string to a number.
        /// @param str 
        /// @param ret 
        /// @param end The end position at which the store will be parsed when it is not empty, and the value of the str pointer if it fails
        /// @return 
        static inline bool try_parse_int(const char* str, int* ret, char** end = NULL);

        /// @brief String separation
        /// @param separator Partitioned character / ASCII character)
        template<typename OutContainer>
        static void split(const std::string& str, std::string::value_type separator, OutContainer& resultOUT, size_t resultLimit = (size_t)-1);
        /// @brief String separation
        /// @param separator Split string (or Chinese characters)
        template<typename OutContainer>
        static void split(const std::string& str, const std::string& separator, OutContainer& resultOUT, size_t resultLimit = (size_t)-1);
        /// @brief String separation
        /// @param separatorList Splits an array of strings, in which they serve as delimiters, respectively, from first to last
        /// @remark StringListContainer can be std::list<std::string> or std::vector<std::string>
        template<typename StringListContainer,typename OutContainer>
            static void split(const std::string& str, const StringListContainer& separatorList, OutContainer& resultOUT, size_t resultLimit = (size_t)-1);
        /// @brief String separation
        /// @param separator Partitioned character / ASCII character)
        template<typename OutContainer>
        static void split(const char* str, std::string::value_type separator, OutContainer& resultOUT, size_t resultLimit = (size_t)-1);
        /// @brief Separate strings according to whitespace, typical whitespace includes "\ t\ r\ n\ f\ v" (in turn: space, horizontal tab, enter, line feed, paper wrap, vertical tab)
        static void split_white_space(const std::string& str, std::vector<std::string>& resultOUT, size_t resultLimit = (size_t)-1);
        /// @brief Split according to the length of the string. After segmentation, the length of each substring in the result is not greater than the given length, and the Chinese character will not be accidentally shredded.
        /// @remark 
        static bool split_fix_size(const std::string& str, std::string::size_type fix_size, std::vector<std::string>& resultOUT);

        /// @brief String bond
        template <class InputIterator>
            static inline std::string& join(const std::string &glue, InputIterator first, InputIterator last, std::string& resultOUT);
        /// @brief String bond
        template <class InputIterator>
            static inline std::string join(const std::string &glue, InputIterator first, InputIterator last);

        /// @brief Replace all from in the string str with to
        static std::string& replace(std::string& str, const std::string& from, const std::string& to);
        /// @brief Replace all from in the string str with to
        static std::string& replace(std::string& str, std::string::value_type from, std::string::value_type to);

        /// @brief Delete all to_remove from the string str and scan only once before and after
        static inline std::string& erase(std::string& str, const std::string& to_remove);

        /// @brief Convert strings to numbers, forward to back as much as possible
        static long int integer(const std::string& str);
        /// @brief Convert strings to numbers, forward to back as much as possible
        /// @return Returns whether all are converted
        static bool integer(const std::string& str, long int& valueOut);

        /// @brief Duplicate string
        static std::string& repeat(const std::string& str, std::string::size_type times, std::string& resultOUT);
        /// @brief Duplicate string
        static inline std::string repeat(const std::string& str, std::string::size_type times);

        /// @brief Determines whether the given string is all lowercase
        static bool is_lower(const std::string& str);
        /// @brief Determines whether a given character is a lowercase letter
        static inline bool is_lower(char c);
        /// @brief Determines whether a given string is all capital letters
        static bool is_upper(const std::string& str);
        /// @brief Determines whether a given character is a capital letter
        static inline bool is_upper(char c);
        /// @brief Determines whether the given string is all letters
        static bool is_alpha(const std::string& str);
        /// @brief Determines whether a given character is a letter
        static inline bool is_alpha(char c);
        /// @brief Determines whether a given string is all numeric
        static bool is_numeric(const std::string& str);
        /// @brief Determines whether a given character is a number
        static inline bool is_numeric(char c);
        /// @brief Determines whether a given string is all numbers or letters
        static bool is_alnum(const std::string& str);
        /// @brief Determines whether a given character is a number or a letter
        static inline bool is_alnum(char c);
        /// @brief Determines whether a given character is a white space character
        static inline bool is_whitespace(char c);

        /// @brief Convert strings in place to lowercase
        static std::string& tolower(std::string& str);
        /// @brief Convert strings in place to lowercase
        static char* tolower(char* pstr);
        /// @brief Convert characters to lowercase
        static inline char tolower(char c);
        /// @brief Convert strings to uppercase
        static std::string& toupper(std::string& str);
        /// @brief Subpoena characters to uppercase
        static inline char toupper(char c);
        /// @brief Reverse the case of a given string in place
        static std::string& swapcase(std::string& str);
        /// @brief Reverse the case of a given character
        static inline char swapcase(char c);

        /// @brief Get the number of module occurrences in str
        static std::string::size_type count(const std::string& str, const std::string &module);
        /// @brief 
        static inline int compare(const char* str1, const char* str2);
        /// @brief 
        static inline int compare(const std::string& str1, const char* str2);
        /// @brief 
        static inline int compare(const std::string& str1, const std::string& str2);
        /// @brief 
        static inline int compare(const char* str1, const std::string& str2);
        /// @brief 
        static inline int compare(char c1, char c2);

        /// @brief 
        static int icompare(const std::string& str1, const std::string& str2);
        /// @brief 
        static inline int icompare(const char* str1, const char* str2);
        /// @brief 
        static inline int icompare(char c1, char c2);

        /// @brief string natural comparison function
        /// @remark http://sourcefrog.net/projects/natsort/
        static int compare_nature(const char *str1, const char *str2, bool case_sensitive = true);
        /// @brief string natural comparison function
        static inline int compare_nature(const std::string& str1, const std::string& str2, bool case_sensitive = true);

        /// @brief String wildcard matching judgment
        /// @remark http://www.codeproject.com/KB/string/wildcmp.aspx
        static bool match_wildcard(const char* str, const char* wildcard);

        /// @brief 
        static inline bool empty(const char* pstr);
        /// @brief 
        static inline bool empty(const std::string& str);
        /// @brief 
        static inline bool empty(char c);

        /// @brief 
        static inline size_t strlen(const char* pstr);
        /// @brief 
        static inline size_t strlen(const std::string& str);
        static inline bool trimEmpty(const char* str);

        /// @brief Determine whether a string contains a prefix prefix
        static inline bool hasPrefix(const std::string& str, const std::string& prefix);
        /// @brief Remove if string contains prefix prefix
        static inline std::string stripPrefix(const std::string& str, const std::string& prefix);
        /// @brief Determines whether a string contains a suffix
        static inline bool hasSuffix(const std::string& str, const std::string& suffix);
        /// @brief If the string contains the suffix prefix, it is removed
        static inline std::string stripSuffix(const std::string& str, const std::string& suffix);


        /// @brief Edit distance
        /// @define (1) The smallest number of insertions, deletions, and substitutions required to change 
        ///        one string or tree into another. (2) A ��(m � n) algorithm to compute the distance between 
        ///        strings, where m and n are the lengths of the strings
        /// @remark consult    http://www.merriampark.com/ld.htm
        ///                    http://www.merriampark.com/ldcpp.htm 
        /// 
        /// @other Manhattan Distance Manhattan distance 
        /// @define The distance between two points measured along axes at right angles. 
        ///        In a plane with p1 at (x1, y1) and p2 at (x2, y2), it is |x1 - x2| + |y1 - y2|. 
        /// 
        /// @other Hamming Distance hamming distance 
        /// @define The number of bits which differ between two binary strings.
        ///        More formally, the distance between two strings A and B is � | Ai - Bi |. 
        /// 
        /// @other Euclidean Distance Euclidean distance
        /// @define The straight line distance between two points. 
        ///        In a plane with p1 at (x1, y1) and p2 at (x2, y2), it is ơ((x1 - x2)? + (y1 - y2)?). 
        static int LevenshteinDistance(const std::string& source, const std::string& target);
        
        //Mask the function
        //static bool convertCharset(const char* inputCharset, const char *inputBuffer, size_t inputLen, const char* outputCharset, char* outputBuffer, size_t outputLen);

    private:
        CStringTool(){}
};

///< ------------------------------------------------------------------------------------------------------

inline std::string CStringTool::vformat(const char *fmt, va_list argptr, int default_size/* = DEFAULT_BUFFER_SIZE */)
{
    std::string resultOUT;
    return vformat(resultOUT, fmt, argptr, default_size);
}
inline bool CStringTool::format_index(std::string& resultOUT, const char* fmt)
{
    return format_index(resultOUT, fmt, std::vector<std::string>());
}
    template<typename Arg0>
bool CStringTool::format_index(std::string& resultOUT, const char* fmt, Arg0 arg0)
{
    std::vector<std::string> args(1);
    tostring(args[0], arg0);
    return format_index(resultOUT, fmt, args);
}
    template<typename Arg0, typename Arg1>
bool CStringTool::format_index(std::string& resultOUT, const char* fmt, Arg0 arg0, Arg1 arg1)
{
    std::vector<std::string> args(2);
    tostring(args[0], arg0); tostring(args[1], arg1);
    return format_index(resultOUT, fmt, args);
}
    template<typename Arg0, typename Arg1, typename Arg2>
bool CStringTool::format_index(std::string& resultOUT, const char* fmt, Arg0 arg0, Arg1 arg1, Arg2 arg2)
{
    std::vector<std::string> args(3);
    tostring(args[0], arg0); tostring(args[1], arg1); tostring(args[2], arg2);
    return format_index(resultOUT, fmt, args);
}
    template<typename Arg0, typename Arg1, typename Arg2, typename Arg3>
bool CStringTool::format_index(std::string& resultOUT, const char* fmt, Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3)
{
    std::vector<std::string> args(4);
    tostring(args[0], arg0); tostring(args[1], arg1); tostring(args[2], arg2); tostring(args[3], arg3); 
    return format_index(resultOUT, fmt, args);
}
    template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
bool CStringTool::format_index(std::string& resultOUT, const char* fmt, Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
{
    std::vector<std::string> args(5);
    tostring(args[0], arg0); tostring(args[1], arg1); tostring(args[2], arg2); tostring(args[3], arg3); tostring(args[4], arg4);
    return format_index(resultOUT, fmt, args);
}
    template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
bool CStringTool::format_index(std::string& resultOUT, const char* fmt, Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)
{
    std::vector<std::string> args(6);
    tostring(args[0], arg0); tostring(args[1], arg1); tostring(args[2], arg2); tostring(args[3], arg3); tostring(args[4], arg4); tostring(args[5], arg5);
    return format_index(resultOUT, fmt, args);
}
    template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
bool CStringTool::format_index(std::string& resultOUT, const char* fmt, Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6)
{
    std::vector<std::string> args(7);
    tostring(args[0], arg0); tostring(args[1], arg1); tostring(args[2], arg2); tostring(args[3], arg3); tostring(args[4], arg4); tostring(args[5], arg5); tostring(args[6], arg6);
    return format_index(resultOUT, fmt, args);
}
    template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
bool CStringTool::format_index(std::string& resultOUT, const char* fmt, Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7)
{
    std::vector<std::string> args(8);
    tostring(args[0], arg0); tostring(args[1], arg1); tostring(args[2], arg2); tostring(args[3], arg3); tostring(args[4], arg4); tostring(args[5], arg5); tostring(args[6], arg6); tostring(args[7], arg7);
    return format_index(resultOUT, fmt, args);
}

inline std::string& CStringTool::tostring(std::string& resultOUT, char c)
{
    resultOUT = c;
    return resultOUT;
}
inline std::string& CStringTool::tostring(std::string& resultOUT, const char* pstr)
{
    resultOUT = pstr == NULL ? "" : pstr; 
    return resultOUT;
}
inline std::string& CStringTool::tostring(std::string& resultOUT, const std::string& str)
{
    resultOUT = str; 
    return resultOUT;
}
inline std::string& CStringTool::tostring(std::string& resultOUT, bool value)
{
    resultOUT = value ? "true" : "false"; 
    return resultOUT;
}
    template<typename ValueType>
inline std::string& CStringTool::tostring(std::string& resultOUT, ValueType value)
{
    std::stringstream oss;
    oss << value;
    resultOUT = oss.str();
    return resultOUT;
} 
inline std::string& CStringTool::append(std::string& str, const std::string& cat)
{
    str += cat;
    return str;
}
inline std::string& CStringTool::append(std::string& str, char c)
{
    str += c;
    return str;
}
inline std::string& CStringTool::append(std::string& str, bool value)
{
    str += value ? "true" : "false";
    return str;
}
    template<typename ValueType>
inline std::string& CStringTool::append(std::string& str, ValueType value)
{
    std::stringstream oss;
    oss << value;
    str += oss.str();
    return str;
}
inline std::string CStringTool::trimbegin(std::string& str, const std::string& whiteSpace/* = WHITE_SPACE*/)
{
    return str.erase(0,str.find_first_not_of(whiteSpace));
}
inline std::string CStringTool::trimend(std::string& str, const std::string& whiteSpace/* = WHITE_SPACE*/)
{
    return str.erase(str.find_last_not_of(whiteSpace)+1);
}
inline std::string CStringTool::trim(std::string& str, const std::string& whiteSpace/* = WHITE_SPACE*/)
{
    str.erase(str.find_last_not_of(whiteSpace)+1);
    return str.erase(0,str.find_first_not_of(whiteSpace));
}
inline bool CStringTool::contains(const std::string& str, const std::string& tosearch)
{
    return str.find(tosearch) != std::string::npos;
}
inline bool CStringTool::contains(const std::string& str, const char* tosearch)
{
    if(tosearch == NULL)
        return false;
    return str.find(tosearch) != std::string::npos;
}
inline bool CStringTool::startwith(const std::string& str, const std::string& needle)
{
    if(str.size() < needle.size())
        return false;
    return str.compare(0, needle.size(), needle) == 0;
}
inline bool CStringTool::endwith(const std::string& str, const std::string& needle)
{
    if(str.size() < needle.size())
        return false;
    return str.compare(str.size() - needle.size(), needle.size(), needle) == 0;
}
inline std::string& CStringTool::padleft(std::string& str, std::string::size_type size, std::string::value_type paddingchar/*  = ' '*/)
{
    if(size > str.size())
        str.insert(0, size - str.size(), paddingchar);
    return str;
}
inline std::string& CStringTool::padright(std::string& str, std::string::size_type size, std::string::value_type paddingchar/*  = ' '*/)
{
    if(size > str.size())
        str.resize(size, paddingchar);
    return str;
}
    template <typename StringListContainerFrom, typename StringListContainerTo>
void CStringTool::unique(const StringListContainerFrom& strList, StringListContainerTo& resultOUT)
{
    resultOUT.clear();
    resultOUT.reserve(strList.size());
    for(typename StringListContainerFrom::const_iterator it_from = strList.begin();
            it_from != strList.end(); ++it_from)
    {
        bool repeat = false;
        for(typename StringListContainerFrom::const_iterator it_to = resultOUT.begin(); 
                it_to != resultOUT.end(); ++it_to)
        {
            if(it_from->compare(*it_to) == 0)
            {
                repeat = true;
                break;
            }
        }
        if(repeat == false)
            resultOUT.push_back(*it_from);
    }
}
    template<typename StringListContainer>
void CStringTool::unique(StringListContainer& strList)
{
    StringListContainer result;
    CStringTool::unique(strList, result);
    if(strList.size() != result.size())
        strList.assign(result.begin(), result.end());
}
    template<typename OutContainer>
void CStringTool::split(const std::string& str, std::string::value_type separator, OutContainer& resultOUT, size_t resultLimit /* = -1*/)
{
    resultOUT.clear();
    if(resultLimit == 0) 
        return;
    resultOUT.push_back(std::string());
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
    {
        if(*it == separator)
        {
            if(resultOUT.back().empty() == false)
            {
                if(resultOUT.size() == resultLimit) 
                    return;
                resultOUT.push_back(std::string());
            }
        }
        else
        {
            resultOUT.back().push_back(*it);
        }
    }
    if(resultOUT.back().empty())
        resultOUT.pop_back();
    //assert_debug(resultOUT.size() <= resultLimit);
}

    template<typename OutContainer>
void CStringTool::split(const std::string& str, const std::string& separator, OutContainer& resultOUT, size_t resultLimit/* = -1*/)
{
    resultOUT.clear();
    if(resultLimit == 0) 
        return;
    if(separator.empty())
    {
        resultOUT.push_back(str);
        return;
    }
    std::string::size_type begin = 0, index;
    for(;;)
    {
        index = str.find(separator, begin);
        if(index == std::string::npos)
            break;
        size_t len = index - begin;
        if(len != 0)
        {
            resultOUT.push_back(str.substr(begin, len));
            if(resultOUT.size() == resultLimit)
                return;
        }
        begin = index + separator.size();
    }
    if(begin < str.size() && resultOUT.size() < resultLimit)
        resultOUT.push_back(str.substr(begin));
    //assert_debug(resultOUT.size() <= resultLimit);
}
    template<typename StringListContainer,typename OutContainer>
void CStringTool::split(const std::string& str, const StringListContainer& separatorList, OutContainer& resultOUT, size_t resultLimit /* = -1*/)
{
    typedef std::vector<std::string> container;

    resultOUT.clear();
    if(resultLimit == 0) 
        return;
    // Partition template de-reduplication
    std::vector<std::string> splitSeparatorList;
    CStringTool::unique(separatorList, splitSeparatorList);
    if(separatorList.empty())
    {
        resultOUT.push_back(str);
        return;
    }

    // Partition operation
    std::string::size_type begin = 0;
    for(std::string::size_type i = 0; i < str.size(); i++)
    {
        for(container::const_iterator it = splitSeparatorList.begin(); it != splitSeparatorList.end(); ++it)
        {
            if(it->compare(0, it->size(), str, i, it->size()) == 0)
            {
                if(i != begin)
                {
                    resultOUT.push_back(str.substr(begin, i - begin));
                    if(resultOUT.size() == resultLimit)
                        return;
                }
                begin = i + it->size();
                i = begin - 1;// -1 to counteract the I behind the outer for loop
                break;
            }
        }
    }
    if(begin < str.size() && resultOUT.size() < resultLimit)
        resultOUT.push_back(str.substr(begin));
    //assert_debug(resultOUT.size() <= resultLimit);
}
    template<typename OutContainer>
void CStringTool::split(const char* str, std::string::value_type separator, OutContainer& resultOUT, size_t resultLimit /* = -1*/)
{
    std::string temp = str;
    CStringTool::split(temp, separator, resultOUT, resultLimit);
}
    template <class InputIterator>
inline std::string& CStringTool::join(const std::string &glue, InputIterator first, InputIterator last, std::string& resultOUT)
{
    resultOUT.clear();
    if(first == last)
        return resultOUT;
    for (; first != last; first++)
    {
        resultOUT.append(*first);
        resultOUT.append(glue);
    }
    resultOUT.erase(resultOUT.size() - glue.size());
    return resultOUT;
}
    template <class InputIterator>
inline std::string CStringTool::join(const std::string &glue, InputIterator first, InputIterator last)
{
    std::string resultOUT;
    return join(glue, first, last, resultOUT);
}
inline std::string& CStringTool::erase(std::string& str, const std::string& to_remove)
{
    return replace(str, to_remove, "");
}
inline std::string CStringTool::repeat(const std::string& str, std::string::size_type times)
{
    std::string resultOUT;
    return repeat(str, times, resultOUT);
}
inline bool CStringTool::is_lower(char c)
{
    return c >= 'a' && c <= 'z';
}
inline bool CStringTool::is_upper(char c)
{
    return c >= 'A' && c <= 'Z';
}
inline bool CStringTool::is_alpha(char c)
{
    return is_lower(c) || is_upper(c);
}
inline bool CStringTool::is_numeric(char c)
{
    return c >= '0' && c <= '9';
}
inline bool CStringTool::is_alnum(char c)
{
    return is_alpha(c) || is_numeric(c);
}
inline bool CStringTool::is_whitespace(char c)
{
    return WHITE_SPACE.find(c) != std::string::npos;
}
inline char CStringTool::tolower(char c)
{
    return is_upper(c) ? c - 'A' + 'a' : c; 
}
inline char CStringTool::toupper(char c)
{
    return is_lower(c) ? c - 'a' + 'A' : c;
}
inline char CStringTool::swapcase(char c)
{
    if(is_upper(c)) 
        return c - 'A' + 'a';
    if(is_lower(c)) 
        return c - 'a' + 'A';
    return c;
}
inline int CStringTool::compare(const char* str1, const char* str2)
{
    if(str1 == NULL)
    {
        if(str2 == NULL) 
            return 0; 
        else    
            return -1;
    }
    else
    {
        if(str2 == NULL) 
            return 1; 
        else 
            return strcmp(str1, str2);
    }
}
inline int CStringTool::compare(const std::string& str1, const char* str2)
{
    if(str2 == NULL) 
        return 1; 
    else 
        return str1.compare(str2);
}
inline int CStringTool::compare(const std::string& str1, const std::string& str2)
{
    return str1.compare(str2);
}
inline int CStringTool::compare(const char* str1, const std::string& str2)
{
    return -compare(str2, str1);
}
inline int CStringTool::compare(char c1, char c2)
{
    if(c1 > c2)
        return 1;
    else if(c1 < c2)
        return -1;
    else
        return 0;
}
inline int CStringTool::icompare(const char* str1, const char* str2)
{
    if(str1 == str2)
        return 0;
    if(str1 == NULL)
        return -1;
    if(str2 == NULL)
        return 1;

    return eagle_strcasecmp(str1, str2);
}
inline int CStringTool::icompare(char c1, char c2)
{
    if(c1 == c2)
        return 0;
    if(is_alpha(c1))
        c1 = tolower(c1);
    if(is_alpha(c2))
        c2 = tolower(c2);
    if(c1 > c2)
        return 1;
    else// if(c1 < c2)
        return -1;
}
inline int CStringTool::compare_nature(const std::string& str1, const std::string& str2, bool case_sensitive /* = true*/)
{
    return compare_nature(str1.c_str(), str2.c_str(), case_sensitive);
}

inline bool CStringTool::empty(const char* pstr)
{
    return pstr == NULL || pstr[0] == '\0';
}
inline bool CStringTool::empty(const std::string& str)
{
    return str.empty();
}
inline bool CStringTool::empty(char c)
{
    return c == '\0';
}
inline size_t CStringTool::strlen(const char* pstr)
{
    return empty(pstr)? 0 : ::strlen(pstr);
}
inline size_t CStringTool::strlen(const std::string& str)
{
    return str.size();
}

inline bool CStringTool::trimEmpty(const char* pstr)
{
    std::string str(pstr);
    CStringTool::trim(str);
    return str.empty();
}

inline bool CStringTool::try_parse_int(const char* str, int* ret, char** end /* = NULL*/)
{
    char* p = NULL;
    long int n = 0;
    if(str == NULL || ret == NULL)
        goto L_ErrorEnd;    
    n = strtol(str, &p, 0);
    if(n == LONG_MAX || n == LONG_MIN)
    {
        if(errno == ERANGE)
            goto L_ErrorEnd;
    }
    else if(n == 0)
    {
        if(p == str)
            goto L_ErrorEnd;
    }
    if(end != NULL)
        *end = p;
    *ret = n;
    return true;
L_ErrorEnd:
    if(end != NULL)
        *end = const_cast<char*>(str);
    if(ret != NULL)
        *ret = 0;
    return false;
}

};

#endif
