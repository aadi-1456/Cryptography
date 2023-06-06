#include <iostream>
#include <fstream>
#include <string>
#include <openssl/sha.h>

int main() {
    std::ofstream passwordFile("passwords.txt");

    if (!passwordFile) {
        std::cerr << "Error creating the password file." << std::endl;
        return 1;
    }

    // Write 10 passwords to the file
    for (int i = 0; i < 10; ++i) {
        std::string password;
        std::cout << "Enter password " << (i + 1) << ": ";
        std::cin >> password;

        passwordFile << password << std::endl;
    }

    passwordFile.close();

    std::cout << "Password file created successfully." << std::endl;

    // Modify one password to store hash values
    std::fstream file("passwords.txt", std::ios::in | std::ios::out);

    if (!file) {
        std::cerr << "Error opening the password file." << std::endl;
        return 1;
    }

    std::string line;
    int lineCount = 0;

    while (std::getline(file, line)) {
        if (lineCount == 5) {
            unsigned char hash[SHA256_DIGEST_LENGTH];
            SHA256_CTX sha256;
            SHA256_Init(&sha256);
            SHA256_Update(&sha256, line.c_str(), line.length());
            SHA256_Final(hash, &sha256);

            std::string hashedPassword;
            for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
                char hex[3];
                sprintf(hex, "%02x", hash[i]);
                hashedPassword += hex;
            }

            file.seekp(file.tellg());
            file << hashedPassword;
            break;
        }

        lineCount++;
    }

    file.close();

    std::cout << "Modified password file to store hash values." << std::endl;

    return 0;
}
