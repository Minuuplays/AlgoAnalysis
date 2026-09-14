#include <bits/stdc++.h>
using namespace std;

vector<int> parent;
vector<int> rankk;

void print(vector<vector<pair<int,int>>> &g,int n,string s){
     for (int i = 0; i < n; i++) {
        cout << s << " : " << i << " -> ";
        int a = g[i].size();
        for (int j = 0; j < a; j++) {
            cout << "(" << g[i][j].first << ", " << g[i][j].second << ") ";
        }
        cout << "\n";
    }
    cout << endl;
}

void print(vector<pair<int,int>> &g,int n){
    int a = g.size();
    for (int j = 0; j < a; j++) {
        cout << "(" << g[j].first << ", " << g[j].second << ") ";
    }
    cout << "\n";
    cout << endl;
}


void make_set(int v) {
    parent[v] = v;
    rankk[v] = 0;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rankk[a] < rankk[b])
            swap(a, b);
        parent[b] = a;
        if (rankk[a] == rankk[b])
            rankk[a]++;
    }
}


int main(){
    int V,E;
    cin >> V >> E;

    parent.resize(V);
    rankk.resize(V);

    int W=15;
    vector<vector<pair<int,int>>> g(W);
    //vector<pair<int,int>> edges(E);

    for(int i=0;i<E;i++){
        int u,v,w;
        cin >> u >> v >> w ;
        if(w>=W){ 
            g.resize(w+1);
            W=w+1;
        } 
        g[w].push_back({u,v});
        //g[w].push_back({v,u});
        //edges.push_back({u,w});
        //edges.push_back({v,w});
    }

    print(g,W,"Weight");

    /*for(int i=0;i<V;i++){
        sort(g[i].begin(), g[i].end(), [](auto &left, auto &right) {
            return left.second < right.second;
        });
    }

    print(g,10);*/

    /*sort(edges.begin(), edges.end(), [](auto &left, auto &right) {
        return left.second < right.second;
    });

    print(edges,V);*/


    for (int i = 0; i < V; i++){
         make_set(i);
    }

    vector<vector<pair<int,int>>> gNew(V);

    int cost=0;
    for (int i=0;i<g.size();i++){
        for (auto e : g[i]) {
            int u=e.first;
            int v=e.second;

            if (find_set(u) != find_set(v)) {
                cost+=i;
                gNew[u].push_back({v,i});
                gNew[v].push_back({u,i});
                union_sets(u,v);
            }
        }
    }

    cout << "Result MST: " << endl;
    print (gNew,V,"Vertex");
    cout<< "Total Cost : " << cost << endl;

    return 0;
}

/*
9 14
0 1 4
0 2 8
1 2 11
2 4 7
2 5 1
3 1 8
3 4 20
3 6 4
3 7 7
4 5 6
5 6 2
6 7 11
6 8 10
7 8 9
*/