#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;
/*
Annettuna on merkkijono sekä joukko haettavia merkkijonoja. Tehtäväsi on ilmoittaa jokaisesta haettavasta merkkijonosta sen esiintymien määrä.
Syöte

Syötteen ensimmäisellä rivillä on merkkijono, jossa on n merkkiä.
Seuraavalla rivillä on kokonaisluku k: haettavien merkkijonojen määrä. Tämän jälkeen on k riviä, jotka kuvaavat merkkijonot.
Kaikki merkkijonot muodostuvat merkeistä a...z.
*/
bool sortBySec(const pair<int,string> &a, const pair<int,string> &b)
{
return a.second < b.second;
}
void getSuffix(vector<pair<int, string>> &suffix, string input)
{
    string s;
    for (int i = 0; i < input.length(); i++)
    {
        s = input.substr(i,input.length()-1);
        suffix.push_back(make_pair(i,s));
    }
    //Arrange suffix to alphabetical order
    sort(suffix.begin(), suffix.end(), sortBySec);
}

void binarySearch(vector<pair<int, string>> suffix, string search){
    int lowerBound = 0, higherBound = 10;
    int i = 0;
    int j = suffix.size()-1;
    int test;
    int searchLength = search.size();
    string compareTo;
    
    //Finds index of alphabetically first instance
    while(true){
        test = (i + j)/2;
        compareTo = suffix[test].second.substr(0,searchLength);
        if(search.compare(compareTo) < 0){
            j = test;
        }
        else if(search.compare(compareTo) > 0){
            i = test;
        }
        else{
            compareTo = suffix[test-1].second.substr(0,searchLength);
            if((test == 0)||search.compare(compareTo) > 0){
                if(search.compare(compareTo) > 0){
                    lowerBound = test;
                    break;
                }
            }
            j = test;
            
        }
    }
    
    
    //Finds index of alphabetically last instance
    i = lowerBound;
    j = suffix.size()-1;
    while(true){
        test = (i + j)/2;
        compareTo = suffix[test].second.substr(0,searchLength);
        if(search.compare(compareTo) < 0){
            j = test;
        }
        else if(search.compare(compareTo) > 0){
            i = test;
        }
        else{
            compareTo = suffix[test+1].second.substr(0,searchLength);
            if((test == suffix.size()-1)||search.compare(compareTo) > 0){
                j = test;
            }
            else{
                higherBound = test;
                break;
            }
        }
    }
    
    //Print answer
    cout << higherBound-lowerBound+1 << " alaraja: "<< lowerBound <<" yläraja "<< higherBound << "\n";
}
int main()
{
    string input = "ABAACBAB";
    //cin >> input;
    int n = 8;
    //cin >> n;
    vector<pair<int, string>> suffix;
    getSuffix(suffix, input);
    binarySearch(suffix, "B");
    cout << "We made IT";
}