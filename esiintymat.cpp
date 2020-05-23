#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;
/*
Annettuna on taulukko, jossa on n lukua. Tehtäväsi on määrittää jokaiselle k luvun yhtenäiselle alitaulukolle, mikä on useimmin esiintyvä luku alitaulukossa. Jos vastaus ei ole yksikäsitteinen, valitaan pienin luvuista.

Syöte
Syötteen ensimmäisellä rivillä on kaksi kokonaislukua n ja k: taulukon koko ja alitaulukon koko.
Seuraavalla rivillä on n kokonaislukua t1,t2,…,tn: taulukon sisältö.
*/
void addNumber(int a[100], unordered_map<int, int> &m, set<int> &s, int add)
{
    //First occurance
    if(a[add] == 0){
        a[add]++;
        s.emplace(add);
    }
    //Second occurance
    else if(a[add] == 1){
        a[add]++;
        m.emplace(add, 2);
    }
    //Number have occured more than twice
    else{
        a[add]++;
        auto it = m.find(add);
        if(it != m.end()){
        it->second++;
        } 
    }
}
void removeNumber(int a[100], unordered_map<int, int> &m, set<int> &s, int remove){
    if(a[remove] < 2){
        s.erase(remove);
    }
    else if(a[remove] < 3){
        m.erase(remove);
    }
    else{
        auto it = m.find(remove);
        if(it!=m.end()){
            it->second--;
        }
    }
    a[remove]--;
}
void insertFirst(int a[100], vector<int> &input, int k, int n, unordered_map<int, int> &m, set<int> &s)
{
    //vector<int> v = {2, 1, 1, 5, 1, 1, 5, 1};
    //vector<int> v = {5,2,8,2,3,7,6,2,10,6};
    //vector<int> v = {6, 9, 6, 3, 8, 4, 6, 9, 9, 8};
    vector<int> v = {2,3,2,5,1,6,5,6};
    //build vector of input
    int ip;
    for (int i = 0; i < n; i++)
    {
        ip = v[i];
        //cin >> ip;
        input.push_back(ip);
    }
    //Insert first k-1 numbers
    for (int i = 0; i < k-1; i++)
    {
        addNumber(a, m, s, input[i]);
    }
}
//Gets most common number in given subarray
void getCommon(unordered_map<int, int> &m, set<int> &s){
    //If map is empty answer is first int in set
    if(m.empty()){
        auto it = s.begin();
        cout << *it << " ";
    }
    else{
        int highestN = 0; //Highest value of occurances
        int highestI;     //Index of currently highest value
        unordered_map<int,int>::iterator it = m.begin();
        while(it != m.end()){
            if(it->second >= highestN){
                if((it->second > highestN)||(highestI > it->first)){
                    highestN = it->second;
                    highestI = it->first;
                }
            }
            it++;
        }
        cout << highestI << " ";
    }
}
void findAnswer(int a[100], vector<int> &input, int k, int n, unordered_map<int, int> &m, set<int> &s)
{
    for(int i = k-1; i < n;i++){
        addNumber(a, m, s, input[i]);
        getCommon(m,s);
        removeNumber(a, m, s, input[i-k+1]);
    }
}
int main()
{
    int n = 8;
    //cin >> n;
    int k = 5;
    //cin >> k;
    vector<int> input;
    unordered_map<int, int> m; //If number has more than one occurance amount is stored here
    set<int> s;      //If map is empty returns smalles number currenly active
    int a[100] = {}; // Stores amount of occurances
    insertFirst(a, input, k, n, m, s);
    findAnswer(a, input, k, n, m, s);
}