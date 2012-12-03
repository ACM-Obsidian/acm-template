#include <cstdio>
#define format64 "%lld"
struct point {
	int x, y;
}l1, r1, l2, r2;
point operator - (point x, point y) {
	point z; z.x = x.x - y.x, z.y = x.y - y.y;
	return z;
}
int operator == (point x, point y) {
	return x.x == y.x && x.y == y.y;
}
long long operator ^ (point x, point y) {
	return (long long) x.x * y.y - (long long) x.y * y.x;
}
int test(point x, point l, point r) {
	if (l.x > r.x || l.x == r.x && l.y > r.y) {
		point t; t = l, l = r, r = t;
	}
	if (l.x == r.x) {
		int t = l.x; l.x = l.y, l.y = t;
		t = r.x, r.x = r.y, r.y = t;
		t = x.x, x.x = x.y, x.y = t;
	}
	if (x.x < l.x) return -2;
	else if (x.x == l.x) return -1;
	else if (x.x == r.x) return 1;
	else if (x.x > r.x) return 2;
	else return 0;
} 
struct fraction {
	long long n, d;
	void simplize() {
		if (d < 0) n = -n, d = -d;
		long long x = n, y = d, t;
		if (!x) return;
		if (x < 0) x = -x;
		for (; y; t = x, x = y, y = t % y) ;
		n /= x, d /= x;
	}
	void print() {
		if (d == 1 || !n) printf(format64, n);
		else printf(format64"/"format64, n, d);
	}
};
struct point2 {
	fraction x, y;
	point2& operator = (point m) {
		x.n = m.x, x.d = 1;
		y.n = m.y, y.d = 1;
		return *this;
	}
}ans;int test_intersection(point l1, point r1, point l2, point r2, point2 &ans) {
	if (l1 == r1 && l2 == r2)
		if (l1 == l2) return ans = l1, 1; else return 0;
	else if (l1 == r1) {
		if ((l1 - l2) ^ (r2 - l2)) return 0;
		int f = test(l1, l2, r2);
		if (f == -2 || f == 2) return 0;
		else return ans = l1, 1;
	} else if (l2 == r2) {
		if ((l2 - l1) ^ (r1 - l1)) return 0;
		int f = test(l2, l1, r1);
		if (f == -2 || f == 2) return 0;
		else return ans = l2, 1;
	}
	point k1 = r1 - l1, k2 = r2 - l2;
	long long x = k1 ^ k2, y = (l2 - l1) ^ k1;
	if (!x && !y) {
		int f1 = test(l2, l1, r1), f2 = test(r2, l1, r1);
		if (f1 < 0 && f2 > 0 || f1 > 0 && f2 < 0 || !f1 || !f2) return 2;
		else if (f1 == -2 && f2 == -2 || f1 == 2 && f2 == 2) return 0;
		else if (f1 == -1 || f1 == 1) return ans = l2, 1;
		else return ans = r2, 1;
	} else if (!x) return 0;
	if (x < 0 && (y < x || y > 0)) return 0;
	if (x > 0 && (y < 0 || y > x)) return 0;
	y = (l2 - l1) ^ k2;
	if (x < 0 && (y < x || y > 0)) return 0;
	if (x > 0 && (y < 0 || y > x)) return 0;
	fraction tmp; tmp.n = y * k1.x + x * l1.x, tmp.d = x; tmp.simplize();
	ans.x = tmp;
	tmp.n = y * k1.y + x * l1.y, tmp.d = x; tmp.simplize();
	ans.y = tmp;
	return 1;
}
int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d%d%d%d%d%d%d%d", &l1.x, &l1.y, &r1.x, &r1.y, &l2.x, &l2.y, &r2.x, &r2.y);
		int m = test_intersection(l1, r1, l2, r2, ans);
		if (!m) printf("0\n");
		else if (m == 2) printf("INF\n");
		else printf("1\n"), ans.x.print(), printf(" "), ans.y.print(), printf("\n");
	}
	return 0;
}
