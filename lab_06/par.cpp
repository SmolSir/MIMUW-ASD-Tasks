#include <bits/stdc++.h>
using namespace std;

int n, m;
int a, b, d;
int d1, d2; // ends of diameter
int LCA[3][20][500007];

bool visited[500007];
vector<int> G[500007];
queue<int> q;

int bfs() {

    while (!q.empty()) {
        int x = q.front();
        visited[x] = true;
        for (auto v : G[x]) {
            if (!visited[v]) {
                q.push(v);
            }
        }
        if (q.size() == 1) {
            for (int i = 0; i <= n; i++) {
                visited[i] = false;
            }
            return q.front();
        }
        q.pop();
    }

    return 0;
}

void dfs(int x, int caller, int depth, int parent) {
    LCA[caller][0][x] = x;
    LCA[caller][1][x] = parent;

    for (auto v : G[x]) {
        if (!LCA[caller][0][v]) {
            dfs(v, caller, depth + 1, x);
        }
    }
    return;
}

void compute_LCA() {
    for (int ancestor = 2; ancestor < 20; ancestor++) {
        for (int i = 1; i <= n; i++) {
            LCA[1][ancestor][i] = LCA[1][ancestor - 1][LCA[1][ancestor - 1][i]];
            LCA[2][ancestor][i] = LCA[2][ancestor - 1][LCA[2][ancestor - 1][i]];
        }
    }
}

int find_ancestor(int x, int depth, int caller) {
    int ancestor = 20;
    while (depth) {
        if (depth >= (1 << ancestor)) {
            x = LCA[caller][ancestor + 1][x];
            depth -= (1 << ancestor);
        }
        ancestor--;

        if (x == 0) {
            return -1;
        }
    }
    return x;
}

int solve(int x, int depth) {
    if (depth == 0) {
        return x;
    }
    return max(find_ancestor(x, depth, 1), find_ancestor(x, depth, 2));
}


int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> a >> b;
        if (a > 0) {
            G[i].push_back(a);
            G[a].push_back(i);
        }
        if (b > 0) {
            G[i].push_back(b);
            G[b].push_back(i);
        }
    }

    q.push(1);
    d1 = bfs();
    d2 = bfs();

    dfs(d1, 1, 0, 0);
    dfs(d2, 2, 0, 0);

    compute_LCA();

    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> a >> d;
        cout << solve(a, d) << "\n";
    }

    return 0;
}