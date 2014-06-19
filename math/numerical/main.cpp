#include <cmath>
#include <algorithm>
#include <complex>
const double pi = 3.14159265358979324;
typedef double (*__F) (double);
double area(double x, double y, double fl, double fmid, double fr) {
	return (fl + 4 * fmid + fr) * (y - x) / 6;
}
double area_simpson_solve(__F f, double x, double mid, double y, double fl, double fmid, double fr, double pre, double zero) {
	double lmid = (x + mid) / 2, rmid = (mid + y) / 2;
	double flmid = f(lmid), frmid = f(rmid);
	double al = area(x, mid, fl, flmid, fmid), ar = area(mid, y, fmid, frmid, fr);
	if (fabs(al + ar - pre) < zero) return al + ar;
	else return area_simpson_solve(f, x, lmid, mid, fl, flmid, fmid, al, zero) + area_simpson_solve(f, mid, rmid, y, fmid, frmid, fr, ar, zero);
}
double area_simpson(__F f, double x, double y, double zero = 1e-10) {
	double mid = (x + y) / 2, fl = f(x), fmid = f(mid), fr = f(y);
	return area_simpson_solve(f, x, mid, y, fl, fmid, fr, area(x, y, fl, fmid, fr), zero);
}
typedef std::complex<double> complex;
void fft_prepare(int maxn, complex *&e) {
	e = new complex[2 * maxn - 1];
	e += maxn - 1;
	e[0] = complex(1, 0);
	for (int i = 1; i < maxn; i <<= 1)
		e[i] = complex(cos(2 * pi * i / maxn), sin(2 * pi * i / maxn));
	for (int i = 3; i < maxn; i++)
		if ((i & -i) != i) e[i] = e[i - (i & -i)] * e[i & -i];
	for (int i = 1; i < maxn; i++) e[-i] = e[maxn - i];
}
/* f = 1: dft; f = -1: idft */
void dft(complex *a, int N, int f, complex *e, int maxn) {
	int d = maxn / N * f;
	complex x;
	for (int n = N, m; m = n / 2, m >= 1; n = m, d *= 2)
		for (int i = 0; i < m; i++)
			for (int j = i; j < N; j += n)
				x = a[j] - a[j+m], a[j] += a[j+m], a[j+m] = x * e[d * i];
	for (int i = 0, j = 1; j < N - 1; j++) {
		for (int k = N / 2; k > (i ^= k); k /= 2);
		if (j < i) std::swap(a[i], a[j]);
	}
}
