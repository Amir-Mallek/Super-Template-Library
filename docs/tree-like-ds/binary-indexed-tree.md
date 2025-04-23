# Binary Indexed Tree

Use it for a short, simple & efficient code. (Always 1-indexed)

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
    BIT(vector<T> a) : BIT(a.size())
    {
        rep(i, 0, n)
            add(i, a[i]);
    }
    void add(int idx, T val)
    {
        for (idx++ ; idx <= n; idx += (idx & -idx))
            t[idx] += val;
    }
    T query(int idx)
    {
        T res = T();
        for (idx++ ; idx > 0; idx -= (idx & -idx))
            res += t[idx];
        return res;
    }
    T query(int l, int r)
    {
        return query(r) - query(l - 1);
    }
};
```