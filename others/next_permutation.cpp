#include <vector>

void nextPermutation(vector<int>& nums) {
    int j = nums.size() - 2;
    while(j != -1 && nums[j] >= nums[j + 1]){
        --j;
    }
    
    if(j == -1){
        int l = 0, r = nums.size() - 1;
        while(l <= r){
            std::swap(nums[l++], nums[r--]);
        }
        return;
    }
    int k = nums.size() - 1;
    while(nums[j] >= nums[k]){
        --k;
    }
    std::swap(nums[j], nums[k]);
    
    int l = j + 1, r = nums.size() - 1;
    while(l <= r){
        std::swap(nums[l++], nums[r--]);
    }
}