# Segment Tree

```cpp
struct Node {};
typedef Node node;

constexpr int N = 1e5 + 5;
node t[4*N];
int n; // WARNING U NEED TO INITILIZE 'n'

node combine(const node& a, const node& b);

void build(int v = 1, int tl = 0, int tr = n-1) {
	if (tl == tr) {
		t[v] = ;
	} else {
		int tm = (tl + tr) / 2;
		build(v<<1, tl, tm);
		build((v<<1)+1, tm+1, tr);
		t[v] = combine(t[v<<1], t[(v<<1)+1]);
	}
}

void push(int v);

void update(int l, int r, int x, int v = 1, int tl = 0, int tr = n-1) {
	if (l > r) return;
	if (tl == l && tr == r) {
        // update lazy variable in t[v] if lazy
	} else {
		push(v); // remove if not lazy
		int tm = (tl + tr) / 2;
		update(l, min(r, tm), x, v<<1, tl, tm);
		update(max(l, tm+1), r, x, (v<<1)+1, tm+1, tr);
		t[v] = combine(t[v<<1], t[(v<<1)+1]);
	}
}

node query(int l, int r, int v = 1, int tl = 0, int tr = n-1) {
	if (tl == l && tr == r) return t[v];
	int tm = (tl + tr) / 2;
	push(v); // remove if not lazy
	if (l > tm) return query(l, r, (v<<1)+1, tm+1, tr);
	if (r <= tm) return query(l, r, v<<1, tl, tm);
	return combine(
		query(l, tm, v<<1, tl, tm),
		query(tm+1, r, (v<<1)+1, tm+1, tr)
	);
}
```

## Usage

- intialize `n` and make sure to have the correct max `N`.
- for `node` you can choose any type: `ll`, `int`, `vi` or make your custom `Node` struct (containing the lazy variable if you need it).
- define the `combine` function. `combine` can be defined for other things other than `node` because you can combine only a part of `node`.
- if you're using lazy propagation define `push`.
- NB: if you're using an array to initilize the seg-tree should be **0-indexed**

How to use :

```cpp
n = ;
build();
update(l, r, x);
query(l, r);
```
