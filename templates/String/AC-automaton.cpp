#include<bits/stdc++.h>
using namespace std;
const int N = 100005;
const int M = 26;

struct AC {
    int t[N][M], fail[N];
    int tot;
    
    void init() {
        memset(t, 0, sizeof(t));
        memset(fail, 0, sizeof(fail));
        tot = 0;
    }
    
    void _insert(char *s) {
        int cur = 1;
        for(int i = 0; s[i]; i++) {
            int x = s[i] - 'a';
            if(!t[cur][x]) t[cur][x] = ++tot;
            cur = t[cur][x];
        }
        // handle sth
    }
    
    void build() {
        queue<int> Q;
        Q.push(1);
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for(int i = 0; i < M; i++) {
                if(t[u][i]) {
                    int p = fail[u];
                    while(p && !t[p][i]) p = fail[p];
                    fail[t[u][i]] = p ? t[p][i] : 1;
                    Q.push(t[u][i]);
                }
            }
        }
    }
};