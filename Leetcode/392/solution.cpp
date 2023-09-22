/*
Given two strings s and t, return true if s is a subsequence of t, or false otherwise.

A subsequence of a string is a new string that is formed from the original string by 
deleting some (can be none) of the characters without disturbing the relative positions 
of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).

Example 1:
Input: s = "abc", t = "ahbgdc"
Output: true

Example 2:
Input: s = "axc", t = "ahbgdc"
Output: false
*/

#include <string>
using namespace std;

class Solution {
    const string* Ss = nullptr;
    const string* Ts = nullptr;
    int Sn = 0;
    int Tn = 0;
    bool isSubsequence(int Si, int Tj) {
        if (Si==Sn) return true;
        if (Tj==Tn) return false;
        for (int j=Tj; j<Tn; ++j) {
            if ( (*Ss)[Si] == (*Ts)[j] ) 
                return isSubsequence(Si+1, j+1); 
        }
        return false;
    }
public:
    bool isSubsequence(const string& s, const string& t) {
        Sn = s.length();
        Tn = t.length();
        Ss = &s;
        Ts = &t;
        for (int j=0; j<Tn-Sn; ++j)
            if (isSubsequence(0, j)) return true;
        return false;
    }
};

int main() {

    string s{"abc"};
    string t{"ahbgdc"};

    Solution sol;
    bool res = sol.isSubsequence(s, t);

    return 0;
}