#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
    
public:
    int LIS(const string_view& A, const string_view& B) {

        int AN = A.length();
        int BN = B.length();

        vector< vector<int> > S(AN+1, vector<int>(BN+1, 0));

        for (int i=AN-1; i>=0; --i) {
            for (int j=BN-1; j>=0; --j) {
                S[i][j] = ( A[i] == B[j] ? 1 + S[i+1][j+1] : max( S[i+1][j], S[i][j+1] ) );
            }
        }

        return S[0][0];
    }
};

int main()
{
    const char* A = "hieroglyphology";
    const char* B = "michaelangelo";
    Solution s;
    int LIS = s.LIS(A, B);
    cout << "Longest Common Subsequence ( " << A << " : " << B << " ) = " << LIS << "\n\n";
    return 0;
}