#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2502;

template<typename T> /// Point update + Range query
struct BIT       ///1-indexed
{
    int szr,szc;///max size of array+1
    vector<vector<T>>t;
    ll MOD;
    void init(int n,int m)
    {

        szr=n,szc=m;
        t.assign(szr,vector<T>(szc,0));
        MOD = LONG_MAX;
    }
    void init(int n,int m,int mod)
    {

        szr=n,szc=m;
        t.assign(szr,vector<T>(szc,0));
        MOD = mod;
    }
    void upd(int r,int c,T val)  ///add val to a[i][j]
    {
        for(int i=r; i<szr; i+=i&-i)
            for(int j=c; j<szc; j+=j&-j)
                t[i][j]= (t[i][j]+val)%MOD;
    }
    T query(int r,int c)
    {
        T sum=0;
        for(int i=r; i>0; i-=i&-i)
            for(int j=c; j>0; j-=j&-j)
                sum= (sum+t[i][j])%MOD;
        return sum;
    }
    T query(int x1,int y1,int x2,int y2)  ///returns sum of the corresponding rectangle
    {
        return (query(x2,y2)-query(x2,y1-1)-query(x1-1,y2)+query(x1-1,y1-1)+2*MOD)%MOD;
    }
    void pri()
    {
        for(int i=1;i<szr;i++){
            for(int j=1;j<szc;j++){
                cout<<t[i][j]<<' ';
            }
            cout<<endl;
        }
    }
};

///in case of range update single query
///for range update use upd(x1,y1,val),upd(x1,y2+1,-val),upd(x2+1,y1,-val),upd(x2+1,y2+1,val)

int main()
{

    return 0;
}
