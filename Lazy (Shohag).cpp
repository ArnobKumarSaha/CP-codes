
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vi vector<int>
#define vll vector<ll>
#define vc vector<char>
#define vs vector<string>
#define vpll vector<pll>
#define vpii vector<pii>
#define umap unordered_map
#define uset unordered_set
#define PQ priority_queue

#define printa(a,L,R) for(int i=L;i<R;i++) cout<<a[i]<<(i==R-1?'\n':' ')
#define printv(a) printa(a,0,a.size())
#define print2d(a,r,c) for(int i=0;i<r;i++) for(int j=0;j<c;j++) cout<<a[i][j]<<(j==c-1?'\n':' ')
#define pb push_back
#define eb emplace_back
#define mt make_tuple
#define fbo find_by_order
#define ook order_of_key
#define MP make_pair
#define UB upper_bound
#define LB lower_bound
#define SQ(x) ((x)*(x))
#define issq(x) (((ll)(sqrt((x))))*((ll)(sqrt((x))))==(x))
#define F first
#define S second
#define mem(a,x) memset(a,x,sizeof(a))
#define E 2.71828182845904523536
#define gamma 0.5772156649
#define nl "\n"
#define lg(r,n) (int)(log2(n)/log2(r))
#define sz(v) (int)v.size()
#define pf printf
#define sf scanf
#define sf1(a)                scanf("%d",&a)
#define sf2(a,b)              scanf("%d %d",&a,&b)
#define sf3(a,b,c)            scanf("%d %d %d",&a,&b,&c)
#define pf1(a)                printf("%d\n",a);
#define pf2(a,b)              printf("%d %d\n",a,b)
#define pf3(a,b,c)            printf("%d %d %d\n",a,b,c)
#define sf1ll(a)              scanf("%lld",&a)
#define sf2ll(a,b)            scanf("%I64d %I64d",&a,&b)
#define sf3ll(a,b,c)          scanf("%I64d %I64d %I64d",&a,&b,&c)
#define pf1ll(a)              printf("%lld\n",a);
#define pf2ll(a,b)            printf("%I64d %I64d\n",a,b)
#define pf3ll(a,b,c)          printf("%I64d %I64d %I64d\n",a,b,c)
#define _ccase printf("Case %lld: ",++cs)
#define _case cout<<"Case "<<++cs<<": "
#define by(x) [](const auto& a, const auto& b) { return a.x < b.x; }

#define asche cerr<<"Ekhane asche\n";
#define rev(v) reverse(v.begin(),v.end())
#define srt(v) sort(v.begin(),v.end())
#define grtsrt(v) sort(v.begin(),v.end(),greater<ll>())
#define all(v) v.begin(),v.end()
#define mnv(v) *min_element(v.begin(),v.end())
#define mxv(v) *max_element(v.begin(),v.end())
#define toint(a) atoi(a.c_str())
#define BeatMeScanf ios_base::sync_with_stdio(false)
#define valid(tx,ty) (tx>=0&&tx<n&&ty>=0&&ty<m)
#define one(x) __builtin_popcount(x)
#define Unique(v) v.erase(unique(all(v)),v.end())
#define stree l=(n<<1),r=l+1,mid=b+(e-b)/2
#define fout(x) fixed<<setprecision(x)
string tostr(int n) {stringstream rr;rr<<n;return rr.str();}
inline void yes(){cout<<"YES\n";exit(0);}
inline void no(){cout<<"NO\n";exit(0);}
template <typename T> using o_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
ll dx[]={1,0,-1,0,1,-1,-1,1};
ll dy[]={0,1,0,-1,1,1,-1,-1};
//random_device rd;
//mt19937 rnd(rd());
#define debug(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); deb(_it, args); }
void deb(istream_iterator<string> it) {}
template<typename T, typename... Args>
void deb(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << endl;
    deb(++it, args...);
}

const int mod=1e9+7;
const int N=3e5+9;
const ld eps=1e-9;
const ld PI=acos(-1.0);
ll gcd(ll a,ll b){while(b){ll x=a%b;a=b;b=x;}return a;}
ll lcm(ll a,ll b){return a/gcd(a,b)*b;}
ll qpow(ll n,ll k) {ll ans=1;assert(k>=0);n%=mod;while(k>0){if(k&1) ans=(ans*n)%mod;n=(n*n)%mod;k>>=1;}return ans%mod;}

///1-indexed
template<typename T>
struct segtree {
    #define lc (n<<1)
    #define rc ((n<<1)|1)
    vector<T>t,lazy,a;
    int x;
    segtree() {}
    segtree(int n)
    {
        x=n;
        t.assign(4*n,0);                    ///initialization
        lazy.assign(4*n,0);
        a.assign(n+1,0);
    }
    void push(int n, int b, int e) {
        if (lazy[n]==0) return;
        t[n]=t[n]+lazy[n]*(e-b+1);              ///process the operation here
        if (b!=e){
            lazy[lc]=lazy[lc]+lazy[n];          ///carry the lazy to the lower nodes
            lazy[rc]=lazy[rc]+lazy[n];
        }
        lazy[n] = 0;
    }
    void pull(int n) {
        t[n] = t[lc]+t[rc];                     ///merge lower nodes of the tree to get the parent node
    }
    T merge_(T a,T b)
    {
        return a+b;                             ///merge left and right queries
    }
    void build(int n,int b,int e)
    {
        if(b>e) return;
        if(b==e){
            t[n]=a[b-1];
            return;
        }
        int mid=(b+e)>>1;
        build(lc,b,mid);
        build(rc,mid+1,e);
        pull(n);
    }
    void upd(int n,int b,int e,int i,int j,T v)
    {
        push(n,b,e);
        if (j<b||e<i) return;
        if (i<=b&&e<=j) {
            lazy[n]=v;
            push(n,b,e);
            return;
        }
        int mid=(b+e)>>1;
        upd(lc,b,mid,i,j,v);
        upd(rc,mid+1,e,i,j,v);
        pull(n);
    }
    T query(int n,int b,int e,int i,int j)
    {
        push(n,b,e);
        if(i>e||b>j) return 0;                  ///return null type
        if(i<=b&&e<=j) return t[n];
        int mid=(b+e)>>1;
        return merge_(query(lc,b,mid,i,j),query(rc,mid+1,e,i,j));
    }
    void build(vector<T>& v)                    ///normally vector a is 0 based but tree is formed 1-based
    {
        a=v;
        build(1,1,x);
    }
    void upd(int i,int j,T v)
    {
        upd(1,1,x,i,j,v);
    }
    T query(int i,int j)
    {
        return query(1,1,x,i,j);
    }
};

int32_t main()
{
    BeatMeScanf;
    int i,j,k,n,m,q,l,r,v;
    cin>>m;
    while(m--){
        cin>>n>>q;
        segtree<ll>t(n);
        while(q--){
            int ty;
            cin>>ty>>l>>r;
            if(ty==0){
                cin>>v;
                t.upd(l,r,v);
            }
            else cout<<t.query(l,r)<<nl;
        }
    }
    return 0;
}
///Before submit=>
///    *check for integer overflow,array bounds
///    *check for n=1

