#include<bits/stdc++.h>
using namespace std;
#define LL long long 
#define pli pair<LL, int>

const int N = 1005;
const LL INF = 0x7f7f7f7f7f7f7f7fLL;

vector<pli> g[N];
int n;
LL d[N];
bool done[N];

void dij(int s) {
    priority_queue<pli, vector<pli>, greater<pli> > Q;
    memset(d, 0x7f, sizeof(d));
    memset(done, 0, sizeof(done));
    d[s] = 0;
    Q.push(make_pair(0, s));
    while(!Q.empty()) {
        int u = Q.top().second;
        Q.pop();
        if(done[u]) continue;
        done[u] = true;
        for(auto &x : g[u]) {
            int v = x.second;
            LL w = x.first;
            if(d[v] > d[u] + w) {
                d[v] = d[u] + w;
                Q.push(make_pair(d[v], v));
            }
        }
    }
}

