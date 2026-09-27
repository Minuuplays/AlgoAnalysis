#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// ================= Adjacency List generators =================
// g[i] holds pairs of (neighbor, weight)

vector<vector<pair<int,int>>> linearGList(int n){
    vector<vector<pair<int,int>>> g(n+1);
    int w;
    for(int i=0;i<n;i++){
        w = rand()%50;
        g[i].push_back(make_pair(i+1, w));
        g[i+1].push_back(make_pair(i, w));
    }
    return g;
}

vector<vector<pair<int,int>>> circularGList(int n){
    vector<vector<pair<int,int>>> g = linearGList(n);
    int w = rand()%50;
    g[n].push_back(make_pair(0, w));
    g[0].push_back(make_pair(n, w));
    return g;
}

vector<vector<pair<int,int>>> completeGList(int n){
    vector<vector<pair<int,int>>> g(n+1);
    int w;
    for(int i=0;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            w = rand()%50;
            g[i].push_back(make_pair(j, w));
            g[j].push_back(make_pair(i, w));
        }
    }
    return g;
}

vector<vector<pair<int,int>>> randomGList(int n, double p){
    vector<vector<pair<int,int>>> g(n+1);
    int w;
    double r;
    for(int i=0;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            r = (double)rand()/RAND_MAX;
            if(r < p){
                w = rand()%50;
                g[i].push_back(make_pair(j, w));
                g[j].push_back(make_pair(i, w));
            }
        }
    }
    return g;
}

// ================= Adjacency Matrix generators =================
// g[i][j] holds the weight of edge (i,j), 0 if no edge

vector<vector<int>> linearGMatrix(int n){
    vector<vector<int>> g(n+1, vector<int>(n+1, 0));
    int w;
    for(int i=0;i<n;i++){
        w = rand()%50;
        g[i][i+1] = w;
        g[i+1][i] = w;
    }
    return g;
}

vector<vector<int>> circularGMatrix(int n){
    vector<vector<int>> g = linearGMatrix(n);
    int w = rand()%50;
    g[n][0] = w;
    g[0][n] = w;
    return g;
}

vector<vector<int>> completeGMatrix(int n){
    vector<vector<int>> g(n+1, vector<int>(n+1, 0));
    int w;
    for(int i=0;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            w = rand()%50;
            g[i][j] = w;
            g[j][i] = w;
        }
    }
    return g;
}

vector<vector<int>> randomGMatrix(int n, double p){
    vector<vector<int>> g(n+1, vector<int>(n+1, 0));
    int w;
    double r;
    for(int i=0;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            r = (double)rand()/RAND_MAX;
            if(r < p){
                w = rand()%50;
                g[i][j] = w;
                g[j][i] = w;
            }
        }
    }
    return g;
}

// ================= Print functions =================

void printMatrix(vector<vector<int>> g){
    int n = g.size();
    cout << "     ";
    for(int i=0;i<n;i++) cout << i << "\t";
    cout << "\n";
    for(int i=0;i<n;i++){
        cout << i << "  | ";
        for(int j=0;j<n;j++){
            cout << g[i][j] << "\t";
        }
        cout << "\n";
    }
    cout << "\n";
}

void printList(vector<vector<pair<int,int>>> g){
    int n = g.size();
    for(int i=0;i<n;i++){
        cout << i << ": ";
        for(int k=0;k<(int)g[i].size();k++){
            cout << "(" << g[i][k].first << ", w=" << g[i][k].second << ") ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// ================= Demo =================

int main(){
    srand((unsigned)time(0));
    int n = 5;       // vertices 0..n
    double p = 0.5;  // edge probability for random graph

    cout << "===== LINEAR =====\n";
    cout << "List:\n";
    printList(linearGList(n));
    cout << "Matrix:\n";
    printMatrix(linearGMatrix(n));

    cout << "===== CIRCULAR =====\n";
    cout << "List:\n";
    printList(circularGList(n));
    cout << "Matrix:\n";
    printMatrix(circularGMatrix(n));

    cout << "===== COMPLETE =====\n";
    cout << "List:\n";
    printList(completeGList(n));
    cout << "Matrix:\n";
    printMatrix(completeGMatrix(n));

    cout << "===== RANDOM (p=0.5) =====\n";
    cout << "List:\n";
    printList(randomGList(n, p));
    cout << "Matrix:\n";
    printMatrix(randomGMatrix(n, p));

    return 0;
}