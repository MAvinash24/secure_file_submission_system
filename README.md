# Secure File Submission System

## Overview
The Secure File Submission System is a C++ application designed to securely upload and store files (small .txt files and image formats such as .png, .jpg, and .jpeg) in a database using AES-256-CBC encryption. The application utilizes a MySQL (MariaDB) database to manage user registrations and store encrypted files securely.

## Features
- User registration with username and password.
- Secure file uploads with AES-256 encryption.
- Encrypted file content and initialization vector (IV) are stored in the database.
- Simple command-line interface for user interaction.

## Getting Started

### Prerequisites
- C++ Compiler (e.g., g++)
- MySQL (MariaDB) server
- OpenSSL library
- C++ MySQL Connector

## Notice

All files must be located in the same directory: database.cpp, database.h, file_encrypt.cpp, main.cpp, register.cpp, and register.h. Additionally, ensure that the files you wish to upload are also placed in the same directory.

### Installation

To compile the file system on a Linux system(Kali Linux),follow these steps:

1.Update the package list:

```
sudo apt update
```

2.Switch to the root user using your own user password:

```
sudo su
```

3.Ensure you have OpenSSL installed:

```
sudo apt install libssl-dev
```

4.Next, install the MySQL C++ Connector:

```
sudo apt-get install libmysqlcppconn-dev
```

5.Clone the repository:

```
git clone https://github.com/MAvinash24/secure_file_submission_system.git
```

6.Navigate to the project directory and compile the code:

```
cd secure_file_submission_system
```

```
g++ -o my_application main.cpp register.cpp file_encrypt.cpp -lmysqlcppconn -lssl -lcrypto
```

7.Start the MySQL (MariaDB) service:

```
systemctl start mysql
```

Then, log in to MySQL as the root user:

```
mysql -u root -p
```

8.Create and select the database:

To create the database, run:

```
CREATE database file_storage_system;
```

Then, switch to the newly created database:

```
USE file_storage_system;
```

9.Create two tables: Users and Files.

Users table:

To create the Users table, execute the following SQL statement:

```
CREATE TABLE Users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL
);
```

Files table:

To create the Files table, execute the following SQL statement:

```
CREATE TABLE Files (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT NOT NULL,
    filename VARCHAR(255) NOT NULL,
    encrypted_content LONGBLOB NOT NULL,
    iv LONGBLOB NOT NULL,  
    upload_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES Users(id) ON DELETE CASCADE
);
```

10.Exit MySQL:

To exit the MySQL command line, simply run:

```
exit
```

## Run the program

```
./my_application
```

## Example

Sample Interaction
Upon executing the program, the menu will be displayed like this:

1. Register User
2. Upload File
3. Exit
Choose an option:

**Option 1:** Register a new user:

You will be prompted to enter a username and password, and the user will be registered in the Users table of the MySQL database.

Enter username: avatar

Enter password: password123

User registered successfully with ID: **1**

Option 2: Upload a file:

You will be prompted to enter a user ID, file name, and passphrase for encryption. The selected file, which can be a small .txt file or an image file in .png, .jpg, or .jpeg format, will be encrypted using AES-256-CBC and saved in the database.

Enter user ID: **1**

Enter file name: example.txt

Enter passphrase for encryption: my_secure_key

Uploading[#######################################################################........92%]

File uploaded and saved to database successfully!

Option 3: Exit the program.

This flow demonstrates the basic working of your secure_file_submission_system. The file will be encrypted using AES-256-CBC and stored securely in the database along with the initialization vector (IV).


# NOTE:

Make sure to update the MySQL (MariaDB) service credentials in the Database class constructor within database.cpp . Replace them with the correct username ("root") and password ("kali") to ensure a successful connection to the database.
Additionally, ensure that the same user ID from the user registration process is used for file uploads to maintain proper association between users and their files.

