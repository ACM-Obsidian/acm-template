#include <stdio.h>
#include <ctype.h>
#pragma GCC optimize ("O3")
#include <math.h>
#define REP(i,l,n) for(i = l; i <= n; i++)
long double zero = 1e-6, eps = 1e-6;
int x[100010], y[100010];int i, j, n, N, l = 1, r, m = 5; long double a[50010][6];
void ins(long long x1, long long y1, long long x2, long long y2) {
	++N; a[N][0] = x2*y1-x1*y2 - eps, a[N][3] = -(a[N][1] = y2 - y1), a[N][4] = -(a[N][2] = x1 - x2), a[N][5] = 1;
}
void nzk(int r, int c) {
	long double t = -a[r][c]; a[r][c] = -1;
	REP(i, 0, m) a[r][i] /= t;
	REP(i, 0, N) if (i != r && fabs(a[i][c]) > zero) {
		t = a[i][c], a[i][c] = 0;
		REP(j, 0, m) a[i][j] += a[r][j] * t;
	}
}
int debug = 0;
long double gao(void) {
	int r = 0, c; long double best = 1e100, t;
	REP(i, 1, N) if (a[i][0] < best) best = a[i][0], r = i; if (!r) return 0; nzk(r, m);
	int tmp = 0;
	for(;;) { c = r = -1, best = -1e100; tmp++; if (tmp > debug) debug = tmp;
		if (a[0][0] >= -zero) return a[0][0];
		REP(i, 1, m) if (a[0][i] > zero) {c = i; break;}
		if (c < 0) return a[0][0];
		REP(i, 1, N) if (a[i][c] < -zero && (t = a[i][0] / a[i][c]) > best) best = t, r = i;
		if (r < 0) return a[0][0]; nzk(r, c);
	}
}
int ScanInt(void) {
	int r = 0, c, d;
	while (!isdigit(c = getchar()) && c != '-');
	if (c != '-') r = c - '0'; d = c;
	while ( isdigit(c = getchar())) r = r * 10 + c - '0';
	return d=='-'?-r:r;
}
int main(void) {
//	freopen("in", "r", stdin);
	scanf("%d", &n); r = n / 2, l = 1;
	if (n <= 100) zero = 1e-7; else zero = 1e-6;
	REP(i,1,n) x[i] = ScanInt(), y[i] = ScanInt(), x[i + n] = x[i], y[i + n] = y[i];
	while (l <= r) { REP(i, 0, m-1) a[0][i] = 0; a[0][m] = -1;
		int mid = (l + r) >> 1; N = 0;
		REP(i, 1, n) ins(x[i], y[i], x[i + mid + 1], y[i + mid + 1]);
		if (gao()>-zero) l = mid + 1; else r = mid - 1;
	}
	printf("%d\n", l);
	return 0;
}
