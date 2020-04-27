#include <iostream>
#include <vector>
using namespace std;
/*
Olet n×n ruudukon vasemmassa ylänurkassa ja tavoitteesi on päästä oikeaan alanurkkaan. Saat liikkua ruudukossa oikealle ja alaspäin.
Jokaisessa ruudussa on merkki . (tyhjä) tai * (este). Et voi kulkea ruudun kautta, jos siinä on este.
Mikä on pienin määrä käännöksiä reitillä vasemmasta ylänurkasta oikeaan alanurkkaan?

Syöte
Syötteen ensimmäisellä rivillä on kokonaisluku n: ruudukon koko.
Sitten syötteessä on n riviä, joista jokaisella on n merkkiä: ruudukon kuvaus.

Tuloste
Tulosta yksi kokonaisluku: pienin määrä käännöksiä.
Jos mitään reittiä ei ole olemassa, tulosta luku −1.
*/
void doMGrid(char mGrid[25][25], int n)
{
    
    string inputS = "..*...*.*...*.*.";
    char input;
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
}
void countSides(char mGrid[25][25], int vGrid[25][25], int dGrid[25][25], int n)
{
        vGrid[1][1] = 0;
        dGrid[1][1] = 2;
    //Counting first row
    for (int i = 2; i <= n; i++)
    {
        if ((mGrid[i][1] == '*')||(vGrid[i-1][1] ==-1))
        {
            vGrid[i][1] = -1;
            dGrid[i][1] = -1;
        }
        else
        {
            vGrid[i][1] = 0;
            dGrid[i][1] = 0;
        }
        
    }
    //Counting first column
    for (int i = 2; i <= n; i++)
    {
        if ((mGrid[1][i] == '*')||(vGrid[1][i-1] ==-1))
        {
            vGrid[1][i] = -1;
            dGrid[1][i] = -1;
        }
        else
        {
            vGrid[1][i] = 0;
            dGrid[1][i] = 1;
        }
        
    }
}
void countRest(char mGrid[25][25], int vGrid[25][25], int dGrid[25][25], int n)
{
    int up = 0;
    int left = 0;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 2; j <= n; j++)
        {   
            //Is current cell obstacle
            if(mGrid[j][i] == '*'){
                vGrid[j][i] = -1;
                dGrid[j][i] = -1;
            }
            else{
            //Amount of turns if using route coming from up
            if(vGrid[j][i-1] == -1){
                up = -1;
            }
            else{
                up = vGrid[j][i-1];
                if(dGrid[j][i-1] == 0){
                    up++;
                }
            }
            //Amount of turns if using route coming from left
            if(vGrid[j-1][i] == -1){
                left = -1;
            }
            else{
                left = vGrid[j-1][i];
                if(dGrid[j-1][i] == 1){
                    left++;
                }
            }
            //Choosing between left and up routes
            if((up == -1)||(left == -1)){
                if((up == -1)&&(left == -1)){
                    vGrid[j][i] = -1;
                    dGrid[j][i] = -1; 
                }
                else if(up == -1){
                    vGrid[j][i] = left;
                    dGrid[j][i] = 0;
                }
                else{
                    vGrid[j][i] = up;
                    dGrid[j][i] = 1; 
                }

            }
            else{
                if(up < left){
                    vGrid[j][i] = up;
                    dGrid[j][i] = 1; 
                }
                else if(left > up){
                    vGrid[j][i] = left;
                    dGrid[j][i] = 0; 
                }
                else{
                    vGrid[j][i] = up;
                    dGrid[j][i] = 2; 
                }
            }
            }
            cout << j << " " << i << " "<< vGrid[j][i] << " " << dGrid[j][i] << "\n";
        }
    }
}
void printGrids(char mGrid[25][25], int vGrid[25][25], int dGrid[25][25], int n){
for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << mGrid[j][i];
        }
        cout << "\n";
    }
    cout <<"\n\n";
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << vGrid[j][i];
        }
        cout << "\n";
    }
    cout<<"\n";
    cout <<"\n\n";
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << dGrid[j][i];
        }
        cout << "\n";
    }
    cout<<"\n";
}
int main()
{
    //Size of grid is n*n
    int n = 4;
    //Obstacles are marked in this grid
    char mGrid[25][25] = {0};
    //Minimum amount of turns to get to the grid are stored in this one
    int vGrid[25][25] = {0};
    //Keeps track on incoming directions 1 = from up, 2 = from left, 3 = both
    int dGrid[25][25] = {0};
    doMGrid(mGrid, n);
    //Lines with either index 1 have only one route to them, this counts encountered monsters
    countSides(mGrid, vGrid, dGrid, n);
    //Counts rest of grid
    countRest(mGrid, vGrid, dGrid, n);
    printGrids(mGrid, vGrid, dGrid, n);

    
    cout << vGrid[n][n];
}