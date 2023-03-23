#include<bits/stdc++.h>
using namespace std;

int n, m, player;
long long power = 1;
vector<long long>codes;

int main() {

    ios_base::sync_with_stdio(0);
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        codes.push_back(0);
    }

    for (int matches = 0; matches < m; matches++) {
        for (int i = 0; i < n; i++) {
            cin >> player;
            if (i < n / 2) {
                codes[player - 1] += power;
            }
        }
        power *= 2;
    }

    sort(codes.begin(), codes.end());

    for (int i = 1; i < n; i++) {
        if (codes[i] == codes[i - 1]) {
            cout << "NIE";
            return 0;
        }
    }

    cout << "TAK";
}