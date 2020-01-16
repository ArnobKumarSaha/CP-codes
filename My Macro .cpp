#include<bits/stdc++.h>
//#include<ext/pb_ds/assoc_container.hpp>
//#include<ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
using namespace std;

/** ----------STL shortcuts--------------*/

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
#define PQ priority_queue
#define pb push_back
#define MP make_pair
#define UB upper_bound
#define LB lower_bound
#define F first
#define S second
#define rev(v) reverse(v.begin(),v.end())
#define srt(v) sort(v.begin(),v.end())
#define grtsrt(v) sort(v.begin(),v.end(),greater<ll>())
#define all(v) v.begin(),v.end()
#define mnv(v) *min_element(v.begin(),v.end())
#define mxv(v) *max_element(v.begin(),v.end())

/** ---------------------Debugging---------------------*/

#define debug(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); deb(_it, args); }
void deb(istream_iterator<string> it)
{
    cout<<endl;
}
template<typename T, typename... Args>
void deb(istream_iterator<string> it, T a, Args... args)
{
    cerr << *it << " = " << a << ",   ";
    deb(++it, args...);
}
#define asche cerr<<"Ekhane asche\n";
#define what_is(x) cerr << #x << " is " << x << endl
#define printa(a,L,R) for(int i=L;i<R;i++) cout<<a[i]<<(i==R-1?'\n':' ')
#define printv(a) printa(a,0,a.size())
#define print2d(a,r,c) for(int i=0;i<r;i++) for(int j=0;j<c;j++) cout<<a[i][j]<<(j==c-1?'\n':' ')
#define printTime cerr << "Time (in ms): " << double(clock() - clk) * 1000.0 / CLOCKS_PER_SEC << '\n';



/** -------------------Other utilities---------------------*/

#define tests(t) int t; cin >> t; while(t--)
#define SQ(x) ((x)*(x))
#define issq(x) (((ll)(sqrt((x))))*((ll)(sqrt((x))))==(x))
#define mem(a,x) memset(a,x,sizeof(a))
#define inf 1e18
#define PI (acos(-1.0))
#define nl "\n"
#define lg(r,n) (int)(log2(n)/log2(r))
#define fast ios_base::sync_with_stdio(false)
#define one(x) __builtin_popcount(x)
#define Unique(v) v.erase(unique(all(v)),v.end())
#define stree ll l=(n<<1),r=l+1,mid=b+(e-b)/2
#define fout(x) fixed<<setprecision(x)
//string tostr(int n){stringstream rr;rr<<n;return rr.str();}
#define toint(a) atoi(a.c_str())
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end));i != (end) - ((begin) > (end));i += 1 - 2 * ((begin) > (end)))

#define For(i,n) for(int i=1;i<=n;i++)
#define For0(i,n) for(int i=0;i<n;i++)

//ll dx[]={1,0,-1,0,1,-1,-1,1};
//ll dy[]={0,1,0,-1,1,1,-1,-1};
#define valid(tx,ty) (tx>=0&&tx<n&&ty>=0&&ty<m)

/*typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update> ordered_set;
methods: find_by_order(k) for finding kth (0 based) Largest element. (returns an Iterator)  &
    order_of_key(k), number of items that are strictly smaller than k. */

/** -------------------Useful Functions---------------------*/

/*int sc()
{
    register int c = getchar();
    register int x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c = getchar());
    if(c=='-') {neg=1;c=getchar();}
    for(;c>47 && c<58;c = getchar()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
    return x;
}*/

/*#define iceil(n, x) (((n) + (x) - 1) / (x))
return the minimum number >=n , which is divisible by x */

/*Returns no. of values x for which ceil(n / x) == y (y must be > 1).
inline ll CC(ll n, ll y) { return iceil(n, y-1) - iceil(n, y); }*/

/*Returns no. of values x for which floor(n / x) == y
inline ll FF(ll n, ll y) { return n / y - n / (y+1); }*/

/*int next_popcount(int n){int c = (n & -n);int r = n+c;int p = r^n;int x = (p>>2)/c;return x  r;}
 Let, n e k ti onBit ache, this func return a serial combination of k onBit. */

/*struct BIT{
    vector<ll> Tree;ll Size=0;void init(int n){Tree.assign(n+1,0);Size=n;}
    void update(int indx,ll val){while(indx<=Size){Tree[indx] += val;indx += (indx)&(-indx);}}
    ll query(int indx){ll sum=0;while(indx>0)
        {sum += Tree[indx];sum %= mod;indx -= (indx)&(-indx);}return sum;}
    ll query(int l, int r){return (query(r) - query(l-1)+mod)%mod;}
};*/
//ll gcd(ll a,ll b){while(b){ll x=a%b;a=b;b=x;}return a;}
//ll lcm(ll a,ll b){return a/gcd(a,b)*b;}

const int mod=1e9+7;
const int mxn=3e5+9;
const ld eps=1e-9;
const int N = 5e3+3;

/*ll bigmod(ll a, ll b){if(b==0) return 1%mod;ll x = bigmod(a,b/2);
    x = (x*x)%mod;if(b%2==1) x = (x*a)%mod;return x;}*/
/*ll egcd(ll a, ll b, ll &x, ll &y){if(a==0){x=0;y=1;return b;}
    ll x1,y1;ll d =egcd(b%a, a,x1,y1);x = y1-(b/a)*x1;y=x1;return d;}*/

/**-------------------------------------------------------------------------------------------------------*/

ll n,k,m, ans=0;
ll a[mxn];
//ll dp[N][N];
//map<ll,ll>mp;
//set<ll>st;


int main()
{
    fast;
    //clock_t clk = clock();

    //printTime;
    return 0;
}
