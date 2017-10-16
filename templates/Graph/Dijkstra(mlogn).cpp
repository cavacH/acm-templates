#include<bits/stdc++.h>
using namespace std;

#define clr(x) memset(x,0,sizeof(x))
#define LL long long
#define pll pair<long long,long long>
#define pii pair<int,int>
#define mkp make_pair
#define pb push_back

const int N = 1005;
const int INF = 0x3f3f3f3f;

struct Edge{
    int from,to,dist;
    Edge(int u,int v,int d):
        from(u),to(v),dist(d){}
};

struct Dijkstra{
    int n,m;
    vector<Edge> edges;
    vector<int> G[N];
    bool done[N];
    int d[N],p[N];

    void init(int n){
        this->n=n;
        for(int i=1;i<=n;i++) G[i].clear();
        edges.clear();
    }

    void AddEdge(int from,int to,int dist){
        edges.pb(Edge(from,to,dist));
        m=edges.size();
        G[from].pb(m-1);
    }

    void dijkstra(int s){
        priority_queue<pii,vector<pii>,greater<pii> > Q;
        for(int i=1;i<=n;i++) d[i]=INF;
        d[s]=0;
        clr(done);
        Q.push(mkp(0,s));
        while(!Q.empty()){
            pii x=Q.top();
            Q.pop();
            int u=x.second;
            if(done[u]) continue;
            done[u]=1;
            for(int i=0;i<G[u].size();i++){
                Edge e=edges[G[u][i]];
                if(d[e.to]>d[u]+e.dist){
                    d[e.to]=d[u]+e.dist;
                    p[e.to]=G[u][i];
                    Q.push(mkp(d[e.to],e.to));
                }
            }
        }
    }
};
