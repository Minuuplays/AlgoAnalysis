#include <bits/stdc++.h>
using namespace std;
int INF= INT_MAX;

vector<vector<int>> completeG(int n){
    vector<vector<int>> g(n+1);
    int w ;
    for(int i=0;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            w = rand()%50;
            g[i].push_back(w);
            g[j].push_back(w);
        }
    }
    return g;
}

void print(vector<vector<int>> &g,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << g[i][j] << " ";
        }
        cout << endl;
    }
}

int primm(vector<vector<int>> &g,int v){
    vector<bool>visited(v,false);
    visited[0]=true;

    int x,y;
    int sum=0;
    int edges=0;

    vector<vector<pair<int,int>>> gNew(v);

    while(edges < (v-1)){
        int min = INF;
        x=0;
        y=0;
        for(int i=0;i<v;i++){
            if(visited[i]){
                for(int j=0;j<v;j++){
                    if(!visited[j] && g[i][j]){
                        if(min>g[i][j]){
                            min = g[i][j];
                            x=i;
                            y=j;
                        }
                    }
                }
            }
        }
        cout << x << " - " << y << " : " << g[x][y] <<endl;
        gNew[x].push_back({y,g[x][y]});
        gNew[y].push_back({x,g[x][y]});
        sum+=g[x][y];
        cout << "Current  sum:" << sum << endl;
        visited[y]=true;
        edges++;
    }
    return sum;
}


int main(){
    int v=10;

    vector<vector<int>> g1= completeG(v);
    cout << "\nGraph-1 :" <<endl;
    print(g1,v);
    int Tsum1=primm(g1,v);
    cout <<"Total sum of Graph1 : " << Tsum1 <<endl;

    vector<vector<int>> g2= completeG(v);
    cout << "\nGraph-2 :" <<endl;
    print(g2,v);
    int Tsum2=primm(g2,v);
    cout <<"Total sum of Graph2 : " << Tsum2 <<endl;

    vector<vector<int>> g3= completeG(v);
    cout << "\nGraph-3 :" <<endl;
    print(g3,v);
    int Tsum3=primm(g3,v);
    cout <<"Total sum of Graph3 : " << Tsum3 <<endl;

    int Tsum=Tsum1+Tsum2+Tsum3;
    cout <<"Total sum : " << Tsum <<endl;

    return 0;
}