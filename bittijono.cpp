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
void startPrep(vector<int> v, int &n, map<int,int> &m){
    vector<int> inputL = {0,0,1,0,1,1};
    int input;
    for(int i = 0; i<n;i++){
        //cin >> input;
        v.push_back(inputL[i]);
    }
    //Fill map
    int started = 0;
    for(int i = 1; i <n;i++){
        if(v[i] != v[i-1]){
            m.emplace(started,(i-1));
            started = i;
        }
    }
    m.emplace(started,(n-1));
}
void changeMap(map<int,int> &m, int changeI){
    int start, end, del1, del2;
    //TODO lisää jos ensimmäinen tai viimeinen vaihtuu
    auto it = m.lower_bound(changeI);
    if(it->first != changeI){
        it--;
    }
        //If int changes in que, which length is 1, 3 ques must be united into one
        if(it->second - it->first == 0){
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
        else if(changeI == it->first){
            start = it->first;
            end = it->second;
            it--;
            it->second = changeI;
            m.erase(start);
            m.emplace(start+1,end);
        }
        else if(changeI == it->second){
            it->second = it->second - 1;
            it++;
            start = it->first;
            end = it->second;
            m.erase(start);
            m.emplace(start-1,end);
        }
        //Else one que will be divided into 3 new ques
        else{
            end = it->second;
            it->second = changeI -1;
            m.emplace(changeI,changeI);
            m.emplace(changeI + 1, end);
        }
        cout << "";
}
void getLongest(int n, map<int,int> m){
    int longest = 0,cur;
    for(auto x:m){
        cur = x.second - x.first + 1;
        if(cur > longest){
            longest = cur;
        }
    }
    cout << longest << " ";
}
void getAnswer(vector<int> v, int n, map<int,int> m){
    vector<int> inputL = {3,2,5};
    int nChanges = 3;
    //cin >> nChanges;
    for(int i = 0; i <nChanges; i++){
        changeMap(m,inputL[i]-1);
        getLongest(n,m);
    }
}
int main()
{
    int n = 6;
    vector<int> v;
    map<int,int> m;
    startPrep(v,n,m);
    getAnswer(v,n,m);
}