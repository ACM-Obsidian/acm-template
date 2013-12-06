#include <cstdio>
#include <cstring>
#include <algorithm>
namespace Solve {
    const long MAXN = 205;
    const long inf = 10000000;
    long a[MAXN][MAXN] = {0}, r[MAXN] = {0};
    long x[MAXN] = {0}, y[MAXN] = {0}, stack[MAXN] = {0};
    bool visx[MAXN] = {0}, visy[MAXN] = {0};
    long n;
 
    #define abs(x) ((x)>0?(-(x)):(x))
    #define rep(i,n) for (long i = 1; i <= n; i++)
    #define max(x, y) ((x)>(y)?(x):(y))
    #define min(x, y) ((x)<(y)?(x):(y))
    void Input(void) {
        scanf("%ld", &n);
        rep(i,n)rep(j,n)a[i][j] = -inf;
        rep(i,n){
            long m, l, r, k;
            scanf("%ld %ld %ld %ld", &m, &l, &r, &k);
            for (long j = l; j <= r; j++) a[i][j] = abs(m - j) * k;
         }
    }
    long A = 0;
    bool find(long u) {
        visx[u] = true;
        rep(i, n) if (!visy[i]) {
            long t = x[u] + y[i] - a[u][i];
            if (!t) {
                visy[i] = true;
                if (!r[i] || find(r[i])) {
                    r[i] = u;
                    return true;
                }
            }else stack[i] = min(t, stack[i]);
        }
        return false;
    }
    void Work(void) {
        Input();
        rep(i ,n) rep(j, n) x[i] = max(x[i], a[i][j]);
        rep(i, n) {
            rep(k, n)stack[k] = inf;
            while (true) {
                memset(visy, 0, sizeof visy); memset(visx, 0, sizeof visx);
                if (find(i)) break;
                long t = inf;
                rep(k, n) if (!visy[k]) t = min(t, stack[k]);
                rep(k, n) if (visx[k]) x[k] -= t;
                rep(k, n) if (visy[k]) y[k] += t; else stack[k] -= t;
            }
        }
        long A = 0, N = 0;
        rep(i, n){ A -= a[r[i]][i];
            if (a[r[i]][i] == -inf) {puts("NIE");return;}
        }
        printf("%ld\n", A);
    }
}
int main(int argc, char** argv) {
    #ifdef Debug
        freopen("1.in", "r", stdin);
    #endif
    Solve::Work();
    return 0;
}
