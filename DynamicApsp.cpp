#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = (ll)1e15;

int n;
vector<vector<ll>> w;
vector<vector<ll>> D;
ll rowsRecomputed = 0;

void initGraph(const vector<vector<int>>& adj) {
    n = (int)adj.size();
    w.assign(n, vector<ll>(n, INF));
    D.assign(n, vector<ll>(n, INF));
    for (int u = 0; u < n; u++)
        for (int v = 0; v < n; v++)
            if (u != v && adj[u][v] > 0) w[u][v] = adj[u][v];
}

void dijkstraRow(int s) {
    vector<bool> done(n, false);
    for (int v = 0; v < n; v++) D[s][v] = INF;
    D[s][s] = 0;
    for (int it = 0; it < n; it++) {
        int u = -1;
        for (int v = 0; v < n; v++)
            if (!done[v] && (u == -1 || D[s][v] < D[s][u])) u = v;
        if (u == -1 || D[s][u] >= INF) break;
        done[u] = true;
        for (int v = 0; v < n; v++)
            if (w[u][v] < INF && D[s][u] + w[u][v] < D[s][v])
                D[s][v] = D[s][u] + w[u][v];
    }
}

void buildInitialAPSP() {
    for (int s = 0; s < n; s++) dijkstraRow(s);
}

ll query(int u, int v) { return D[u][v]; }

void update(int u, int v, ll newW) {
    if (u == v) return;
    ll oldW = w[u][v];
    if (newW == oldW) return;

    if (newW < oldW) {
        w[u][v] = newW;
        for (int i = 0; i < n; i++) {
            if (D[i][u] >= INF) continue;
            for (int j = 0; j < n; j++) {
                if (D[v][j] >= INF) continue;
                ll cand = D[i][u] + newW + D[v][j];
                if (cand < D[i][j]) D[i][j] = cand;
            }
        }
    } else {
        vector<int> affected;
        for (int i = 0; i < n; i++) {
            if (D[i][u] >= INF) continue;
            for (int j = 0; j < n; j++) {
                if (D[v][j] >= INF) continue;
                if (D[i][u] + oldW + D[v][j] == D[i][j]) { affected.push_back(i); break; }
            }
        }

        w[u][v] = newW;
        for (int i : affected) { dijkstraRow(i); rowsRecomputed++; }
    }
}

vector<vector<ll>> floydWarshall(const vector<vector<ll>>& src) {
    vector<vector<ll>> F = src;
    for (int i = 0; i < n; i++) F[i][i] = 0;
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++) {
            if (F[i][k] >= INF) continue;
            for (int j = 0; j < n; j++)
                if (F[k][j] < INF && F[i][k] + F[k][j] < F[i][j])
                    F[i][j] = F[i][k] + F[k][j];
        }
    return F;
}

void updateNaive(int u, int v, ll newW) {
    if (u == v) return;
    w[u][v] = newW;
    D = floydWarshall(w);
}

bool verify() { return D == floydWarshall(w); }

void printD(const string& title) {
    cout << title << "\n     ";
    for (int j = 0; j < n; j++) cout << setw(4) << j;
    cout << "\n";
    for (int i = 0; i < n; i++) {
        cout << setw(4) << i << ":";
        for (int j = 0; j < n; j++) {
            if (D[i][j] >= INF) cout << setw(4) << "INF";
            else cout << setw(4) << D[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    {
        vector<vector<int>> adj = {
            {   0, 4, 1, 0, 0 },
            {   0, 0, 0, 1, 0 },
            {   0, 2, 0, 5, 0 },
            {   0, 0, 0, 0, 3 },
            {   0, 0, 0, 0, 0 },
        };
        initGraph(adj);
        buildInitialAPSP();
        printD("Initial D0:");

        update(0, 4, 20);  printD("U1: insert edge 0->4 (w=20)");
        update(2, 3, 1);   printD("U2: decrease 2->3 from 5 to 1");
        update(2, 1, 9);   printD("U3: increase 2->1 from 2 to 9");
        update(3, 4, INF); printD("U4: delete edge 3->4");
        cout << "Query D[0][3] = " << query(0, 3) << "\n";
        cout << "Demo verified against Floyd-Warshall: " << (verify() ? "OK" : "FAILED") << "\n\n";
    }

    mt19937 rng(12345);

    {
        int V = 30, E = 90;
        vector<vector<int>> adj(V, vector<int>(V, 0));
        for (int e = 0; e < E; e++) {
            int u = rng() % V, v = rng() % V;
            if (u == v) { e--; continue; }
            int wt = 1 + (int)(rng() % 20);
            if (adj[u][v] == 0 || wt < adj[u][v]) adj[u][v] = wt;
        }
        initGraph(adj);
        buildInitialAPSP();

        bool ok = true;
        for (int k = 0; k < 2000 && ok; k++) {
            int u = rng() % n, v = rng() % n;
            ll nw = (rng() % 4 == 0) ? INF : 1 + (ll)(rng() % 20);
            update(u, v, nw);
            ok = verify();
        }
        cout << "Random test (n=30, 2000 updates, checked after each): "
             << (ok ? "ALL OK" : "MISMATCH") << "\n\n";
    }

    {
        int V = 150, E = 900, K = 300;
        vector<vector<int>> adj(V, vector<int>(V, 0));
        for (int e = 0; e < E; e++) {
            int u = rng() % V, v = rng() % V;
            if (u == v) { e--; continue; }
            int wt = 1 + (int)(rng() % 50);
            if (adj[u][v] == 0 || wt < adj[u][v]) adj[u][v] = wt;
        }
        initGraph(adj);
        buildInitialAPSP();
        vector<vector<ll>> wSaved = w, DSaved = D;

        vector<array<ll, 3>> ups;
        for (int t = 0; t < K; t++) {
            ll nw = (rng() % 4 == 0) ? INF : 1 + (ll)(rng() % 50);
            ups.push_back({(ll)(rng() % V), (ll)(rng() % V), nw});
        }

        auto t0 = chrono::steady_clock::now();
        for (auto& x : ups) update((int)x[0], (int)x[1], x[2]);
        auto t1 = chrono::steady_clock::now();

        w = wSaved; D = DSaved;
        for (auto& x : ups) updateNaive((int)x[0], (int)x[1], x[2]);
        auto t2 = chrono::steady_clock::now();

        double tDyn = chrono::duration<double, milli>(t1 - t0).count();
        double tScr = chrono::duration<double, milli>(t2 - t1).count();
        cout << "Timing: n=" << V << ", m=" << E << ", updates=" << K << "\n";
        cout << "Incremental update()      : " << tDyn << " ms\n";
        cout << "Recompute (Floyd-Warshall): " << tScr << " ms\n";
        cout << "Speed-up                  : " << tScr / tDyn << "x\n";
        cout << "Dijkstra rows rerun        : " << rowsRecomputed
             << " (worst case " << (ll)K * V << ")\n";

        w = wSaved; D = DSaved;
        for (auto& x : ups) update((int)x[0], (int)x[1], x[2]);
        cout << "Final results match       : " << (verify() ? "OK" : "FAILED") << "\n";
    }

    return 0;
}