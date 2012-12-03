#include <cstdio>
#include <cctype>
#include <algorithm>
#define REP(i,l,r) for(int i = l; i <= r; i++)

using namespace std;

const int MAXN = 500005;
int Mod = 0;

inline int ScanInt(void) {
	int r = 0, c, d;
	while (!isdigit(c = getchar()) && c != '-');
	if (c != '-') r = c - '0'; d = c;
	while ( isdigit(c = getchar())) r = r * 10 + c - '0';
	return d=='-'?-r:r;
}

inline int mul_mod(int a,int b, int MO){
	int ret;
	__asm__ __volatile__ ("\tmull %%ebx\n\tdivl %%ecx\n"
			:"=d"(ret):"a"(a),"b"(b),"c"(MO));
	return ret;
}

inline int Pow(int a, int n) {
	int ret = 1;
	while (n) {
		if (n&1) ret = mul_mod(ret, a, Mod);
		n >>= 1;
		a = mul_mod(a, a, Mod);
	}
	return ret;
}

int n, a[MAXN], b[MAXN], DATA[MAXN << 1], *e = DATA + MAXN, w[MAXN], C;

inline void Dft(int a[], int w[], int n, int f) {
	if (n == 1) return;
	int k = 2, d = ::n / n * f; while (n % k != 0) ++k; int Len = n / k;
	REP(i, 0, n - 1) w[Len * (i % k) + i / k] = a[i];
	for (int i = 0; i < n; i += Len) Dft(w + i, a + i, Len, f);
	for (int i = 0; i < n; i++) {
		a[i] = w[i % Len];
		for (int j = 1; j * Len < n; j++) {
			a[i] += mul_mod(e[j * i * d % ::n], w[j * Len + i % Len], Mod);
			if (a[i] >= Mod) a[i] -= Mod;
		}
	}
}

int main(void) {
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	n = ScanInt(), C = ScanInt(); REP(i, 0, n - 1) a[i] = ScanInt(); REP(i, 0, n - 1) b[i] = ScanInt(); Mod = n + 1;
	e[1] = e[0] = 1;
	while (++e[1]) {
		bool ok = true;
		REP(i, 2, n - 1) {e[i] = mul_mod(e[i - 1], e[1], Mod); if (e[i] == 1) {ok = false; break;}}
		if (ok) break;
	}
	REP(i, 1, n - 1) e[-i] = e[n - i];
	Dft(a, w, n, 1); Dft(b, w, n, 1);
	REP(i, 0, n - 1) b[i] = Pow(b[i], C), a[i] = mul_mod(a[i], b[i], Mod);
	Dft(a, w, n, -1);
	int g = Pow(n, n - 1);
	REP(i, 0, n - 1) printf("%d\n", mul_mod(a[i], g, Mod));
	return 0;
}

