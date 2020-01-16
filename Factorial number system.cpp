vi decimal_to_factoradic(int n)
{
    vi v;
    int i=1;
    while(n){
        v.eb(n%i);
        n/=i;
        i++;
    }
    rev(v);
    return v;
}
int factoradic_to_decimal(vi &v)
{
    int n=v.size();
    int ans=0;
    for(int i=0,mul=n;i<n;i++,mul--) ans=(ans*mul%mod+v[i])%mod;
    return ans;
}
vi permutation(int n,vi &v)
{
    o_set<int>se;
    int sz=v.size();
    vi p;
    for(int i=0;i<n-sz;i++) p.eb(i);
    for(int i=n-sz;i<n;i++) se.insert(i);
    for(int i=0;i<sz;i++){
        int nw=*se.fbo(v[i]);
        p.eb(nw);
        se.erase(nw);
    }
    return p;
}
///returns k-th lexicographically smallest permutation of size n
///0-th permutation is the unit permutation i.e. 0,1,2,....n-1
vi kth_perm(int n,int k)
{
    ///need to return something when k>=n!
    vi v=decimal_to_factoradic(k);
    return permutation(n,v);
}
vi factoradic_order(vi &p)
{
    o_set<int>se;
    int n=p.size();
    for(int i=0;i<n;i++) se.insert(p[i]);
    vi fac;
    for(int i=0;i<n;i++){
        int x=se.ook(p[i]);
        fac.eb(x);
        se.erase(p[i]);
    }
    return fac;
}
///?-th lexicographically smallest permutation of size n
int order(vi &p)
{
    vi fac=factoradic_order(p);
    return factoradic_to_decimal(fac);
}



///Given two permutation of size n, find Perm((ord(P)+ord(Q))mod n!)
///where Perm(k) is k-th lexicographically smallest permutation
///and ord(P) is the number k of the permutation
int main()
{
    BeatMeScanf;
    int i,j,k,n,m;
    cin>>n;
    vi p(n);
    for(i=0;i<n;i++) cin>>p[i];
    vi q(n);
    for(i=0;i<n;i++) cin>>q[i];
    vi ordp=factoradic_order(p);
    vi ordq=factoradic_order(q);
    vi sum=ordp;
    int carry=0;
    for(i=n-1;i>=0;i--){
        sum[i]+=ordq[i]+carry;
        carry=sum[i]/(n-i);
        sum[i]%=(n-i);
    }
    vi perm=permutation(n,sum);
    for(i=0;i<n;i++) cout<<perm[i]<<' ';
    return 0;
}
