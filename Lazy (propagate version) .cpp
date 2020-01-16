#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod = (ll)1e9+7;

struct LazyPropagation /// This is the set Value version of Lazy Propagation.
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
        tree[pos].sum = (tree[pos * 2].sum + tree[pos * 2 + 1].sum);
    }

    void propagate( int node, int a, int b ) {
        if ( tree[node].prop ) {
            if (true /** if something Condition is true */) {
                tree[ node ].sum = b - a + 1;
            }
            else {
                tree[ node ].sum = 0;
            }
            if ( a != b ) {
                tree[ node * 2 ].prop = tree[node].prop;
                tree[ node * 2 + 1 ].prop = tree[node].prop;
            }
            tree[node].prop = 0;
        }
    }

    void update(int pos, int left, int right, int x, int y, long long val)
    {
        if (left > y || right < x) {propagate(pos, left, right);return;}
        if (left >= x && right <= y)
        {
            tree[pos].prop = val;
            propagate(pos, left, right);
            return;
        }
        propagate(pos, left, right);
        int mid = (left + right) >> 1;
        update(pos * 2, left, mid, x, y, val);
        update(pos * 2 + 1, mid + 1, right, x, y, val);
        if(left != right)
        tree[pos].sum = tree[pos * 2].sum + tree[pos * 2 + 1].sum ;
    }
    long long query(int pos, int left, int right, int x, int y)
    {
        if (x > y) return 0LL;
        if (left > y || right < x) return 0LL;
        propagate(pos, left, right);
        if (left >= x && right <= y) return tree[pos].sum;
        int mid = (left + right) >> 1;
        long long m = query(pos * 2, left, mid, x, y);
        long long n = query(pos * 2 + 1, mid + 1, right, x, y);
        return (m + n) ;
    }
};
int main()
{
    int te;
    scanf("%d",&te);
    for(int cs=1;cs<=te;cs++){
        LazyPropagation s;
        int n,q;
        scanf("%d%d",&n,&q);
        s.initialize(n);
        for(int i=1;i<=n;i++){
            ll x;
            scanf("%lld",&x);
            s.a[i] = x;
        }
        s.build(1,1,n);
        printf("Case %d:\n",cs);
        while(q--)
        {
            int t,l,r;
            scanf("%d%d%d",&t,&l,&r);
            if(t==0){
                int v;scanf("%d",&v);
                s.update(1,1,n,l,r,v);
            }
            else {
                long long ans = s.query(1,1,n,l,r);
                printf("%lld\n",ans);
            }
        }
    }
    return 0;
}

