#include <iostream>
#include <cmath>

// Function to calculate modular exponentiation: (base^exponent) % modulus
long long power(long long base, long long exponent, long long modulus) {
    if (modulus == 1) return 0; // Invalid case

    long long result = 1;
    base = base % modulus;

    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;

        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }

    return result;
}

int main() {
    // Get input from the user
    long long g, p, x, y;
    std::cout << "Enter the value of g: ";
    std::cin >> g;
    std::cout << "Enter the value of p: ";
    std::cin >> p;
    std::cout << "Enter the private key for party A (x): ";
    std::cin >> x;
    std::cout << "Enter the private key for party B (y): ";
    std::cin >> y;

    // Calculate public keys
    long long A = power(g, x, p);
    long long B = power(g, y, p);

    // Exchange public keys

    // Party A receives public key B from party B
    // Party A calculates the shared secret key
    long long sharedSecretA = power(B, x, p);

    // Party B receives public key A from party A
    // Party B calculates the shared secret key
    long long sharedSecretB = power(A, y, p);

    // Verify that both shared secret keys match
    if (sharedSecretA == sharedSecretB) {
        std::cout << "Shared secret key: " << sharedSecretA << std::endl;
    } else {
        std::cout << "Error: Shared secret keys do not match." << std::endl;
    }

    return 0;
}
