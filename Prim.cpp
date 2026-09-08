#include <bits/stdc++.h>
using namespace std;

void print(vector<vector<int>> &g,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << g[i][j] << " ";
        }
        cout << endl;
    }
}


void print(vector<vector<pair<int,int>>> &g,int n){
     for (int i = 0; i < n; i++) {
        cout << "Vertex : " << i << " -> ";
        int a = g[i].size();
        for (int j = 0; j < a; j++) {
            cout << "(" << g[i][j].first << ", " << g[i][j].second << ") ";
        }
        cout << "\n";
    }
}

void dijkstra(vector<vector<pair<int, int>>> &graph, int n, int src);


int main(){
    int V , E;
    cin >> V >> E;

    vector<vector<int>> graph(V,vector<int>(V,0));
    vector<vector<pair<int,int>>> graphList(V);


    int u,v,w;
    for(int i=0;i<E;i++){
        cin >> u >> v >> w;
        graph[u][v]=w;
        graph[v][u]=w;
        graphList[u].push_back({v,w});
        graphList[v].push_back({u,w});
    }

    dijkstra(graphList, V, 0);


    cout << endl;
    print(graph,V);
    cout << endl;

    vector<bool> visited(V);

    for (int i = 0; i < V; i++){
         visited[i] = false;
    }
    visited[0] = true;

    int INF = INT_MAX;
    int x,y;
    int edge =0;
    int sum = 0;

    vector<vector<pair<int,int>>> newGraph(V);
    //priint(newGraph,V);

    while (edge < V - 1) {

    int min = INF; // int max = 0; .. maximum spanning tree 
    x = 0;
    y = 0;

    for (int i = 0; i < V; i++) {
      if (visited[i]) {
        for (int j = 0; j < V; j++) {
          if (!visited[j] && graph[i][j]) {  // not visited and there is an edge
            if (min > graph[i][j]) { // if(max < graph[i][j])
              min = graph[i][j];     // max = graph[i][j]
              // sum += graph[i][j];
              //cout << sum << endl;
              x = i;
              y = j;
            }
          }
        }
      }
    }
    cout << x << " - " << y << " :  " << graph[x][y];
    newGraph[x].push_back({y,graph[x][y]});
    newGraph[y].push_back({x,graph[x][y]});
    sum += graph[x][y];
    cout << endl << "Current Weight: " << sum ;

    cout << endl;
    visited[y] = true;
    edge++;
   }

    cout << endl;
    cout << "Total Weight :" << sum << endl;
    cout << endl;

    print(newGraph,V);

    dijkstra(newGraph, V, 0);

    return 0;
}

void dijkstra(vector<vector<pair<int, int>>> &graph, int n, int src) {
    vector<int> dist(n, INT_MAX);
    vector<bool> visited(n, false);
    dist[src] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; // greater is used to make it a min-heap ...flips the pq
    pq.push(make_pair(0, src)); // same as pq.push({0, src})

    while (!pq.empty()) {
        pair<int,int> top = pq.top();
        pq.pop();

        int d = top.first;
        int u = top.second;

        if (visited[u]) continue;      // already finalized, skip
        if (d > dist[u]) continue;     // stale entry, skip (lazy deletion)

        visited[u] = true;

        int a = graph[u].size();
        for (int j = 0; j < a; j++) {
            int v = graph[u][j].first;
            int w = graph[u][j].second;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    cout << "\nShortest distances from vertex " << src << ":\n";
    for (int i = 0; i < n; i++) {
        cout << "Vertex " << i << " : " << dist[i] << "\n";
    }
}