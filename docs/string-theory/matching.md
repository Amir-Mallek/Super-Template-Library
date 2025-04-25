# String Matching

## Prefix Function (KMP)

```cpp
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
```

### Usage

- `prefix_function` takes a string or a vector of anything comparable `s` and returns of a vector containing pi for every index. Complexity is $O(|s|)$.
- `match` takes a container `s` and a target `t` and returns the indices of the beginings of each match. Complexity is $O(|t|+|s|)$.

## Rolling Hash

```cpp
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
```

### Usage

- `precompute` precomputes powers of all `p` and `ip` in $O(N)$. should be run before using anything else.
- `hash_string` hashes a given string `s` with different `NBH` hashes in $O(|s|)$.
- `r_hash` given a string `s` constructs `pref_hash` in $O(|s|)$. Then you can get with `get_hash` any hash of a substring of `s` in $O(1)$.

### Notes

- You can change anything about the primes used to hash.
- You can also change the number of hashes using `NBH`. This will affect run time significantly.
- Comparing $10^6$ string will require in most cases 2 hashes.
- Use a prime `p` close to the size of the alphabet.
- You can create different hashing optimizations and formulations based on the problem's nature.
