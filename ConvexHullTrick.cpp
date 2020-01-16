#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fast ios_base::sync_with_stdio(false)

deque<long long> m,b;
bool bad(int f1, int f2, int f3)
{
//    return __int128(b[f3] - b[f1]) * (m[f1] - m[f2]) <=
//           __int128(b[f2] - b[f1]) * (m[f1] - m[f3]);
    return 1.0 * (b[f3] - b[f1]) * (m[f1] - m[f2]) >=
           1.0 * (b[f2] - b[f1]) * (m[f1] - m[f3]);
}
/**

slope descending order, min query  <=
slope descending order, max query  >=
slope ascending order, min query  >=
slope ascending order, max query  <=
on the 'bad' function.
*/
void add(long long m_ , long long b_)
{
    m.push_back(m_);
    b.push_back(b_);
    int sz = m.size();
    // notice that f1 from discussion is in position sz - 3
    // f2 is in sz - 2, new line is in sz - 1
    while(sz >= 3 && bad(sz - 3, sz - 2, sz - 1))
    {
        m.erase(m.end() - 2); // remove f2's m
        b.erase(b.end() - 2);
        sz--;
    }
}
ll f(int i, ll x)
{
    return m[i] * x + b[i];
}

const int mxn = 1e6+9;
ll n,ans=0;

struct Rectangle
{
    ll p, q, a;
    Rectangle() {};

    bool operator < (Rectangle r) const{
        return p < r.p ;
    }
} rects[mxn];


int main()
{
    fast;
    cin>>n;
    for(int i=1; i<=n; i++)
        cin>>rects[i].p>>rects[i].q>>rects[i].a;
    sort(rects+1, rects+1+n);

    m.push_back(0);
    b.push_back(0);

    for(int i=1;i<=n;i++)
    {
        while(m.size()>=2 and f(0, rects[i].q) <= f(1, rects[i].q) ) {
            m.pop_front();
            b.pop_front();
        }
        ll tmp = f(0, rects[i].q) + rects[i].p * rects[i].q - rects[i].a;
        add(-rects[i].p, tmp);
        //cout<<"Debug : "<<-rects[i].p<<' '<<tmp<<endl;
        ans = max(ans, tmp);
    }
    cout<<ans<<endl;
    return 0;
}
