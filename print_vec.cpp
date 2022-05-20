#include <vector>
#include <iostream>

template<typename T>
void print_vec(std::vector<T> vec){
    for(auto &elem : vec){
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}