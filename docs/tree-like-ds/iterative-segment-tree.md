# Iterative Segment Tree

## Range Query, Point Update

```cpp
struct custom_node {
    ll sum = 0;
    custom_node() {}
    custom_node(int x) : sum(x) {}
};
typedef custom_node node;
node combine(const node& l, const node& r) {
    node res;
    res.sum = l.sum + r.sum;
    return res;
}
struct i_seg_tree {
    int n;
    vector<node> t;

    i_seg_tree(int _n) : n(_n), t(2*_n) {}

    void build(const vector<int>& a) {
        for(int i = 0; i < n; i++) t[i + n] = node(a[i]);
        for(int i = n - 1; i > 0; --i) t[i] = combine(t[i<<1], t[i<<1 | 1]);
    }

    void set(int p, int v) {
        for (t[p += n] = node(v); p >>= 1; ) t[p] = combine(t[p<<1], t[p<<1|1]);
    }

    // query on the range [l, r[
    node query(int l, int r) {
        node resl, resr;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if(l & 1) resl = combine(resl, t[l++]);
            if(r & 1) resr = combine(t[--r], resr);
        }
        return combine(resl, resr);
    }
};
```

## Range Query, Lazy Range Update

```cpp
constexpr int MOD = 998244353;
struct custom_node {
    int sum = 0, cnt = 1;
    custom_node() {}
    custom_node(int x) : sum(x) {}
};
typedef custom_node node;
node combine(const node& l, const node& r) {
    node res;
    res.sum = (l.sum + r.sum) % MOD;
    res.cnt = l.cnt + r.cnt;
    return res;
}
struct lazy_node {
    int b = 1, c = 0;
    lazy_node() {}
    lazy_node(int _b, int _c) : b(_b), c(_c) {}
};
typedef lazy_node lnode;
struct i_lazy_seg_tree {
    int n, log_n;
    vector<node> t;
    vector<lnode> lazy;

    i_lazy_seg_tree(int _n) : n(_n), t(2*_n), lazy(_n) {
        log_n = sizeof(int) * 8 - __builtin_clz(_n);
    }

    void build(const vector<int>& a) {
        for(int i = 0; i < n; i++) t[i + n] = node(a[i]);
        for(int i = n - 1; i > 0; --i) t[i] = combine(t[i<<1], t[i<<1 | 1]);
    }

    void modify(int v, const lnode& x) {
        t[v].sum = (1LL * x.b * t[v].sum + 1LL * x.c * t[v].cnt) % MOD;
        if (v < n) {
            lazy[v].b = 1LL * x.b * lazy[v].b % MOD;
            lazy[v].c = (1LL * x.b * lazy[v].c + x.c) % MOD;
        }
    }

    void push(int v) {
        if (lazy[v].b != 1 || lazy[v].c != 0) {
            modify(v<<1, lazy[v]);
            modify(v<<1 | 1, lazy[v]);
            lazy[v] = lnode();
        }
    }

    // update on the range [l, r[
    void update(int l, int r, const lnode& x) {
        l += n; r += n;
        for (int i = log_n; i >= 1; --i) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        int l0 = l, r0 = r;
        for(; l < r; l >>= 1, r >>= 1) {
            if(l & 1) modify(l++, x);
            if(r & 1) modify(--r, x);
        }

        l = l0; r = r0;
        for (int i = 1; i <= log_n; ++i) {
            if (((l >> i) << i) != l) t[l>>i] = combine(t[(l>>i)<<1], t[(l>>i)<<1 | 1]);
            if (((r >> i) << i) != r) t[(r-1)>>i] = combine(t[((r-1)>>i)<<1], t[((r-1)>>i)<<1 | 1]);
        }
    }

    // query on the range [l, r[
    node query(int l, int r) {
        l += n; r += n;
        for (int i = log_n; i >= 1; --i) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        bool f1 = true, f2 = true;
        node resl, resr;
        for(; l < r; l >>= 1, r >>= 1) {
            if(l & 1) resl = f1 ? t[l++] : combine(resl, t[l++]), f1 = false;
            if(r & 1) resr = f2 ? t[--r] : combine(t[--r], resr), f2 = false;
        }
        if(f2) return resl;
        if(f1) return resr;
        return combine(resl, resr);
    }
};
```