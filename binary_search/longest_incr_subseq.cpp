#include <vector>
#include <iostream>
#include <algorithm>


int lengthOfLIS(std::vector<int>& nums) {
    std::vector<int> L(nums.size(), INT32_MAX);
    L[0] = nums[0];
    
    int count = 1;
    for(int i = 1; i < L.size(); ++i){
        int idx = std::upper_bound(L.begin(), L.end(), nums[i]) - L.begin();
        if(L[idx] == INT32_MAX){
            ++count;
        }
        L[idx] = nums[i];
        // print_vec(L);
    }
    // int count = 0;
    // for()
    return count;
}