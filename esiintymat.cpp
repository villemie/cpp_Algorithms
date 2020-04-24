#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
int maxN(unordered_map<int, int> m, unordered_map<int, int>::iterator it )
{
    int maxN = 0;
    int i = 0;
    for(auto x: m){
        if(x.second >= maxN){
            if((x.second != maxN)||(x.first < i)){
                maxN = x.second;
                i = x.first;
            }
        }
    }
    return i;

}
int main()
{
    unordered_map<int, int> m;
    unordered_map<int, int>::iterator it;
    vector<int> inputL = {2, 3, 2, 5, 1, 6, 5, 6};
    vector<int> list;
    int n = 8;
    int k = 5;
    int input;
    for (int i = 0; i < n; i++)
    {
        //cin >> input;
        list.push_back(inputL[i]);
    }
    for (int i = 0; i < k; i++)
    {
        it = m.find(list[i]);
        if (it == m.end())
        {
            m.emplace(list[i], 1);
        }
        else
        {
            it->second++;
        }
    }

    cout << maxN(m,it);
}
