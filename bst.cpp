#include <vector>
#include <iostream>

int search(std::vector<int>& nums, int target) {
    int l = 0, r = nums.size() - 1;
    int medium;
    while(r >= l){
        medium = l + (r - l) / 2;
        // std::cout << medium << '\n';
        if(nums[medium] > target){
            r = medium - 1;
        }
        else if(nums[medium] < target){
            l = medium + 1;
        }
        else{
            return medium;
        }
    }
    
    return -1;
}

int main(){
    std::vector<int> vec{5};

    std::cout << search(vec, -5);

}