#include <iostream>
#include <vector>
#include <stack>
/*
Haluat suorittaa n kurssia, joilla on tiettyjä riippuvuuksia muotoa "kurssi a tulee suorittaa ennen kurssia b".
Tehtäväsi on etsiä jokin mahdollinen järjestys, jossa voit suorittaa kurssit.

Syöte
Syötteen ensimmäisellä rivillä on kaksi kokonaislukua n ja m: kurssien määrä ja riippuvuuksien määrä. Kurssit on numeroitu 1,2,…,n.
Seuraavat m riviä kuvaavat riippuvuudet. Jokaisella rivillä on kaksi kokonaislukua a ja b: kurssi a tulee suorittaa ennen kurssia b.
*/
using namespace std;
void createGraph(vector<int> graph[250000], int m, int n, vector<int> &nodeColour){
    int i=0, start, end;
    //Saves edges to graph
    while(i<m*2){
        cin >> start;
        i++;
        cin >> end;
        i++;
        graph[start].push_back(end);
    }
    for(i = 0; i <= n; i++){
        nodeColour.push_back(0);
    }
}
void search(int curNode, vector<int> graph[250000], vector<int> &nodeColour, stack<int> &route){
    if(nodeColour[curNode] == 1) return;
    for(int nextNode: graph[curNode]){
        search(nextNode,graph,nodeColour, route);
    }
    nodeColour[curNode] = 1;
    route.push(curNode);
    return;

}
void getRoute(vector<int> graph[100], vector<int> &nodeColour, int n){
    stack <int> route;
    for(int i = 1; i <= n ;i++){
        //If node is unvisited it should be handled
        if(nodeColour[i] == 0) search(i,graph,nodeColour,route);
    }
    //Print answer
    while(!route.empty()){
        cout << route.top() << " ";
        route.pop();
    }
}
int main()
{
    int n;
    cin >> n;
    int m;
    cin >> m;
    vector<int> graph[250000];
    vector<int> nodeColour;
    createGraph(graph,m,n, nodeColour);
    getRoute(graph,nodeColour,n);
}