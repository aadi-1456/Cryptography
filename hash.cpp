#include <iostream>
#include <openssl/sha.h>
#include <cstring>

std::string sha256Hash(const std::string& message) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, message.c_str(), message.length());
    SHA256_Final(digest, &sha256);

    char hashString[2 * SHA256_DIGEST_LENGTH + 1];
    hashString[2 * SHA256_DIGEST_LENGTH] = '\0';
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashString[i * 2], "%02x", (unsigned int)digest[i]);
    }

    return std::string(hashString);
}

int main() {
    std::string originalMessage;
    std::string modifiedMessage;

    // Get user input for the original message
    std::cout << "Enter the original message: ";
    std::getline(std::cin, originalMessage);

    // Get user input for the modified message
    std::cout << "Enter the modified message: ";
    std::getline(std::cin, modifiedMessage);

    // Compute hash for the original message
    std::string originalHash = sha256Hash(originalMessage);
    std::cout << "Original Message: " << originalMessage << std::endl;
    std::cout << "Original Hash: " << originalHash << std::endl;

    // Simulate receiver computing hash for the original message
    std::string computedOriginalHash = sha256Hash(originalMessage);
    std::cout << "Computed Original Hash: " << computedOriginalHash << std::endl;

    // Verify integrity of the original message
    if (computedOriginalHash == originalHash) {
        std::cout << "Original Message is intact and unmodified." << std::endl;
    } else {
        std::cout << "Original Message has been modified!" << std::endl;
    }

    std::cout << std::endl;

    // Compute hash for the modified message
    std::string modifiedHash = sha256Hash(modifiedMessage);
    std::cout << "Modified Message: " << modifiedMessage << std::endl;
    std::cout << "Modified Hash: " << modifiedHash << std::endl;

    // Simulate receiver computing hash for the modified message
    std::string computedModifiedHash = sha256Hash(modifiedMessage);
    std::cout << "Computed Modified Hash: " << computedModifiedHash << std::endl;

    // Verify integrity of the modified message
    if (computedModifiedHash == modifiedHash) {
        std::cout << "Modified Message is intact and unmodified." << std::endl;
    } else {
        std::cout << "Modified Message has been modified!" << std::endl;
    }

    return 0;
}
