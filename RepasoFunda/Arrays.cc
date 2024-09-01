#include <iostream>

int main(int argc, char* argv[]) {
    int arr[5] = {10, 20, 30, 40, 50};

    std::cout << "Elementos del array:" << std::endl;
    for(int i = 0; i < 5; i++) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }

    return 0;
}