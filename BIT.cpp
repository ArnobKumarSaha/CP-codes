#include<bits/stdc++.h>
using namespace std;

template<typename T>
struct BIT
{
    vector<T> Tree;
    int Size=0;
    long long MOD;
    BIT(int n)
    {
        Tree.assign(n+1,0);
        Size=n;
        MOD = 1e18;
    }
    BIT(int n, long long _MOD)
    {
        Tree.assign(n+1,0);
        Size = n;
        MOD = _MOD;
    }
    BIT(vector<T>v)
    {
        Size = v.size();
        MOD = 1e18;
        for(int i=0;i<Size;i++){
            update(i,v[i]);
        }
    }
    void update(int indx,T val)
    {
        while(indx<=Size)
        {
            Tree[indx] += val;
            Tree[indx] %= MOD;
            indx += (indx)&(-indx);
        }
    }
    T query(int indx)
    {
        T sum=0;
        while(indx>0)
        {
            sum += Tree[indx];
            sum %= MOD;
            indx -= (indx)&(-indx);
        }
        return sum;
    }
    T query(int l, int r)
    {
        T ret = (query(r) - query(l-1));
        if(ret<0) ret+=MOD;
        return ret;
    }
    void clr()
    {
        for(int i=Tree.size()-1;i>=0;i--) Tree[i]=0;
    }
};

int main()
{

    return 0;
}
