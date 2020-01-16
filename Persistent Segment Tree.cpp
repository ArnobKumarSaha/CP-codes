#include<bits/stdc++.h>
using namespace std;
const int N =1e5+2;

struct node
{
    int l,r,val;
    node()
    {
        l=r=val=0;
    }     node(int _l,int _r,int _val)
    {
        l=_l,r=_r,val=_val;
    }
} t[20*N]; ///size will be nlogn
int root[N],a[N],cnt;
void build(int cur,int b,int e)
{
    if(b==e)
    {
        t[cur]=node(0,0,0);
        return ;
    }
    int left,right,mid=(b+e)/2;
    t[cur].l=left=++cnt;
    t[cur].r=right=++cnt;
    build(left,b,mid);
    build(right,mid+1,e);
    t[cur].val=t[left].val+t[right].val;
}
void upd(int pre,int cur,int b,int e,int i,int v)
{
    if(i<b||i>e)
        return;
    if(b==e)
    {
        t[cur].val+=v;
        return;
    }
    int left,right,mid=(b+e)/2;
    if(i<=mid)
    {
        t[cur].r=right=t[pre].r;
        t[cur].l=left=++cnt;
        upd(t[pre].l,t[cur].l,b,mid,i,v);
    }
    else
    {
        t[cur].l=left=t[pre].l;
        t[cur].r=right=++cnt;
        upd(t[pre].r,t[cur].r,mid+1,e,i,v);
    }
    t[cur].val=t[left].val+t[right].val;
}
int query(int pre,int cur,int b,int e,int k)
{
    if(b==e)
        return b;
    int cnt=t[t[cur].l].val-t[t[pre].l].val;
    int mid=(b+e)/2;
    if(cnt>=k)
        return query(t[pre].l,t[cur].l,b,mid,k);
    else
        return query(t[pre].r,t[cur].r,mid+1,e,k-cnt);
}
///1 2 2 3 , 3rd number is 3
///the code returns k-th unique number in a range l to r if the range were sorted
int flag[N];
int main()
{
    int i,j,k,n,m,q,t,x,l,r,c=0;
    map<int,int>mp;
    cin>>n>>q;
    for(i=1; i<=n; i++)
        cin>>a[i],mp[a[i]];
    for(auto x:mp)
        mp[x.first]=++c,flag[c]=x.first;
    root[0]=++cnt;
    build(root[0],1,n);
    for(i=1; i<=n; i++)
    {
        root[i]=++cnt;
        upd(root[i-1],root[i],1,n,mp[a[i]],1);
    }
    while(q--)
    {
        cin>>l>>r>>k;
        cout<<flag[query(root[l-1],root[r],1,n,k)]<<endl;
    }
}
