#include<bits/stdc++.h>
using namespace std;

int n, m;
int a, b;
int tree_size = 1;
char c;
int tree[3000007];
int lazy[3000007];

void update(int x, int L, int R, int L_query, int R_query, int val) {
    int length = (R - L + 1);
    if (lazy[x]) {
        tree[x] = max(0, min(length, tree[x] + length * lazy[x]));
        if (L != R) {
            lazy[2 * x] = lazy[x];
            lazy[2 * x + 1] = lazy[x];
        }
        lazy[x] = 0;
    }

    if (R_query < L || R < L_query) {
        return;
    }
    if (L_query <= L && R <= R_query) {
        tree[x] = max(0, min(length, tree[x] + length * val));
        if (L != R) {
            lazy[2 * x] = val;
            lazy[2 * x + 1] = val;
        }
        return;
    }

    int S = (L + R) / 2;
    update(2 * x, L, S, L_query, R_query, val);
    update(2 * x + 1, S + 1, R, L_query, R_query, val);

    tree[x] = max(0, min(length, tree[2 * x] + tree[2 * x + 1]));
}

int query(int x, int L, int R, int L_query, int R_query) {
    int length = (R - L + 1);

    if (R_query < L || R < L_query) {
        return 0;
    }

    if (lazy[x]) {
        tree[x] = max(0, min(length, tree[x] + length * lazy[x]));
        if (L != R) {
            lazy[2 * x] = lazy[x];
            lazy[2 * x + 1] = lazy[x];
        }
        lazy[x] = 0;
    }

    if (L_query <= L && R <= R_query) {
        return tree[x];
    }

    int S = (L + R) / 2;
    int sum_L = query(2 * x, L, S, L_query, R_query);
    int sum_R = query(2 * x + 1, S + 1, R, L_query, R_query);
    return (sum_L + sum_R);
}


int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;

    while (tree_size < n) {
        tree_size *= 2;
    }

    for (int q = 0; q < m; q++) {
        cin >> a >> b >> c;
        update(1, 1, tree_size, a, b, (c == 'B' ? 1 : -1));
        cout << query(1, 1, tree_size, 1, n) << "\n";
    }

    return 0;
}