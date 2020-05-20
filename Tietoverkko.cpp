#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
/*
Syrjälän tietoverkossa on n konetta ja m yhteyttä. Jokainen yhteys kuvaa, miten nopeasti jokin kone voi lähettää tietoa toiselle koneelle.
Kotivalo haluaa ladata tietoa palvelimelta. Mikä on suurin mahdollinen latausnopeus käyttäen verkossa olevia yhteyksiä?

Syöte
Syötteen ensimmäisellä rivillä on kaksi kokonaislukua n ja m: koneiden ja yhteyksien määrä. Koneet on numeroitu 1,2,…,n Kone 1 on palvelin ja kone n on Kotivalon kone.
Tämän jälkeen tulee m riviä, jotka kuvaavat yhteydet. Jokaisella rivillä on kolme kokonaislukua a, b ja c: kone a voi lähettää tietoa koneelle b nopeudella c.
*/
void createGraph(vector<int> graph[100], int flowMatrix[100][100], int n, int m)
{
    vector<int> inputL = {1, 2, 3, 2, 4, 2, 1, 3, 4, 3, 4, 5, 4, 1, 3};
    int i = 0, start, end, flow;
    //Saves edges to graph
    while (i < m * 3)
    {
        start = inputL[i];
        //cin >> start;
        i++;
        end = inputL[i];
        //cin >> end;
        i++;
        flow = inputL[i];
        //cin >> flow;
        i++;
        graph[start].push_back(end);
        //Residual edges 
        graph[end].push_back(start);
        //Amount of flow is saved in flowMatrix
        flowMatrix[start][end] = flow;
    }
}
bool getPath(vector<int> graph[100], int rGraph[100][100], int n, int parent[100])
{
    bool visited[100];
    memset(visited, 0, sizeof(visited));

    // Create a queue, enqueue source vertex and mark source vertex
    // as visited
    queue<int> q;
    q.push(1);
    visited[1] = true;
    parent[1] = -1;

    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int i: graph[u])
        {
            if (visited[i] == false && rGraph[u][i] > 0)
            {
                q.push(i);
                parent[i] = u;
                visited[i] = true;
            }
        }
    }

    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (visited[n] == true);
}
int edmondsKarp(vector<int> graph[100], int flowMatrix[100][100], int n, int m)
{
    int maxFlow = 0;
    int path[100] = {0};
    int u;
    while (getPath(graph, flowMatrix, n, path))
    {
        int pathFlow = INT_MAX;
        //i is index of current node and n is parent node of current node
        for (int i = n; i != 1; i = path[i])
        {
            u = path[i];
            pathFlow = min(pathFlow, flowMatrix[u][i]);
        }
        for (int i = n; i != 1; i = path[i])
        {
            u = path[i];
            flowMatrix[u][i] -=pathFlow;
            flowMatrix[i][u] +=pathFlow;
        }
        maxFlow += pathFlow;

    }
    return maxFlow;
}

int main()
{
    int n = 4; //Amount of nodes
    //cin >> n;
    int m = 5; //Amount of edges
    //cin >> n;
    vector<int> graph[100];
    int flowMatrix[100][100];
    int residualMatrix[100][100];
    createGraph(graph, flowMatrix, n, m);
    cout << edmondsKarp(graph, flowMatrix, n, m);
}