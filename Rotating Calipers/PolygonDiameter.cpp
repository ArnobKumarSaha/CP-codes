#include<bits/stdc++.h>
using namespace std;

double polygonDiameter(vector<Pt> &p)
{
    int n = p.size();
    if(n<2) return 0;
    else if(n==2){
        return distPoint(p[0], p[1]);
    }
    else{
        int i=n-1,j=0,k=1;
        double res=0;
        while(abs(cross(p[j]-p[i], p[k+1]-p[i]) ) > abs(cross(p[j]-p[i], p[k]-p[i]) )) k++;
        i=0,j=k;
        while(i<=k and j<n){
            res = max(distPoint(p[i],p[j]),res );
            while(j<n-1 and abs(cross(p[i+1]-p[i], p[j+1]-p[i]) ) > abs(cross(p[i+1]-p[i], p[j]-p[i]) ) ){
                j++;
                res = max(res, distPoint(p[i],p[j]) );
            }
            i++;
        }
        return res;
    }
}
vector<pt> convex_hull(vector<Pt>vp)
{
    int n = vp.size(), k=0;
    if(n<=3) return vp;
    vector<Pt>ret(2*n);
    sort(vp.begin(), vp.end());
    for(int i=0;i<n;i++){
        while(k>=2 and cross(ret[k-2]- ret[k-1], vp[i]-ret[k-1]) <= 0LL ) k--;
        ret[k++] = vp[i];
    }
    for(int i=n-2, t=k+1; i>=0; i--){
        while(k>t and cross(ret[k-2]-ret[k-1], vp[i]-ret[k-1]) <= 0LL ) k--;
        ret[k++] = vp[i];
    }
    ret.resize(k-1);
    return ret;
}
int main()
{
    vector<Pt> poly,cpoly;
    Pt a;
    cin>>n;
    for(int i=0;i<n;i++){
        a.input();
        poly.psb(a);
    }
    Convexhull(poly, cpoly);
    cout<<polygonDiameter(cpoly)<<endl;
    return 0;
}
