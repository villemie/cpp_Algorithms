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
bool sortBySec(const pair<int, string> &a, const pair<int, string> &b)
{
    return a.second < b.second;
}
void getSuffix(vector<pair<int, string>> &suffix, string input)
{
    string s;
    for (int i = 0; i < input.length(); i++)
    {
        s = input.substr(i, input.length() - 1);
        suffix.push_back(make_pair(i, s));
    }
    //Arrange suffix to alphabetical order
    sort(suffix.begin(), suffix.end(), sortBySec);
}

int lowerBound(vector<pair<int, string>> suffix, string search, int &lb)
{
    int test;
    int i = 0;
    int j = suffix.size() - 1;
    int searchLength = search.size();
    string compareTo = "";

    while (i <= j)
    {
        test = (i + j) / 2;
        compareTo = suffix[test].second.substr(0, searchLength);
        if (search.compare(compareTo) < 0)
        {
            j = test - 1;
        }
        else if (search.compare(compareTo) > 0)
        {
            i = test + 1;
        }
        else
        {
            if (test == 0)
            {
                if (search.compare(suffix[test + 1].second.substr(0, searchLength)) == 0)
                {
                    lb = test;
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                if (search.compare(suffix[test - 1].second.substr(0, searchLength)) == 0)
                {
                    j = test - 1;
                }
                else if (search.compare(suffix[test + 1].second.substr(0, searchLength)) == 0)
                {
                    lb = test;
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
        }
    }
    return -1;
}

void upperBound(vector<pair<int, string>> suffix, string search, int &ub)
{
    int test;
    int i = 0;
    int j = suffix.size() - 1;
    int searchLength = search.size();
    string compareTo = "";

    while (i <= j)
    {
        test = (i + j) / 2;
        compareTo = suffix[test].second.substr(0, searchLength);
        if (search.compare(compareTo) < 0)
        {
            j = test - 1;
        }
        else if (search.compare(compareTo) > 0)
        {
            i = test + 1;
        }
        else
        {
            if (test == suffix.size() - 1)
            {
                ub = suffix.size() - 1;
                return;
            }
            else
            {
                if (search.compare(suffix[test + 1].second.substr(0, searchLength)) == 0)
                {
                    i = test + 1;
                }
                else
                {
                    ub = test;
                    return;
                } 
            }
        }
    }
    return;
}


void binarySearch(vector<pair<int, string>> suffix, string search)
{
    int lb, ub;
    int lbTest = lowerBound(suffix, search, lb);
    //String is not found
    if (lbTest == -1)
    {
        cout << 0 << "\n";
    }
    //String is found exactly one time
    else if (lbTest == 0)
    {
        cout << 1 << "\n";
    }
    //String is found more than once
    else
    {
        upperBound(suffix, search, ub);
        cout << ub - lb + 1 << "\n";
    }
}

int main()
{
    string input = "ABAACBAB";
    //cin >> input;
    int n = 1;
    //cin >> n;
    vector<pair<int, string>> suffix;
    getSuffix(suffix, input);
    string searchedWord = "A";
    for(int i = 0; i < n; i++){
        //cin >> searchedWord;
        binarySearch(suffix, searchedWord);
    }
}