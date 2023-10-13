/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 */

#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

class MountainArray {
    vector<int> _d;
    int N;
    public:
        MountainArray(vector<int>&& data) : _d(data) { N=length(); }
        int get(int index) { assert(0 <= index && index < N); return _d[index]; }
        int length() { return _d.size(); }
 };
 

class Solution {
public:
    int findInMountainArray(int target, MountainArray &&mountainArr) {
        // search top
        int a = 0, b = mountainArr.length() - 1; 
        int M = (a+b)/2;
        int prev, curr, next;
        do {
            prev = mountainArr.get(M-1);
            curr = mountainArr.get(M+0);
            next = mountainArr.get(M+1);
            // Top
            if (prev<curr && curr>next) break;
            // Up
            if (prev<curr && curr<next) a=M;
            // Down
            if (prev>curr && curr>next) b=M;
            M = (b+a)/2;
        } while (true);

        if (curr==target) return M;

        int m;

        // try up
        int left = -1;
        a = 0; b = M-1; m = (a+b)/2; 
        while (a < b) {
            curr = mountainArr.get(m);
            if (  curr == target ) { left = m; break; }
            if ( target < curr   ) { b = m-1; }
            if (   curr < target ) { a = m+1; }
            m = (a+b)/2;
        };
        if ( a==b && mountainArr.get(a) == target ) left = a;

        // try down
        int right = -1;
        a = M+1; b = mountainArr.length() - 1; m = (a+b)/2; 
        while (a < b) {
            curr = mountainArr.get(m);
            if (  curr == target ) { right = m; break; }
            if ( target < curr   ) { a = m+1; }
            if (   curr < target ) { b = m-1; }
            m = (a+b)/2;
        };
        if ( a==b && mountainArr.get(a) == target ) right = a;

        //cout << "left:" << left << " right:" << right << "\n";
        return (left!=-1?left:right);
    }
};

int main()
{
    Solution s;

    cout << s.findInMountainArray(0, MountainArray({3,5,3,2,0})) << "\n";
    cout << s.findInMountainArray(2, MountainArray({1,2,3,4,5,3,1})) << "\n";
    cout << s.findInMountainArray(1, MountainArray({1,2,5,1})) << "\n";
    cout << s.findInMountainArray(0, MountainArray({1,2,5,1})) << "\n";
    cout << s.findInMountainArray(0, MountainArray({1,5,2})) << "\n";
    cout << s.findInMountainArray(3, MountainArray({1,2,3,4,5,3,1})) << "\n";
    cout << s.findInMountainArray(3, MountainArray({0,1,2,4,2,1})) << "\n";
}