#include <bits/stdc++.h>
using namespace std;

#define N (1000 * 1000 + 7)

int n;

int sequence[N];
int component[N];
int cnt[N];
int rep[N];
int min_rep[N];
int max_rep[N];

vector<int> component_members[N];

int Find(int v) {
    if (rep[v] == v) {
        return v;
    }
    rep[v] = Find(rep[v]);
    return rep[v];
}

void Union(int id1, int id2) {
    id1 = Find(id1);
    id2 = Find(id2);

    if (id1 == id2) {
        return;
    }

    if (cnt[id1] > cnt[id2]) {
        rep[id2] = id1;
        min_rep[id1] = min(min_rep[id1], min_rep[id2]);
        max_rep[id1] = max(max_rep[id1], max_rep[id2]);
        cnt[id1] += cnt[id2];
        cnt[id2] = 0;
    }

    else { // cnt[id1] <= cnt[id2]
        rep[id1] = id2;
        min_rep[id2] = min(min_rep[id1], min_rep[id2]);
        max_rep[id2] = max(max_rep[id1], max_rep[id2]);
        cnt[id2] += cnt[id1];
        cnt[id1] = 0;
    }
}

bool compare_first_members(vector<int> &lhs, vector<int> &rhs) {
    if (lhs.empty() || rhs.empty()) {
        return rhs.empty();
    }
    return lhs.front() < rhs.front();
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        cnt[i] = 1;
        rep[i] = i;

        cin >> sequence[i];
        min_rep[sequence[i]] = sequence[i];
        max_rep[sequence[i]] = sequence[i];
    }

    for (int i = 2; i <= n; i++) {
        if (max_rep[rep[sequence[i - 1]]] > min_rep[rep[sequence[i]]]) {
            Union(sequence[i - 1], sequence[i]);
        }
    }

    for (int i = n; i >= 2; i--) {
        if (max_rep[rep[sequence[i - 1]]] > min_rep[rep[sequence[i]]]) {
            Union(sequence[i - 1], sequence[i]);
        }
    }

    for (int i = 1; i <= n; i++) {
        component_members[Find(sequence[i])].push_back(sequence[i]);
    }


    int count = 0;
    for (int i = 0; i <= n; i++) {
        if (component_members[i].empty()) {
            component_members[i].push_back(n + 1);
        }
        else {
            count++;
        }
    }

    sort(component_members, component_members + n + 1);

    cout << count << "\n";

    for (int i = 0; i < count; i++) {
        cout << component_members[i].size() << " ";
        sort(component_members[i].begin(), component_members[i].end());

        for (auto member : component_members[i]) {
            cout << member << " ";
        }
        cout << "\n";
    }

    return 0;
}