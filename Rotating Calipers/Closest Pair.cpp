#include<bits/stdc++.h>
using namespace std;

struct Pt
{
    int x, y;
};
typedef vector<Pt> Vp;
Vp P;
int n;

bool compareX(Pt a, Pt b) {return (a.x < b.x);}
bool compareY(Pt a, Pt b) {return (a.y < b.y);}
#define SQ(x) ( (x)*(x) )
double dist(Pt p1, Pt p2) {return sqrt( SQ(p1.x - p2.x) +SQ(p1.y - p2.y));}

double bruteForce(Vp P)
{
    double min = DBL_MAX;
    for (int i = 0, sz = P.size(); i < sz; ++i)
        for (int j = i+1; j < sz; ++j)
            if (dist(P[i], P[j]) < min)
                min = dist(P[i], P[j]);
    return min;
}

double min(double x, double y)
{
    return (x < y)? x : y;
}

double stripClosest(Vp strip ,double d)
{
    double min = d;
    // Pick all Pts one by one and try the next Pts till the difference
    // between y coordinates is smaller than d.
    // This is a proven fact that this loop runs at most 6 times
    for (int i = 0, sz = strip.size(); i < sz; ++i)
        for (int j = i+1; j < sz && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i],strip[j]) < min)
                min = dist(strip[i], strip[j]);

    return min;
}
double closestUtil(Vp Px,Vp Py, int sz)
{
    if (sz <= 3)
        return bruteForce(Px);
    int mid = sz/2;
    Pt midPt = Px[mid];
    Vp Pyl,Pyr;

    int li = 0, ri = 0;
    for (int i = 0; i < sz; i++)
    {
      if (Py[i].x <= midPt.x) Pyl.push_back(Py[i]),li++;
      else Pyr.push_back(Py[i]),ri++;
    }

    double dl = closestUtil(vector<Pt>(Px.begin(),Px.begin()+mid), Pyl, mid); /// solve the left part of midPoint
    double dr = closestUtil(vector<Pt>(Px.begin()+mid,Px.end()), Pyr, sz-mid); /// for Right part
    double d = min(dl, dr);
    Vp strip;
    for (int i = 0; i < sz; i++){
        if (abs(Py[i].x - midPt.x) < d) strip.push_back(Py[i]);
    }
    return min(d, stripClosest(strip, d) );
}
double closest()
{
    vector<Pt>Px=P, Py=P;
    sort(Px.begin(),Px.end(),compareX);
    sort(Py.begin(),Py.end(),compareY);
    return closestUtil(Px, Py, n);
}

int main()
{
    P.push_back({2,3});
    P.push_back({12,30});
    P.push_back({40,50});
    P.push_back({5,1});
    P.push_back({12,10});
    P.push_back({3,4});
    n = P.size();
    cout << "The smallest distance is " << closest();
    return 0;
}
