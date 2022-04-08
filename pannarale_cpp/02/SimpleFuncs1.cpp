#include <iostream>

// Function with a single input
double times_pi(double a) {
    return 3.14*a;
}

// Input-free void function
void question() {
    std::cout << "What number do you want to multiply by pi? " << std::endl;
}

int main() {

    double a;

    question();
    std::cin >> a;

    std::cout << "Your number times pi is: " << times_pi(a) << std::endl;

    return 0;
}
