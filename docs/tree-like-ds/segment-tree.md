# Segment Tree
```cpp
const int MAXN = 1e5+10;

// Everything is ONE-INDEXED
template <typename T>
struct SegmentTree {

    function<T(T, T)> combine;        // <T(const T&, const T&)>
    // neutral element
    T e;
    T t[4*MAXN]; 
    int n;

    SegmentTree(function<T(T, T)> combine, T e, int n = MAXN-1) :
    combine(combine), e(e), n(n) {}

    // a is ONE-INDEXED (can be an array)
    void build(vector<T> &a, int v = 1, int tl = 1, int tr = -1) {
        if (tr == -1) tr = n;
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }
    // pos is ONE-INDEXED
    void update(int pos, T new_val, int v = 1, int tl = 1, int tr = -1) {
        if (tr == -1) tr = n;
        if (tl == tr) {
            t[v] = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(pos, new_val, 2*v, tl, tm);
            else
                update(pos, new_val, 2*v+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }
    // l and r are ONE-INDEXED
    T query(int l, int r, int v = 1, int tl = 1, int tr = -1) {
        if (tr == -1) tr = n;
        if (l > r) return e;
        if (tl == l && tr == r) return t[v];
        int tm = (tl + tr) / 2;
        return combine(
            query(l,   min(r, tm), 2*v ,  tl  , tm) ,
            query(max(l, tm+1), r, 2*v+1, tm+1, tr)
        );
    }
};
```
How to use : 
```cpp
/* struct Node { ... };*/

SegmentTree<Node> sgt (
    [](Node a, Node b){return Node(a,b);}, /*combine*/
    Node(),                               /*neutral*/ 
    n                                    /*n*/ 
);
sgt.build(v);
sgt.query(l,r);
sgt.update(i,Node());
```
Now we can focus more on the logic of `combine`, and the structure of `Node`.