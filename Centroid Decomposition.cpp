#include<bits/stdc++.h>
using namespace std;
#define fast ios_base::sync_with_stdio(false)

struct Centroid
{
    int subtree_sz , n;
    vector<int> cenpar,sz,dep,ans;
    vector< vector<int> >par, g;
    vector<bool> done;

    Centroid(int _n)
    {
        n=_n;
        cenpar.assign(n+1,0);
        sz.assign(n+1,0);
        dep.assign(n+1,0);
        ans.assign(n+1,0);
        subtree_sz=0;
        par.assign(n+1,vector<int>(20));
        g.assign(n+1,vector<int>(0));
        done.assign(n+1,false);
    }
    ///preprocessing part, This DFS finds the level and imidiate parent of each node.
    void dfs(int u,int pre)
    {
        dep[u]=dep[pre]+1;
        par[u][0]=pre;
        for(auto v:g[u])
        {
            if(v==pre)
                continue;
            dfs(v,u);
        }
    }
    int lca(int u,int v)
    {
        if(dep[u]<dep[v])
            swap(u,v);
        for(int k=19; k>=0; k--)
            if(dep[par[u][k]]>=dep[v])
                u=par[u][k];
        if(u==v)
            return u;
        for(int k=19; k>=0; k--)
            if(par[u][k]!=par[v][k])
                u=par[u][k],v=par[v][k];
        return par[u][0];
    }
    int dist(int u,int v)
    {
        return dep[u]+dep[v]-2*dep[lca(u,v)];
    }
    void parentSetUp()
    {
        for(int k=1;k<20;k++){
            for(int i=1;i<=n;i++){
                par[i][k] = par[ par[i][k-1] ][k-1];
            }
        }
    }
    ///Decomposition part
    void set_subtree_size(int u,int pre)
    {
        subtree_sz++;
        sz[u]=1;
        for(auto v:g[u])
        {
            if(v==pre||done[v])
                continue;
            set_subtree_size(v,u);
            sz[u]+=sz[v];
        }
    }
    int get_centroid(int u,int pre)
    {
        for(auto v:g[u])
        {
            if(v==pre||done[v])
                continue;
            else if(sz[v]>subtree_sz/2)
                return get_centroid(v,u);
        }
        return u;
    }
    void decompose(int u,int pre) /// The main  function ... in action
    {
        subtree_sz=0;
        set_subtree_size(u,pre);
        int centroid=get_centroid(u,pre);
        cenpar[centroid]=pre;
        done[centroid]=1;
        for(auto v:g[centroid])
        {
            if(v==pre||done[v])
                continue;
            decompose(v,centroid);
        }
    }
    ///query part
    void upd(int x)
    {
        int u=x;
        while(x)
        {
            ans[x]=min(ans[x],dist(u,x));
            x=cenpar[x];
        }
    }
    int query(int x)
    {
        int ret=1e9,u=x;
        while(x)
        {
            ret=min(ret,ans[x]+dist(u,x));
            x=cenpar[x];
        }
        return ret;
    }
    /// To use this structure, first make the adjecency list.
    /// Then Call dfs(1,0), parentSetUp() and decompose(1,0) function one by one.
};
int main()
{
    fast;
    int n,k;
    cin>>n>>k;
    Centroid c(n);
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        c.g[x].push_back(y);
        c.g[y].push_back(x);
    }
    c.dfs(1,0);
    c.parentSetUp();
    c.decompose(1,0);
    for(int i=0;i<=n;i++) c.ans[i]=(1<<29);
    c.upd(1);
    while(k--)
    {
        int ty,x;
        cin>>ty>>x;
        if(ty==1){
            c.upd(x);
        }
        else{
            cout<<c.query(x)<<endl;
        }
    }
    return 0;
}
