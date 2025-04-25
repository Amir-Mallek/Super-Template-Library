/**
* Prefix Function Simple Use Case
* Link : https://cses.fi/problemset/task/1753
*/

#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define pb push_back
#define lv (v<<1)
#define rv ((v<<1)+1)
#define endl '\n'
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<typename T>
vi prefix_function(const T& s) {
	int n = sz(s);
	vi pi(n);
	pi[0] = 0;
	for (int i = 1; i < n; i++) {
		int j = pi[i-1];
		while (j > 0 && s[i] != s[j])
			j = pi[j-1];
		if (s[i] == s[j])
			++j;
		pi[i] = j;
	}
	return pi;
}

template<typename T>
vi match(const T& s, const T& t) {
	int n_s = sz(s), n_t = sz(t);
	vi pi_t = prefix_function(t), matches;
	int prv = (t[0] == s[0]);
	if (prv == n_t) {
		matches.push_back(0);
		prv = 0;
	}
	for (int i = 1; i < n_s; ++i) {
		int j = prv;
		while (j > 0 && s[i] != t[j])
			j = pi_t[j-1];
		if (s[i] == t[j])
			++j;

		if (j == n_t) {
			matches.push_back(i-n_t+1);
			prv = pi_t[n_t-1];
		} else prv = j;
	}

	return matches;
}

int main() {
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	IOS

	string s, t;
	cin >> s >> t;
	cout << sz(match(s, t));

	return 0;
}