#include<bits/stdc++.h>
using namespace std;
#define PI acos(-1.0)
#define DD double
//#define DD long long
const double EPS = 1e-9;


/** -------------------------Points and Vectors----------------------------*/
struct Pt
{
    DD x, y;
    Pt() : x(0), y(0) {}
    Pt(const DD& x, const DD& y) : x(x), y(y) {}

    void swap(Pt& other){using std::swap;swap(x, other.x);swap(y, other.y);}
    Pt& operator = (const Pt& other){x = other.x;y = other.y;return *this;}
    DD square() {return x*x + y*y;}
    double absolute() {return sqrt( (double) square());}
    double argument(){
        // Return value in between (-PI , PI]
        complex<double> _cc{ (double)x, (double)y};
        if(arg(_cc)< 0)
            return arg(_cc)+ 2*PI;
        return arg(_cc);
    }
    Pt operator +(const Pt& other){return {(x+other.x), (y+other.y)};}
    Pt operator -(const Pt other){return {(x-other.x), (y-other.y)};}
    Pt operator *(const Pt& other){return {(x*other.x), (y*other.y)};}
    Pt operator *(const DD& factor){return {(x*factor), (y*factor)};}
    Pt operator /(const Pt& other){return {(x/other.x), (y/other.y)};}
    Pt operator /(const DD& factor){return {(x/factor), (y/factor)};}
    bool operator < (const Pt& p)const{return (x<p.x or (x==p.x and y<p.y) );}
};
istream& operator >> (istream& is, Pt& Pt){return is >> Pt.x >> Pt.y;}
ostream& operator << (ostream& os, const Pt& Pt){return os << Pt.x << ' ' << Pt.y;}
DD dist2(Pt a, Pt b) {return (a-b).absolute(); }
int Sign(double x) {return (x>EPS) - (x<EPS);} /// Safe sign checking
bool isEqual (Pt& p, Pt& q){return (p.x == q.x && p.y == q.y) ;}

/** --------------------------------Transformations---------------------------------------*/

Pt Translate(Pt& p, Pt& v){return p+v;}
/// Let, distance CP is unit distance. Scale will return the new coOrdinate of p after scaling CP by factor.
Pt Scale(Pt& c, double factor, Pt& p) {Pt k{factor, factor};k = k*(p-c);return {c + k} ;}
/// Rotate point p with angle d, around the point c.  /// f(p) = c + cis(d) * (p-c)
Pt Rotate(Pt c, Pt p, double d){
    Pt pc = (p-c);
    return {pc.x*cos(d) - pc.y*sin(d) + c.x , pc.x*sin(d) + pc.y*cos(d) + c.y};
}
Pt perp(Pt p) {return {-p.y,p.x}; }
Pt linearTransfo(Pt p,Pt q,Pt r,Pt fp,Pt fq){q=q-p;r=r-p;fq=fq -fp;return fp + r* (fq/q);}

/** ------------------------------Dot and Cross Product------------------------------------*/
DD dotProduct (Pt v, Pt w){return v.x * w.x + v.y * w.y;}
bool isPerpendicular(const Pt v, const Pt w){return dotProduct(v,w) == 0;}
double smallAngle(Pt v, Pt w){
    double cosTheta = (double)dotProduct(v,w) / (v.absolute() * w.absolute());
    if(cosTheta < -1) cosTheta = -1;
    if(cosTheta > 1) cosTheta = 1;
    return acos(cosTheta);
}
DD crossProduct(Pt v, Pt w){return v.x * w.y - v.y * w.x;}
DD orientation (Pt a,Pt b, Pt c){return crossProduct(b-a, c-a);}
/// If point p is in angle <bac
bool isInAngle(Pt a, Pt b,Pt c, Pt p)
{
    assert(orientation(a,b,c) != 0);
    if(orientation(a,b,c) < 0) swap(b,c);
    return orientation(a,b,p)>=0 && orientation(a,c,p)<=0;
}
bool isConvex(vector<Pt> &v)
{
    bool hasPos = false, hasNeg = false;
    for(int i=0,n =v.size();i<n;i++){
        DD o = orientation(v[i], v[(i+1)%n], v[(i+2)%n]);
        if(o > 0) hasPos = true;
        if(o < 0) hasNeg = true;
    }
    return !(hasPos && hasNeg);
}
bool half(Pt p){assert(p.x!=0 || p.y!=0);return p.y>0 || (p.y==0 && p.x<0);}
bool half(Pt p, Pt v){return crossProduct(v,p) < 0 || (crossProduct(v,p)==0 && dotProduct(v,p)<0);}
void polarSort(vector<Pt> &k, Pt pp)
{
    sort(k.begin(), k.end(), [](Pt v, Pt w){
        return make_tuple(half(v),0) <
            make_tuple(half(w), crossProduct(v,w));
    });
}
/// To find a point from 'a' through 'b' with distance d.
Pt pointAlongLine(Pt a, Pt b, double d){return a + ((b-a)/ sqrt(dotProduct(b-a,b-a)) ) * d;}

/** ------------------------------- Lines ------------------------------------*/

struct Line{
    Pt v;
    DD c;
    Line(Pt p, Pt q) : v(q-p) , c(crossProduct(v,p)){};
    Line(DD a, DD b,DD c) : v({b,-a}) , c(c) {};
    Line(Pt v, DD c) : v(v), c(c) {};

    DD side(Pt p){return crossProduct(v,p) - c;} /// Left side is positive , right side is negative.
    double distanceFromPoint(Pt p){return fabs(side(p)) / v.absolute();}
    double sqDist(Pt p){ return side(p)*side(p)/(double)v.square(); }
    Line perpendicularThrough(Pt p){return {p , p + perp(v)};}

    /// returns true , if point p comes before point q , when walking along Line V
    bool cmpProjection(Pt p, Pt q){return dotProduct(v,p) < dotProduct(v,q);}
    void sortingAlong_a_line(vector<Pt> &vec){sort(vec.begin(), vec.end(), [&](Pt p, Pt q){return dotProduct(v ,p) < dotProduct(v, q);});}
    Line Translate(Pt t){return {v , c+ crossProduct(v,t)};}

    /// Shifting a line with a certain distance.
    Line shiftLeft(double dist){return {v , c+ dist * v.absolute()};}
    bool intersection(Line other, Pt& point){
        DD d = crossProduct(v,other.v);
        if(d==0) return false;
        point = (other.v * c - v * other.c) / d;
        return true;
    }
    Pt projection(Pt p){return {p - perp(v) * side(p) / v.square()};}
    Pt reflection(Pt p){return {p - perp(v) * 2 * side(p) / v.square()};}

    /// There are two "angle Bisector", Interior and Exterior.
    Line bisector(Line other, bool interior)
    {
        double sign = interior ? 1 : -1;
        return { other.v / other.v.absolute() +  (v / v.absolute()) * sign ,
           other.c / other.v.absolute() + (c / v.absolute()) * sign };
    }
};
/// To check ab line and cd line are parallel or collinear or same
bool lineParallel(Pt a, Pt b, Pt c, Pt d) {return fabs(crossProduct(b-a,c-d)) < EPS;}
bool lineCollinear(Pt a, Pt b, Pt c, Pt d) {return lineParallel(a,b,c,d) and fabs(crossProduct(a-b,a-c))<EPS and fabs(crossProduct(c-d,c-a))<EPS ;}
bool isSame(Pt a, Pt b, Pt c,Pt d) { return (fabs(crossProduct(a-c,c-d)) < EPS and fabs(crossProduct(b-c,c-d))<EPS ); }
Pt computeLineIntersection(Pt a, Pt b, Pt c, Pt d)
{
    double a1,b1,c1,a2,b2,c2;
    a1=a.y-b.y,b1=b.x-a.x,c1=crossProduct(a,b);
    a2=c.y-d.y,b2=d.x-c.x,c2=crossProduct(c,d);
    double D = a1*b2 - a2*b1;
    return Pt( (b1*c2 - b2*c1)/D, (c1*a2 - c2*a1)/D );
}
/** --------------------------------Segments-----------------------------------*/

bool inDisk(Pt a,Pt b, Pt p){return dotProduct(a-p, b-p) <= 0;} /// If p is in the circle of diameter ab.
bool onSegment(Pt a, Pt b, Pt p){return orientation(a,b,p) == 0 && inDisk(a,b,p);}
/// Proper Intersection means , point r is not equal to a,b,c or d.
bool properIntersection(Pt a, Pt b, Pt c, Pt d, Pt& r){
    double oa = orientation(c,d,a),
        ob = orientation(c,d,b),
        oc = orientation(a,b,c),
        od = orientation(a,b,d);
    if(oa*ob < 0 && oc*od < 0){
        r = (a*ob - b*oa) / (ob-oa);
        return true;
    }
    return false;
}
/// Size of returned vector is 0 if no intersection, 1 if point intersection, and 2 if segment intersection.
vector<Pt> intersection(Pt a, Pt b,Pt c, Pt d){
    Pt out;
    if(properIntersection(a,b,c,d,out)) return {out};
    vector<Pt> s;
    if(onSegment(c,d,a)) s.push_back(a);
    if(onSegment(c,d,b)) s.push_back(b);
    if(onSegment(a,b,c)) s.push_back(c);
    if(onSegment(a,b,d)) s.push_back(d);
    return s;
}
double segmentPointDistance(Pt a, Pt b, Pt p){
    if(!isEqual(a,b)){
        Line l(a,b);
        if(l.cmpProjection(a,p) && l.cmpProjection(p,b))
            return l.distanceFromPoint(p);
    }
    return min( ((Pt)(p-a)).absolute(), ((Pt)(p-b)).absolute());
}
double segmentSegmentDistance(Pt a, Pt b, Pt c, Pt d){
    Pt dummy;
    if(properIntersection(a,b,c,d,dummy)) return 0;
    double mini = (1e6);
    mini = min(mini, segmentPointDistance(a,b,c));
    mini = min(mini, segmentPointDistance(a,b,d));
    mini = min(mini, segmentPointDistance(c,d,a));
    mini = min(mini, segmentPointDistance(c,d,b));
    return mini;
}
/** --------------------------------Polygon-----------------------------------*/
double areaTriangle(Pt a,Pt b,Pt c){return abs( crossProduct(b-a,c-a) )/2.0;}
double areaPolygon(vector<Pt>p, bool Signed){
    double area=0.0;
    for(int i=0,n=p.size();i<n;i++){
        area += crossProduct(p[i],p[(i+1)%n]);
    }
    if(Signed) return area/2.0;
    return fabs(area)/2.0;
}
bool above(Pt a, Pt p) {return p.y >= a.y;}
/// To check , if pq segment crosses 0a ray.
bool crossesRay(Pt a, Pt p, Pt q) {return (above(a,q) - above(a,p)) * orientation(a,p,q) > 0;}
bool inPolygon(vector<Pt> p, Pt a, bool strict = true) {
    int numCrossings = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        if (onSegment(p[i], p[(i+1)%n], a))
        return !strict;
        numCrossings += crossesRay(a, p[i], p[(i+1)%n]);
    }
    return numCrossings & 1;
}
Pt computeCentroid(const vector<Pt>&p){
    Pt c = Pt(0,0);
    double scale = 6.0 * areaPolygon(p,true);
    for(int i=0;i<p.size();i++){
        int j = (i+1)%p.size();
        Pt x = p[i], y= p[j],r = (x+y);
        c = c + ( r * crossProduct(p[i],p[j]) );
    }
    return (c/scale);
}
bool isSimple(const vector<Pt>&p){
    for(int i=0;i<p.size();i++){
        for(int k=i+1;k<p.size();k++){
            int j = (i+1)%p.size(), x = (k+1)%p.size();
            if(i==x or j==k) continue;
            vector<Pt> v = intersection(p[i],p[j],p[k],p[x]);
            if(v.size()) return false;
        }
    }
    return true;
}
/***-----------------------------------Circle----------------------------------------*/

Pt circumCenter(Pt a, Pt b, Pt c) {
    b = b-a, c = c-a;assert(crossProduct(b,c) != 0);
    return a + perp(b*c.square() - c*b.square())/crossProduct(b,c)/2;
}
int circleLine(Pt o, double r, Line l, pair<Pt,Pt> &out) {
    double h2 = r*r - l.sqDist(o);
    if (h2 >= 0) { // the line touches the circle
        Pt p = l.projection(o);
        Pt h = l.v*sqrt(h2)/(l.v.absolute()); // vector parallel to l, of length h
        out = {p-h, p+h};
    }
    return 1 + (h2>0);
}
int circleCircle(Pt o1, double r1, Pt o2, double r2, pair<Pt,Pt> &out) {
    Pt d=o2-o1; double d2=d.square();
    if (d2 == 0) {assert(r1 != r2); return 0;} // concentric circles
    double pd = (d2 + r1*r1 - r2*r2)/2; // = |O_1P| * d
    double h2 = r1*r1 - pd*pd/d2; // = hˆ2
    if (h2 >= 0) {
        Pt p = o1 + d*pd/d2, h = perp(d)*sqrt(h2/d2);
        out = {p-h, p+h};
    }
    return 1 + (h2>0);
}
/// if two circles are identical , it aborts.
///the same code can be used to find the tangent to a circle passing through a point by setting r2 to 0
int tangents(Pt o1, double r1, Pt o2, double r2, bool inner, vector<pair<Pt,Pt> > &out) {
    if (inner) r2 = -r2;
    Pt d = o2-o1;
    double dr = r1-r2, d2 = d.square(), h2 = d2-dr*dr;
    if (d2 == 0 || h2 < 0) {assert(h2 != 0); return 0;}
    for (double sign : {-1,1}) {
        Pt v = (d*dr + perp(d)*sqrt(h2)*sign)/d2;
        out.push_back({o1 + v*r1, o2 + v*r2});
    }
    return 1 + (h2 > 0);
}
/**----------------------------------Rectangle------------------------------------------------*/
struct Rect{
    int xl,yl,xu,yu;
    Rect(int _xl,int _yl, int _xu,int _yu){
        xl = _xl;
        yl = _yl;
        xu = _xu;
        yu = _yu;
    }
    Rect(){}
    DD area(){return (xu-xl)*(yu-yl);}
};
Rect findIntersection(Rect a, Rect b)
{
    int x1 = max(a.xl, b.xl);
    int y1 = max(a.yl, b.yl);
    int x2 = min(a.xu, b.xu);
    int y2 = min(a.yu, b.yu);
    if(x1>=x2 or y1>=y2) return Rect(0,0,0,0);
    return Rect(x1,y1,x2,y2);
}
/**-------------------------------------Extras-------------------------------------------------*/
void convexHull(vector<Pt>&v){
    sort(v.begin(),v.end());
    vector<Pt>up,dn;
    for(auto& p : v){
        while(up.size()>1 and orientation(up[up.size()-2],up.back(),p) >=0) up.pop_back();
        while(dn.size()>1 and orientation(dn[dn.size()-2],dn.back(),p) <=0) dn.pop_back();
        up.push_back(p), dn.push_back(p);
    }
    v=dn;
    v.pop_back();
    reverse(v.begin(),v.end());
    up.pop_back();
    for(auto& p : up) v.push_back(p);
}
double maxDist2(vector<Pt>u, vector<Pt>v){ /// Maximum distance between two convex polygon
    convexHull(u), convexHull(v);
    int n = u.size(), m = v.size();
    double dist=0;
    if(n<3 or m<3){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                dist = max(dist, (u[i]-v[j]).absolute() );
            }
        }
        return dist;
    }
    if(u[0].x > v[0].x) swap(n,m),swap(u,v);
    int i=0, j=0, step=n+m+10;

    while(j<m and v[j].x < v[j+1].x) j++;
    while(step--){
        if(crossProduct( u[(i+1)%n] - u[i] ,v[(j+1)%m] - v[j] ) >= 0) j = (j+1)%m;
        else i = (i+1)%n;
        dist = max(dist, (u[i]-v[j]).absolute() );
    }
    return dist;
}
struct PolyQuery{ /// Minimum distance between point and convex polygon in O(nlogn)
    vector<Pt>u,v; /// polygon points must be in counterClockwise order.
    int n,s,pw;
    PolyQuery(){}
    PolyQuery(vector<Pt>v) : v(v){
        n = v.size();
        for(int i=0;i<n;i++){
            Pt a = v[(i+1)%n] - v[i];
            Pt b = v[(i-1+n)%n] - v[i];
            b = b*sqrt(dotProduct(a,a)/dotProduct(b,b));
            u.push_back(a*(-1)-b);
        }
        s=0,pw=1;
        while(s<n and Sign(crossProduct(u[0],u[s]))>=0) s++;
        while( (pw<<1)<n ) pw<<=1;
    }
    double distFunc(Pt a, Pt b, Pt c){
        double d = min(dist2(a,c),dist2(b,c));
        //return d; //For minimum vertex  distance return here.
        double t = dotProduct(b-a,c-a)/dotProduct(b-a,b-a);
        t = max(0.0, min(t,1.0));
        d = min(d, dist2(a+(b-a)*t,c ));
        return d;
    }
    double minDist2(Pt p)
    {
        int i=0,j=pw;
        if(Sign(crossProduct(u[i],p-v[i])) < 0) i=s;
        if(Sign(crossProduct(u[i],p-v[i])) < 0) return distFunc(v[i],v[i-1],p);
        while(j){
            int t = (i+j)%n;
            if(Sign(crossProduct(u[i],u[t])) >= 0 and Sign(crossProduct(u[t],p-v[t])) >= 0) i=t;
            j >>= 1;
        }
        return distFunc(v[i],v[(i+1)%n],p);
    }
};
typedef pair<long long, long long> pll;
int compare(pll a, pll b){
    return a.second < b.second;
}
double closest_pair(vector<pll>v) /// Returns the closest pair of points.
{
    sort(v.begin(), v.end(),compare);
    double best = DBL_MAX;
    set<pll>box;
    box.insert(v[0]);
    int left=0, n = v.size();
    set<pll>::iterator it;
    for(int i=1;i<n;i++){
        while(left<i and v[i].second - v[left].second > best) box.erase(v[left++]);

        for(it = box.lower_bound(make_pair(v[i].first-best, v[i].second-best));it != box.end() and v[i].first+best >= it->first; it++) {
            best = min( best, sqrt( pow(v[i].first - it->first, 2.0) + pow(v[i].second - it->second, 2.0) ) );
        }
        box.insert(v[i]);
    }
    return best;
}

double deg(double rd){return (rd*180)/PI;}
double rad(double dg){return (dg*PI)/180;}
/** ********************************************************************************************** */
int main()
{
    Pt v = {3,1};
    return 0;
}

