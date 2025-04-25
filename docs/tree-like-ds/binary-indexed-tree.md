# Binary Indexed Tree

Use it for a short, simple & efficient code. (Always 1-indexed)

Only for reversible operations.

## Classic BIT
```cpp
template <class T>
struct BIT
{
    int n;
    vector<T> t;
    BIT(int s)
    {
        n = s;
        t = vector<T>(n + 1, T());
    }
    BIT(vector<T> &a) : BIT(a.size())
    {
        rep(i, 0, n)
            add(i, a[i]);
    }
    void add(int idx, T val)
    {
        for (idx++; idx <= n; idx += (idx & -idx))
            t[idx] += val;
    }
    T query(int idx)
    {
        T res = T();
        for (idx++; idx > 0; idx -= (idx & -idx))
            res += t[idx];
        return res;
    }
    T query(int l, int r)
    {
        return query(r) - query(l - 1);
    }
};
```

## Range Update & Range Query
```cpp
template <class T>
struct RangeBIT
{
    int n;
    BIT<T> B1, B2;
    RangeBIT(int s) : n(s), B1(s), B2(s) {}
    RangeBIT(vector<T> &a) : RangeBIT(a.size())
    {
        rep(i, 0, n)
            add(i, i, a[i]);
    }
    void __add_till_infinity(int r, T val) /* '+val' to [r, +inf) */ 
    {
        B1.add(r, val);
        B2.add(r, (r - 1) * (-val));
    }
    void add(int l, int r, T val)
    {
        __add_till_infinity(l, val);
        __add_till_infinity(r + 1, -val);
    }
    T query(int r)
    {
        return r * B1.query(r) + B2.query(r);
    }
    T query(int l, int r)
    {
        return query(r) - query(l - 1);
    }
};
```

## 2-Dimensional BIT
```cpp
template <class T>
struct BIT2D
{
    int n, m;
    vector<vector<T>> t;
    BIT2D(int x, int y)
    {
        n = x;
        m = y;
        t = vector<vector<T>>(n + 1, vector<T>(m + 1, T()));
    }
    BIT2D(vector<vector<T>> &a) : BIT2D(a.size(), a[0].size())
    {
        rep(i, 0, n)
            rep(j, 0, m)
                add(i, j, a[i][j]);
    }
    void add(int x, int y, T val)
    {
        for (int i = x + 1; i <= n; i += (i & -i))
            for (int j = y + 1; j <= m; j += (j & -j))
                t[i][j] += val;
    }
    T query(int x, int y)   /*Warning : use i & j not x & y*/
    {
        T res = T();
        for (int i = x + 1; i > 0; i -= (i & -i)) 
            for (int j = y + 1; j > 0; j -= (j & -j))
                res += t[i][j];
        return res;
    }
    T query(int x1, int y1, int x2, int y2) /* (x1,y1): lower left corner */
    {
        return query(x2, y2) + query(x1-1, y1-1) - query(x1-1, y2) - query(x2, y1-1);
    }
};
```

## Linear Construction
```cpp
    BIT(vector<T> &a) : BIT(a.size())
    {
        rep(i, 0, n){
            int idx = i+1;
            t[idx] += a[i];
            int nxt = idx + (idx & -idx);
            if(nxt <= n)
                t[nxt] += t[idx];
        }
    }
    BIT2D(vector<vector<T>> &a) : BIT2D(a.size(), a[0].size())
    {
        rep(x, 0, n)
            rep(y, 0, m){
                int i = x+1;
                int j = y+1;
                t[i][j] += a[x][y];
                int nxt_i = i + (i & -i);
                int nxt_j = j + (j & -j);
                /* As usual */
                if(nxt_i <= n) t[nxt_i][j] += t[i][j];
                if(nxt_j <= m) t[i][nxt_j] += t[i][j];
                /* Now, plot twist */
                if(nxt_i <= n && nxt_j <= m) t[nxt_i][nxt_j] -= t[i][j];
            }
    }
    BIT3D(vector<vector<vector<T>>> &a) : BIT3D(a.size(), a[0].size(), a[0][0].size())
    {
        rep(x, 0, n)
            rep(y, 0, m)
                rep(z, 0, l){
                int i = x+1;
                int j = y+1;
                int k = z+1;
                t[i][j][k] += a[x][y][z];
                int nxt_i = i + (i & -i);
                int nxt_j = j + (j & -j);
                int nxt_k = k + (k & -k);
                /* 1-Step */
                if(nxt_i <= n) t[nxt_i][j][k] += t[i][j][k];
                if(nxt_j <= m) t[i][nxt_j][k] += t[i][j][k];
                if(nxt_k <= l) t[i][j][nxt_k] += t[i][j][k];
                /* 2-Steps */
                if(nxt_i <= n && nxt_j <= m) t[nxt_i][nxt_j][k] -= t[i][j][k];
                if(nxt_i <= n && nxt_k <= l) t[nxt_i][j][nxt_k] -= t[i][j][k];
                if(nxt_j <= m && nxt_k <= l) t[i][nxt_j][nxt_k] -= t[i][j][k];
                /* 3-Steps */
                if(nxt_i <= n && nxt_j <= m && nxt_k <= l) t[nxt_i][nxt_j][nxt_k] += t[i][j][k];
            }
    }
    /*Inclusion-Exclusion*/

```