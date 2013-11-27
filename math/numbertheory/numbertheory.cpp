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
/* solve a^x = b (mod m) */
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
