#include <vector> 
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
int main() {
    int T; scanf("%d", &T);
    int cas = 0;
    int N, K, r;
    while(T--) {
        scanf("%d%d", &N, &K);
        vector<pii> intervals(N);
        for(int i=0; i<N; ++i) {
            scanf("%d%d", &intervals[i].first, &intervals[i].second);
            ++intervals[i].first;
        }
        sort(intervals.begin(), intervals.end());
        int ans = 0, r = -1, tmp;
        for(int i=0; i<N; ++i) {
            if(intervals[i].first > r) {
                ++ans;
                r = intervals[i].first+K-1;
            }
                
            if(intervals[i].second > r) {
                tmp = intervals[i].second-r;
                ans += tmp/K;
                if(tmp%K) ++ans;
                r += (tmp/K+(tmp%K?1:0))*K; 
            }
        }
        printf("Case #%d: %d\n", ++cas, ans);
    }
    return 0;
}