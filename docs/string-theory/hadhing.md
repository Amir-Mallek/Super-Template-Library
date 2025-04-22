```cpp
// rod taill 4 max w nbh variable
const int MAXN = 2e5 + 5, NBH = 2,
P[NBH] = {29 , 31}, IP[NBH] = {758620695, 838709685}, MOD[NBH] = {1000000007, 1000000009};
int pw[NBH][MAXN], ipw[NBH][MAXN];

void precompute() {
    for (int pi = 0; pi < NBH; ++pi) {
        pw[pi][0] = ipw[pi][0] = 1;
    }

    for (int i = 1; i < MAXN; ++i) {
        for (int pi = 0; pi < NBH; ++pi) {
            pw[pi][i] = 1ll * pw[pi][i-1] * P[pi] % MOD[pi];
            ipw[pi][i] = 1ll * ipw[pi][i-1] * IP[pi] % MOD[pi];
        }
    }
}

// WARNING KEN ALPHABET MAYHIECH a..z BEDDEL HASH FORMULA
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
    // pref_hash 0-indexed
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

    // l and r inclusive and  0-indexed
    array<int, NBH> gib_hash(int l, int r) const {
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
```
