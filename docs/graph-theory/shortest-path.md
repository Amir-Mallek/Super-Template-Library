# Shortest Path

## Dijkstra $O(n^2 + m)$

```cpp
// WARNING CHANGE ANYTHING RELATED TO D TO LL IF NEEDED
constexpr int INF = 1000000000, MAXN = 1e5 + 1;
vector<pair<int, int>> adj[MAXN];
int u[MAXN], n, t_id = 0; // t_id is used to avoid reseting u;

//                 fill d wiht INF / fill p with -1
void dijkstra(int s, vector<int>& d, vector<int>& p) {
    ++t_id;

    d[s] = 0;
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (u[j] != t_id && (v == -1 || d[j] < d[v]))
                v = j;
        }

        if (d[v] == INF)
            break;

        u[v] = t_id;
        for (auto& [to, len] : adj[v]) {
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
            }
        }
    }
}
```

### Notes

- this version is used when the graph is dense, $m \approx n^2$.
- `d` should be filled with `INF` and `p` with `-1`.
- `p` is used to restore the shortest path from `s` to any vertex `u` having `d[u] < INF`.
- Dijkstra can't handle negative weights (same for the version below).

## Dijkstra $O(n \log_2n + m \log_2n)$

```cpp
// WARNING CHANGE ANYTHING RELATED TO D TO LL IF NEEDED
constexpr int INF = 1000000000, MAXN = 1e5 + 1;
vector<pair<int, int>> adj[MAXN];
int n;

//                 fill d wiht INF / fill p with -1
void dijkstra(int s, vector<int>& d, vector<int>& p) {
    d[s] = 0;
    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty()) {
        auto [d_v, v] = q.top();
        q.pop();
        if (d_v != d[v])
            continue;

        for (auto& [to, len] : adj[v]) {
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                q.push({d[to], to});
            }
        }
    }
}
```

### Notes

- this version is used when the graph is sparse, $m \approx n$.

## Bellman-Ford $O(n m)$

```cpp
// WARNING CHANGE ANYTHING RELATED TO D TO LL IF NEEDED
constexpr int INF = 1000000000, MAXM = 1e5 + 1;
int m;
tuple<int, int, int> edges[MAXM]; // (u, v, w)

//                      fill d wiht INF / fill p with -1
void bellman_ford(int v, vector<int>& d, vector<int>& p) {
    d[v] = 0;

    // will do a max of n-1 iterations
    while (true) {
        bool any = false;
        for (int i = 0; i < m; ++i) {
            auto& [a, b, cost] = edges[i];
            if (d[a] < INF)
                if (d[b] > d[a] + cost) {
                    d[b] = d[a] + cost;
                    p[b] = a;
                    any = true;
                }
        }
        if (!any)
            break;
    }
}
```

### Notes

- this implementation assumes there is no negative cycles.
- to detect and extract a negative cycle, we do $n$ iteration of the scan and if in the $n$-th iteration if there is a relaxation for vertex `x`. Then go back $n$ times in the predecessors of `x` to obtain `y` which is guaranteed to be on the cycle. Now you just go through `p` starting from `y` until you revisit it. 

## All Pairs Shortest Path: Floyd-Warshall

```cpp
for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 
        }
    }
}
```