# Treap

Precisely, this is an Implicit Treap.



```cpp
#include<bits/stdc++.h>
using namespace std;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct node
{
    /* Essentials */
    node *l, *r;
    int key;    // x-coordinate (can be ignored if cautious split&merge)
    int prior;  // y-coordinate
    int nb;     // general purpose
    /* Plugins here ... */
    
    /* Constructor */
    node(/*change this*/)
    {
        l = r = nullptr;
        // key = id ;
        prior = rnd();
        nb = 1;
        /* Initialize plugins here ... */
    }
};

struct Treap // 1-indexed
{
    //\\//\\//\\//\\//\\//
    // ESSENTIAL TOOLZZ //
    //\\//\\//\\//\\//\\//

    node *root;
    /* Constructors */
    Treap()
    {
        root = nullptr;
    }
    Treap(node* nd)
    : root(nd) {}
    
    /* Subtree size */
    static int size(node *t)
    {
        if (!t)
            return 0;
        else
            return t->nb;
    }

    /* Keep coherent after splits and merges */
    static void pull(node *t)
    {
        if (!t)
            return;
        t->nb = 1 + size(t->l) + size(t->r);
        /* no push, please, no push */
        // Write here ...

    }
    
    /* Propagate lazy updates */
    static void push(node *t)
    {
        // return ; /* if no lazy */
        if (!t)
            return;
        /* if( lazy_XYZ ) { update_XYZ(t->l); update_XYZ(t->r); }*/
        /* update_functions need to be non recursive nor referencing push */
        /* ... */
        /* no pull, please, no pull */
    }

    /* Split first #nb elements */
    static void split(node *t, int nb, node *&l, node *&r)
    {
        if (t == nullptr)
        {
            l = r = nullptr;
            return;
        }
        push(t);
        if (size(t->l) + 1 <= nb)
        {
            split(t->r, nb - (size(t->l) + 1), l, r);
            t->r = l;
            l = t;
            pull(l);
        }
        else
        {
            split(t->l, nb, l, r);
            t->l = r;
            r = t;
            pull(r);
        }
    }
    
    /* Concatenation Merge [by position] */
    static node* merge(node *l, node *r)
    {
        if (!l || !r)
            return l ? l : r;
        if (l->prior < r->prior)
        {
            push(l);
            l->r = merge(l->r, r);
            pull(l);
            return l;
        }
        else
        {
            push(r);
            r->l = merge(l, r->l);
            pull(r);
            return r;
        }
    }
    
    /* BST Merge [by key] */
    static node* merge_treap(node *a, node *b)
    {
        if (!a)
            return b;
        if (!b)
            return a;
        if (a->prior > b->prior)
            swap(a, b);
        node *L, *R;
        push(a);
        split(b, a->key, L, R);
        a->r = merge_treap(a->r, R);
        a->l = merge_treap(L, a->l);
        pull(a);
        return a;
    }
    
    /* Delete subtree */
    static void destroy(node *t)
    {
        if (!t)
            return;
        destroy(t->l);
        destroy(t->r);
        delete t;
    }
    
    /* Remove range [L,R] */
    void erase(int L, int R)
    {
        node *r, *mid;
        split(root, R, root, r);
        split(root, L - 1, root, mid);
        root = merge(root, r);
        // destroy(mid);
    }
    
    /* Delete Treap */
    void destroy()
    {
        return destroy(root);
    }
    
    /* Append to the end [concatenate]*/
    void push_back(/*change this*/)
    {
        root = merge(root, new node(/*change this*/));
    }
    
    /* Insert at position P */
    void insert(int P/*, change this*/)
    {
        node* rest;
        split(root, P-1, root, rest);
        push_back(/*change this*/);
        root = merge(root, rest);
    }

    /* Split root into 3 ranges +| 1-indexed */
    tuple<node*,node*,node*> range_split(int l, int r)
    {
        node *L, *M, *R;
        split(root,   r, root, R);
        split(root, l-1,    L, M);
        return {L,M,R};
    }
    /* Merge back ranges after range_split */
    void range_merge(node * L, node * M , node * R)
    {
        root =  merge(L,merge(M,R));
    }
    
    //\\//\\//\\//\\//\\//
    // DEBUGGING TOOLZZ //
    //\\//\\//\\//\\//\\//
    
    static void dbgfs(node *t)
    {
        if (!t)
            return;
        push(t);
        dbgfs(t->l);
        cout << 0/*change this*/ << ' ';
        dbgfs(t->r);
    }
    
    void dbgfs()
    {
        dbgfs(root);
        cout << ("$\n");
    }

    //\\//\\//\\//\\//\\//
    // PROBLEM SPECIFIC //
    //\\//\\//\\//\\//\\//

    
};
```

## Notes
- EZ2UZ, just update the `/* change this */` comments, `node` struct, `push` & `pull` function, problem specific functions.