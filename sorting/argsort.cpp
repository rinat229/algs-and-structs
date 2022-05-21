#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>


template<typename T>
void print_vec(std::vector<T> vec){
    for(auto &elem : vec){
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}


template <typename T>
std::vector<int> argsort(const std::vector<T>& input){
    std::vector<int> indexes(input.size());
    std::iota(indexes.begin(), indexes.end(), 0);
    std::stable_sort(indexes.begin(), indexes.end(), [&input](int idxA, int idxB){
        return input[idxA] < input[idxB];
    });

    return indexes;
}

int main(){
    std::vector<int> to_sort = {3, -5, 4, 10, 7, -2};
    std::vector<int> argsorted = argsort(to_sort);
    print_vec(argsorted);
}