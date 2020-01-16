#include<bits/stdc++.h>
using namespace std;

/**
Given an undirected Graph . You have to make it directed such that SCC count is minimum.
In other words, given a bridgeless undirected graph, make it directed Strongly connected component.
*/

vector<vector<pair<int, int>>> adj; // adjacency list - vertex and edge pairs
vector<pair<int, int>> edges;

vector<int> tin, low;
int bridge_cnt;
string orient;
vector<bool> edge_used;
void find_bridges(int v) {
    static int time = 0;
    low[v] = tin[v] = time++;
    for (auto p : adj[v]) {
        if (edge_used[p.second]) continue;
        edge_used[p.second] = true;
        orient[p.second] = v == edges[p.second].first ? '>' : '<';
        int nv = p.first;
        if (tin[nv] == -1) { // if nv is not visited yet
            find_bridges(nv);
            low[v] = min(low[v], low[nv]);
            if (low[nv] > tin[v]) {
                // a bridge between v and nv
                bridge_cnt++;
            }
        } else {
            low[v] = min(low[v], low[nv]);
        }
    }
}

int main() {
    int n, m;
    cin>>n>>m;
    adj.resize(n);
    tin.resize(n, -1);
    low.resize(n, -1);
    orient.resize(m);
    edges.resize(m);
    edge_used.resize(m);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin>>a>>b;
        a--; b--;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
        edges[i] = {a, b};
    }
    int comp_cnt = 0;
    for (int v = 0; v < n; v++) {
        if (tin[v] == -1) {
            comp_cnt++;
            find_bridges(v);
        }
    }
    cout<<"Total number of SCC : "<<comp_cnt + bridge_cnt<<endl;
    for(int i=0;i<m; i++){
		cout<<edges[i].first+1<<' '<<orient[i]<<' '<<edges[i].second+1<<endl;
    }
}
/*
6 8

1 2
1 5
2 3
2 4
3 4
4 5
5 6
3 6
*/
