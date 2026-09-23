#include <bits/stdc++.h>
using namespace std;

const int V   = 33;
const int E   = V * (V - 1) / 2;   // Complete graph--528 edges total
const int INF = INT_MAX;
const int SRC = 10;
const int DST = 20;

void generateGraph(vector<vector<int>> &graph, vector<vector<pair<int,int>>> &graphList){
    srand(42);  //fixed seed so we get the same graph every run

    for (int u = 0; u < V; u++) {
        for (int v = u + 1; v < V; v++) {
            int w = rand() % 100 + 1;   
            graph[u][v] = w;
            graph[v][u] = w;
            graphList[u].push_back({v, w});
            graphList[v].push_back({u, w});
        }
    }

    cout << "Graph ready: " << V << " vertices, " << E << " edges." << endl;
    cout << endl;
}

vector<vector<int>> warshall(vector<vector<int>> &dist)
{
    int a = dist.size();
 
    for (int k = 0; k < a; k++){
        for (int i = 0; i < a; i++){
            for (int j = 0; j < a; j++){
                if (dist[i][k] != INF && dist[k][j] != INF){
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    cout << "Floyd-Warshall done." << endl;
    return dist;
}

vector<int> dijkstra(vector<vector<pair<int,int>>> &graph, int n, int src)
{
    vector<int>  dist(n, INT_MAX);
    vector<bool> visited(n, false);
    dist[src] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push(make_pair(0, src));

    while (!pq.empty())
    {
        pair<int,int> top = pq.top();
        pq.pop();

        int d = top.first;
        int u = top.second;

        if (visited[u]) continue;    
        if (d > dist[u]) continue;   

        visited[u] = true;

        int a = graph[u].size();
        for (int j = 0; j < a; j++)
        {
            int v = graph[u][j].first;
            int w = graph[u][j].second;
            if (!visited[v] && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    cout << "Dijkstra (source = " << src << ") done." << endl;
    return dist;
}


void compare(vector<int> &d, vector<vector<int>> &D, int src, int dst)
{
    cout << endl;
    cout << "=============================" << endl;
    cout << "Dijkstra       d[" << dst << "]        = " << d[dst] << endl;
    cout << "Floyd-Warshall D[" << src << "][" << dst << "]   = " << D[src][dst] << endl;
    cout << endl;

    if (d[dst] == D[src][dst])
        cout << "MATCH: d[20] == D[10][20]" << endl;
    else
        cout << "MISMATCH: d[20] != D[10][20]" << endl;

    cout << "=============================" << endl;
}

int main()
{
    vector<vector<int>> graph(V, vector<int>(V, 0));
    vector<vector<pair<int,int>>> graphList(V);

    generateGraph(graph, graphList);

    vector<vector<int>> f = warshall(graph);
    vector<int> d = dijkstra(graphList, V, SRC);

    compare(d, f, SRC, DST);

    return 0;
}