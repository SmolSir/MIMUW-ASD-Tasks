#include <bits/stdc++.h>
using namespace std;

int n, m, k;
int a, b;

int cost[100007];
int children[100007];
vector<vector<int> > G;

priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;

int toposort() {
    int max_task = 0;
    
    for (int i = 0; i < k; i++) {
        auto x = q.top();
        q.pop();
        max_task = max(max_task, x.first);
        
        for (auto v : G[x.second]) {
            children[v]--;
            if (!children[v]) {
                q.push(make_pair(cost[v], v));
            }
        }
    }
    
    return max_task;
}

int main() {
    
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m >> k;

    G = vector<vector<int> > (n + 7, vector<int> ());

    for (int i = 1; i <= n; i++) {
        cin >> cost[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        G[b].push_back(a);
        children[a]++;
    }

    for (int i = 1; i <= n; i++) {
        if (!children[i]) {
            q.push(make_pair(cost[i], i));
        }
    }
    
    cout << toposort();
    return 0;
}