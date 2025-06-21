# Segment Tree

```cpp
struct custom_node {};
typedef custom_node node;
inline node combine(const node& a, const node& b) {}

struct seg_tree {
    int n;
    bool isBuilt = false;
    vector<node> t;

    seg_tree(int _n) : n(_n), t(4*_n+1) {}

    void push(int v, int tl, int tr){
        // ...
    }

    void build(const vi& a) { _build(a, 1, 0, n-1); isBuilt = true; }
    void update(int l, int r, int x) { assert(isBuilt); _update(l, r, x, 1, 0, n-1); }
    node query(int l, int r) { assert(isBuilt); return _query(l, r, 1, 0, n-1); }

    void _build(const vi& a, int v, int tl, int tr) {
        if (tl == tr) {
            // init t[v]
        } else {
            int tm = (tl + tr) >> 1;
            _build(a, v<<1, tl, tm);
            _build(a, (v<<1)+1, tm+1, tr);
            t[v] = combine(t[v<<1], t[(v<<1)+1]);
        }
    }
    void _update(int l, int r, int x, int v, int tl, int tr) {
        if (l > r) return;
        if (tl == l && tr == r) {
            // update t[v]
            // update lazy variable in t[v] if lazy
        } else {
            int tm = (tl + tr) >> 1;
            push(v, tl, tr); // remove if not lazy
            _update(l, min(r, tm), x, v<<1, tl, tm);
            _update(max(l, tm+1), r, x, (v<<1)+1, tm+1, tr);
            t[v] = combine(t[v<<1], t[(v<<1)+1]);
        }
    }
    node _query(int l, int r, int v, int tl, int tr) {
        if (tl == l && tr == r) return t[v];
        int tm = (tl + tr) >> 1;
        push(v, tl, tr); // remove if not lazy
        if (l > tm) return _query(l, r, (v<<1)+1, tm+1, tr);
        if (r <= tm) return _query(l, r, v<<1, tl, tm);
        return combine(
            _query(l, tm, v<<1, tl, tm),
            _query(tm+1, r, (v<<1)+1, tm+1, tr)
        );
    }
};
```

## Usage

- intilize `seg_tree` by specifying its size `n`.
- `build` builds the seg-tree by giving it an `vi` (you can change it to iterable of your liking).
- define the `combine` function. `combine` can combine only a part of `node`.
- if you're using lazy propagation define `push`.

## Notes

- if you want 2 of the same seg-tree (same method logic), just make another one with the struct and build it. Example:

```cpp
seg_tree s1(n), s2(m);
s1.build(a); s2.build(b);
```

- if you want 2 different seg-trees (different method logic), copy the struct, give it a new name and change methods directly. Example:

```cpp
struct seg_tree1 { ... } // min max seg tree
struct seg_tree2 { ... } // lazy prop seg tree on strings
.
.
.
string s = ...;
vi a = ...;
seg_tree1 st1(s.size()); st1.build(s);
seg_tree2 st2(a.size()); st2.build(a);
```
