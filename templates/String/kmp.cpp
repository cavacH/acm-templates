const int N = 100005;

char s[N], t[N]; // t occur in s
int fail[N]; // fail ptr of t
int sl, tl; // length

void build() {
    fail[0] = -1;
    fail[1] = 0;
    for(int i = 2; i <= tl; i++) {
        int j = fail[i - 1];
        while(j && t[i] != t[j + 1]) j = fail[j];
        fail[i] = (t[i] == t[j + 1] ? j + 1 : 0); 
    }
}

void match() {
    int ps = 1, pt = 1;
    while(ps <= sl) {
        if(pt == 0 || s[ps] == t[pt]) {
            ps++;
            pt++;
        }
        else pt = fail[pt - 1] + 1;
        if(pt > tl) {
            // match
            pt = fail[pt - 1] + 1;
        }
    }
}