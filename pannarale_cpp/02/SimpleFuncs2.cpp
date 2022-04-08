#include <iostream>

// Function with a single input
double times_pi(double a) {
    return 3.14*a;
}

// Declare to compiler question() is a void function
extern void question();

int main() {

    double a;

    question();
    std::cin >> a;

    std::cout << "Your number times pi is: " << times_pi(a) << std::endl;

    return 0;
}

// Now implement/define question()
void question() {
    std::cout << "What number do you want to multiply by pi? " << std::endl;
}
