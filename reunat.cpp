#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Merkkijonon reuna on merkkijono, joka on sekä merkkijonon alkuosa että loppuosa mutta ei koko merkkijono. Esimerkiksi merkkijonon abcababcab reunat ovat ab ja abcab.

Tehtäväsi on selvittää annetun merkkijonon kaikkien reunojen pituudet.
*/
int main()
{
    string input;
    cin>>input;
    int n = input.size();
    vector<int> z (n);
    int l = 0, r = 0;
    for (int i=1; i<n; i++) {
        z[i] = max(0,min(z[i-l],r-i));
        while (i+z[i]<n && input[z[i]] == input[i+z[i]]) z[i]++;
        if (i+z[i] > r) {
            l=i; r=i+z[i];
        }
    }
    int skip = 1;
    for(auto x: z){
        if(skip == 0){
            if(x != 0){
                skip = x-1;
                cout << x << " ";
            }
        }
        else{
            skip--;
        }
    }
}