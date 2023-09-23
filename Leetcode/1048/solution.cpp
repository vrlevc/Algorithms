/*
1048. Longest String Chain

You are given an array of words where each word consists of lowercase English letters.

wordA is a predecessor of wordB if and only if we can insert exactly one letter anywhere in wordA without changing the order of the other characters to make it equal to wordB.

For example, "abc" is a predecessor of "abac", while "cba" is not a predecessor of "bcad".
A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1, where word1 is a predecessor of word2, word2 is a predecessor of word3, and so on. A single word is trivially a word chain with k == 1.

Return the length of the longest possible word chain with words chosen from the given list of words.

 

Example 1:

Input: words = ["a","b","ba","bca","bda","bdca"]
Output: 4
Explanation: One of the longest word chains is ["a","ba","bda","bdca"].

Example 2:

Input: words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]
Output: 5
Explanation: All the words can be put in a word chain ["xb", "xbc", "cxbc", "pcxbc", "pcxbcf"].

Example 3:

Input: words = ["abcd","dbqca"]
Output: 1
Explanation: The trivial word chain ["abcd"] is one of the longest word chains.
["abcd","dbqca"] is not a valid word chain because the ordering of the letters is changed.
 

Constraints:

1 <= words.length <= 1000
1 <= words[i].length <= 16
words[i] only consists of lowercase English letters.
*/

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    bool is_predecessor(const string& a, const string& b) {
        int fails = 0;
        auto i = a.begin();
        auto j = b.begin();

        while (i!=a.end() && j!=b.end() && fails<2)
        {
            if ( *i == *j ) { ++i; ++j; }
            else { ++fails; ++j; }
        }        

        return i==a.end() && (fails==1||j!=b.end());
    }



    int longestStrChain(vector<string>& words) {

        // Prepare : sort and remove duplicates:
        sort(words.begin(), words.end(), [](const string& a, const string& b) { return a.length() < b.length(); });
        auto last = unique(words.begin(), words.end());
        words.erase(last, words.end());

        // Base:
        vector<int> S(words.size(), 1);

        // Topological order:
        for (int i=0; i<words.size(); ++i) 
        {
            int max_s = 0;
            for (int j=i-1; j>=0; --j) {
                if ( words[i].length() - words[j].length() > 1 ) break;
                if (words[i].length() - words[j].length() == 1 && is_predecessor(words[j], words[i])) {
                    max_s = max( max_s, S[j] );
                }
            }
            S[i] += max_s;
        }    

        return *max_element(S.begin(), S.end());
    }
};


// return true if a is predecessor of b, false otherwise
bool is_predecessor(string a, string b) {
    int error_n = 0; // max 1
    auto i = a.begin();
    auto j = b.begin();

    return true;
}





int main() 
{
    Solution s;
    vector<string> words{"a","b","ba","bca","bda","bdca"};
    s.longestStrChain(words);
    words = {"xbc","pcxbcf","xb","cxbc","pcxbc"};
    s.longestStrChain(words);
    words = {"abcd","dbqca"};
    s.longestStrChain(words);

    return 0;
}




















