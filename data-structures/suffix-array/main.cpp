// string is 1-base, sa is 1-base
int w[MAXM];

inline void Sort(int a[], int ret[], int n, int m = MAXM - 1) {
	for (int i = 0; i <= m; i++) w[i] = 0;
	for (int i = 1; i <= n; i++) w[a[i]]++;
	for (int i = 1; i <= m; i++) w[i] += w[i - 1];
	for (int i = n; i >= 1; i--) ret[w[a[i]]--] = i;
}

int wa[MAXN], wb[MAXN], tmp[MAXN];

inline void getSA(int ch[], int sa[], int n) {
	int *x = wa, *y = wb;
	for (int i = 1; i <= n; i++) x[i] = ch[i];
	Sort(ch, sa, n);
	for (int j = 1, p = 1, m = MAXN - 1; p < n; m = p, j <<= 1) {
		p = 0;
		for (int i = n - j + 1; i <= n; i++) y[++p] = i;
		for (int i = 1; i <= n; i++) if (sa[i] > j) y[++p] = sa[i] - j;
		for (int i = 1; i <= n; i++) tmp[i] = x[y[i]];
		Sort(tmp, sa, n, m);
		for (int i = 1; i <= n; i++) sa[i] = y[sa[i]];
		swap(x, y); x[sa[1]] = p = 1;
		for (int i = 2; i <= n; i++) {
			if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + j] == y[sa[i - 1] + j]) x[sa[i]] = p;
			else x[sa[i]] = ++p;
		}
	}
	sa[0] = n + 1; // for calculate height.
}

int rank[MAXN];

inline void getHeight(int ch[], int sa[], int height[], int n) {
	for (int i = 1; i <= n; i++) rank[sa[i]] = i;
	for (int i = 1, t = 0; i <= n; i++) {
		if (t > 0) t--;
		while (ch[i + t] == ch[sa[rank[i] - 1] + t]) t++;
		height[rank[i]] = t;
	}
}

void Clear(void) {
}

