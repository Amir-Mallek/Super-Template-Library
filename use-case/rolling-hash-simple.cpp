/**
* Rolling hash Simple Use Case
* Link : https://codeforces.com/contest/271/problem/D
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

const int N = 2e5 + 5, NBH = 2,
P[4] = {29 , 31, 137, 199},
IP[4] = {758620695, 838709685, 13138691, 52763884},
MOD[4] = {1000000007, 1000000009, 100000037, 100000123};

int pw[NBH][N], ipw[NBH][N];

void precompute() {
    for (int pi = 0; pi < NBH; ++pi) {
        pw[pi][0] = ipw[pi][0] = 1;
    }

    for (int i = 1; i < N; ++i) {
        for (int pi = 0; pi < NBH; ++pi) {
            pw[pi][i] = 1ll * pw[pi][i-1] * P[pi] % MOD[pi];
            ipw[pi][i] = 1ll * ipw[pi][i-1] * IP[pi] % MOD[pi];
        }
    }
}

// WARNING IF THE ALPHABET IS NOT a..z CHANGE HASH FORMULA
array<int, NBH> hash_string(const string &s) {
    int n = s.size();
    array<int, NBH> res = {};
    for (int i = 0; i < n; ++i) {
        for (int pi = 0; pi < NBH; ++pi) {
            res[pi] = (res[pi] + 1ll * (s[i]-'a'+1) * pw[pi][i]) % MOD[pi];
        }
    }
    return res;
}

struct r_hash {
    int sz;
    // pref_hash is 0-indexed
    vector<array<int, NBH>> pref_hash;

    r_hash(const string &_s) {
        sz = _s.size();
        pref_hash = vector<array<int, NBH>>(sz);
        int prv[NBH] = {};
        for (int i = 0; i < sz; ++i) {
            for (int pi = 0; pi < NBH; ++pi) {
                pref_hash[i][pi] = (prv[pi] + 1ll * (_s[i]-'a'+1) * pw[pi][i]) % MOD[pi];
                prv[pi] = pref_hash[i][pi];
            }
        }
    }

    // l and r are inclusive and 0-indexed
    array<int, NBH> get_hash(int l, int r) const {
        if (l > r) return array<int, NBH>{};
        if (l == 0) return pref_hash[r];

        array<int, NBH> res;
        for (int pi = 0; pi < NBH; ++pi) {
            res[pi] =
                (1ll * pref_hash[r][pi] - pref_hash[l-1][pi] + MOD[pi]) * ipw[pi][l] % MOD[pi];
        }
        return res;
    }
};

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    IOS

    precompute();

    string s, good;
    cin >> s;

    int n = sz(s), k;
    r_hash rh(s);
    cin >> good >> k;
    int pref[1505];
    pref[0] = (good[(s[0]-'a')] == '0');
    for (int i = 1; i < n; ++i) {
        pref[i] = pref[i-1] + (good[(s[i]-'a')] == '0');
    }
    int ans = 0;
    for (int len = 1; len <= n; ++len) {
        unordered_set<int> unique[2];
        for (int i = 0; i <= n-len; ++i) {
            int j = i + len - 1;
            int nbBad = pref[j] - ((i == 0) ? 0 : pref[i-1]);
            array<int, NBH> hashsub = rh.get_hash(i, j);
            if (nbBad <= k && (!unique[0].contains(hashsub[0]) || !unique[1].contains(hashsub[1]))) {
                unique[0].insert(hashsub[0]);
                unique[1].insert(hashsub[1]);
                ans++;
            }

        }
    }
    cout << ans << endl;

    return 0;
}