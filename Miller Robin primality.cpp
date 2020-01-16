#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mod = 1e9+7;

ll bigmod(ll a, ll b, ll mod)
{
    if(b==0) return 1%mod;
    ll x = bigmod(a,b/2,mod);
    x = (x*x)%mod;
    if(b%2==1) x = (x*a)%mod;
    return x;
}
bool calculate(ll n, ll d){
	ll a = 2 + rand()%(n-4);
	ll x = bigmod(a,d,n);
	if(x==1 or x==n-1) return true;
	while(d != n-1){
		x = (x*x)%n;
		d = (d*2);
		if(x==1) return false;
		if(x==n-1) return true;
	}
	return false;
}
bool testPrimality(ll n, int iteration)
{
	if(n<=1 or n==4) return false;
	if(n<=3) return true;
	ll d = n-1,r=0;
	while(d%2==0) d/=2,r++;
	for(int i=0;i<iteration;i++){
		if(!calculate(n,d)) return false;
	}
	return true;
}
int main()
{
	ll cnt=0;
    for(ll i=1;i<=100;i++){
		if(testPrimality(i,2)) cout<<i<<' ',cnt++;
    }
    cout<<cnt<<endl;
    return 0;
}
