```cpp
constexpr int MAXLEN = 100005, K = 26;

int sa_sz, last, smaxl[MAXLEN*2], sminl[MAXLEN*2],
len[MAXLEN*2], flink[MAXLEN*2], cnt[MAXLEN*2];
array<array<int, 26>, MAXLEN*2> go;

void sa_init() {
    len[0] = 0;
    flink[0] = -1;
    sa_sz = 1;
    last = 0;
    for (auto &row : go) {
        row.fill(-1);
    }
    memset(cnt, 0, sizeof cnt);
}

void sa_extend(char _c) {
    int c = _c - 'a';
    int cur = sa_sz++;
    len[cur] = len[last] + 1;
    cnt[cur] = 1;
    int p = last;
    while (p != -1 && go[p][c] == -1) {
        go[p][c] = cur;
        p = flink[p];
    }
    if (p == -1) {
        flink[cur] = 0;
    } else {
        int q = go[p][c];
        if (len[p] + 1 == len[q]) {
            flink[cur] = q;
        } else {
            int clone = sa_sz++;
            len[clone] = len[p] + 1;
            go[clone] = go[q];
            flink[clone] = flink[q];
            while (p != -1 && go[p][c] == q) {
                go[p][c] = clone;
                p = flink[p];
            }
            flink[q] = flink[cur] = clone;
        }
    }
    last = cur;
}

void precompute_cnt() {
    vi freq(sa_sz+1, 0), sorted_by_len(sa_sz);
    rep(i, 0, sa_sz) ++freq[len[i]];
    rep(i, 1, sa_sz+1) freq[i] += freq[i-1];
    rep(i, 0, sa_sz) {
        sorted_by_len[sa_sz-freq[i]];
        --freq[i];
    }
    rep(i, 0, sa_sz-1) cnt[flink[i]] += cnt[i];
}
```