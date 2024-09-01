#include <iostream>

int main(int argc, char* argv[]) {
    int a = 10;
    int* p = &a;

    std::cout << "Valor de a: " << a << std::endl;
    std::cout << "Dirección de a: " << &a << std::endl;
    std::cout << "Valor de p (dirección de a): " << p << std::endl;
    std::cout << "Valor apuntado por p: " << *p << std::endl;

    return 0;
}
