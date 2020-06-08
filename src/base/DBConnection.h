/* 
 * File:   DBConnection.h
 *
 * Created on 2012年4月5日, 下午3:19
 */

#ifndef _DBCONNECTION_H_
#define    _DBCONNECTION_H_

#include "Sys.h"
#include "mysql++.h"

namespace eagle
{

class DBConnection
{
    public:
        DBConnection();
        virtual ~DBConnection();

        /// @brief 初始化连接
        bool init(const char* dbname, const char *user, const char *passwd, const char* ip, uint32_t port = 3306);

        /// @brief 断线重连
        bool reconnect();

        /// @brief 当前连接
        mysqlpp::Connection* connection();

        /// @brief 获得当前连接的一个查询对象
        mysqlpp::Query query();

        /// @brief delete语句
        template<typename T>
            static void makeDeleteQuery(mysqlpp::Query& query, const char* tableName, const T& where);    

        /// @brief delete语句
        static void makeDeleteQuery(mysqlpp::Query& query, const char* tableName, const char* where="");

        /// @brief insert语句
        template<typename Ssqls>
            static void makeInsertQuery(mysqlpp::Query& query, const Ssqls& ssqls, std::vector<bool>& flag);

        /// @brief insert语句
        template<typename Ssqls>
            static void makeInsertQuery(mysqlpp::Query& query, const std::vector<Ssqls>& rows, std::vector<bool>& flag); 

        /// @brief update语句
        template<typename T1, typename T2>
            static void makeUpdateQuery(mysqlpp::Query& query, const char* tableName, const T1& column, const T2& where);

        /// @brief update语句
        template<typename T>
            static void makeUpdateQuery(mysqlpp::Query& query, const char* tableName, const T& column);

            /// @brief update语句
            template<typename T1, typename T2, typename T3>
            static void makeUpdateQuery(mysqlpp::Query& query, const char* tableName, const T1& column, const T2& where, const T3& where1);
    private:
        mysqlpp::Connection __connection;
        BYTE __connectOK;
        std::string m_dbname;
        std::string m_user;
        std::string m_passwd;
        std::string m_ip;
        uint32_t m_port;
};

inline mysqlpp::Connection* DBConnection::connection()
{
    return &__connection;
}

inline mysqlpp::Query DBConnection::query()
{
    return __connection.query();
}

    template<typename T>
void DBConnection::makeDeleteQuery(mysqlpp::Query& query, const char* table, const T& where)
{

    query << "DELETE FROM `"<<table<<"` " << "WHERE " << where;

}

inline void DBConnection::makeDeleteQuery(mysqlpp::Query& query, const char* table, const char* where)
{
    query << "DELETE FROM `"<<table<<"` ";
    if(where && std::string(where) != "")
        query << "WHERE " << where;
}

    template<typename Ssqls>
void DBConnection::makeInsertQuery(mysqlpp::Query& query, const Ssqls& ssqls, std::vector<bool>& flag)
{

    query << "INSERT INTO " << ssqls.table() << " ( " << ssqls.field_list(&flag) << " ) VALUES (" << ssqls.value_list(&flag) << " )";

}


    template<typename Ssqls>
void DBConnection::makeInsertQuery(mysqlpp::Query& query, const std::vector<Ssqls>& rows, std::vector<bool>& flag)
{
    if(rows.empty())
        return;
    query << "INSERT INTO " << rows[0].table() << " ( " << rows[0].field_list(&flag) << " ) VALUES " ;
    for(unsigned int i = 0; i < rows.size(); i++){
        query << "( " << rows[i].value_list(&flag) << " )";
        if(i < rows.size() - 1){
            query << ",";
        }
    }

}

    template<typename T1, typename T2>
void DBConnection::makeUpdateQuery(mysqlpp::Query& query, const char* tableName, const T1& column, const T2& where)
{

    query << "UPDATE `"  << tableName << "` SET " << column << " WHERE " << where ;

}

    template<typename T>
void DBConnection::makeUpdateQuery(mysqlpp::Query& query, const char* tableName, const T& column)
{
    query << "UPDATE `"  << tableName << "` SET " << column ;

}

template<typename T1, typename T2, typename T3>
void DBConnection::makeUpdateQuery(mysqlpp::Query& query, const char* tableName, const T1& column, const T2& where, const T3& where1)
{

    query << "UPDATE `" << tableName << "` SET " << column << " WHERE " << where << " AND " << where1;

}
};

#endif    

