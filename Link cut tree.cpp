#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+3;
random_device rd;
mt19937_64 mt(rd());

struct node
{
    int sz, prior, id, rev;
    node *par, *pp, *l, *r;
    node()
    {
        id = 0;
        sz = 0;
        rev = 0;
        prior = 0;
        par = NULL;
        l = NULL;
        r = NULL;
        pp=NULL;
    }
    node(int v)
    {
        id = v;
        sz = 1;
        rev = 0;
        prior = mt();
        l = NULL;
        r = NULL;
        par=NULL;
        pp=NULL;
    }
};

typedef node* pnode;

inline int size(pnode v)
{
    return v ? v->sz : 0;
}
void push(pnode &t)
{
    if(!t)
        return;
    if(t->rev)
    {
        swap(t->l, t->r);
        if(t->l)
            t->l->rev ^= 1;
        if(t->r)
            t->r->rev ^= 1;
        t->rev = 0;
    }
}

void pull(pnode &v)
{
    if(!v)
        return;

    push(v->l);
    push(v->r);

    v->par = NULL;
    v->sz = size(v->l) + size(v->r) + 1;

    if(v->l)
        v->l->par = v;
    if(v->r)
        v->r->par = v;

    if(v->l && v->l->pp)
        v->pp = v->l->pp, v->l->pp = NULL;
    if(v->r && v->r->pp)
        v->pp = v->r->pp, v->r->pp = NULL;
}

void merge(pnode &t, pnode l, pnode r)
{
    push(l), push(r);
    if(!l)
    {
        t = r;
        return;
    }
    if(!r)
    {
        t = l;
        return;
    }
    if(l->prior > r->prior)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;

    pull(t);
}

void split(pnode t, pnode &l, pnode &r, int k, int add = 0)
{
    push(t);
    if(!t)
    {
        l = NULL;
        r = NULL;
        return;
    }

    int idx = add + size(t->l);
    if(idx <= k)
        split(t->r, t->r, r, k, idx + 1), l = t;
    else
        split(t->l, l, t->l, k, add), r = t;

    pull(t);
}

pnode get_root(pnode t)
{
    if(!t)
        return NULL;
    while(t->par)
        t = t->par;
    return t;
}

pnode remove_right(pnode t)
{
    pnode rt = t;

    int pos = size(rt->l);
    if(rt->rev)
        pos = size(rt) - pos - 1;
    while(rt->par)
    {
        if(rt->par->r == rt)
            pos += size(rt->par->l) + 1;
        if(rt->par->rev)
            pos = size(rt->par) - pos - 1;
        rt = rt->par;
    }

    pnode l, r, pp = rt->pp;
    rt->pp = NULL;
    split(rt, l, r, pos);

    l->pp = pp;
    if(r)
        r->pp = t;

    return l;
}

pnode remove_left(pnode t)
{
    pnode rt = t;

    int pos = size(rt->l);
    if(rt->rev)
        pos = size(rt) - pos - 1;
    while(rt->par)
    {
        if(rt->par->r == rt)
            pos += size(rt->par->l) + 1;
        if(rt->par->rev)
            pos = size(rt->par) - pos - 1;
        rt = rt->par;
    }

    pnode l, r, pp = rt->pp;
    rt->pp = NULL;
    split(rt, l, r, pos - 1);

    l->pp = pp;
    return r;
}

pnode merge_trees(pnode u, pnode t)
{
    u = get_root(u);
    t = get_root(t);
    t->pp = NULL;
    merge(u, u, t);
    return u;
}

struct link_cut_tree
{
    pnode ver[N];

    pnode access(pnode t)
    {
        t = remove_right(t);
        while(t->pp)
        {
            pnode u = t->pp;
            u = remove_right(u);
            t = merge_trees(u, t);
        }

        return t;
    }

    pnode find_root(pnode u)
    {
        u = access(u);
        push(u);
        while(u->l)
            u = u->l, push(u);
        access(u);
        return u;
    }

    void make_root(pnode u)
    {
        u = access(u);
        u->rev ^= 1;
        push(u);
    }

    void link(pnode u, pnode w)
    {
        make_root(u);
        access(w);
        merge_trees(w, u);
    }
    void cut(pnode p)
    {
        access(p);
        remove_left(p);
    }

    int depth(pnode u)
    {
        u = access(u);
        return size(u);
    }

    pnode lca(pnode u, pnode v)
    {
        if(u == v)
            return u;
        if(depth(u) > depth(v))
            swap(u, v);

        access(v);
        access(u);

        return get_root(v)->pp;
    }
    ///creating vertices of the tree
    void init(int c)
    {
        for(int i = 0; i <= c; i++)
            ver[i] = new node(i);
    }
    ///returns lca of two vertices
    inline int lca(int u, int v)
    {
        return lca(ver[u], ver[v])->id;
    }
    ///finds the root of tree which has node u
    inline int root(int u)
    {
        return find_root(ver[u])->id;
    }
    ///add an edge from vertex v to u, making u a child of v,
    ///where initially u and v are in different trees.
    inline void link(int u, int v)
    ///add directed edge v to u
    {
        link(ver[u], ver[v]);
    }
    ///make u the root of its representative tree
    inline void make_root(int u)
    {
        make_root(ver[u]);
    }
    ///depth of vertex u in its own tree
    inline int depth(int u)
    {
        return depth(ver[u]);
    }
    ///remove edge from u to its parent, where u is a non-root vertex.
    inline void cut(int u)
    {
        cut(ver[u]);
    }
};


link_cut_tree lct;

int main()
{
    int i,j,k,n,m,u,v;
    cin>>n>>m;
    lct.init(n);
    while(m--)
    {
        string type;
        cin >> type;

        if(type == "add")///add an edge
        {
            int u, w;
            cin >> u >> w;
            lct.link(u, w);
        }
        else if(type == "conn")///if u and v is connected
        {
            int u, v;
            cin >> u >> v;
            cout << (lct.root(u) == lct.root(v) ? "YES" : "NO") << endl;
        }
        else if(type == "rem") ///remove edge
        {
            int u, v;
            cin >> u >> v;
            if(lct.depth(u) > lct.depth(v))
                swap(u, v);
            lct.cut(v);
        }
    }
    return 0;
}

