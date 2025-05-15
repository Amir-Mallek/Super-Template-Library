# KD Tree

```cpp
// The following 3 instructions need to be updated
const int K = 2;
using Unit = double; 
Unit UNIT_MAX = DBL_MAX; 


using Point = array<Unit,K>;
Point origin = {};

struct Node {
    Point point; int dimension, before, after ;
    Node(Point point, int dimension = 0, int before = -1, int after = -1)
    : point(point), dimension(dimension), before(before), after(after) {}
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

istream& operator>>(istream& os, Point& p){rep(i,0,K)cin >> p[i];return cin;}
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
        t.pb(Node(v[mid], d, -1, -1));

        t[res].before = build(v, (d+1)%K,     l, mid);
        t[res].after  = build(v, (d+1)%K, mid+1,   r);
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
            rep(i,0,K) start[i] = -UNIT_MAX, end[i] = UNIT_MAX;
        }
        auto Nd = t[idx];
        // Update best
        if( distance(q, Nd.point) < distance(q, t[best].point))
            best = idx;
        // Getting Ready To Dive
        auto new_end = end;
        new_end[Nd.dimension] = Nd.point[Nd.dimension];
        auto new_start = start;
        new_start[Nd.dimension] = Nd.point[Nd.dimension];
        // Where To Go First
        if( q[Nd.dimension] <= Nd.point[Nd.dimension] ) // before first
        {
            best = nearest(q, Nd.before, best, start, new_end);
            // Should We Go ?
            if( distance2box(q, new_start, end) < distance(q, t[best].point))
                best = nearest(q, Nd.after, best, new_start, end);
        }
        else
        {
            best = nearest(q, Nd.after, best, new_start, end);
            // Should We Go ?
            if( distance2box(q, start, new_end) < distance(q, t[best].point))
                best = nearest(q, Nd.before, best, start, new_end);
        }
        return best;
    }
};
```

## Usage

```cpp
    KDTree kdt;
    kdt.build(v);
    /*...*/
    Point q;
    int idx = kdt.query(q);
```

## Notes

- We can add a  `delete`       function (store a link to parent)
- We can add an `insert`       function (dive then push)
- We can add a  `countInBox` function (store the size + `boxesIntersect` function)