/**
* Trie Simple Use Case
* Link : https://www.spoj.com/problems/EMOTICON/
*/

#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define pb push_back
#define lv (v<<1)
#define rv ((v<<1)+1)
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct node {
	bool is_black;
};

constexpr int LEN = 20*102 + 11, K = 128;
int go[LEN][K], fail[LEN], nd_cnt;
node tdata[LEN];

void init() {
	memset(go[0], -1, sizeof go[0]);
	nd_cnt = 1;
}

int add_node() {
	memset(go[nd_cnt], -1, sizeof go[nd_cnt]);
	return nd_cnt++;
}

void add_string(const string& s, int id) {
	int v = 0, n = sz(s);
	rep(i, 0, n) {
		int c = s[i];
		if (go[v][c] == -1) {
			tdata[nd_cnt].is_black = false;
			go[v][c] = add_node();
		}
		v = go[v][c];
	}
	tdata[v].is_black = true;
}

void build_trie() {
	fail[0] = 0;
	queue<int> to_process;
	rep(c, 0, K) {
		int& nxt = go[0][c];
		if (nxt != -1) {
			fail[nxt] = 0;
			to_process.push(nxt);
		} else nxt = 0;
	}

	while (!to_process.empty()) {
		int v = to_process.front();
		to_process.pop();
		rep(c, 0, K) {
			int& nxt = go[v][c];
			if (nxt != -1) {
				fail[nxt] = go[fail[v]][c];
				tdata[nxt].is_black |= tdata[fail[nxt]].is_black;
				to_process.push(nxt);
			} else nxt = go[fail[v]][c];
		}
	}
}

int main() {
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	IOS

	int n, m;
	cin >> n >> m;
	string temp;

	while (n != 0 || m != 0) {
		int ans = 0;
		init();
		rep(i, 0, n) {
			cin >> temp;
			add_string(temp, i);
		}
		build_trie();
		cin.ignore();
		rep(i, 0, m) {
			getline(cin, temp);
			int v = 0;
			for (char c: temp) {
				if (c == ' ') {
					v = 0;
					continue;
				}
				v = go[v][c];
				if (tdata[v].is_black) {
					ans++;
					v = 0;
				}
			}
		}
		cout << ans << endl;
		cin >> n >> m;
	}

	return 0;
}