#include<bits/stdc++.h>
using namespace std;


long long mod = 1e9;
int n;
long long p[1007];
long long T[1007][1007];
long long L[1007][1007];
long long R[1007][1007];

int main() {

    ios_base::sync_with_stdio(0);
    cin >> n;

    if (n == 1) {
        cout << 1;
        return 0;
    }

    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    for (int i = 0; i < n; i++) {
        L[i][i] = 1;
        R[i][i] = 1;
    }

    for (int i = 0; i < n - 1; i++) {
        if (p[i] < p[i + 1]) {
            L[i][i + 1] = 1;
            R[i][i + 1] = 1;
        }
    }

    for (int i = n - 3; i >= 0; i--) {
        for (int j = i + 2; j < n; j++) {
            L[i][j] = ((p[i] < p[i + 1] ? L[i + 1][j] : 0) + (p[i] < p[j] ? R[i + 1][j] : 0)) % mod;
            R[i][j] = ((p[i] < p[j] ? L[i][j - 1] : 0) + (p[j - 1] < p[j] ? R[i][j - 1] : 0)) % mod;
        }
    }

    cout << (L[0][n - 1] + R[0][n - 1]) % mod;

    return 0;
}
