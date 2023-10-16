/*
119. Pascal's Triangle II
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> row(rowIndex+1, 1); 
        
        int m = 0;
        for (int i=1; i<=rowIndex; ++i)
        {
            m = i / 2;
            for (int j=0; j<m; ++j)
            {
                row[m-j] += row[m-j-1];
                row[m+j+(i%2?1:0)] = row[m-j];
            }
            
        }

        return move(row);    
    }
};

void print(vector<int>&& v)
{
    for (const auto& i: v){
        cout << i << " ";
    }
    cout << "\n";
}

int main()
{
    Solution s;
    print( s.getRow(0) );
    print( s.getRow(1) );
    print( s.getRow(2) );
    print( s.getRow(3) );
    print( s.getRow(4) );
    print( s.getRow(5) );
    print( s.getRow(6) );
    print( s.getRow(7) );
    print( s.getRow(8) );

    return 0;
}