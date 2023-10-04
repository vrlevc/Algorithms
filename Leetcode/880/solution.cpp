/*
880. Decoded String at Index
*/
#include <string>
#include <iostream>
#include <stack>
#include <cmath>
using namespace std;



class Solution {
public:
    string decodeAtIndex(string S, int K) {
        long N = 0;
        short i;
        for (i = 0; N < K; ++i)
            N = ('0'<=S[i]&&S[i]<='9') ? N * (S[i] - '0') : N + 1;
        while (i--)
            if ('0'<=S[i]&&S[i]<='9')
                N /= S[i] - '0', K %= N;
            else if (K % N-- == 0) {
                S = S[i];
                return S;
            }
        return S;
    }
};


int main()
{
    Solution s;
    cout << s.decodeAtIndex("vzpp636m8", 2920) << " : z\n";
    cout << s.decodeAtIndex("a23", 6) << " : a\n";
    cout << s.decodeAtIndex("leet2code3", 10) << " : o\n";
    cout << s.decodeAtIndex("ha22", 5) << " : h\n";
    cout << s.decodeAtIndex("a2345678999999999999999", 1) << " : a\n";

    return 0;
}