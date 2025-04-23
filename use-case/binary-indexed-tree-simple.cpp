/**
 * BIT Simple Use Case
 * Link : https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3238
 */

 #include <bits/stdc++.h>
 using namespace std;
 
 #define rep(i, a, b) for (int i = a; i < (b); ++i)
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
     BIT(vector<T> a) : BIT(a.size())
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
 
 int counter = 0;
 
 void solve(int n)
 {
     cout << "Case " << (++counter) << ":\n";
     vi a(n);
     rep(i, 0, n)
     {
         cin >> a[i];
     }
     BIT<int> b(a);
     while (true)
     {
         string s;
         cin >> s;
         if (s == "END")
             break;
         if (s == "M")
         {
             int x, y;
             cin >> x >> y;
             x--, y--;
             cout << b.query(x, y) << '\n';
         }
         else
         {
             int x, r;
             cin >> x >> r;
             x--;
             int old = b.query(x, x);
             b.add(x, r - old);
         }
     }
 }
 
 int main()
 {
     cin.tie(0);
     ios::sync_with_stdio(0);
     while (true)
     {
         int N;
         cin >> N;
         if (N)
         {
             if(counter)
                 cout << "\n";
             solve(N);
         }
         else
             break;
     }
 }