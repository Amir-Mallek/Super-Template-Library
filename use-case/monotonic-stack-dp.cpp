/**
 * DP using monotonic stack 
 * 
 * Hint : some old dp states are not needed, because some later ones will always win them.
 * 
 * Hint2: store only the data you will need, in some order, and remove new-obsolete dp states.
 * 
 * Hint3: simulate the process by hand and guess what DataStr can do that.
 *  
 * Link : https://codeforces.com/contest/777/problem/E
 */

 #include <bits/stdc++.h>
 using namespace std;
 
 #define rep(i, a, b) for (int i = a; i < (b); ++i)
 typedef long long ll;
 typedef vector<int> vi;
 
 
 stack<pair<ll,int>> s;
 void add(pair<ll,int> val)
 {
     while(!s.empty() && s.top() <= val)
         s.pop();
     s.push(val);
 }
 pair<ll,int> get(int a){
     pair<ll,int> res = {0, a+1};
     while(!s.empty() && s.top().second > a){
         res = s.top();
         s.pop();
     }
     return res;
 }
 
 
 
 int main()
 {
     cin.tie(0);
     ios::sync_with_stdio(0);
     int n;
     cin >>n;
     ll a[n], b[n], h[n];
     rep(i,0,n)cin >> a[i] >> b[i] >> h[i];
     vi v;
     rep(i,0,n) v.push_back(i);
     //sorting the indeces by their content
     sort(v.begin(), v.end(), [&](const int i, const int j){
         if(b[i] == b[j])
             return a[i] < a[j];
         return b[i] < b[j];
     });
     // rep(i,0,n) cout << v[i] << ' ';
 
     rep(i,0,n){
         int idx = v[i];
         //considering the ring number 'idx'
         auto val = get(a[idx]);
         add({ h[idx] + val.first , b[idx] });
     }
     cout << get(0).first;
 }