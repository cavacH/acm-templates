#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<cmath>
#include<queue>
using namespace std;
#define Min(a,b) (((a)<(b))?(a):(b))

const int N = 105;

struct Edge {
    int from, to, flow, cap;
    Edge(int f, int t, int fl, int c):
        from(f), to(t), flow(fl), cap(c){}
};

struct EK {
    int n;
    vector<Edge> E;
    vector<int> g[N];
    int p[N], df[N];
    bool vis[N];

    void init(int n) {
        this->n = n;
        for(int i = 1; i <= n; i++) g[i].clear();
        E.clear();
    }

    void addEdge(int u, int v, int c) {
        E.push_back(Edge(u, v, 0, c));
        E.push_back(Edge(v, u, 0, 0));
        int sz = E.size();
        g[u].push_back(sz - 2);
        g[v].push_back(sz - 1);
    }

    int bfs(int S, int T) {
        memset(df, 0, sizeof(df));
        memset(vis, 0, sizeof(vis));
        queue<int> Q;
        df[S] = 0x3f3f3f3f, vis[S] = 1;
        Q.push(S);
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for(int i = 0; i < (int)g[u].size(); i++) {
                Edge &e = E[g[u][i]];
                if(!vis[e.to] && e.cap > e.flow) {
                    p[e.to] = g[u][i];
                    vis[e.to] = 1;
                    df[e.to] = Min(df[e.from], e.cap - e.flow);
                    Q.push(e.to);
                }
            }
            if(vis[T]) break;
        }
        for(int u = T; u != S; u = E[p[u]].from) {
            E[p[u]].flow += df[T];
            E[p[u] ^ 1].flow -= df[T];
        }
        return df[T];
    }

    int maxFlow(int S, int T) {
        int F = 0;
        while(1) {
            int D = bfs(S, T);
            if(!D) break;
            F += D;
        }
        return F;
    }
};

