#include <iostream>
#include <fstream>
#include <vector>
//                      #include <bits/stdc++.h>
using namespace std;

// undirected weighted graph representation using adjacency list

int main() {
    ifstream fin("txt/input.txt");
    ofstream fout("txt/output.txt");   // opens/creates output.txt for writing

    if (!fin || !fout) {
        cerr << "Could not open file!" << endl;
        return 1;
    }

    int n,m;
    // cout << "Enter the number of vertices and edges: ";
    fin >> n >> m;

    vector<vector<pair<int, int>>> graph(n);
    for(int i = 0; i < m; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    
    for(int i=0; i<n ; i++) {
        fout << "Vertex : " << i << " -> ";
        int a = graph[i].size();
        for (int j=0; j<a; j++) {
            fout << "(" << graph[i][j].first << ", " << graph[i][j].second << ") ";
        }
    }
    fin.close();  // good practice, though it auto-closes when fin goes out of scope
    fout.close();
    return 0;
}