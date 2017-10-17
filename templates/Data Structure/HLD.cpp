const int N = 100005;

struct HLD {
    int n;
    vector<int> g[N];
    int sz[N], son[N], dep[N], fa[N], top[N];
    int id[N]; // tree node -> segment tree node
    int tot;
    
    void init(int n) {
        this->n = n;
        for(int i = 1; i <= n; i++) {
            g[i].clear();
        }
        dep[0] = 0;
    }
    
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    void dfs_1(int u, int pa) {
        dep[u] = dep[pa] + 1;
        sz[u] = 1;
        fa[u] = pa;
        pair<int, int> mx = make_pair(0, 0);
        for(auto v : g[u]) {
            if(v != pa) {
                dfs_1(v, u);
                sz[u] += sz[v];
                mx = max(mx, make_pair(sz[v], v));
            }
        }
        son[u] = mx.second;
    }
    
    void dfs_2(int u, int pa) {
        id[u] = ++tot;
        if(son[u]) {
            top[son[u]] = top[u];
            dfs_2(son[u], u);
        }
        for(auto v : g[u]) {
            if(v != pa && v != son[u]) {
                top[v] = v;
                dfs_2(v, u);
            }
        }
    }
    
    void build() {
        dfs_1(1, 0);
        top[1] = 1;
        dfs_2(1, 0);
    }
    
    void query(int u, int v) {
        int x = top[u], y = top[v];
        while(x != y) {
            if(dep[x] < dep[y]) swap(x, y), swap(u, v);
            // ask segment [id[x], id[u]] in segment tree
            u = fa[x];
            x = top[u];
            y = top[v];
        }
        // ask segment [min(id[u], id[v]), max(id[u], id[v])] in segment tree
    }
    
};
