#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//Adds coins to vector and sorts them
void addCoins(vector<int> &coins, int n){
    //int input;
    vector<int> inputL = {4,2,5,2};
    for(int i = 0; i < n; i++){
        //cin >> input;
        coins.push_back(inputL[i]);
    }
    sort(coins.begin(),coins.end());
}

void countCombinations(vector<int> coins, vector<int> possible, int n){
    //Counts highest coin combination value
    int highestCombination = 0;
    for(auto x: coins){
        highestCombination += x;
    }
    for(int i = 0; i <= highestCombination; i++){
        possible.push_back(0);
    }
    possible[0] = 1;

    //Counts possible coin combination values
    for(int j = 1; j <= n; j++){
        for(int i = highestCombination; i>-1; i--){
            if(possible[i] == 1){
                possible[i + coins[j-1]] = 1;
            }
        }
    }
    //Count amount of possibilities
    int answer = -1;
    for(auto x : possible){
        if(x == 1){
            answer++;
        }
    }
    cout << answer << "\n";
    //Print possibilities
    for(int i = 1; i<=highestCombination; i++){
        if(possible[i] == 1){
            cout << i << " ";
        }
    }
    

}
int main()
{
    int n = 4;
    //cin >> n;
    vector<int> coins;
    //Collects possible coin combinations
    vector<int> possible;
    addCoins(coins,n);
    countCombinations(coins, possible, n);

}