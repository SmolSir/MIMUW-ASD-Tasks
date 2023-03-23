#include <bits/stdc++.h>
#define m_p make_pair
using namespace std;

int p, k, z, n, m;
int a, b, zw;
int final_power = -1;

bool banned[5007];
bool visited[1007];
int energy[1007];
int arrived_from[1007];
queue<pair<int, int> > q; // first - where, second - from where
vector<int> Graph[1007];
vector<int> path;
vector<int> used_chargers;
pair<int, bool> dp[1007][5007];
// first - energy before travel, second - powerbank consumed after arrival

void get_data() {
    cin >> p >> k >> z;

    for (int i = 0; i < z; i++) {
        cin >> zw;
        banned[zw] = true;
    }

    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        Graph[a].push_back(b);
        Graph[b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        cin >> energy[i];
    }
}

void bfs() {
    q.push(m_p(1, 0));

    while (!q.empty()) {
        int x = q.front().first;
        int from = q.front().second;
        q.pop();
        if (visited[x]) {
            continue;
        }
        visited[x] = true;
        arrived_from[x] = from;
        for (int i = 0; i < Graph[x].size(); i++) {
            q.push(m_p(Graph[x][i], x));
        }
    }
}

void compute_dp() {
    for (int col = 1; col < n; col++) {
        for (int power = 0; power <= p; power++) {
            dp[col][power] = m_p(-1, false);
        }
    }

    int next_charged = min(p - k + energy[1], p + 1); // next energy with charge on arrival
    int next = p - k; //next energy without charge on arrival

    dp[1][next_charged] = banned[next_charged] ? m_p(-1, false) : m_p(p, true);
    dp[1][next] = m_p(p, false);

    for (int col = 1; col < n; col++) {
        for (int power = k; power <= p; power++) { // from k, if less we fail anyways
            if (dp[col][power] == m_p(-1, false)) {
                continue;
            }

            next_charged = min(power - k + energy[col + 1], p + 1);
            next = power - k;

            dp[col + 1][next_charged] = banned[next_charged] ? m_p(-1, false) : m_p(power, true);
            dp[col + 1][next] = m_p(power, false);
        }
    }
}

void get_path() {
    int x = n;
    do {
        path.push_back(x);
        x = arrived_from[x];
    } while (x);

    reverse(path.begin(), path.end());
}

void get_chargers() {
    int prev = 0;
    int col = (int) path.size() - 1;
    for (int power = p; power >= 0; power--) {
        prev = dp[col][power].first;
        if (prev >= 0) {
            final_power = power;
            if (dp[col][power].second) {
                used_chargers.push_back(path[col]);
            }
            break;
        }
    }

    // cannot reach end of path
    if (final_power < 0) {
        return;
    }

    do {
        col--;
        if (dp[col][prev].second) {
            used_chargers.push_back(path[col]);
        }
        prev = dp[col][prev].first;
    } while (col);

    reverse(used_chargers.begin(), used_chargers.end());
}

void print_output() {
    if (final_power < 0) {
        cout << "-1";
        return;
    }

    cout << path.size() << " " << final_power << " " << used_chargers.size() << "\n";
    for (auto x : path) {
        cout << x << " ";
    }
    cout << "\n";
    for (auto x : used_chargers) {
        cout << x << " ";
    }
}


int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    get_data();
    bfs();
    if (!visited[n]) {
        cout << "-1";
        return 0;
    }
    
    get_path();
    compute_dp();
    get_chargers();
    print_output();

    return 0;
}