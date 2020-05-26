#include <iostream>
#include <vector>
#include <map>
using namespace std;
/*
Bittijono muodostuu n bitistä. Jonoon tulee joukko muutoksia, joissa bitti vaihtuu vastakkaiseksi, ja tehtäväsi on ilmoittaa jokaisen muutoksen jälkeen, kuinka pitkä on pisin samaa bittiä toistava osuus jonossa.
Syöte
Ensimmäisellä rivillä on bittijono, jossa on n bittiä. Bitit on numeroitu 1,2,…,n.
Seuraavalla rivillä on kokonaisluku m: muutosten määrä.
Viimeisellä rivillä on m kokonaislukua x1,x2,…,xm, jotka kuvaavat muutokset.
Tuloste
Tulosta jokaisen muutoksen jälkeen, kuinka pitkä on bittijonon pisin samaa bittiä toistava osuus.
*/
//Fills vector with input and fills map with ques of same numbers
void startPrep(vector<int> v, int &n, map<int, int> &m, int &nChange)
{
    vector<int> inputL = {1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 10};
    int input;
    //cin >> input;
    while (inputL[n] < 2)
    {
        v.push_back(inputL[n]);
        n++;
    }
    nChange = inputL[n];
    //Fill map
    int started = 0;
    for (int i = 1; i < n; i++)
    {
        if (v[i] != v[i - 1])
        {
            m.emplace(started, (i - 1));
            started = i;
        }
    }
    m.emplace(started, (n - 1));
}
void changeMap(map<int, int> &m, int changeI, int n)
{
    int start, end, del1, del2;
    //TODO lisää jos ensimmäinen tai viimeinen vaihtuu
    auto it = m.lower_bound(changeI);
    if (it->first != changeI)
    {
        it--;
    }
    if(changeI == 0){
        if(it->second - it->first == 0){
            start = 0;
            it++;
            end = it->second;
            m.erase(0);
            m.erase(1);
            m.emplace(start,end);
        }
        else{
            end = it->second;
            m.erase(0);
            m.emplace(1,end);
            m.emplace(0,0);
        }
    }
    else if(changeI == n-1){
        if(it->second - it->first == 0){
            it--;
            it->second = n-1;
            m.erase(n-1);
        }
        else{
            it->second--;
            m.emplace(n-1,n-1);
        }
    }
    //If int changes in que, which length is 1, 3 ques must be united into one
    else if (it->second - it->first == 0)
    {
        it--;
        start = it->first;
        it++;
        del1 = it->first;
        it++;
        del2 = it->first;
        end = it->second;
        m[start] = end;
        m.erase(del1);
        m.erase(del2);
    }
    //If changeable number is first or last of que it will be moved to another que
    else if (changeI == it->first)
    {
            start = it->first;
            end = it->second;
            it--;
            it->second = changeI;
            m.erase(start);
            m.emplace(start + 1, end);
    }
    else if (changeI == it->second)
    {
        it->second = it->second - 1;
        it++;
        start = it->first;
        end = it->second;
        m.erase(start);
        m.emplace(start - 1, end);
    }
    //Else one que will be divided into 3 new ques
    else
    {
        end = it->second;
        it->second = changeI - 1;
        m.emplace(changeI, changeI);
        m.emplace(changeI + 1, end);
    }
    cout << "";
}
void getLongest(int n, map<int, int> m)
{
    int longest = 0, cur;
    for (auto x : m)
    {
        cur = x.second - x.first + 1;
        if (cur > longest)
        {
            longest = cur;
        }
    }
    cout << longest << " ";
}
void getAnswer(vector<int> v, int n, map<int, int> m, int nChange)
{
    vector<int> inputL = {6, 9, 2, 10, 2, 3, 1, 6, 8, 1};

    //cin >> nChanges;
    for (int i = 0; i < nChange; i++)
    {
        changeMap(m, inputL[i] - 1, n);
        getLongest(n, m);
    }
}
int main()
{
    int n = 0;
    int nChanges = 0;
    vector<int> v;
    map<int, int> m;
    startPrep(v, n, m, nChanges);
    getAnswer(v, n, m, nChanges);
}