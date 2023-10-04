/*
3. Longest Substring Without Repeating Characters
https://leetcode.com/problems/longest-substring-without-repeating-characters/
*/

#include <iostream>
#include <string>
#include <set>
#include <queue>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.size()==0) return 0;
        char used[128] = {0};
        int f=0, b=0;
        int maxl = 0;
        used[s[0]] = 1;
        for (int i=1; i<s.size(); ++i) { 
            char c = s[i];
            if (used[c] == 0)
            {
                ++b;
                used[c] = 1;
            }
            else 
            {
                maxl = max(maxl, b - f + 1);
                while (s[f] != c) { used[s[f]]=0; ++f; }
                ++f;  
                ++b;  used[c]=1;            
            }
            
        }
        return max(maxl, b - f + 1);
    }
};

int main() 
{
    Solution s;
    cout << s.lengthOfLongestSubstring("") << '\n';
    cout << s.lengthOfLongestSubstring("a") << '\n';
    cout << s.lengthOfLongestSubstring("abba") << '\n';
    cout << s.lengthOfLongestSubstring("abcabcbb") << '\n';
    cout << s.lengthOfLongestSubstring("bbbbb") << '\n';
    cout << s.lengthOfLongestSubstring("pwwkew") << '\n';

    return 0;
}