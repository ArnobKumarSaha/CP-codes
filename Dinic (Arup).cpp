/**
 Adjacency list implementation of Dinic's blocking flow algorithm.
 For Undirected graphs, add each edge in both directions.
 This is very fast in practice, and only loses to push-relabel flow.

 Source: Stanford Notebook
 Running time:  O(V^2 E)
 Memory : O(V+E)

 INPUT:
     - graph, constructed using AddEdge()
     - source and sink

 OUTPUT:
     - maximum flow value
     - To obtain actual flow values, look at edges with capacity > 0
       (zero capacity edges are residual edges).
**/

#include<bits/stdc++.h>
using namespace std;

struct Edge
{
    int u, v;
    long long cap, flow;
    Edge() {}
    Edge(int u, int v, long long cap): u(u), v(v), cap(cap), flow(0) {}
};

struct Dinic
{
    /// call by Dinic flow(N)
    /// N =  number of nodes
    int N;
    vector < Edge > edges;
    vector < vector < int > > adj;
    vector < int > d, pt;

    Dinic(int N): N(N), edges(0), adj(N), d(N), pt(N) {}

    void AddEdge(int u, int v, long long cap)
    {
        if (u != v)
        {
            edges.emplace_back(u, v, cap);
            adj[u].emplace_back(edges.size() - 1);
            edges.emplace_back(v, u, cap);
            /// 0 -> unidirectional edge
            /// cap -> for bidirectional edge
            adj[v].emplace_back(edges.size() - 1);
        }
    }

    bool BFS(int S, int T)
    {
        queue < int > q({S});
        fill(d.begin(), d.end(), N + 1);
        d[S] = 0;
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            if (u == T)
            {
                break;
            }
            for (int k: adj[u])
            {
                Edge &e = edges[k];
                if (e.flow < e.cap and d[e.v] > d[e.u] + 1)
                {
                    d[e.v] = d[e.u] + 1;
                    q.emplace(e.v);
                }
            }
        }
        return d[T] != N + 1;
    }

    long long DFS(int u, int T, long long flow = -1)
    {
        if (u == T or flow == 0)
        {
            return flow;
        }
        for (int &i = pt[u]; i < adj[u].size(); ++i)
        {
            Edge &e = edges[adj[u][i]];
            Edge &oe = edges[adj[u][i] ^ 1];
            if (d[e.v] == d[e.u] + 1)
            {
                long long amt = e.cap - e.flow;
                if (flow != -1 and amt > flow)
                {
                    amt = flow;
                }
                if (long long pushed = DFS(e.v, T, amt))
                {
                    e.flow += pushed;
                    oe.flow -= pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    long long MaxFlow(int S, int T)
    {
        long long total = 0;
        while (BFS(S, T))
        {
            fill(pt.begin(), pt.end(), 0);
            while (long long flow = DFS(S, T))
                total += flow;
        }
        return total;
    }
    void printEdges()
    {
        for(auto z : edges)
        {
            cout<<z.u<<' '<<z.v<<' '<<z.cap<<endl;
        }
    }
};

int main()
{
    return 0;
}
