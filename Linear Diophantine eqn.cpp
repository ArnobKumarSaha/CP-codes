#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll gcd(ll a, ll b, ll &x, ll &y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    ll x1, y1;
    ll d = gcd(b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

bool find_any_solution(ll a, ll b, ll c, ll &x0, ll &y0, ll &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}
int main()
{
	ll a=4, b=-3, c = -1, x0,y0,g;
	if(find_any_solution(a,b,c,x0,y0,g)){
		printf("x0=%lld, y0=%lld, g=%lld\n",x0,y0,g);
	}
	return 0;
}
