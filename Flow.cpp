#include<bits/stdc++.h>
using namespace std;

bool bfs(vector<vector<int>> &rsG, int s, int t, int parent[]) {
  bool visited[t+1];
  //memset(visited, 0, sizeof(visited));
  for(int i=0;i<(t+1);i++){
    visited[i]=false;
  }

  queue<int> q;
  q.push(s);
  visited[s] = true;
  parent[s] = -1;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v = 0; v < (t+1); v++) {
      if (visited[v] == false && rsG[u][v] > 0) {
        q.push(v);
        parent[v] = u;
        visited[v] = true;
      }
    }
  }

  return (visited[t] == true);
}

int fordFulkerson(vector<vector<int>> &g,int s,int t){
    int V = t+1;
    vector<vector<int>> rsGrph(V,vector<int>(V,0));

    int parent[V];
    int maxflow=0;

    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            rsGrph[i][j]=g[i][j];
        }
    }

    int u,v;
    while (bfs(rsGrph, s, t, parent)) {
    int pathflow = INT_MAX;
    for (v = t; v != s; v = parent[v]) {
      u = parent[v];
      pathflow = min(pathflow, rsGrph[u][v]);
    }

    for (v = t; v != s; v = parent[v]) {
      u = parent[v];
      rsGrph[u][v] -= pathflow;
      rsGrph[v][u] += pathflow;
    }

    maxflow += pathflow;
  }

    return maxflow;
}

int main(){
    int V,E;
    cin >> V >> E;
    vector<vector<int>> graph(V,vector<int>(V,0));
    for (int i=0;i<E;i++){
        int u,v,w;
        cin >> u >> v >> w;
        graph[u][v]=w;
    }

    /*for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            cout << graph[i][j]<< " ";
        }cout << endl;
    }*/

    cout<< "Maximum flow possible: " << fordFulkerson(graph,0,(V-1));

    return 0;
}


/*
6 9
0 1 16
0 2 13
2 1 4
1 3 12
3 2 9
2 4 14
4 3 7
3 5 20
4 5 4
*/