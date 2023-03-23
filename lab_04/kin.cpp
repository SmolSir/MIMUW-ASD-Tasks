#include<bits/stdc++.h>

using namespace std;

#define MOD 1000000000;

int tree_size = 32768;
long long tree[66007][17];
pair<int, int> t[20007];
vector<int> insertion_order;
int a, addition = 1;
int n, k;

void push(int x, int k_value, long long val) {
    x += addition - 1;
    while (x) {
        tree[x][k_value] = (tree[x][k_value] + val) % MOD;
        x /= 2;
    }
}

long long query(int L, int R, int x, int L_bound, int R_bound, int k_value) {
    long long sum = 0;
    if (R < L_bound || R_bound < L) {
        return 0;
    }
    if (L_bound <= L && R <= R_bound) {
        return tree[x][k_value];
    }
    int S = (L + R) / 2;
    sum += query(L, S, x * 2, L_bound, R_bound, k_value);
    sum += query(S + 1, R, x * 2 + 1, L_bound, R_bound, k_value);
    return sum % MOD;
}


int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;

    while (addition < n) {
        addition *= 2;
    }

    for (int i = 0; i < n; i++) {
        cin >> a;
        t[i] = make_pair(a, i + 1);
    }

    sort(t, t + n);

    for (int i = 0; i < n; i++) {
        insertion_order.push_back(t[i].second);
    }

    for (auto i : insertion_order) {
        push(i, 1, 1);
        for (int k_value = 2; k_value <= k; k_value++) {
            push(i, k_value, query(1, addition, 1, i + 1, addition, k_value - 1));
        }
    }

    cout << query(1, addition, 1, 1, addition, k);

    return 0;
}
