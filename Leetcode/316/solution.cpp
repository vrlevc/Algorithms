/*
316. Remove Duplicate Letters
https://leetcode.com/problems/remove-duplicate-letters
*/

#include <string>
#include <algorithm>
#include <array>
#include <iostream>
using namespace std;

class Solution {
public:
    string removeDuplicateLetters(string s) {
        constexpr const char M = 'z'-'a'+1; 
        bool used[M] = {false};
        short poss[M]  = {0};
        char outs[M+1] = {0};

        for (short i=0; i<s.length(); ++i) 
            poss[ s[i] - 'a' ] = max( poss[ s[i] - 'a' ], i );
        
        char* stack = outs;
        for (short i=0; i<s.length(); ++i) {
            if (  !used[s[i] - 'a'] ) {
                while ( stack!=outs && *(stack-1)>s[i] && i < poss[*(stack-1)-'a'] ) {
                    used[*(stack-1)-'a'] = false;    
                    *(stack-1) = 0; stack -= 1;
                }
                *stack = s[i]; stack += 1;
                used[s[i] - 'a'] = true;
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