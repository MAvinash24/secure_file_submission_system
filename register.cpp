#include "register.h"  // Include the header file with the function declaration
#include <iostream>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include "database.cpp"  // Include the database connection

using namespace std;

class User {
public:
    User(int id, string username, string password) : id(id), username(username), password(password) {}

private:
    int id;
    string username;
    string password;
};

void registerUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    Database db;
    sql::PreparedStatement* pstmt = nullptr;
    sql::ResultSet* res = nullptr;
    int userId = 0;
    
    try {
        pstmt = db.getConnection()->prepareStatement("INSERT INTO Users (username, password) VALUES (?, ?)");
        pstmt->setString(1, username);
        pstmt->setString(2, password);
        pstmt->executeUpdate();

        // Fetch the last inserted user ID
        pstmt = db.getConnection()->prepareStatement("SELECT LAST_INSERT_ID()");
        res = pstmt->executeQuery();
        if (res->next()) {
            userId = res->getInt(1);  // Fetch the last inserted ID
        }

        User* user = new User(userId, username, password);
        cout << "User registered successfully with ID: " << userId << endl;

    } catch (sql::SQLException &e) {
        cerr << "SQLException in registerUser: " << e.what() << endl;
    }

    delete pstmt;  // Clean up prepared statement
    delete res;    // Clean up result set
}
