# Presistent Segment Tree

```cpp
struct p_seg_tree {
	struct custom_node {};
	typedef custom_node node;
	int n, nd_cnt = 0;
	vector<node> t;
	vi tlv, trv;

	int log2(int n) {
		int res = 1;
		while (n > 1) {
			++res;
			n /= 2;
		}
		return res+1;
	}
	pseg_tree(int _n) {
		n = _n;
		int lg2 = log2(_n);
		t = vector<node>((4+lg2)*_n+1);
		tlv = trv = vi((4+lg2)*_n+1);
	}

	node combine(const node& a, const node& b);
	int build() { return _build(0, n-1); }
	void update(int pos, int x, int v) { _update(pos, x, v, 0, n-1); }
	node query(int k, int vs, int ve) { return _query(k, vs, ve, 0, n-1); }

	int _build(int tl, int tr) {
		if (tl == tr) {
			// init t[nd_cnt]
			return nd_cnt++;
		}
		int tm = (tl + tr) / 2;
		int cur_id = nd_cnt++;
		tlv[cur_id] = _build(tl, tm);
		trv[cur_id] = _build(tm+1, tr);
		t[cur_id] = combine(t[tlv[cur_id]], t[trv[cur_id]]);
		return cur_id;
	}
	int _update(int pos, int x, int v, int tl, int tr) {
		if (tl == tr) {
			// update t[nd_cnt]
			return nd_cnt++;
		}
		int tm = (tl + tr) / 2;
		int cur_id = nd_cnt++;
		if (pos <= tm) {
			tlv[cur_id] = _update(pos, x, tlv[v], tl, tm);
			trv[cur_id] = trv[v];
		} else {
			tlv[cur_id] = tlv[v];
			trv[cur_id] = _update(pos, x, trv[v], tm+1, tr);
		}
		t[cur_id] = combine(t[tlv[cur_id]], t[trv[cur_id]]);
		return cur_id;
	}
	node _query(int k, int vs, int ve, int tl, int tr) {
		// logic differs. write your own.
		int tm = (tl + tr) / 2;
		node ql = _query(k, tlv[vs], tlv[ve], tl, tm);
		node qr = _query(k, trv[vs], trv[ve], tl, tm);
		return node();
	}
};
```
