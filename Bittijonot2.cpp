#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
/*
Tehtäväsi on laskea, montako n bitin jonoa on olemassa, 
jossa pisin samaa bittiä toistava osuus on vähintään k bitin mittainen.
*/

bool startPrep(int n , int k ,long long &totalN, int M, vector<int> &v){
     
    //if n < k answer is 0
    if(n<k){
        cout << 0;
        return true;
    }
    for(int i = 1; i <n;i++){
        totalN = (totalN*2)%M;
    }
    if(k == 1){
        cout << totalN;
        return true;
    }
    if(k == 2){
        cout << (totalN-2);
        return true;
    }
    v.push_back(0);
    for(int i = 1; i < k;i++){
        v.push_back(pow(2,i));
    }
    for(int i = k+1; i <= n;i++){
    }
    return false;
}
int count(int n, int k, vector<int> v, int M){
    int x;
    for(int i = k; i <= n; i++){
        x=0;
        for(int j = 0; j < k; j++){
            if(j > 0){
                x = (v[i-j] + x)%M;
            }
        }
        v.push_back(x);
    }
    return x;
}
int main() 
{ 
    int M = 1000000007;
    int n;
    cin >> n;
    int k;
    cin >> k;
    vector <int> v;
    long long totalN = 2;

    //If special cases occured program will be stopped.
    bool stop = startPrep(n,k,totalN,M, v);
    if(stop){
        return 0;
    }
    //Counts amount of binaries taht does not meet the requirements
    cout << (M + totalN - count(n,k,v,M))%M;
} 