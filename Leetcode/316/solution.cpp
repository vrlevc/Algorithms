/*
316. Remove Duplicate Letters
https://leetcode.com/problems/remove-duplicate-letters
*/

#include <string>
#include <algorithm>
#include <array>
#include <iostream>
using namespace std;

#define IDX(c) c-'a'
#define TOP(s) *(s-1)
#define POP(s) TOP(s)=0;s-=1;
#define PUSH(c,s) *s=c;s+=1;

class Solution {
public:
    string removeDuplicateLetters(string s) {
        constexpr const char M = 'z'-'a'+1; 
        bool used[M] = {false};
        short poss[M]  = {0};
        char outs[M+1] = {0};

        for (short i=0; i<s.length(); ++i) 
            poss[ IDX(s[i]) ] = max( poss[ IDX(s[i]) ], i );
        
        char* stack = outs;
        for (short i=0; i<s.length(); ++i) {
            if (  !used[ IDX(s[i]) ] ) {
                while ( stack!=outs && TOP(stack)>s[i] && i < poss[ IDX( TOP(stack)) ] ) {
                    used[ IDX( TOP(stack)) ] = false;    
                    POP(stack);
                }
                PUSH(s[i],stack);
                used[ IDX(s[i]) ] = true;
            }
        }

        s.assign(outs);
        return s;
    }
};


int main() {

    Solution s;
    //cout << s.removeDuplicateLetters("bcabc") << "\n";
    //cout << s.removeDuplicateLetters("cbacdcbc") << "\n";
    //cout << s.removeDuplicateLetters("abacb") << "\n";
    cout << s.removeDuplicateLetters("bcabc") << "\n";

    return 0;
}