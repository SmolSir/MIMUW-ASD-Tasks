#include<bits/stdc++.h>
using namespace std;

int n, m, odd_cnt, even_cnt;
long long odd[1000007];
long long even[1000007];
long long ans[1000007];

int main() {

    ios_base::sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        if (a % 2LL == 0LL) {
            even[even_cnt] = a;
            even_cnt++;
        }
        else {
            odd[odd_cnt] = a;
            odd_cnt++;
        }
    }

    sort(odd, odd + odd_cnt);
    sort(even, even + even_cnt);
    reverse(odd, odd + odd_cnt);
    reverse(even, even + even_cnt);

    
    int odd_pointer = 0;

    if (odd_cnt == 0) {
		ans[1] = -1LL;
	}
	else {
		ans[1] = odd[odd_pointer];
		odd_pointer++;
	}
	
		
	int odd_ptr = odd_pointer, even_ptr = 0;
	
	for (int i = 3; i <= n; i += 2) {
		if ((odd_ptr + 1 >= odd_cnt && even_ptr + 1 >= even_cnt) || odd_cnt == 0) {
			ans[i] = -1LL;
			continue;
		}
		if (odd_ptr + 1 >= odd_cnt) {
			ans[i] = ans[i - 2] + even[even_ptr] + even[even_ptr + 1];
			even_ptr += 2;
			continue;
		}
		if (even_ptr + 1 >= even_cnt) {
			ans[i] = ans[i - 2] + odd[odd_ptr] + odd[odd_ptr + 1];
			odd_ptr += 2;
			continue;
		}
		if (odd[odd_ptr] + odd[odd_ptr + 1] > even[even_ptr] + even[even_ptr + 1]) {
			ans[i] = ans[i - 2] + odd[odd_ptr] + odd[odd_ptr + 1];
			odd_ptr += 2;
		}
		else {
			ans[i] = ans[i - 2] + even[even_ptr] + even[even_ptr + 1];
			even_ptr += 2;
		}
	}
	
	odd_ptr = odd_pointer, even_ptr = 0;
	
	if (even_cnt == 0 || odd_cnt == 0) {
		ans[2] = -1LL;
	}
	else {
		ans[2] = ans[1] + even[even_ptr];
		even_ptr++;
	}
	
	for (int i = 4; i <= n; i += 2) {
		if ((odd_ptr + 1 >= odd_cnt && even_ptr + 1 >= even_cnt) || even_cnt == 0 || odd_cnt == 0) {
			ans[i] = -1LL;
			continue;
		}
		if (odd_ptr + 1 >= odd_cnt) {
			ans[i] = ans[i - 2] + even[even_ptr] + even[even_ptr + 1];
			even_ptr += 2;
			continue;
		}
		if (even_ptr + 1 >= even_cnt) {
			ans[i] = ans[i - 2] + odd[odd_ptr] + odd[odd_ptr + 1];
			odd_ptr += 2;
			continue;
		}
		if (odd[odd_ptr] + odd[odd_ptr + 1] > even[even_ptr] + even[even_ptr + 1]) {
			ans[i] = ans[i - 2] + odd[odd_ptr] + odd[odd_ptr + 1];
			odd_ptr += 2;
		}
		else {
		ans[i] = ans[i - 2] + even[even_ptr] + even[even_ptr + 1];
		even_ptr += 2;
		}
	}
	
	cin >> m;
	int k;
	
	for (int i = 0; i < m; i++) {
		cin >> k;
		cout << ans[k] << "\n";
	}
	
	return 0;
}