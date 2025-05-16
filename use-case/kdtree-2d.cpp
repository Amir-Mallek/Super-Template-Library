/**
* KDTree - modified use case (nearest point not equal to query point)
* Link : www.spoj.com/problems/FAILURE/
*/
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = (a); i < (b) ; i++)
#define pb push_back
// The following 3 instructions need to be updated
const int K = 2;
using Unit = long long; 
Unit UNIT_MAX = 1e9; 

inline Unit pow( Unit x , int y ){
    return x*x;
}

using Point = array<Unit,K>;
Point origin = {};

struct Node {
    Point point; int dimension, before, after, size;
    Node(Point point, int dimension = 0, int before = -1, int after = -1, int size = 1)
    : point(point), dimension(dimension), before(before), after(after), size(size) {}
};

Unit distance(Point a, Point b){
    Unit res = Unit(0);
    rep(i,0,K)
        res += pow(a[i]-b[i],2);
    return res;
}
Unit distance2box(Point a, Point start,Point end){
    Unit res = Unit(0);
    rep(i,0,K)
        res += pow( max({start[i] - a[i], Unit(0), a[i] - end[i]}) ,2);
    return res;
}
bool intersection(Point a_start, Point a_end, Point b_start, Point b_end){
    rep(i,0,K)
    if( b_end[i] < a_start[i] || a_end[i] < b_start[i] )
        return false;
    return true;
}
bool inclusion(Point in_start, Point in_end, Point out_start, Point out_end){
    rep(i,0,K)
        if( out_start[i] > in_start[i] || in_end[i] > out_end[i] )
            return false;
    return true;
}

istream& operator>>(istream& in, Point& p){rep(i,0,K)in >> p[i];return in;}
ostream& operator<<(ostream& os, Node  nd){os << "(" ;rep(i,0,K)os<< nd.point[i] << ",)"[i == K-1];return os << "[" << nd.dimension << "]";}

struct KDTree {
    vector<Node> t;

    // Optimized version : in place sorting
    int build(vector<Point> &v, int d=0, int l=-1, int r=-1) {
        if(l ==-1) l = 0, r = v.size();
        if(l == r) return -1;
        sort(v.begin()+l,v.begin()+r,[&](const Point &a, const Point &b){return a[d] < b[d];});

        int mid = (l + r) / 2;
        int res = t.size();
        t.push_back(Node(v[mid], d));

        t[res].size = r - l;
        auto tmp = build(v, (d+1)%K,     l, mid);
        t[res].before = tmp;
        tmp = build(v, (d+1)%K, mid+1,   r);
        t[res].after  = tmp;

        return res;
    }

    // Best way to print any tree
    void print(int x = 0, string pre = ""){
        cout << pre << t[x] <<"\n";
        cout << (pre + "|\\") << "\n";
        if(-1 <t[x].before ) print(t[x].before, pre + "| ");
        if(-1 <t[x].after) cout << (pre + "|") << "\n", print(t[x].after, pre);
    }

    // Optimized version : [start, end] = the corners of the current box
    // Returns the index of the closest point to `q`
    int nearest(Point& q, int idx = 0, int best = 0, Point start={}, Point end={}){ 
        if(idx == -1)
            return best;    
        if(idx == 0){
            rep(i,0,K) start[i] = 0, end[i] = UNIT_MAX; // Adapted to the problem
            if(t[0].point == q) // Only on the first iteration // Adapted to the problem
                best = 1;
        }
        auto now = t[idx];
        // Update best
        if( now.point == q); // Adapted to the problem
        else if(distance(q, now.point) < distance(q, t[best].point)) // Adapted to the problem
            best = idx;
        // Getting Ready To Dive
        auto new_start = start, new_end = end;
        new_start[now.dimension] = new_end[now.dimension] = now.point[now.dimension];
        // Where To Go First
        if( q[now.dimension] <= now.point[now.dimension] ) // before first
        {
            best = nearest(q, now.before, best, start, new_end);
            // Should We Go ?
            if( distance2box(q, new_start, end) < distance(q, t[best].point))
                best = nearest(q, now.after, best, new_start, end);
        }
        else
        {
            best = nearest(q, now.after, best, new_start, end);
            // Should We Go ?
            if( distance2box(q, start, new_end) < distance(q, t[best].point))
                best = nearest(q, now.before, best, start, new_end);
        }
        return best;
    }
    int range_count(Point& range_start, Point& range_end, int idx=0, Point start={}, Point end={}){
        if(idx == -1)
            return 0;    
        if(idx == 0){
            rep(i,0,K) start[i] = 0, end[i] = UNIT_MAX; // Adapted to the problem
        }
        auto now = t[idx];
        if(!intersection(range_start, range_end, start, end))
            return 0;
        if(inclusion(start, end, range_start, range_end))
            return now.size;
        else{
            // Getting Ready To Dive
            auto new_start = start, new_end = end;
            new_start[now.dimension] = new_end[now.dimension] = now.point[now.dimension];
            return
            range_count(range_start, range_end, now.before, start, new_end)
            +
            range_count(range_start, range_end, now.after , new_start, end)
            +
            intersection(range_start, range_end, now.point, now.point);
        }
    }
    void clear(){
        t.clear();
    }
};

void solve(){
    int n;
    cin >> n;
    vector<Point> v(n);
    rep(i,0,n)
        cin >> v[i];
    vector<Point> vcopy = v;
    KDTree kdt;
    kdt.build(vcopy);
    rep(i,0,n)
        // cout << distance(v[i], kdt.t[0].point)<< "\n";
        cout << distance(v[i], kdt.t[kdt.nearest(v[i])].point)<< "\n";
}

int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
}