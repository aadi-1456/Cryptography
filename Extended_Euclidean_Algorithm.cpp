#include <iostream>

int extendedEuclidean(int a, int b, int& x, int& y) {
    // Base case: if a is 0, set x = 0, y = 1, and return b as the gcd
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }

    // Recursive call to calculate gcd and coefficients
    int x1, y1;
    int gcd = extendedEuclidean(b % a, a, x1, y1);

    // Update coefficients x and y using the results of recursive call
    x = y1 - (b / a) * x1;
    y = x1;

    return gcd;
}

int main() {
    int a, b;
    std::cout << "Enter the first number (a): ";
    std::cin >> a;

    std::cout << "Enter the second number (b): ";
    std::cin >> b;

    int x, y;
    int gcd = extendedEuclidean(a, b, x, y);

    std::cout << "Extended Euclidean Algorithm Result:" << std::endl;
    std::cout << "GCD(" << a << ", " << b << ") = " << gcd << std::endl;
    std::cout << "x = " << x << ", y = " << y << std::endl;

    return 0;
}
