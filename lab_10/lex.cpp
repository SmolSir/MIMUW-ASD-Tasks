#include <bits/stdc++.h>
using namespace std;

const long long N = 300007;
const long long mod = 1000000007;
const long long p = 997; //prime

int n, m;
int a, b, c, d;
string s;
long long Hash[N];
long long P[N]; // prime powers % mod

long long get_hash(int x, int y) {
    return ((Hash[y] - Hash[x - 1] * P[y - x + 1]) % mod + mod) % mod;
}

bool equal_hash(int length) {
    return get_hash(a, a + length - 1) == get_hash(c, c + length - 1);
}

char querry() {
    if (get_hash(a, b) == get_hash(c, d)) {
        return '=';
    }

    int length_ab = b - a + 1;
    int length_cd = d - c + 1;

    if (length_ab < length_cd && get_hash(a, b) == get_hash(c, c + b - a)) {
        return '<';
    }
    if (length_ab > length_cd && get_hash(a, a + d - c) == get_hash(c, d)) {
        return '>';
    }

    int L = 0, R = min(length_ab, length_cd) - 1;
    while (L < R) {
        int M = (L + R + 1) / 2;
        equal_hash(M) ? L = M : R = M - 1;
    }
    return s[a + L - 1] < s[c + L - 1] ? '<' : '>';
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    cin >> s;

    P[0] = 1LL;
    for (int i = 1; i <= n; i++) {
        Hash[i] = (Hash[i - 1] * p + s[i - 1]) % mod;
        P[i] = (P[i - 1] * p) % mod;
    }

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c >> d;
        cout << querry() << "\n";
    }

    return 0;
}
