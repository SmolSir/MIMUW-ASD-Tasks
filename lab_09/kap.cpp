#include <bits/stdc++.h>
using namespace std;

int n;

struct island {
    int x = 0;
    int y = 0;
    int id = 0;
    long long value = LONG_LONG_MAX;
};

island archipelago[200007];
vector<int> G[200007];
priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> Q;

bool by_x_value(island &lhs, island &rhs) {
    return lhs.x == rhs.x ? lhs.y < rhs.y : lhs.x < rhs.x;
}
bool by_y_value(island& lhs, island& rhs) {
    return lhs.y == rhs.y ? lhs.x < rhs.x : lhs.y < rhs.y;
}

void construct_graph() {

    island temp[n];
    copy(archipelago, archipelago + n, temp);

    sort(temp, temp + n, by_x_value);

    G[temp[0].id].push_back(temp[1].id);
    G[temp[n - 1].id].push_back(temp[n - 2].id);

    for (int i = 1; i < n - 1; i++) {
        G[temp[i].id].push_back(temp[i - 1].id);
        G[temp[i].id].push_back(temp[i + 1].id);
    }

    sort(temp, temp + n, by_y_value);

    G[temp[0].id].push_back(temp[1].id);
    G[temp[n - 1].id].push_back(temp[n - 2].id);

    for (int i = 1; i < n - 1; i++) {
        G[temp[i].id].push_back(temp[i - 1].id);
        G[temp[i].id].push_back(temp[i + 1].id);
    }
}

long long travel_cost(int a, int b) {
    return min(
            abs(archipelago[a].x - archipelago[b].x),
            abs(archipelago[a].y - archipelago[b].y)
            );
}

void Dijkstra() {
    Q.push({0, 0LL});
    while (!Q.empty()) {
        auto vert = Q.top();
        Q.pop();
        if (vert.first >= archipelago[vert.second].value) {
            continue;
        }
        archipelago[vert.second].value = vert.first;

        for (auto neighbour : G[vert.second]) {
            Q.push({vert.first + travel_cost(vert.second, neighbour), neighbour});
        }
    }

    cout << archipelago[n - 1].value;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> archipelago[i].x >> archipelago[i].y;
        archipelago[i].id = i;
    }

    construct_graph();
    Dijkstra();

    return 0;
}