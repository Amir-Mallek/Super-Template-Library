/**
 * BIT 2D range queries, point updates
 * Link : https://lightoj.com/problem/points-in-rectangle
 */

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
typedef long long ll;
typedef vector<int> vi;

/**
 * Classical Binary 1-Indexed Tree
 * Methods are 0-indexed
 * Notes :
 * - BIT is halfway between a normal array and a prefix sum array
 * - 1-indexing uses LSB(x) = (x & -x)
 */
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

/**
 * Range Query Range Update Binary 1-Indexed Tree
 * Methods are 0-indexed
 * Notes :
 * - it uses the classic BIT as a blackbox
 * - the used logic has a very nice visual explanation
 * - beware of overflows on multiplications --> you may have to use Segment Tree
 */
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
    void __add_till_infinity(int r, T val) /* '+val' to [r, +inf) */ /*private*/
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

/**
 * 2D Binary 1-Indexed Tree
 */
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
    T query(int x, int y)
    {
        T res = T();
        for (int i = x + 1; i > 0; i -= (i & -i))
            for (int j = y + 1; j > 0; j -= (j & -j))
                res += t[i][j];
        return res;
    }
    T query(int x1, int y1, int x2, int y2) /* (x1,y1): lower left corner */
    {
        return query(x2, y2) + query(x1 - 1, y1 - 1) - query(x1 - 1, y2) - query(x2, y1 - 1);
    }
};

int counter = 0;
void solve()
{
    cout << "Case " << (++counter) << ":\n";
    int q;
    cin >> q;
    /*
    //testing RangeBIT
    RangeBIT<ll> a(n);
    rep(i,0,n)
        cout << a.query(i,i) << ' ';
    cout << endl;
    a.add(2,4,3);
    rep(i,0,n)
        cout << a.query(i,i) << ' ';
    cout << endl;
    // Works well
    */
    BIT2D<int> b(1001, 1001);
    while (q--)
    {
        int c;
        cin >> c;
        if (c)
        {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << b.query(x1, y1, x2, y2) << '\n';
        }
        else
        {
            int x, y;
            cin >> x >> y;
            /*if point exist*/
            if (b.query(x, y, x, y) == 0)
                b.add(x, y, 1);
            // cout << b.query(x,y) << "*\n";
        }
    }
}

int main()
{
    // Preprocessing here please...
    int t = 1;
    cin >> t; // press `Tab` to go to solve
    while (t--)
        solve();
    return 0;
}