
int euler[N];

// euler[i] = count{j | 1 <= j < i && gcd(i, j) == 1}

void init() {
    for(int i = 2; i < N; i++) euler[i] = i;
    for(int i = 2; i < N; i++) {
        if(euler[i] == i) {
            for(int j = i; j < N; j += i) euler[j] = euler[j] / i * (i - 1);
        }
    }
}