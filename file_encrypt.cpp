#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include "database.cpp"

using namespace std;

class FileUpload {
public:
    bool isFileSelected() const {
        return !fileName.empty();
    }

    void setFileName(const string& fName) {
        fileName = fName;
    }

    void uploadFile(const string& passphrase, int userId) {
        if (isFileSelected()) {
            string encryptedContent, iv;
            encryptFile(fileName, passphrase, encryptedContent, iv);
            saveFileToDatabase(fileName, encryptedContent, iv, userId);  // Store encrypted content and IV
        } else {
            cout << "No file selected!" << endl;
        }
    }

private:
    string fileName;

    void encryptFile(const string& fileName, const string& passphrase, string& encryptedContent, string& iv) {
        // Read file content (for both text and binary files)
        ifstream inFile(fileName, ios::binary);
        if (!inFile.is_open()) {
            throw runtime_error("Failed to open file: " + fileName);
        }

        stringstream buffer;
        buffer << inFile.rdbuf();
        string fileContent = buffer.str();
        
        inFile.close();

        // Generate random IV
        unsigned char iv_buf[EVP_MAX_IV_LENGTH];
        if (!RAND_bytes(iv_buf, sizeof(iv_buf))) {
            throw runtime_error("Failed to generate random IV");
        }
        iv.assign(reinterpret_cast<char*>(iv_buf), sizeof(iv_buf));

        // Create key from passphrase (simple demonstration, use proper key derivation like PBKDF2 or HKDF in production)
        unsigned char key[EVP_MAX_KEY_LENGTH];
        memset(key, 0, sizeof(key));  // Ensure key is zeroed before use
        strncpy(reinterpret_cast<char*>(key), passphrase.c_str(), sizeof(key));

        // Prepare encryption context
        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        if (!ctx) {
            throw runtime_error("Failed to create cipher context");
        }

        // Initialize encryption operation (AES-256-CBC)
        if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv_buf) != 1) {
            EVP_CIPHER_CTX_free(ctx);
            throw runtime_error("Failed to initialize encryption");
        }

        // Encrypt file content
        unsigned char encryptedBuf[fileContent.size() + EVP_MAX_BLOCK_LENGTH];
        int encryptedLen = 0;
        int len = 0;

        if (EVP_EncryptUpdate(ctx, encryptedBuf, &len, reinterpret_cast<const unsigned char*>(fileContent.data()), fileContent.size()) != 1) {
            EVP_CIPHER_CTX_free(ctx);
            throw runtime_error("Encryption failed");
        }
        encryptedLen += len;

        // Finalize encryption
        if (EVP_EncryptFinal_ex(ctx, encryptedBuf + encryptedLen, &len) != 1) {
            EVP_CIPHER_CTX_free(ctx);
            throw runtime_error("Failed to finalize encryption");
        }
        encryptedLen += len;

        encryptedContent.assign(reinterpret_cast<char*>(encryptedBuf), encryptedLen);

        // Clean up
        EVP_CIPHER_CTX_free(ctx);
    }

    // Function to save encrypted content and IV to the database
    void saveFileToDatabase(const string& originalFileName, const string& encryptedContent, const string& iv, int userId) {
        Database db;
        sql::PreparedStatement* pstmt = nullptr;

        try {
            pstmt = db.getConnection()->prepareStatement("INSERT INTO Files (user_id, filename, encrypted_content, iv) VALUES (?, ?, ?, ?)");
            pstmt->setInt(1, userId);
            pstmt->setString(2, originalFileName);
            pstmt->setString(3, encryptedContent);  // Save encrypted content
            pstmt->setString(4, iv);  // Save IV
            pstmt->executeUpdate();
            cout<<"Uploading[#######################################################################........92%]"<<endl;
            cout << "File uploaded and saved to database successfully!" << endl;
        } catch (sql::SQLException &e) {
            cerr << "SQLException in saveFileToDatabase: " << e.what() << endl;
        }

        delete pstmt;  // Clean up prepared statement
    }
};
