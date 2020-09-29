#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int a[100005];
typedef pair<int, int> pii;
pii p[100005];
bool cmp(pii x, pii y) {
    if(x.first == y.first)
        return x.second < y.second;
    return x.first < y.first;
}
int main() {
    int T; scanf("%d", &T);
    int cas = 0;
    int N, X, t;
    while(T--) {
        scanf("%d%d", &N, &X);
        for(int i=0; i<N; ++i) {
            scanf("%d", &t);
            p[i].first = t/X + (t%X?1:0);
            p[i].second = i + 1;
        }
        sort(p, p+N, cmp);
        printf("Case #%d:", ++cas);
        for(int i=0; i<N; ++i) {
            printf(" %d", p[i].second);
        }
        printf("\n");
    }
    return 0;
}