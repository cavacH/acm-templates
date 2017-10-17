#include<bits/stdc++.h>
using namespace std;
const int N = 105;
const int INF = 0x7f7f7f7f;

struct Edge {
    int from, to, flow, cap, cost;
};

struct mcmf {
    int n, m, s, t;
    vector<Edge> Edges;
    vector<int> g[N];
    int p[N], df[N], w[N];
    bool vis[N];

    void init(int n) {
        this->n = n;
        for(int i = 1; i <= n; i++) g[i].clear();
        Edges.clear();
    }

    void addEdge(int u, int v, int c, int w) {
        Edges.push_back((Edge){u, v, 0, c, w});
        Edges.push_back((Edge){v, u, 0, 0, -w});
        m = Edges.size();
        g[u].push_back(m - 2);
        g[v].push_back(m - 1);
    }

    int spfa() {
        for(int i = 1; i <= n; i++) {
            df[i] = 0;
            vis[i] = 0;
            w[i] = INF;
        }
        queue<int> Q;
        df[s] = INF, vis[s] = 1, w[s] = 0;
        Q.push(s);
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            vis[u] = 0;
            for(auto &x : g[u]) {
                Edge &e = Edges[x];
                if(e.cap > e.flow && w[e.to] > w[u] + e.cost) {
                    p[e.to] = x;
                    df[e.to] = min(df[e.from], e.cap - e.flow);
                    w[e.to] = w[u] + e.cost;
                    if(!vis[e.to]) {
                        vis[e.to] = 1;
                        Q.push(e.to);
                    }
                }
            }
        }
        for(int u = t; u != s; u = Edges[p[u]].from) {
            Edges[p[u]].flow += df[t];
            Edges[p[u] ^ 1].flow -= df[t];
        }
        return w[t];
    }

    int mincost(int s, int t) {
        this->s = s;
        this->t = t;
        int ret = 0;
        while(1) {
            int cost = spfa();
            if(cost == INF) break;
            ret += cost;
        }
        return ret;
    }
    
} T;