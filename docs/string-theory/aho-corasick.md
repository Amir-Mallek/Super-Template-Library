# Aho-Corasick Algorithm

## Trie with failure links

```cpp
// change it however you like
struct node {
    int nmax, nmin, depth;
    node(): nmax(0), nmin(INF) {}
};

constexpr int LEN = 1e6 + 5, K = 26;
int go[LEN][K], fail[LEN], nd_cnt = 0;
node tdata[LEN];

// run it once before using the trie to init
int add_node() {
    memset(go[nd_cnt], -1, sizeof go[nd_cnt]);
    return nd_cnt++;
}

void add_string(const string& s, int id) {
    int v = 0, n = sz(s);
    rep(i, 0, n) {
        // WARNING CHANGE THIS IF ALPHA CHANGES
        int c = (s[i]-'a');

        if (go[v][c] == -1) {
            go[v][c] = add_node();
        }
        v = go[v][c];

        // add context logic
        tdata[v].nmax = max(tdata[v].nmax, a[id][i]);
        tdata[v].nmin = min(tdata[v].nmin, a[id][i]);
        tdata[v].depth = i;
    }
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
                to_process.push(nxt);
            } else nxt = go[fail[v]][c];
        }
    }
}
```

### Usage

- `LEN` is the maximum total length of strings that will be add to the trie.
- `K` is the size of the alphabet. If it is big and you have memory concerns use a map (or a persistent DS) instead of static array.
- Make you own struct `node` with its special attributes thats the data in every node.
- `add_node` should be run to initilize the first node of the trie.
- `add_string` adds a string to the trie in $O(K \cdot |s|)$.
- `buil_trie` should be run after adding the strings to build failure links and `go` in $O(LEN \cdot K)$. If you use a persistent DS the complexity would be $O(LEN \cdot log(K))$

### Notes

- If you're dealing with `A...Z`, `a..z`, `0..9`, `` ! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _ ` { | } ~  ``, you can chose `K = 128` and where you adding a string use `s[i]` instead of `s[i]-'a'`.
