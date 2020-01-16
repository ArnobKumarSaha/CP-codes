Rotating Calipers (Rumman Vai)_________________
double polygonDiameter(vector<PT> &p)
{
    int n=SZ(p);
    if(n<2) return 0;
    else if(n==2) return distPoint(p[0],p[1]);//distance between two points
    else
    {
        int i=n-1,j=0,k=1;
        double res=0;
        while(abs(cross(p[j]-p[i],p[k+1]-p[i]) >
                  abs(cross(p[j]-p[i],p[k]-p[i]))))
        {
            k++;
        }
        i=0,j=k;
        while(i<=k && j<n)
        {
            res=max(distPoint(p[i],p[j]),res);
            while(j<n-1 && abs(cross(p[i+1]-p[i],p[j+1]-p[i]) >
                      abs(cross(p[i+1]-p[i],p[j]-p[i]))))
            {
                j++;
                res=max(distPoint(p[i],p[j]),res);
            }
            i++;
        }
        return res;
    }
}

int main()
{
    vector<PT> poly,cpoly;PT a;
    int n;
    sf("%d",&n);
    for(int i=0;i<n;i++)
    {
        a.input();
        poly.psb(a);
    }
    ConvexHull(poly,cpoly);
    pf("%.12f\n",polygonDiameter(cpoly));
    return 0;
}


Precode_________________
#include<bits/stdc++.h>
using namespace std;
#define debug(x) cout << #x << " " << x <<endl;
#define cord long long
struct pt{
	cord x,y;
	pt(){}
	pt(cord x,cord y): x(x), y(y) {}

	void scan(){
		scanf("%lld%lld",&x,&y);
	}

	pt(const pt &p) : x(p.x), y(p.y) {}
	pt operator + (const pt &p) const {return pt(x+p.x, y+p.y);}
	pt operator - (const pt &p) const {return pt(x-p.x, y-p.y);}
	pt operator * (cord c) const {return pt(x*c, y*c);}
	pt operator / (cord c) const {return pt(x/c, y/c);}
	bool operator<(const pt &p) const{
		return x<p.x || (x == p.x && y < p.y);
	}
};

cord dot(pt p, pt q) {return p.x*q.x+p.y*q.y;}
cord dist2(pt p,pt q) {return dot(p-q,p-q);}
cord cross(pt p,pt q) {return p.x*q.y-p.y*q.x;}

ostream &operator<<(ostream &os, const pt &p){
	return os << "(" << p.x << "," << p.y << ")";
}

cord point_to_line_distence(pt p1,pt p2,pt q)//distence from q to line(p1->p2)//
{
	cord dist = sqrt(dist2(p1,p2));
	cord cross_product = abs(cross(p2-p1,q-p1));
	return cross_product/dist;
}

convex_hull_code______________
vector<pt> convex_hull(vector<pt> vp)
{
	int n = vp.size(),k = 0;
	if(n<=3)return vp;
	vector<pt> ret(2*n);
	sort(vp.begin(),vp.end());

	for(int i=0;i<n;++i)
	{
		while(k>=2 && cross(ret[k-2]-ret[k-1],vp[i]-ret[k-1])<=0LL)k--;
		ret[k++] = vp[i];
	}
	for(int i=n-2,t = k+1;i>=0;--i)
	{
		while(k>=t && cross(ret[k-2]-ret[k-1],vp[i]-ret[k-1])<=0LL)k--;
		ret[k++] = vp[i];
	}
	ret.resize(k-1);
	return ret;
}
////////convex_hull_code_______end_______

Diameter_of_convex_polygon_______

cord polygonDiameter(vector<pt> &vp)
{
	int n = vp.size();
	if(n<2) return 0;
	else if(n<=3){
		cord ret = 0;
		for(int i=0;i<n;i++)
			for(int j=i+1;j<n;j++)
				ret = max(ret,dist2(vp[i],vp[j]));
		return ret;
	}
	/*cord ret = 0LL;
	int i=0,j=0;
	for(int i=0;i<n;i++)
	{
		while(dist2(vp[i],vp[(j+1)%n])>=dist2(vp[i],vp[j])) j = (j+1)%n;
		ret = max(ret, dist2(vp[i],vp[j]));
	}
	return ret;
	*/

	int i=n-1, j = 0, k = 1;

	cord ret = 0;

	while(abs(cross(vp[j]-vp[i],vp[k+1]-vp[i]))>abs(cross(vp[j]-vp[i],vp[k]-vp[i])))
		k++;

	i = 0, j = k;
	while(i<=k && j<n)
	{
		ret = max(dist2(vp[i],vp[j]),ret);
		while(j<n-1 && abs(cross(vp[i+1]-vp[i],vp[j+1]-vp[i]))>abs(cross(vp[i+1]-vp[i],vp[j]-vp[i])))
		{
			j++;
			ret = max(dist2(vp[i],vp[j]),ret);
		}
		i++;
	}
	return ret;
}
///////diameter_of_convex_polygon___end___

Width_of_convex_polygon_________________
////////width_of_convex_polygon_______

cord polygonWidth(vector<pt> &vp)
{
	int n = vp.size();
	if(n<=2) return 0;
	int i=0,k=1;
	cord ret = 1000000000.00;// inf here
	while(i<n)
	{
		while(abs(cross(vp[(i+1)%n]-vp[i],vp[(k+1)%n]-vp[i]))>abs(cross(vp[(i+1)%n]-vp[i],vp[k]-vp[i])))
			k = (k+1)%n;
		cord dis = point_to_line_distence(vp[i],vp[(i+1)%n],vp[k]);
		ret = min(ret,dis);
		i++;
	}
	return ret;
}
///////widt_of_convex_polygon___end__
int main(){
	int t; scanf("%d",&t);
	while(t--){
	int n; scanf("%d",&n);
	vector<pt> inp;
	for(int i=0;i<n;i++){pt a;a.scan();inp.push_back(a);}
	vector<pt> con_pol;
	con_pol = convex_hull(inp);
	cord ans = polygonDiameter(con_pol);
	printf("%lld\n",ans);
  }}

Perimeter___________________
#include<bits/stdc++.h>
using namespace std;
#define debug(x) cout << #x << " " << x <<endl;
#define cord double
#define eps 1e-9
struct pt{
	cord x,y;
	pt(){}
	pt(cord x,cord y): x(x), y(y) {}

	void scan(){
		scanf("%lf%lf",&x,&y);
	}

	pt(const pt &p) : x(p.x), y(p.y) {}
	pt operator + (const pt &p) const {return pt(x+p.x, y+p.y);}
	pt operator - (const pt &p) const {return pt(x-p.x, y-p.y);}
	pt operator * (cord c) const {return pt(x*c, y*c);}
	pt operator / (cord c) const {return pt(x/c, y/c);}
	bool operator<(const pt &p) const{
		return x<p.x || (x == p.x && y < p.y);
	}
};

cord dot(pt p, pt q) {return p.x*q.x+p.y*q.y;}
cord dist2(pt p,pt q) {return dot(p-q,p-q);}
cord cross(pt p,pt q) {return p.x*q.y-p.y*q.x;}

ostream &operator<<(ostream &os, const pt &p){
	return os << "(" << p.x << "," << p.y << ")";
}

cord point_to_line_distence(pt p1,pt p2,pt q)//distence from q to line(p1->p2)//
{
	cord dist = sqrt(dist2(p1,p2));
	cord cross_product = cross(p2-p1,q-p1);
	return cross_product/dist;
}

pt point_line_projetion(pt p1,pt p2,pt q)
{
	return p1 + (p2-p1)*dot(q-p1,p2-p1)/dot(p2-p1,p2-p1);
}

int sign(double t)
{
	if(abs(t)<eps)return 0;
	return t<0.0 ? -1:1;}

vector<pt> convex_hull(vector<pt> vp)
{
	int n = vp.size();
	vector<pt> ret(2*n);
	sort(vp.begin(),vp.end());
	int k = 0,i=0;
	for(int i=0;i<n;i++){
	while(k>=2 && cross(ret[k-1]-ret[k-2],vp[i]-ret[k-2])<=0)k--;
	ret[k++] = vp[i];
	}
	for(int i=n-2,t = k+1;i>=0;i--){

		while(k>=t && cross(ret[k-1]-ret[k-2],vp[i]-ret[k-2])<=0)k--;
		ret[k++] = vp[i];
	}
	ret.resize(k-1);
	//for(auto x:ret)cout << x << endl;
	//	cout << endl;
	return ret;
}

cord func(vector<pt> vp)
{
	int n = vp.size();
	//for(auto x:vp)cout << x << endl;
	//	cout << endl;
	int right = 1,upper = 1,left = 1,cur = 0;
	cord ret = 1000000000000000000.00;
	while(cur<n)
	{
		while(sign(dot(vp[(cur+1)%n]-vp[cur],vp[(right+1)%n]-vp[cur])-
			dot(vp[(cur+1)%n]-vp[cur],vp[right]-vp[cur]))>=0)right = (right+1)%n;
		while(sign(cross(vp[(cur+1)%n]-vp[cur],vp[(upper+1)%n]-vp[cur])-
			cross(vp[(cur+1)%n]-vp[cur],vp[upper]-vp[cur]))>=0)upper = (upper+1)%n;
		if(cur==0)left = right;
		while(sign(dot(vp[(cur+1)%n]-vp[cur],vp[(left+1)%n]-vp[cur])-
				dot(vp[(cur+1)%n]-vp[cur],vp[left]-vp[cur]))<=0)left=(left+1)%n;
		//pt R = point_line_projetion(vp[cur],vp[(cur+1)%n],vp[right]);
				//pt L = point_line_projetion(vp[cur],vp[(cur+1)%n],vp[left]);

		cord width = (dot(vp[(cur+1)%n]-vp[cur],vp[right]-vp[cur])-
						dot(vp[(cur+1)%n]-vp[cur],vp[left]-vp[cur]))/sqrt(dist2(vp[(cur+1)%n],vp[cur]));
		cord height = point_to_line_distence(vp[cur],vp[(cur+1)%n],vp[upper]);
		cord peri = (width+height);
		//debug(peri);
		ret = min(ret,peri);
		cur++;
	}
	return ret*2.00;}

Diameter2____________
cord polygonDiameter(vector<pt> &vp)
{
	int n = vp.size();
	if(n<2) return 0;
	else if(n<=3){
		cord ret = 0;
		for(int i=0;i<n;i++)
			for(int j=i+1;j<n;j++)
				ret = max(ret,dist2(vp[i],vp[j]));
		return ret;
	}
	/*cord ret = 0LL;
	int i=0,j=0;
	for(int i=0;i<n;i++)
	{
		while(dist2(vp[i],vp[(j+1)%n])>=dist2(vp[i],vp[j])) j = (j+1)%n;
		ret = max(ret, dist2(vp[i],vp[j]));
	}
	return ret;
	*/
	int i=n-1, j = 0, k = 1;
	cord ret = 0;
	while(abs(cross(vp[j]-vp[i],vp[k+1]-vp[i]))>abs(cross(vp[j]-vp[i],vp[k]-vp[i]))){
		//debug(k);
		k++;
	}
	//debug(k);
	i = 0, j = k;
	while(i<=k && j<n)
	{
		ret = max(dist2(vp[i],vp[j]),ret);
		while(j<n-1 && abs(cross(vp[i+1]-vp[i],vp[j+1]-vp[i]))>abs(cross(vp[i+1]-vp[i],vp[j]-vp[i])))
		{
			j++;
			ret = max(dist2(vp[i],vp[j]),ret);
		}
		i++;
	}
	return ret;
}
///////diameter_of_convex_polygon___end___



