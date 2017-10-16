
struct SuffixArray {
    int n, m, buc[N], x[N], y[N], sa[N], rk[N], height[N];
    int st[N][LOG], lg[N];
    char s[N];
    void init(char A[]) {
        n = strlen(A);
        for(int i = 0; i < n; i++) s[i] = A[i];
        m = 256;
    }
    void build() {
        for(int i = 0; i < m; i++) buc[i] = 0;
        for(int i = 0; i < n; i++) buc[x[i] = s[i]]++;
        for(int i = 1; i < m; i++) buc[i] += buc[i - 1];
        for(int i = n - 1; i >= 0; i--) sa[--buc[x[i]]] = i;
        for(int k = 1; k <= n; k <<= 1) {
            int p = 0;
            for(int i = n - 1; i >= n - k; i--) y[p++] = i;
            for(int i = 0; i < n; i++) if (sa[i] >= k) y[p++] = sa[i] - k;
            for(int i = 0; i < m; i++) buc[i] = 0;
            for(int i = 0; i < n; i++) buc[x[y[i]]]++;
            for(int i = 1; i < m; i++) buc[i] += buc[i - 1];
            for(int i = n - 1; i >= 0; i--) sa[--buc[x[y[i]]]] = y[i];
            swap(x, y);
            p = 1; x[sa[0]] = 0;
            for (int i = 1; i < n; i++) {
                if(y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k]) {
                    x[sa[i]] = p - 1;
                }
                else x[sa[i]] = p++;
            }
            if (p >= n) break;
            m = p;
        }
        for(int i = 0; i < n; i++) rk[sa[i]] = i;
        int k = 0;
        for(int i = 0; i < n; i++) {
            if(rk[i] == 0) {
                height[0] = 0;
                continue;
            }
            if(k) k--;
            int j = sa[rk[i] - 1];
            while(s[i + k] == s[j + k] && i + k < n && j + k < n) k++;
            height[rk[i]] = k;
        }
        for(int i = 1; i <= n - 1; i++) st[i][0] = height[i], lg[i] = log(i) / log(2);
        for(int j = 1; (1 << j) <= n - 1; j++) {
            for(int i = 1; i + (1 << j) <= n; i++) {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int lcp(int x, int y) {
        if(x == y) return n - x;
        x = rk[x], y = rk[y];
        if(x > y) swap(x, y);
        x++;
        int t = lg[y - x + 1];
        return min(st[x][t], st[y - (1 << t) + 1][t]);
    }
};

