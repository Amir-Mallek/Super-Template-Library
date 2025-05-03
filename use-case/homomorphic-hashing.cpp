/**
* Not Rolling Hash ---But--> Segment Tree Hash (using homomorphic hashing)
* Link : https://codeforces.com/contest/271/problem/D
*/

/**
 * 2nd trick ~ homomorphic encryption
 * 
 * I am writing this for you to understand it:
 * 
 * First we decided to store the chars as numbers,
 * and scrolls are range addition updates ... smells lazy.
 * 
 * ************************* Straightforward approach *************************
 * 
 * If we want to use the normal hashing method
 * (and still do classic LazySegTree range addition update),
 * we are forced to use 26 as a modulant ; since adding 26 shouldn't modify the hash.
 * 
 * Using 26 as a modulo is easily counterable :
 * - scroll 13 on a range of size 2, for example "aab" becomes "ano" (a->n & b->o)
 * --> for any power you choose, "ab" and "no" will collide, here's why:
 * hash_after   = a + n*p + o*p*p
 *              = a + (a+13)*p + (b+13)*p*p             [mod 26]
 *              = a + a*p + b*p*p + 13*p + 13*p*p       [mod 26]
 *              = hash_before + 13*p*(p+1)              [mod 26]
 *              = hash_before + 26*k                    [mod 26]
 *              = hash_before                           [mod 26]
 * --> Collision
 * 
 * ************************* Walk around *************************
 * 
 * First thing, we must make our hash space bigger :
 * [0...25] -> [0...(2^26 - 1)] (2 was arbitrary, but convenient for implmtn)
 * so for each character c -> 2^c
 * --> we now have a new set of values for the alphabet and we iterate through them by multiplying by 2
 * 
 * ----> a new constraint : MOD must divide (2^26 - 1)
 * simply ... take MOD = (2^26 - 1) 
 * 
 * ************************* Experimenting (Trying to make a collision) *******
 * Let's shift 'a' by 'x' and 'b' by 'y' :
 * 
 * new_hash_func    ("ab")      = normal_hash(2^a,2^b)
 *                              = 2^a + 2^b * p
 * new_hash_func("(a+x)(b+y)")  = normal_hash(2^(a+x),2^(b+y))
 *                              = 2^(a+x) + 2^(b+y) * p
 * 
 * For collision to happen, we need : MOD | 2^a * (2^x - 1) + 2^b * (2^y - 1) * p
 * So if you find (x,y)!=(0,0) such that MOD divides the formula above than a collision is very possible
 * but that's hard, since we have a total of ~ 26*26 (x,y) pairs, too few to span space, or should i say, too few to make (A*X + B*Y*P) a mult of MOD
 * 
 * ************************* Final touches *************************
 * now scrolling by k (adding k to the alphabet) becomes multiplying by 2^k
 * --> easier implmnt fortunately
 */
#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = a; i < (b); ++i)

//#define int long long // secret weapon
typedef long long ll;

// for SegmentTree
const int MAXN = 5e4+10;
// for Hashing
const int NBH = 1, _NBH = 1;
const ll MOD = (1ll<<26)-1;
const ll P[_NBH] = {118000}; // a number with a high primitive order
ll powp[_NBH][MAXN];
ll pow2[MAXN];
using Hash = array<ll, NBH> ;
const Hash e = Hash();

struct Node {
    int nb;
    Hash hash;
    int mult; //lazy
    Node(int nb = 0, Hash hash = e) : nb(nb), hash(hash), mult(1){}
    Node(char c) : nb(1), mult(1){
        int x = c - 'a' + 1;
        rep(i,0, NBH)
            hash[i] = pow2[x];
    }
};

// Everything is ONE-INDEXED
template <typename T>
struct SegmentTree {

    function<T(T, T)> combine;        // <T(const T&, const T&)>
    // neutral element
    T e;
    vector<T> t; 
    int n;

    SegmentTree(function<T(T, T)> combine, T e, int n = MAXN-1) :
    combine(combine), e(e), n(n), t(n*4 + 1){}

    // a is ONE-INDEXED (can be an array)
    template<typename M>
    void build(vector<M> &a, int v = 1, int tl = 1, int tr = -1) {
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
    void update(int l, int r, int mult, int v = 1, int tl = 1, int tr = -1) {
        if (tr == -1) tr = n;
        if (l > r)
            return ;
        if (tl == l && tr == r) {
            t[v].mult = (1ll * t[v].mult * mult) % MOD;
        } else {
            int tm = (tl + tr) / 2;
            update(l,   min(r, tm), mult, 2*v, tl, tm);
            update(max(l, tm+1), r, mult, 2*v+1, tm+1, tr);
            t[v].hash = combine(t[v*2], t[v*2+1]).hash;
        }
    }
    // l and r are ONE-INDEXED
    T query(int l, int r, int v = 1, int tl = 1, int tr = -1) {
        if (tr == -1) tr = n;
        if (l > r) return e;
        if (tl == l && tr == r) return t[v];
        int tm = (tl + tr) / 2;
        auto tmp = combine(
            query(l,   min(r, tm), 2*v ,  tl  , tm) ,
            query(max(l, tm+1), r, 2*v+1, tm+1, tr)
        );
        tmp.mult = t[v].mult;
        return tmp;
    }
};

int main(){
    //PreProcess : powp and powp
    rep(i,0,NBH){
        powp[i][0] = 1ll;
        rep(j,1,MAXN)
            powp[i][j] = (1ll * powp[i][j-1] * P[i]) % MOD;
    }
    pow2[0]=1ll;
    rep(j,1,MAXN)
        pow2[j] = (1ll * pow2[j-1] * 2ll) % MOD;

    //main
    int n;
    cin >> n;
    string s1,s2;
    cin >> s1 >> s2;

    //preparation for segtree
    vector<Node> v1, v2;
    v1.push_back(Node()),
    v2.push_back(Node());//1-indexed
    rep(i,0,n)
        v1.push_back(Node(s1[i])),
        v2.push_back(Node(s2[i]));
    
    //SegmentTree
    //lambda
    function<Node(Node,Node)> combine = [](Node a, Node b) {
        Hash res = Hash();
        //consider the shift
        rep(i,0,NBH)
            a.hash[i] = (1ll * a.hash[i] * a.mult) % MOD,
            b.hash[i] = (1ll * b.hash[i] * b.mult) % MOD;
        //now merging
        rep(i,0,NBH)
            res[i] = (a.hash[i] + 1ll * powp[i][a.nb] * b.hash[i]) % MOD;
        return Node( a.nb + b.nb, res);
    };
    SegmentTree<Node> 
        st1(combine,Node(),n),
        st2(combine,Node(),n);
    st1.build(v1),
    st2.build(v2);

    //Queries
    int q ;
    cin >> q;
    while(q--){
        int c, id, l, r, x;
        cin >> c;
        if(c == 2){
            cin >> l >> r;
            // dbg
            // auto a = combine(st1.query(l,r),Node());
            // auto b = combine(st2.query(l,r),Node());
            if(
                combine(st1.query(l,r),Node()).hash // in case lazy inside
                ==
                combine(st2.query(l,r),Node()).hash // same
            )   
                cout << "YES\n";
            else
                cout << "NO\n";
        }
        else{
            cin >> id >> l >> r >> x;
            if(id == 1)
                st1.update(l,r, pow2[x%26]);
            else
                st2.update(l,r, pow2[x%26]);
        }
    }
    return 0;
}