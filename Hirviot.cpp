#include <iostream>
#include <vector>

using namespace std;
/*
Olet n×n ruudukon vasemmassa ylänurkassa ja tavoitteesi on päästä oikeaan alanurkkaan. Saat liikkua ruudukossa oikealle ja alaspäin.
Jokaisessa ruudussa on merkki . (tyhjä) tai * (hirviö). Jos menet ruutuun, jossa on hirviö, joudut tappeluun sen kanssa.
Mikä on pienin määrä hirviöitä reitillä vasemmasta ylänurkasta oikeaan alanurkkaan?

Syöte
Syötteen ensimmäisellä rivillä on kokonaisluku n: ruudukon koko.
Sitten syötteessä on n riviä, joista jokaisella on n merkkiä: ruudukon kuvaus.

Tuloste
Tulosta yksi kokonaisluku: pienin määrä hirviöitä.
*/
void doMGrid(char mGrid[25][25], int n)
{
    //Test 0
    //string inputS = "..*...*.***.....";
    //Test 2
    //string inputS = ".......*..*.*.*.***.......*...**.**.......*....***.......*...*...*......*......*......**.**..**.....";
    //Test 5
    //string inputS ="****************************************************************************************************";
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
void countSides(char mGrid[25][25], int vGrid[25][25], int n)
{
    if (mGrid[1][1] == '.')
    {
        vGrid[1][1] = 0;
    }
    else
    {
        vGrid[1][1] = 1;
    }
    //Counting first row
    for (int i = 2; i <= n; i++)
    {
        if (mGrid[i][1] == '*')
        {
            vGrid[i][1] = vGrid[i - 1][1] + 1;
        }
        else
        {
            vGrid[i][1] = vGrid[i - 1][1];
        }
    }
    //Counting first column
    for (int i = 2; i <= n; i++)
    {
        if (mGrid[1][i] == '*')
        {
            vGrid[1][i] = vGrid[1][i - 1] + 1;
        }
        else
        {
            vGrid[1][i] = vGrid[1][i - 1];
        }
    }
}
void countRest(char mGrid[25][25], int vGrid[25][25], int n)
{
    //Stores smallest amount of encountered monsters
    int smallest = 0;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 2; j <= n; j++)
        {
            if (vGrid[i - 1][j] < vGrid[i][j - 1])
            {
                smallest = vGrid[i - 1][j];
            }
            else
            {
                smallest = vGrid[i][j - 1];
            }

            if (mGrid[i][j] == '*')
            {
                vGrid[i][j] = smallest + 1;
            }
            else
            {
                vGrid[i][j] = smallest;
            }
        }
    }
}
int main()
{
    //Size of grid is n*n
    int n = 10;
    //Monsters are marked in this grid
    char mGrid[25][25] = {0};
    //Minimum amount of encountered monsters are stored in this one
    int vGrid[25][25] = {0};
    doMGrid(mGrid, n);
    //Lines with either index 1 have only one route to them, this counts encountered monsters
    countSides(mGrid, vGrid, n);
    //Counts rest of grid
    countRest(mGrid, vGrid, n);
    int line = n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << mGrid[j][i];
        }
        cout << "\n";
    }
    cout <<"\n\n";
    line = n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << vGrid[j][i];
        }
        cout << "\n";
    }
    cout << vGrid[n][n];
}