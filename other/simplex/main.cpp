const long double eps = 1e-9;
const int MAXN = 10100; // 最大约束个数
const int MAXM = 1010; // 最大变量个数
const long double inf = 1e100;

int next[MAXM]; long double a[MAXN][MAXM], b[MAXM];
int where[MAXM + MAXN]; // where[i] 表示原来第 i 个变量现在在哪个位置
int pos[MAXM + MAXN]; // pos[i] 表示第 i 个位置现在是哪个变量

int n, m;

void pivot(int r, int c) {
	int &x = pos[r + m], &y = pos[c];
	swap(where[x], where[y]); swap(x, y);
	long double t = -a[r][c]; a[r][c] = -1; 
	int last = MAXM - 1;
	for (int i = 0; i <= m; i++) {
		a[r][i] /= t;
		if (fabs(a[r][i]) > eps) next[last] = i, last = i;
	}
	next[last] = -1;
	for (int i = 0; i <= n; i++) if (i != r && fabs(a[i][c]) > eps) {
		t = a[i][c], a[i][c] = 0;
		for (int j = next[MAXM - 1]; j != -1; j = next[j])
			a[i][j] += a[r][j] * t;
	}
}

long double get(void) {
	long double best, t; int r, c;
	for (;;) {
		r = c = -1, best = -inf;
		for (int i = 1; i <= m; i++) if (a[0][i] > eps) {c = i; break;}
		if (c == -1) return a[0][0]; // 从这里返回表示找到了最优解
		for (int i = 1; i <= n; i++) if (a[i][c] < -eps && (t = a[i][0] / a[i][c]) > best) best = t, r = i;
		if (r == -1) return inf; // 从这里返回表示最优解为inf
		pivot(r, c);
	}
}

int init(void) {
	for (int i = 1; i <= m + n + 1; i++) where[i] = i, pos[i] = i;
	long double best = -eps, r = 0;
	for (int i = 1; i <= n; i++) if (a[i][0] < best) best = a[i][0], r = i;
	if (!r) return 1;
	for (int i = 0; i <= m; i++) b[i] = a[0][i], a[0][i] = 0; a[0][m + 1] = -1;
	for (int i = 1; i <= n; i++) a[i][m + 1] = 1; m++;
	pivot(r, m);
	long double tmp = get();
	if (tmp < -eps) return 0; else {
		if (where[m] > m) {
			for (int i = 1; i <= m; i++) if (fabs(a[where[m] - m][i]) > eps) {
				pivot(where[m] - m, i);
				break;
			}
		}
		for (int i = 0; i <= n; i++) a[i][where[m]] = 0;
		for (int i = 0; i <= m; i++) a[0][i] = 0; a[0][0] = b[0];
		for (int i = 1; i <= m; i++) if (where[i] > m) {
			int t = where[i] - m;
			for (int j = 0; j <= m; j++) a[0][j] += b[i] * a[t][j];
		} else a[0][where[i]] += b[i];
		return 1;
	}
}

long double process(void) {
	if (!init()) return -inf;
	return get();
}

