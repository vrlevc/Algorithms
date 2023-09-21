#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
    
public:
    string LIS(const string_view& A) {

        const int N = A.length();
        vector<string> S( N );
        for (int i=0; i<N; ++i) S[i]=A[i];

        for (int i=N-1; i>=0; --i) 
            for (int j=i+1; j<N-1; j++)
                if (A[j] > A[i])
                    if  (1+S[j].length() > S[i].length())
                        S[i] = A[i] + S[j];

        auto lis = max_element(S.begin(), S.end(), [](const string &a, const string& b){ return a.length() < b.length(); }); 
        return (lis!=S.end()?*lis:"");
    }
};

int main()
{
    const char* A = "carbohydrate";
    Solution s;
    string lis = s.LIS(A);
    cout << "Longest Increasing Subsequence ( " << A << " ) = " << lis << "\n\n";
    return 0;
}