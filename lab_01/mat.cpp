#include<bits/stdc++.h>
using namespace std;

string s;
int prev_pos = -1;
char prev_char;
int min_dist = 1e9;
bool multi_letters = false;

int main() {

    ios_base::sync_with_stdio(0);
    cin >> s;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] != '*') {
            prev_pos = i;
            prev_char = s[i];
            break;
        }
    }

    if (prev_pos < 0) {
        cout << 1;
        return 0;
    }

    for (int i = prev_pos; i < s.size(); i++) {
        if (s[i] == '*') continue;
        if (s[i] == prev_char) {
            prev_pos = i;
            continue;
        }
        min_dist = min(min_dist, i - prev_pos - 1);
        multi_letters = true;
        prev_pos = i;
        prev_char = s[i];
    }

    if (multi_letters) cout << s.size() - min_dist;
    else cout << 1;
}