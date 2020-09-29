#include <map>
#include <vector> 
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
const int INF = 1000000007;
int underCons[10][205];
int dx[2][3] = {{-1,0,0}, {1,0,0}};
int dy[2][3] = {{-1,-1,1}, {1,-1,1}};
int dfs(int s, int xa, int ya, int xb, int yb, int step,
    map<pii, int>& painted, int is_A_end, int is_B_end) {
    int tx, ty, ok = 0;
    if(is_A_end && is_B_end) {
        int c[3] = {0};
        for(int x=1; x<=s; ++x) {
            for(int y=1; y<=2*x-1; ++y) {
                if(underCons[x][y]) continue;
                ++c[painted[make_pair(x, y)]];
            }
        }
        return c[1]-c[2];
    }
    int mmin = INF, mmax = -INF;
    if(step%2) { // A
        if(is_A_end) {
            mmax = max(mmax, dfs(s, xa, ya, xb, yb, step^1, painted, is_A_end, is_B_end));
        } else {
            for(int i=0; i<3; ++i) {
                tx = xa + dx[ya%2][i];
                ty = ya + dy[ya%2][i];
                if(!(tx>=1&&tx<=s&&ty>=1&&ty<=2*tx-1)) continue;
                if(underCons[tx][ty] || painted[make_pair(tx, ty)]) continue;
                ok = 1;
                painted[make_pair(tx, ty)] = 1;
                mmax = max(mmax, dfs(s, tx, ty, xb, yb, step^1, painted, 0, is_B_end));
                painted[make_pair(tx, ty)] = 0;
            }
            if(!ok) {
                mmax = max(mmax, dfs(s, xa, ya, xb, yb, step^1, painted, 1, is_B_end));
            }
        }
        return mmax;
    } else { // B
        if(is_B_end) {
            mmin = min(mmin, dfs(s, xa, ya, xb, yb, step^1, painted, is_A_end, is_B_end));
        } else {
            for(int i=0; i<3; ++i) {
                tx = xb + dx[yb%2][i];
                ty = yb + dy[yb%2][i];
                if(!(tx>=1&&tx<=s&&ty>=1&&ty<=2*tx-1)) continue;
                if(underCons[tx][ty] || painted[make_pair(tx, ty)]) continue;
                ok = 1;
                painted[make_pair(tx, ty)] = 2;
                mmin = min(mmin, dfs(s, xa, ya, tx, ty, step+1, painted, is_A_end, 0));
                painted[make_pair(tx, ty)] = 0;
            }
            if(!ok) {
                mmin = min(mmin, dfs(s, xa, ya, xb, yb, step+1, painted, is_A_end, 1));
            }
        }
        return mmin;
    }
}
int main() {
    int T; scanf("%d", &T);
    int cas = 0;
    int x, y;
    int s, ra, pa, rb, pb, c;
    map<pii, int> painted;
    while(T--) {
        scanf("%d%d%d%d%d%d", &s, &ra, &pa, &rb, &pb, &c);
        memset(underCons, 0, sizeof underCons);
        for(int i=0; i<c; ++i) {
            scanf("%d%d", &x, &y);
            underCons[x][y] = 1;
        }
        painted.clear();
        painted[make_pair(ra, pa)] = 1;
        painted[make_pair(rb, pb)] = 2;
        int ans = dfs(s, ra, pa, rb, pb, 1, painted, 0, 0);
        printf("Case #%d: %d\n", ++cas, ans);
    }
    return 0;
}