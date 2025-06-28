# Matching

## Maximum Bipartite Matching

### Tips
- independent subsets of a graph contains vertices having no edges.
- in a bipartite graph, the size of the minimum vertex cover is equal to the size of the maximum matching.
- in every graph, independent subsets and vertex covers are complements of each other (if S is a vertex cover, then the set of all vertices not belonging to S is an independent subset, and vice versa). So, the maximum independent subset is the complement of the minimum vertex cover.

### Hopcroft-Karp $O(m\sqrt n)$

```cpp
constexpr int MAXV = 2e5 + 2, INF = 1e9;
// l , r and d filled with 0s
int l[MAXV], r[MAXV], d[MAXV];
vi g[MAXV]; // 1-indexed

struct hopcroft_karp {
    int n;
    hopcroft_karp(int _n) : n(_n) {}
    void add_edge(int u, int v) {
        g[u].push_back(v + n); //right id is increased by n, so is l[u]
    }
    bool bfs() {
        queue<int> q;
        for (int u = 1; u <= n; u++) {
            if (!l[u]) d[u] = 0, q.push(u);
            else d[u] = INF;
        }
        d[0] = INF;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto v : g[u]) {
                if (d[r[v]] == INF) {
                    d[r[v]] = d[u] + 1;
                    q.push(r[v]);
                }
            }
        }
        return d[0] != INF;
    }
    bool dfs(int u) {
        if (!u) return true;
        for (auto v : g[u]) {
            if(d[r[v]] == d[u] + 1 && dfs(r[v])) {
                l[u] = v;
                r[v] = u;
                return true;
            }
        }
        d[u] = INF;
        return false;
    }
    int maximum_matching() {
        int ans = 0;
        while (bfs()) {
            for(int u = 1; u <= n; u++) {
                if (!l[u] && dfs(u)) {
                    ans++;
                }
            }
        }
        return ans;
    }
};
```

#### Notes

- if you want to extract the matching for each `l[i] != 0` it contains the corresponding `j+n` that is matched to, just subtract the n (1-indexed).

## Assignment problem in a Bipartite graph in $O(n^3)$

```cpp
// A and ans are 1-indexed
constexpr ll INF = (1LL<<40);
void correct_fill(vector<vector<ll>>& A, int n, int m) {
    if (n == m) return;
    if (n < m) {
        rep(i, n+1, m+1) {
            rep(j, 1, m+1) {
                A[i][j] = 0;
            }
        }
    } else {
        rep(i, 1, n+1) {
            rep(j, m+1, n+1) {
                A[i][j] = INF;
            }
        }
    }
}
// A should be of size (max(n, m)+1) X (max(n, m)+1)
// ans should be of size (max(n, m)+1)
void optimal_assign(vector<vector<ll>>& A, int n, int m, vector<int>& ans) {
    assert(sz(A) == max(n, m)+1 && sz(A[0]) == max(n, m)+1);
    correct_fill(A, n, m);

    n = m = max(n, m);
    vector<ll> u(n+1), v(m+1);
    vi p(m+1), way(m+1);
    for (int i=1; i<=n; ++i) {
        p[0] = i;
        int j0 = 0;
        vector<ll> minv (m+1, INF);
        vector<bool> used (m+1, false);
        do {
            used[j0] = true;
            int i0 = p[j0],  j1;
            ll delta = INF;
            for (int j=1; j<=m; ++j)
                if (!used[j]) {
                    ll cur = A[i0][j]-u[i0]-v[j];
                    if (cur < minv[j])
                        minv[j] = cur,  way[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j],  j1 = j;
                }
            for (int j=0; j<=m; ++j)
                if (used[j])
                    u[p[j]] += delta,  v[j] -= delta;
                else
                    minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    for (int j=1; j<=m; ++j) {
        ans[p[j]] = j;
    }
}
```

### Notes
- this algorithm solves a problem where you have $n$ workers and $m$ jobs. Each worker has a cost for each job.
After running the algorithm `ans[i]` will contain the job assigned to worker `i` if `a[i] > m` then this worker wasn't assigned any job.
- before running the hungarian algorithm we will try to make the `A` square filling missing rows with `0`s and missing rows with `INF`s