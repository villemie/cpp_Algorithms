#include <iostream>
#include <vector>
#include <utility>
using namespace std;
/*
Sinulle on annettu n×n -ruudukko, joka kuvaa metsän. Jokaisessa ruudussa on merkki . (tyhjä) tai * (puu).
Haluat rakentaa metsään neliön muotoisen rakennuksen, mutta et halua kaataa mitään puuta rakennuksen takia.
Tehtäväsi on laskea jokaiselle rakennuksen koolle 1×1,2×2,…,n×n, montako mahdollista paikkaa niin suurelle rakennukselle on metsässä.

Syöte
Syötteen ensimmäisellä rivillä on kokonaisluku n: ruudukon koko.
Sitten syötteessä on n riviä, joista jokaisella on n merkkiä: metsän kuvaus.

Tuloste
Tulosta n kokonaislukua: rakennusten paikkojen määrät
*/
void doMGrid(char mGrid[25][25], pair<int,int> vGrid[25][25],  int n, vector<int> &answer)
{
    answer.push_back(0);
    string inputS = "..............*.....*............**.*.*...*..*..*.........*.**.....**..*......*..........*..........";
    //char input;
    int k = 0;
    for (int i = 1; i <= n; i++)
    {
        //cin >> input;
        for (int j = 1; j <= n; j++)
        {
            mGrid[j][i] = inputS[k];
            k++;
        }
    }
    for(int i = 0; i <= n;i++){
        vGrid[0][i].first = -1;
        vGrid[0][i].second = -1;
        vGrid[i][0].first = -1;
        vGrid[i][0].second = -1;
        answer.push_back(0);
    }
}
void largestSquare(pair<int,int> vGrid[25][25], int j, int i, vector<int> &answer){
    int lowest = 9999;
    int steps = 0;
    bool goLeft = true;
    if(vGrid[j][i].first > vGrid[j][i].second){
        goLeft = false;
    }
    if(goLeft){
        for(int k = 0; k < vGrid[j][i].first;k++){
            if(vGrid[j-k][i].second < lowest){
                lowest = vGrid[j-k][i].second;
            }
            if(lowest < steps){
                break;
            }
            steps++;
        }
        
    }
    else{
        for(int k = 0; k < vGrid[j][i].second;k++){
            if(vGrid[j][i-k].first < lowest){
                lowest = vGrid[j][i-k].first;
            }
            if(lowest < steps){
                break;
            }
            steps++;
        }
    }
    cout << j << " " << i << " Suurin neliö on " << steps << "\n";
    answer[steps]++;
}
void fillVGrid(char mGrid[25][25], pair<int,int> vGrid[25][25],  int n, vector<int> &answer){

    for(int i = 1; i <= n; i++){
        for(int j = 1; j<=n;j++){
            if(mGrid[j][i] == '*'){
                vGrid[j][i].first = -1;
                vGrid[j][i].second = -1;
            }
            else{
                //Check left
                if(vGrid[j-1][i].first == -1){
                    vGrid[j][i].first = 1;
                }
                else{
                    vGrid[j][i].first = vGrid[j-1][i].first + 1;
                }
                //Check up
                 if(vGrid[j][i-1].second == -1){
                    vGrid[j][i].second = 1;
                }
                else{
                    vGrid[j][i].second = vGrid[j][i-1].second + 1;
                }
                //Get largest square, which has current cell as bottom right corner
                largestSquare(vGrid, j,i, answer);
            }
        }
    }
}

void printGrids(char mGrid[25][25], pair<int,int> vGrid[25][25], int n){
for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << mGrid[j][i];
        }
        cout << "\n";
    }
    cout <<"\n\n";
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            cout << vGrid[j][i].first << "/" << vGrid[j][i].second << " ";
        }
        cout << "\n";
    }
    cout<<"\n";
    cout <<"\n\n";
}
void countAnswer(vector<int> answer, int n){
    for(int i = n-1; i > 0; i--){
        answer[i] += answer[i+1];
    }
    //Print answer
    for(int i = 1; i <=n;i++){
        cout << answer[i] << " ";
    }
}
int main()
{
    //Size of grid is n*n
    int n = 10;
    vector<int> answer;
    //Obstacles are marked in this grid
    char mGrid[25][25] = {0};
    //Minimum amount of turns to get to the grid are stored in this one
    pair<int,int> vGrid[25][25];
    doMGrid(mGrid, vGrid, n, answer);
    fillVGrid(mGrid, vGrid, n, answer);
    printGrids(mGrid, vGrid, n);
    countAnswer(answer, n);
}