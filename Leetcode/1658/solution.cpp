/*
1658. Minimum Operations to Reduce X to Zero

You are given an integer array nums and an integer x. 
In one operation, you can either remove the leftmost 
or the rightmost element from the array nums and subtract 
its value from x. Note that this modifies the array for 
future operations.

Return the minimum number of operations to reduce x to 
exactly 0 if it is possible, otherwise, return -1.


Example 1:
Input: nums = [1,1,4,2,3], x = 5
Output: 2
Explanation: The optimal solution is to remove the last two elements to reduce x to zero.

Example 2:
Input: nums = [5,6,7,8,9], x = 4
Output: -1

Example 3:
Input: nums = [3,2,20,1,1,3], x = 10
Output: 5
Explanation: The optimal solution is to remove the last three elements and the first two elements (5 operations in total) to reduce x to zero.
*/

#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>&& nums, int x) {

        int N = nums.size();
        int i = -1, j = N;
        int Si = 0, Sj = 0;
        int Xi = 0, Xj = N+1;
        bool success = false;

        // Base
        for (int k=0; k<N; ++k) {
            if ( Si+nums[k] <=x ) { Si+=nums[k]; i=k; }
            else break;
        }

        if (i==N-1&&Si<x) 
            return -1;

        do
        {
            // Save min result:
            if ( Si+Sj == x ) { 
                if ( i+1+N-j < Xj+Xi ) { Xi=i+1; Xj=N-j; success=true; }   
            }

            // Move j till Si+Sj>x
            do {
                Sj+=nums[--j];
            } while ( Si + Sj < x );

            // Adjust i
            while ( Si + Sj > x ) { 
                if (i>=0) { Si-=nums[i--]; }
                else break;
            }
        }while (i>=0);

        if ( Si+Sj == x ) { 
            if ( i+1+N-j < Xj+Xi ) { Xi=i+1; Xj=N-j; success=true; }   
        }
        
        return (success?Xj+Xi:-1);
    }
};

int main() {

    Solution s;

    cout << "Input: nums = [1,1], x = 3\n";
    cout << "Expected: -1\n";
    cout << "Output: " << s.minOperations({1,1}, 3) << "\n\n";

    cout << "Input: nums = [1,1,4,2,3], x = 5\n";
    cout << "Expected: 2\n";
    cout << "Output: " << s.minOperations({1,1,4,2,3}, 5) << "\n\n";
    
    cout << "Input: nums = [5,6,7,8,9], x = 4\n";
    cout << "Expected: -1\n";
    cout << "Output: " << s.minOperations({5,6,7,8,9}, 4) << "\n\n";

    cout << "Input: nums = [3,2,20,1,1,3], x = 10\n";
    cout << "Expected: 5\n";
    cout << "Output: " << s.minOperations({3,2,20,1,1,3}, 10) << "\n\n";

    cout << "Input: nums = [10,1,1,1,1,1], x = 5\n";
    cout << "Expected: 5\n";
    cout << "Output: " << s.minOperations({10,1,1,1,1,1}, 5) << "\n\n";

    return 0;
}