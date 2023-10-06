/*
229. Majority Element II
https://leetcode.com/problems/majority-element-ii/
*/

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<int> majorityElement(vector<int>&& nums) {
        int N = nums.size();
        if (N == 0) return {};
        if (N == 1) return { nums[0] };

        int count1=0, count2=0, candidate1=0, candidate2=1;
        for (int i=0; i<N; ++i){
            int n = nums[i];
            if (n == candidate1)
                ++count1;
            else if (n == candidate2)
                ++count2;
            else if (count1 == 0) {
                candidate1=n; count1=1; }
            else if (count2 == 0) {
                candidate2=n; count2=1; }
            else {
                --count1; --count2;
            }
        }

        count1 = count2 = 0;
        for (int i=0; i<N; ++i){
            int n = nums[i];
            if      (n==candidate1) ++count1;
            else if (n==candidate2) ++count2;
        }
        
        char nn = 0;
        if (count1 > N / 3) { nums[0]=candidate1; ++nn; }
        if (count2 > N / 3) { nums[nn]=candidate2; ++nn; }
        nums.erase(nums.begin()+nn, nums.end());
        return nums;
    }
};

void print(vector<int>&& nums) {
    cout << "[ ";
    for (auto& v : nums)
        cout << v << " ";
    cout << "]\n";
}

int main() 
{
    Solution s; 

    print(s.majorityElement({6,5,5}));
    print(s.majorityElement({2,2,1,3}));
    print(s.majorityElement({0,3,4,0}));
    print(s.majorityElement({3,2,3}));
    print(s.majorityElement({1}));
    print(s.majorityElement({1,2}));

    cout << "\n\n";

    return 0;
}