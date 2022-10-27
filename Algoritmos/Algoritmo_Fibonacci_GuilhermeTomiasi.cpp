#include <iostream>

unsigned long long fibonnaci(unsigned n) {
    if (n <= 1)
        return n;
    else
        return (fibonnaci(n - 1) + fibonnaci(n - 2));
}

int main() {
    unsigned input;

    std::cout<<"Insira um n: ";
    std::cin>>input;

    for (auto i = 0; i < input; i++) {
        std::cout<<fibonnaci(i)<<", ";
    }
    std::cout<<fibonnaci(input);

    return 0;
}