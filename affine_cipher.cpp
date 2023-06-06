#include <iostream>
#include <string>
#include <cctype>

std::string affineCipherEncrypt(const std::string& plaintext, int a, int b) {
    std::string ciphertext;
    int n = plaintext.length();

    for (int i = 0; i < n; i++) {
        if (std::isalpha(plaintext[i])) {
            char c = std::toupper(plaintext[i]);
            int x = c - 'A';
            int encryptedChar = (a * x + b) % 26;
            char encrypted = 'A' + encryptedChar;
            ciphertext += encrypted;
        } else {
            ciphertext += plaintext[i];
        }
    }

    return ciphertext;
}

std::string affineCipherDecrypt(const std::string& ciphertext, int a, int b) {
    std::string plaintext;
    int n = ciphertext.length();
    int aInverse = 0;

    // Find multiplicative inverse of a
    for (int i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            aInverse = i;
            break;
        }
    }

    if (aInverse == 0) {
        throw std::invalid_argument("Invalid value of 'a'. It must be coprime with 26.");
    }

    for (int i = 0; i < n; i++) {
        if (std::isalpha(ciphertext[i])) {
            char c = std::toupper(ciphertext[i]);
            int y = c - 'A';
            int decryptedChar = (aInverse * (y - b + 26)) % 26;
            char decrypted = 'A' + decryptedChar;
            plaintext += decrypted;
        } else {
            plaintext += ciphertext[i];
        }
    }

    return plaintext;
}

int main() {
    std::string plaintext;
    int a, b;

    std::cout << "Enter the plaintext: ";
    std::getline(std::cin, plaintext);

    std::cout << "Enter the value of 'a' (multiplicative key): ";
    std::cin >> a;

    std::cout << "Enter the value of 'b' (additive key): ";
    std::cin >> b;

    std::string encryptedText = affineCipherEncrypt(plaintext, a, b);
    std::cout << "Encrypted text: " << encryptedText << std::endl;

    std::string decryptedText = affineCipherDecrypt(encryptedText, a, b);
    std::cout << "Decrypted text: " << decryptedText << std::endl;

    return 0;
}
