#pragma once  // This avoids multiple inclusions of the Database class

#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>

using namespace std;
using namespace sql::mysql;

class Database {
public:
    Database() {
        try {
            driver = get_mysql_driver_instance();
            con = driver->connect("tcp://127.0.0.1:3306", "root", "kali");  // Update with your MySQL credentials
            con->setSchema("file_storage_system");  // Your database schema name
        } catch (sql::SQLException &e) {
            cerr << "SQLException in Database: " << e.what() << endl;
        }
    }

    ~Database() {
        delete con;
    }

    sql::Connection* getConnection() {
        return con;
    }

private:
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
};
