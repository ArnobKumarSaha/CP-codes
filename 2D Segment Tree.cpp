#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e2+2;
typedef vector<int> vi;
#define pb push_back

int n,m;
struct segtree
{
    int a[N*4];
    #define stree mid=(b+e)/2
    #define l node*2
    #define r l+1
    segtree()
    {
        for(int i=0; i<N*4; i++)
            a[i]=0;
    }
    void pri()
    {
        for(int i=1;i<=7;i++) cout<<a[i]<<' ';
        cout<<endl;
    }
    void reset()
    {
        for(int i=0; i<N*4; i++)
            a[i]=0;
    }     // update i-th column by val
    void upd(int node,int b,int e,int i,int val,vi &v)
    {
        v.pb(node);
        if(b==e)
        {
            a[node]=val;
            return;
        }
        int stree;
        if(i<=mid)
            upd(l,b,mid,i,val,v);
        else
            upd(r,mid+1,e,i,val,v);
        a[node]=a[l]+a[r];
    }     //sum from column i to j
    int query(int node,int b,int e,int i,int j)
    {
        if(j<b||i>e)
            return 0;
        if(b>=i&&e<=j)
            return a[node];
        int stree;
        return query(l,b,mid,i,j)+query(r,mid+1,e,i,j);
    }
};
/// if n=m=4, upd(1,3) will change rows (1,2,4) , colomns (1,3,6) ;;;
///make segment tree with n leafs, then go from root to r
struct segtree2d
{
    segtree a[N*4];
    void reset()
    {
        for(int i=0; i<N*4; i++)
            a[i].reset();
    }
    vi v;
    //set a[i][j]=val
    void upd(int node,int b,int e,int i,int j,int val)
    {
        if(b==e)
        {
            v.clear();
            a[node].upd(1,1,m,j,val,v);
            return;
        }
        int stree;
        if(i>=b&&i<=mid)
            upd(l,b,mid,i,j,val);
        else
            upd(r,mid+1,e,i,j,val);
        for(auto x:v){
            a[node].a[x]=a[l].a[x]+a[r].a[x];
        }
    }
//return sum from top-left (i,y1) to bottom-right (j,y2)
    int query(int node,int b,int e,int i,int y1,int j,int y2)
    {
        if(j<b||i>e)
            return 0;
        if(b>=i&&e<=j)
            return a[node].query(1,1,m,y1,y2);
        int stree;
        return query(l,b,mid,i,y1,j,y2)+query(r,mid+1,e,i,y1,j,y2);
    }
};
