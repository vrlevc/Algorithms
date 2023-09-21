#include <vector>
#include <numeric>
#include <iostream>
using namespace std;

// Alternating Coin Game
// • Given sequence of n coins of value v0, v1,...,vn 1
// • Two players (“me” and “you”) take turns
// • In a turn, take first or last coin among remaining coins
// • My goal is to maximize total value of my taken coins, where I go first
// • First solution exploits that this is a zero-sum game: I take all coins you don’t
class Solution {
public: 
    int ACG( const vector<int> c ) {
        int N = c.size();
        auto sum = [&](int i, int j) {
            int s = 0;
            for (int k=i; k<=j; ++k)
                s += c[k];
            return s;
        };
        // Base:
        vector< vector<int> > S( N, vector<int>(N, 0) );
        for (int i=0; i<N; ++i) 
            S[i][i] = c[i];
        // Topological Order:
        for (int j=1; j<N; ++j) {
            for (int i=j-1; i>=0; --i) {
                int Si = sum(i+1, j  );
                int Sj = sum(i  , j-1);
                // Relate:
                S[i][j] = max( c[i]+Si-S[i+1][j  ], 
                               c[j]+Sj-S[i  ][j-1] );
                // Loging:
                cout << "i=" << i << " j=" << j << "\n";
                cout << "c["<<i<<"]="<<c[i]<< " sum("<<i+1<<","<<j<<")="<<Si<<" S("<<i+1<<","<<j<<")="<<S[i+1][j]<<"\n";
                cout << "c["<<j<<"]="<<c[j]<< " sum("<<i<<","<<j-1<<")="<<Sj<<" S("<<i<<","<<j-1<<")="<<S[i][j-1]<<"\n";
                cout << "S("<<i<<","<<j<<")=max("<<c[i]+Si-S[i+1][j]<<","<<c[j]+Sj-S[i][j-1]<<")="<<S[i][j]<<"\n";
            }
        }      
        // Loging:
        for (int i=0; i<N; ++i) {
            cout << "\n";
            for (int j=0; j<N; ++j)
                cout << S[i][j] << " ";  
        }
        // Original Problem:
        return S[0][N-1];
    }
};

int main()
{
    vector<int> c{1,2,3,4,5};
    Solution s;
    auto max = s.ACG(c);
    cout << "\n\nMaximum total value of ";
    for (const auto& v : c) cout << v << ",";
    cout << " coins, where I go first is " << max << "\n\n";
    return 0;
}