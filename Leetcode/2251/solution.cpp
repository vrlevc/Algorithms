/*
2251. Number of Flowers in Full Bloom
https://leetcode.com/problems/number-of-flowers-in-full-bloom/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>&& flowers, vector<int>&& people) 
    {
        vector<int> start, end;
        for (int t = 0; t<flowers.size(); ++t)
            start.push_back(flowers[t][0]), end.push_back(flowers[t][1]);
        sort(start.begin(), start.end());
        sort(end.begin(), end.end());
        
        for (int t=0; t<people.size(); ++t)
        {
            int started = upper_bound(start.begin(), start.end(), people[t]) - start.begin();
            int ended = lower_bound(end.begin(), end.end(), people[t]) - end.begin();
            people[t] = (started - ended);
        }
        return people;
    }
};

void print(vector<int>&& v)
{
    cout << "{ ";
    for (auto& x : v) 
        cout << x << " ";
    cout << "}";
}

int main()
{
    Solution s;
    cout << "Expected : "; print({1,2,2,2}); cout << "\n";
    cout << "Output   : "; print(s.fullBloomFlowers({{1,6},{3,7},{9,12},{4,13}}, {2,3,7,11})); cout << "\n\n";

    cout << "Expected : "; print({2,2,1}); cout << "\n";
    cout << "Output   : "; print(s.fullBloomFlowers({{1,10},{3,3}}, {3,3,2})); cout << "\n\n";

    return 0;
}