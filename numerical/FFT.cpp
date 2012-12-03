
#include <cstdio>
#include <algorithm>
#include <complex>
#include <cmath>

#define REP(i,l,r) for(int i = l; i <= r; i++)
#define pi 3.14159265358979323846

namespace Solve {
	const int MAXN = 65536 << 1;

	typedef std::complex<long double> ii;

	long long a[MAXN], b[MAXN];int l, t, n, pow[4];
	ii DATA[MAXN << 1], *e = DATA + MAXN, X[MAXN], Y[MAXN], T[MAXN];
	char ch[MAXN];

	char c1[300010], c2[300010];

	inline void Input(void) {
		pow[0] = 1, pow[1] = 10, pow[2] = 100, pow[3] = 1000;
		n = Scan(ch); std::reverse(ch, ch + n);
		REP(i, 0, n - 1) l = i / 4, a[l] += (ch[i] - 48) * pow[i % 4];Scan(ch); std::reverse(ch, ch + n);
		REP(i, 0, n - 1) l = i / 4, b[l] += (ch[i] - 48) * pow[i % 4];
		n = n / 4 + 1; while (n & (n - 1)) ++n;
		n *= 2;
	}

	inline void Init(void) {
		e[0] = ii(1, 0);
		for(int i = 1; i < MAXN; i++) e[i] = ii(cos(pi * i * 2 / MAXN), sin(pi * i * 2 / MAXN));
		REP(i, 1, n - 1) e[-i] = e[n - i];
	}

	inline void Dft(ii *a, ii *w, int L, int f) {
		register ii t; int d = MAXN / L * f;
		for (int n = L, m; m = n >> 1, m >= 1; n = m, d <<= 1)
			for (int i = 0, x = 0; i < m; i++, x += d)
				for (int j = i; j < L; j += n)
					t = a[j] - a[j + m], a[j] += a[j + m], a[j + m] = t * e[x];
		for (int i = 0, j = 1; j < L - 1; j++) {
			for (int k = L >> 1; k > (i ^= k); k >>= 1); if (j < i) swap(a[j], a[i]);
		}
	}

	inline void Mul(void) {
		REP(i, 0, n - 1) X[i] = ii(a[i], 0), Y[i] = ii(b[i], 0);
		Dft(X, T, n, 1); Dft(Y, T, n, 1);
		REP(i, 0, n - 1) X[i] *= Y[i];
		Dft(X, T, n, -1);
		REP(i, 0, n - 1) a[i] = (long long)(X[i].real() / n + 0.5);
		int L = 0;
		REP(i, 0, n - 1) a[i + 1] += a[i] / 10000, a[i] %= 10000, L = a[i] ? i : L;
		printf("%lld", a[L]);
		for (int i = L - 1; i >= 0; --i) {
			if (a[i] < 10) putchar('0');
			if (a[i] < 100) putchar('0');
			if (a[i] < 1000) putchar('0');
			printf("%lld", a[i]);
		}
		puts("");
	}

	inline void solve(void) {
		Input();
		Init();
		Mul();
	
	}
}

int main(void) {
	freopen("in", "r", stdin);
	Solve::solve();
	return 0;
}
