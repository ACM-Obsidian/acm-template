#include <cstdlib>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
void ext_gcd(int a, int b, int &x, int &y) {
	if (!b) x = 1, y = 0;
	else if (!a) x = 1, y = -1;
	else if (a > b) ext_gcd(a % b, b, x, y), y += a / b * x;
	else ext_gcd(a, b % a, x, y), x += b / a * y;
}
long long flsum_t (long long a, long long b, long long c, long long n) {
	if (n < 0) return 0;
	if (c < 0) a = -a, b = -b, c = -c;
	n++; long long res = 0;
	if (a < 0 || a >= c) {
		long long ra = (a % c + c) % c;
		long long k = (a - ra) / c;
		res += k * n * (n - 1) / 2;
		a = ra;
	}
	if (b < 0 || b >= c) {
		long long rb = (b % c + c) % c;
		long long k = (b - rb) / c;
		res += k * n;
		b = rb;
	}
	if (a * n + b < c) return res;
	else return res + flsum_t(c, (a * n + b) % c, a, (a * n + b) / c - 1);
}
long long flsum (long long a, long long b, long long c, long long st, long long ed) {
	return flsum_t(a, b, c, ed) - flsum_t(a, b, c, st - 1);
}
int power(int n, int k, int r) {
	int t = n, s = 1;
	for (; k; k >>= 1, t = 1LL * t * t % r)
		if (k & 1) s = 1LL * s * t % r;
	return s;
}
int millerrabin(int x, int tester) {
	int k = x-1; for (; !(k & 1); k >>= 1);
	int y = power(tester, k, x);
	if (y == 1) return 1;
	for (; k < x-1; k <<= 1, y = 1LL * y * y % x)
		if (y == x-1) return 1;
	return 0;
}
int isprime(int x) {
	if (x == 2 || x == 7 || x == 61) return 1;
	return millerrabin(x, 2) && millerrabin(x, 7) && millerrabin(x, 61);
}
int rho_f(int x, int c, int p) {
	return (1LL * x * x + c) % p;
}
int rho(int n) {
	int c = rand() % (n-1) + 1, x = 2, y = x, d = 1;
	while (d == 1) {
		x = rho_f(x, c, n);
		y = rho_f(rho_f(y, c, n), c, n);
		d = std::__gcd(y > x ? y-x : x-y, n);
	}
	return d;
}
void factor(int n, std::vector<int> &res) {
	if (n == 1) return;
	else if (isprime(n)) res.push_back(n);
	else if (n == 4) res.push_back(2), res.push_back(2);
	else {
		int d;
		while ((d = rho(n)) == n);
		factor(d, res), factor(n / d, res);
	}
}
int ind(int a, int b, int m) {
	a %= m, b %= m;
	std::map<int, int> hash;
	int r = (int)(sqrt(m)), k = 1;
	if (r * r < m) r++;
	for (int i = 0; i < r; i++, k = 1LL * k * a % m)
		if (hash.find(k) == hash.end())
			hash.insert(std::make_pair(k, i));
	int s = 1;
	std::map<int, int>::iterator it;
	for (int i = 0; i < r; i++, s = 1LL * s * k % m) {
		int x, y, t;
		ext_gcd(s, m, x, y);
		t = 1LL * b * x % m;
		if ((it = hash.find(t)) != hash.end())
			return i * r + it->second;
	}
}
void prepare_inv(int *inv, int p) {
	inv[1] = 1;
	for (int i = 2; i < p; i++)
		inv[i] = 1LL * inv[p%i] * (p - p/i) % p;
}
