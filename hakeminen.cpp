#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Sinulle annetaan kaksi merkkijonoa, ja tehtäväsi on laskea, montako kertaa toinen merkkijono esiintyy ensimmäisen osana.

Syöte
Syötteen ensimmäisellä rivillä on merkkijono, jossa on n merkkiä, ja toisella rivillä on merkkijono, jossa on m merkkiä.
Molemmat merkkijonot muodostuvat merkeistä a...z.

Tuloste
Tulosta yksi kokonaisluku: tehtävän vastaus.

*/
int main()
{
    string input;
    cin>>input;
    int n = input.size();
    string subString;
    cin>>subString;
    int ssN = subString.size();
    vector<int> z (n);
    //if substring's length is equal to string's length, onyl check starting in the first letter is required 
    int x = 1;
    if(n != ssN){
        x = n;
    }
    int l = 0, r = 0;
    for (int i=0; i<x; i++) {
        z[i] = max(0,min(z[i-l],r-i));
        while ((i+z[i]<n && z[i] <= ssN) && subString[z[i]] == input[i+z[i]]) z[i]++;
        if (i+z[i] > r) {
            l=i; r=i+z[i];
        }
    }
    int answer = 0;
     for(auto x: z){
         if(x == ssN){
             answer++;
         }
     }
     cout << answer;
     
    
}