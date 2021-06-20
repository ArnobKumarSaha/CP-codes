#include<bits/stdc++.h>
using namespace std;
/*#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
// find_by_order() returns iterator ,, order_of_key()
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>ordered_set;*/

#define aks __FUNCTION__<<' '<<__LINE__<<".. "
#define debug(x) cerr<<#x<<" = "<<x
#define dbg(x) cerr<<aks,debug(x),cerr<<endl
#define dbg2(x,y) cerr<<aks,debug(x),cerr<<" , ",debug(y),cerr<<endl
#define dbg3(x,y,z) cerr<<aks,debug(x),cerr<<" , ",debug(y),cerr<<" , ",debug(z),cerr<<endl
#define fast ios_base::sync_with_stdio(false)
#define ll long long
#define vll vector<ll>
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vi vector<int>
const int mod = 1e9+7;
const int N = 1e6+7;
const int mxn=3e5+9;
//ll bigmod(ll a, ll b, ll m){if(b==0) return 1%m;ll x = bigmod(a,b/2,m);x = (x*x)%m;if(b%2) x = (x*a)%m;return x;}
inline ll in(){ll _;scanf("%lld",&_);return _;}
int n,m,k, ans=0;
int a[mxn];
/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

struct pair_hash
{
	template <class T1, class T2>
	std::size_t operator () (std::pair<T1, T2> const &pair) const
	{
		std::size_t h1 = std::hash<T1>()(pair.first);
		std::size_t h2 = std::hash<T2>()(pair.second);

		return h1 ^ h2;
	}
};
#define psi pair<string,int>
unordered_set<psi,pair_hash>mp;
unordered_map<pii, int, pair_hash>mm;

int main()      /// Hey ... check the CONSTRAINTS .
{
    mp.insert({"two", 2});
    mp.insert({"one", 1});
    mp.insert({"four", 4});
    mp.insert({"three", 3});
    for(auto z: mp){
        cout<<z.first<<' '<<z.second<<endl;
    }

    mm[{4, 2}]++;
    mm[{16, 4}] = 3;
    for(auto z: mm){
        cout<<z.first.first<<' '<<z.first.second<<' '<<z.second<<endl;
    }
    return 0;
}


