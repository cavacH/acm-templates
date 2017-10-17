#include<bits/stdc++.h>
using namespace std;
const int N = 105;
const int INF = 0x7f7f7f7f;

struct Edge {
    int from, to, cap, flow;
};

struct Dinic {
    int n, m, s, t;
    vector<Edge> Edges;
    vector<int> g[N];
    bool vis[N];
    int level[N], cur[N];
    
    void init(int n) {
        this->n = n;
        for(int i = 1; i <= n; i++) g[i].clear();
        Edges.clear();
    }
    
    void add_edge(int u, int v, int c) {
        Edges.push_back((Edge){u, v, c, 0});
        Edges.push_back((Edge){v, u, 0, 0});
        m = Edges.size();
        g[u].push_back(m - 2);
        g[v].push_back(m - 1);
    }
    
    bool bfs() {
        queue<int> Q;
        for(int i = 1; i <= n; i++) vis[i] = 0;
        d[s] = 0;
        vis[s] = 1;
        Q.push(s);
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for(auto &x : g[u]) {
                Edge &e = Edges[x];
                if(!vis[e.to] && e.cap > e.flow) {
                    vis[e.to] = 1;
                    d[e.to] = d[u] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }
    
    int dfs(int u, int a) {
        if(u == t || a == 0) return a;
        int ret = 0;
        for(int &i = cur[u]; i < g[u].size(); i++) {
            Edge &e = Edges[g[u][i]];
            if(d[u] + 1 == d[e.to] && (f = dfs(e.to, min(a, e.cap - e.flow))) > 0) {
                e.flow += f;
                Edges[g[u][i] ^ 1].flow -= f;
                ret += f;
                a -= f;
                if(a == 0) break;
            }
        }
        return ret;
    }
    
    int maxflow(int s, int t) {
        this->s = s;
        this->t = t;
        int ret = 0;
        while(bfs()) {
            for(int i = 1; i <= n; i++) cur[i] = 0;
            ret += dfs(s, INF);
        }
        return ret;
    }
    
};

