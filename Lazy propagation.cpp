#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod = (ll)1e9+7;

struct LazyPropagation
{
    int MAX_VALUE = 2e5+3 , N;
    vector<long long>a;
    struct info
    {
        long long sum, prop;
        info(ll _sum, ll _prop){
            sum = _sum;
            prop = _prop;
        }
    };
    vector<info> tree;

    void initialize(int n)
    {
        N = n;
        //tree.reserve(N*4+10);
        tree.assign(N*4+10,info(0,0) );
        a.assign(N+10,0);
    }
    void build(int pos, int left, int right)
    {
        if (left == right)
        {
            tree[pos].sum = a[left];
            return;
        }
        int mid = (left + right) >> 1;
        build(pos * 2, left, mid);
        build(pos * 2 + 1, mid + 1, right);
        tree[pos].sum = (tree[pos * 2].sum + tree[pos * 2 + 1].sum) % mod;
    }

    void update(int pos, int left, int right, int x, int y, long long val)
    {
        if (left > y || right < x) return;
        if (left >= x && right <= y)
        {
            tree[pos].sum = (tree[pos].sum + (val * ((long long)right - left + 1)) % mod) % mod;
            tree[pos].prop = (tree[pos].prop + val) % mod;
            return;
        }
        int mid = (left + right) >> 1;
        update(pos * 2, left, mid, x, y, val);
        update(pos * 2 + 1, mid + 1, right, x, y, val);
        tree[pos].sum = (tree[pos * 2].sum + tree[pos * 2 + 1].sum + (tree[pos].prop * ((long long)right - left + 1)) % mod) % mod;
    }
    long long query(int pos, int left, int right, int x, int y, long long p = 0LL)
    {
        if (x > y) return 0LL;
        if (left > y || right < x) return 0LL;
        if (left >= x && right <= y) return (tree[pos].sum + (p * ((long long)right - left + 1)) % mod) % mod;
        int mid = (left + right) >> 1;
        long long m = query(pos * 2, left, mid, x, y, (p + tree[pos].prop) % mod);
        long long n = query(pos * 2 + 1, mid + 1, right, x, y, (p + tree[pos].prop) % mod);
        return (m + n) % mod;
    }
};
int main()
{
    LazyPropagation s;
    int n,q;
    cin>>n>>q;
    s.initialize(n);
    for(int i=1;i<=n;i++) cin>>s.a[i];
    s.build(1,1,n);
    while(q--)
    {
        int t,l,r;
        cin>>t>>l>>r;
        if(t==1){
            int v;cin>>v;
            s.update(1,1,n,l,r,checkPrime(v));
        }
        else {
            long long ans = s.query(1,1,n,l,r);
            cout<<ans<<endl;
        }
    }
    return 0;
}
/*
6 4
2 6 4 2 3 7
2 1 6
1 1 5 1
2 4 5
2 1 6
*/
