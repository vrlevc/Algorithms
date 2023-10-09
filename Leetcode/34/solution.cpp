/*
34. Find First and Last Position of Element in Sorted Array
https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>&& nums, int target) {
        if (nums.size() == 0) return {-1, -1};

        auto it = find(nums.begin(), nums.end(), target);
        
        int b = -1, e = -1;
        if (it != nums.end()) {
            b = e = it - nums.begin();
            while (0<=b-1 && nums[b-1] == target) --b;
            while (e+1<nums.size() && nums[e+1] == target) ++e;
        }

        return {b, e};
    }
};


int main()
{
    Solution s;
    s.searchRange({1, 2, 3}, 1);
    s.searchRange({1}, 0);
    s.searchRange({1,4}, 4);
    s.searchRange({5,7,7,8,8,10}, 8);
    s.searchRange({5,7,7,8,8,10}, 6);
    s.searchRange({}, 0);

    return 0;
}