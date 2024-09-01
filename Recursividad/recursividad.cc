#include <iostream>

int factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <numero>" << std::endl;
        return 1;
    }

    int num = std::atoi(argv[1]);
    int result = factorial(num);

    std::cout << "El factorial de " << num << " es " << result << std::endl;

    return 0;
}
