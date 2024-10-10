#include <iostream>
#include "register.h"    // Include the header file instead of .cpp
#include "file_encrypt.cpp"  // Include the file encryption logic

using namespace std;

int main() {
    int option;
    FileUpload fileUpload;

    while (true) {
        cout << "1. Register User\n2. Upload File\n3. Exit\nChoose an option: ";
        cin >> option;

        if (option == 1) {
            registerUser();  // Register a new user
        } else if (option == 2) {
            string fileName, passphrase;
            int userId;

            cout << "Enter user ID: ";
            cin >> userId;
            cout << "Enter file name: ";
            cin >> fileName;
            cout << "Enter passphrase for encryption: ";
            cin >> passphrase;

            fileUpload.setFileName(fileName);  // Set the file name
            fileUpload.uploadFile(passphrase, userId);  // Upload the file
        } else if (option == 3) {
            cout << "Exiting..." << endl;
            break;
        } else {
            cout << "Invalid option. Try again!" << endl;
        }
    }

    return 0;
}
