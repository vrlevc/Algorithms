/*
343. Integer Break
https://leetcode.com/problems/integer-break/
*/

#include <iostream>

using namespace std;

class Solution {
public:
    int integerBreak(int n) {
        constexpr const char N = 59;
        int S[N]={0};
        S[0] = S[1] = S[2] = 1; S[3] = 2;
        for (int i=2; i<=n; ++i)
            for (int k=2; k<i-1; ++k)
                S[i] = max( S[i], k * max(S[i-k], i-k) );
        return S[n];
    }
};


int main()
{
    Solution s;

    cout << s.integerBreak(2) << '\n';
    cout << s.integerBreak(10) << '\n';

    return 0;
}