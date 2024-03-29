#include<bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define pb push_back
#define mem(a,x) memset(a,x,sizeof a)

const int N =2e5+3;
const int LG=16;
int a[N],total_chain,T,node[N],pos[N];
int par[N][LG+1],son[N],chain_head[N],sz[N],dep[N],chain_no[N];
vi g[N];

struct segtree
{
    int t[4*N];
    #define l (n*2)
    #define r (n*2+1)
    void build(int n,int b,int e)
    {
        if(b==e)
        {
            t[n]=a[node[b]];
            return;
        }
        int stree;
        int mid = (b+e)>>1;
        build(l,b,mid);
        build(r,mid+1,e);
        t[n]=t[l]+t[r];
    }
    void upd(int n,int b,int e,int i,int x)
    {
        if(b>i||e<i)
            return;
        if(b==e&&b==i)
        {
            t[n]=x;
            return;
        }
        int stree;
        int mid = (b+e)>>1;
        upd(l,b,mid,i,x);
        upd(r,mid+1,e,i,x);
        t[n]=t[l]+t[r];
    }
    int query(int n,int b,int e,int i,int j)
    {
        if(b>j||e<i)
            return 0;
        if(b>=i&&e<=j)
            return t[n];
        int stree;
        int mid = (b+e)>>1;
        int a=query(l,b,mid,i,j);
        int p=query(r,mid+1,e,i,j);
        return a+p;
    }
} t;

void dfs(int u,int pre)
{
    dep[u]=dep[pre]+1;
    int mx=-1;
    sz[u]=1;
    par[u][0]=pre;
    for(int i=1; i<=LG; i++)
        par[u][i]=par[par[u][i-1]][i-1];
    for(auto v:g[u])
    {
        if(v==pre)
            continue;
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>mx)
            mx=sz[v],son[u]=v;
    }
}
int lca(int u,int v)
{
    if(dep[u]<dep[v])
        swap(u,v);
    for(int k=LG; k>=0; k--)
        if(dep[par[u][k]]>=dep[v])
            u=par[u][k];
    if(u==v)
        return u;
    for(int k=LG; k>=0; k--)
        if(par[u][k]!=par[v][k])
            u=par[u][k],v=par[v][k];
    return par[u][0];
}
int kth(int u,int k)
{
    assert(k>=0);
    for(int i=0; i<=LG; i++)
        if(k&(1<<i))
            u=par[u][i];
    return u;
}
int dist(int u,int v)
{
    int lc=lca(u,v);
    ///v is an ancestor of u
    return dep[u]+dep[v]-2*dep[lc];
}
///kth node from u to v,0th node is u
int go(int u,int v,int k)
{
    int lc=lca(u,v);
    int d=dep[u]+dep[v]-2*dep[lc];
    assert(k<=d);
    if(dep[lc]+k<=dep[u])
        return kth(u,k);
    k-=dep[u]-dep[lc];
    return kth(v,dep[v]-dep[lc]-k);
}
void hld(int u,int pre)
{
    if(chain_head[total_chain]==-1)
        chain_head[total_chain]=u;
    pos[u]=++T;
    node[T]=u;
    chain_no[u]=total_chain;
    if(son[u]==-1)
        return;
    hld(son[u],u);
    for(auto v:g[u])
    {
        if(v==pre||v==son[u])
            continue;
        total_chain++;
        hld(v,u);
    }
}
int query_up(int u,int v)
{
    int ans=0;
    int chain1=chain_no[u];
    int chain2=chain_no[v];
    int chd_u=chain_head[chain1];
    int chd_v=chain_head[chain2];
    while(chd_u!=chd_v)
    {
        ans+=t.query(1,1,T,pos[chd_u],pos[u]);
        ///queries should be from low depth node to high depth node
        u=par[chd_u][0];
        chain1=chain_no[u];
        chd_u=chain_head[chain1];
    }
    ans+=t.query(1,1,T,pos[v],pos[u]);
    return ans;
}
int query(int u,int v)
{
    int lc=lca(u,v);
    int ans=query_up(u,lc);
    if(v!=lc)
        ans+=query_up(v,kth(v,dep[v]-dep[lc]-1));
    return ans;
}
int main()
{
    int i,j,k,n,m,u,v,q,tt,w;
    cin>>n;
    for(i=1; i<=n; i++)
        cin>>a[i];
    for(i=1; i<n; i++)
        cin>>u>>v,g[u].pb(v),g[v].pb(u);
    mem(son,-1);
    mem(chain_head,-1);
    dfs(1,0);
    hld(1,0);
    t.build(1,1,T);
    cin>>q;
    while(q--)
    {
        cin>>tt;
        if(tt==1)
        {
            cin>>u>>w;
            a[u]=w;
            t.upd(1,1,T,pos[u],w);
        }
        else
        {
            cin>>u>>v;
            cout<<query(u,v)<<endl;
        }
    }
    return 0;
}
