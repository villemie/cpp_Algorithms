#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <queue>
using namespace std;
/*
Kaaleppi on juuri ryöstänyt pankin ja aikoo paeta kaupungista sataman kautta. Kuitenkin poliisi haluaa pysäyttää hänet sulkemalla joitakin katuja.
Mikä on pienin määrä katuja, jotka poliisin täytyy sulkea, jotta ei ole mitään reittiä pankista satamaan?
Syöte
Ensimmäisellä rivillä on kaksi kokonaislukua n ja m: risteysten ja katujen määrä. Risteykset on numeroitu 1,2,…,n. Pankki on risteyksessä 1 ja satama on risteyksessä n.
Sitten tulee m riviä, jotka kuvaavat kadut. Jokaisella rivillä on kaksi kokonaislukua a ja b: risteysten a ja b välillä on katu. Kaikki kadut ovat kaksisuuntaisia, ja kahden risteyksen välillä on enintään yksi katu.
*/
void createGraph(vector<int> graph[100], vector<int> edges[100], int n, int m)
{
    //vector<int> inputL = {1, 2, 1, 3, 2, 3, 3, 4, 4, 5, 4, 6, 5, 6};
    vector<int> inputL = {1,2,1,3,2,3,2,5,3,5,3,4,4,6,5,7,5,6,6,7};
    int j = 0, start, end;
    for (int i = 0; i < m; i++)
    {
        start = inputL[j];
        j++;
        //cin >> start;
        end = inputL[j];
        j++;
        //cin >> end;
        edges[i].push_back(start);
        edges[i].push_back(end);
        edges[i].push_back(start);
        edges[i].push_back(end);
        graph[start].push_back(end);
        graph[end].push_back(start);
    }
}
bool uniteNodes(int edgeInd, int n, vector<int> edges[100], int m)
{
    //n2 will be integrated to n1 and all its edges will lead to n1. All edges between n1 and n2 will be removed
    int n1 = edges[edgeInd][2];
    int n2 = edges[edgeInd][3];
    if (n1 == 1 || n1 == n)
    {
        if (n2 == 1 || n2 == n)
        {
            return false;
        }
    }
    else if (n2 == 1 || n2 == n)
    {
        int k = n1;
        n1 = n2;
        n2 = k;
    }
    else
    {
        int rnd = (rand() % 2);
        if (rnd == 0)
        {
            int k = n1;
            n1 = n2;
            n2 = k;
        }
    }

    //Decide which node will be
    //cout << "Yhdistetään " << n1 << " ja " << n2 << "\n";
    //Goes throught every edge
    for (int i = 0; i < m; i++)
    {
        //If n2 is part of edge is will be handled
        if (edges[i][2] == n2)
        {
            //If edge goes between n1 and n2 it will be marked -1
            if (edges[i][3] == n1)
            {
                edges[i][2] = -1;
                edges[i][3] = -1;
                //cout << "Edge " << n2 << "-" << n1 << "Tuhottu \n";
            }
            else
            {

                //cout << "Edge " << edges[i][2] << "-" << edges[i][3] << "Tunnetaan jatkossa" << n1 << "-" << edges[i][3] << "\n";
                edges[i][2] = n1;
            }
        }
        else if (edges[i][3] == n2)
        {
            if (edges[i][2] == n1)
            {
                edges[i][2] = -1;
                edges[i][3] = -1;
                //cout << "Edge " << n1 << "-" << n2 << "Tuhottu \n";
            }
            else
            {
                //cout << "Edge " << edges[i][2] << "-" << edges[i][3] << "Tunnetaan jatkossa" << edges[i][2] << "-" << n1 << "\n";
                edges[i][3] = n1;
            }
        }
    }
    return true;
}
//Using Kargers algorithm to get one cut
void karger(vector<int> graph[100], vector<int> edges[100], int n, int m, int &best, vector<pair<int, int>> &bestEdges, vector<int> next)
{

    //vector <int> next;
    for (int i = 0; i < m; i++)
    {
        edges[i][2] = edges[i][0];
        edges[i][3] = edges[i][1];
        next.push_back(i);
    }
    //Shuffle vector next
    for (int i = 0; i < m - 1; i++)
    {
        int j = i + rand() % (m - i);
        swap(next[i], next[j]);
    }
    cout << "NEXT: \n";
    for (int x : next)
    {
        cout << x << " ";
    }

    int nLeft = n;

    int i = 0;
    while (nLeft > 2)
    {
        if (uniteNodes(next[i], n, edges, m))
        {
            nLeft--;
        }
        i++;
    }
    //Collect edgest that are left
    vector<pair<int, int>> currentEdges;
    int edgesN = 0;
    for (int i = 0; i < m; i++)
    {
        if (edges[i][2] != -1)
        {
            currentEdges.push_back(make_pair(edges[i][0], edges[i][1]));
            edgesN++;
        }
    }
    //If answer is best if will be saved
    cout << "Eräs vastaus on " << edgesN << "\n";
    for (pair<int, int> x : currentEdges)
    {
        cout << x.first << "-" << x.second << " ";
    }
    cout << "\n";
    if (edgesN < best)
    {
        best = edgesN;
        bestEdges = currentEdges;
    }
}
void checkStart(vector<int> edges[100], int n, int m, int &best, vector<pair<int, int>> &bestEdges)
{
    int startEdges = 0;
    vector<pair<int, int>> currentEdges;
    for (int i = 0; i < m; i++)
    {
        if ((edges[i][0] == 1) || (edges[i][1]) == 1)
        {
            currentEdges.push_back(make_pair(edges[i][0], edges[i][1]));
            startEdges++;
        }
    }
    if (startEdges < best)
    {
        bestEdges = currentEdges;
        best = startEdges;
    }
    //Check if onyl destination should be cut off
    startEdges = 0;
    currentEdges.clear();
    for (int i = 0; i < m; i++)
    {
        if ((edges[i][0] == n) || (edges[i][1]) == n)
        {
            currentEdges.push_back(make_pair(edges[i][0], edges[i][1]));
            startEdges++;
        }
    }
    if (startEdges < best)
    {
        bestEdges = currentEdges;
        best = startEdges;
    }
}
bool getRoute(vector<int> graph[100], int parent[100], bool visited[100], int n)
{
    bool success = false;
    queue<int> q;
    q.push(1);
    visited[1] = true;
    parent[1] = -1;

    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int i : graph[u])
        {
            if (visited[i] == false)
            {
                q.push(i);
                parent[i] = u;
                visited[i] = true;
            }
        }
    }
    cout << "";
    success = (visited[n] == true);

    return success;
}
bool findRoutes(vector<int> graph[100], int n)
{
    vector<int> originalPath;
    originalPath.push_back(n);
    int parent[100];
    bool visited[100];
    getRoute(graph, parent, visited, n);
    //Mark previous route to visited
    for (int i = 0; i <= n; i++)
    {
        visited[i] = false;
    }
    int i = parent[n];
    while (parent[i] != -1)
    {
        originalPath.push_back(i);
        visited[i] = true;
        i = parent[i];
    }
    originalPath.push_back(1);

    //If second route finding fails only one edge has to be cut
    if (getRoute(graph, parent, visited, n) == false)
    {
        //Clean visited
        for (int i = 0; i <= n; i++)
        {
            visited[i] = false;
        }
        int start, end;
        while (originalPath.size() > 1)
        {
            //remove one edge at the time, when path cannot be found we have found correct edge to cut
            start = originalPath.back();
            originalPath.pop_back();
            end = originalPath.back();
            for (int i = 0; i < graph[start].size(); i++)
            {
                if (graph[start][i] == end)
                {
                    graph[start][i] = 0;
                }
            }
            for (int i = 0; i < graph[end].size(); i++)
            {
                if (graph[end][i] == start)
                {
                    graph[end][i] = 0;
                }
            }
            if (getRoute(graph, parent, visited, n) == false)
            {
                cout << "Löytyi! " << start << "-" << end << " on poistettava";
                return false;
            }
            //Clean visited
            for (int i = 0; i <= n; i++)
            {
                visited[i] = false;
            }
        }
        return false;
    }
    return true;
}
void getMinCut(vector<int> graph[100], vector<int> edges[100], int n, int m)
{

    int best = 9999;
    vector<pair<int, int>> bestEdges;
    if (findRoutes(graph, n))
    {
        vector<int> next;
        for (int i = 0; i < m; i++)
        {
            next.push_back(i);
        }
        srand((unsigned)time(0));
        for (int i = 0; i < m - 1; i++)
        {
            int j = i + rand() % (m - i);
            swap(next[i], next[j]);
        }

        for (int i = 0; i < 10; i++)
        {
            karger(graph, edges, n, m, best, bestEdges, next);
        }
        checkStart(edges, n, m, best, bestEdges);
        cout << "VASTAUS:" << best << "\n";
        for (int i = 0; i < best; i++)
        {
            cout << bestEdges[i].first << "-" << bestEdges[i].second << " leikataan\n";
        }
    }
}
int main()
{
    int n = 7;
    //cin >> n;
    int m = 10;
    //cin >> m;
    vector<int> edges[100];
    vector<int> graph[100];
    createGraph(graph, edges, n, m);
    getMinCut(graph, edges, n, m);
}