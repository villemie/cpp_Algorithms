#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;
void addToMap(set<int> &s,unordered_map<int, int> &m, int add){
     unordered_map<int, int>::iterator it;
     if(s.find(add) == s.end()){
            s.emplace(add);
        }
        else{
            it = m.find(add);
            if(it != m.end()){
                it->second++;
            }
            else{
                m.emplace(add,2);
            }
        }
}
void removeFromMap(set<int> &s, unordered_map<int, int> &m, int remove){
    unordered_map<int, int>::iterator it;
    it = m.find(remove);
    if(it != m.end()){
        if(it->second < 3){
            m.erase(it->first);
        }
        else{
            it->second--;
        }
    }
    else{
        s.erase(remove);
    }
}
//Prepares maps
void startPrep(set<int> &s, unordered_map<int, int> &m, vector<int> &list, int n, int k){
    vector<int> inputL = {3,6,4,3,4,3,5,1,1,7};
    int input;
    for (int i = 0; i < n; i++)
    {
        //cin >> input;
        list.push_back(inputL[i]);
    }
    for (int i = 0; i < k; i++)
    {
       addToMap(s,m,list[i]);
    }
}
//Gets most common integer
void maxN(set<int> s, unordered_map<int, int> m){
unordered_map<int, int>::iterator it;
//if m is empty there is no duplicates, lowest int will be chosen
if(m.empty() == true){
    for(auto x: s){
        cout << x << " ";
        break;
    }
}
else{
    int maxI;
    int maxCount = 0;
    for(auto x: m){
        
        if((x.second > maxCount)||((x.second == maxCount)&&(x.first < maxI))){
            maxCount = x.second;
            maxI = x.first;
        }
    }
    cout << maxI << " ";

}
}

int main()
{
    //All ints are stored in set s
    set<int> s;
    //If amount of ceraint int is over 1 it is also stored in map m
    unordered_map<int, int> m;
    unordered_map<int, int>::iterator it;
    vector<int> list;
    int n = 10;
    //cin >> n;
    int k = 5;
    //cin >> k;
    startPrep(s,m,list,n,k);
    maxN(s,m);
    int i = 0;
    while(k < n){
            removeFromMap(s,m,list[i]);
            addToMap(s,m,list[k]);
            maxN(s,m);
        i++;
        k++;
    }
}