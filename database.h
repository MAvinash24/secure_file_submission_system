#ifndef DATABASE_H
#define DATABASE_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <string>

class Database {
public:
    Database(const std::string& host, const std::string& user, const std::string& password, const std::string& dbname);
    ~Database();

    bool connect();
    void disconnect();

    // Methods to interact with the database
    void createTables();
    void registerUser(const std::string& username, const std::string& password);
    bool userExists(const std::string& username);
    void uploadFile(int userId, const std::string& filename, const std::string& fileContent);
    
private:
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* connection;

    std::string host;
    std::string user;
    std::string password;
    std::string dbname;

    void executeQuery(const std::string& query);
};

#endif // DATABASE_H
