# Prefix function

```cpp
const int MAXN = 1e5 + 1;
int pi[MAXN];
void prefix_function(const string& s) {
    int n = (int)s.length();
    pi[0] = 0;
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
}
```

# Z-Function

```cpp
vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}
```

# Trie (Aho-Corasick)

```cpp
const int K = 26;
vector<Vertex> trie(1);

struct Vertex {
    int next[K];
		int count = 0;
		bool output = false;
    Vertex() {
        memset(next, -1, sizeof(next));
    }
};

void add_string(string const& s) {
    int v = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (trie[v].next[c] == -1) {
            trie[v].next[c] = trie.size();
            trie.emplace_back();
        }
        v = trie[v].next[c];
    }
    trie[v].output = true;
}
```

# Trie with failure links with BFS O(n log K)

```cpp
const int K = 26;

struct Vertex {
    int next[K];
    bool output = false;

    Vertex() {
        fill(begin(next), end(next), -1);
    }
};

vector<Vertex> t(1);

void add_string(string const& s) {
    int v = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (t[v].next[c] == -1) {
            t[v].next[c] = t.size();
            t.emplace_back();
        }
        v = t[v].next[c];
    }
    t[v].output = true;
}

vvi go;
vi link;

void buildLinks() {
    go = vvi(t.size(), vi(K, -1));
    link = vi(t.size());
    link[0] = 0;
    queue<int> q;
    rep(c, 0, K) {
        int& u = t[0].next[c];
        if (u == -1)
            go[0][c] = 0;
        else {
            go[0][c] = u;
            link[u] = 0;
            q.push(u);
        }
    }
    int v;
    while (!q.empty()) {
        v = q.front();
        q.pop();
        rep(c, 0, K) {
            int& u = t[v].next[c];
            if (u == -1) {
                go[v][c] = go[link[v]][c];
            } else {
                link[u] = go[link[v]][c];
                go[v][c] = u;
                q.push(u);
            }
        }
    }
}

```

# Trie with failure links with BFS for big alphabet

```cpp
struct Vertex {
    unordered_map<char, int> next;
    bool output = false;

    int findNext(int c) {
        if (next.count(c)) return next[c];
        return -1;
    }
};

int nb = 1;
vector<Vertex> t(1);

void add_string(string const& s) {
    int v = 0;
    for (char ch : s) {
        if (t[v].findNext(ch) == -1) {
            t[v].next[ch] = nb++;
            t.emplace_back();
        }
        v = t[v].next[ch];
    }
    t[v].output = true;
}

vector<map<char, int>> go;
vi link;

int goTo(int v, char c) {
    if (go[v].count(c)) return go[v][c];
    if (v == 0) return 0;
    return go[v][c] = goTo(link[v], c);
}

void buildLinks() {
    go = vector<map<char, int>>(nb);
    link = vi(nb);
    link[0] = 0;
    queue<int> q;
    q.push(0);
    int v;
    while (!q.empty()) {
        v = q.front();
        q.pop();
        for (auto &[c, u] : t[v].next) {
					//TARTIB VERY IMPORTANT MATBEDLOUCH
            link[u] = goTo(link[v], c);
            go[v][c] = u;
            q.push(u);
        }
    }
}
```

## Notes

- tparkourih kima taddi string presque
- next yejjem ykoun map ken alphabet mteek kbira

# String Hashing Rabin-Karp

### Notes

//in english

- IMPORTANT: Ken tnejjem tnakass mel strings li tcomparihom behi bech tnakkas colisions kima par exemple tkaren string of length l bebaadhom
- p1 = 31, p2 = 53 - m1 = 1e9+9, m2 = 1e9+7
- ken tcompari fi $10^6$ strings bin baadhhom zid aamel hash theni
- estaamel p fi kobr alphabet mteek
- dima haael elka relationet bin les hash hasb el problem kima problem li khdemtou maa mahmoud men sheet mtaylor

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
