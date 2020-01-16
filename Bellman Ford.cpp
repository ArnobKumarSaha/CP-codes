#include<bits/stdc++.h>
using namespace std;
const int INF = (1<<30);
struct edge
{
    int a, b, cost;
};

int n, m, start, endd;
vector<edge> e;

void BellmanFord()
{
    vector<int> d (n, INF);
    d[start] = 0;
    vector<int> p (n - 1); /** who is causing the Relaxation */
    int x;
    for (int i=0; i<n; ++i) /** Nth iteration e update means negative cycle exists */
    {
        x = -1;
        for (int j=0; j<m; ++j)
            if (d[e[j].a] < INF)
                if (d[e[j].b] > d[e[j].a] + e[j].cost)
                {
                    d[e[j].b] = max (-INF, d[e[j].a] + e[j].cost);  /** -INF for avoiding int overflow. */
                    p[e[j].b] = e[j].a;
                    x = e[j].b;
                }
    }

    if (x == -1)
        cout << "No negative cycle from " << start;
    else
    {
        int y = x;
        for (int i=0; i<n; ++i)
            y = p[y];

        vector<int> path;
        for (int cur=y; ; cur=p[cur])
        {
            path.push_back (cur);
            if (cur == y && path.size() > 1)
                break;
        }
        reverse (path.begin(), path.end());

        cout << "Negative cycle: ";
        for (size_t i=0; i<path.size(); ++i)
            cout << path[i] << ' ';
    }
}
int main()
{
	return 0;
}
