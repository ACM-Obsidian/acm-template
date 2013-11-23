#include <cstdio>
#include <cmath>
#include <vector>
#include <deque>
#include <algorithm>
const double eps = 1e-13;
const double pi = 3.14159265358979324;

struct point2 {
	double x, y;
	point2& operator += (point2 a) {
		x += a.x, y += a.y;
		return *this;
	}
	point2& operator -= (point2 a) {
		x -= a.x, y -= a.y;
		return *this;
	}
	point2& operator *= (double a) {
		x *= a, y *= a;
		return *this;
	}
	point2& operator /= (double a) {
		x /= a, y /= a;
		return *this;
	}
};
point2 operator + (point2 a, point2 b) {
	point2 c; c = a; c += b; return c;
}
point2 operator - (point2 a, point2 b) {
	point2 c; c = a; c -= b; return c;
}
point2 operator * (point2 a, double b) {
	point2 c; c = a; c *= b; return c;
}
point2 operator * (double a, point2 b) {
	point2 c; c = b; c *= a; return c;
}
point2 operator / (point2 a, double b) {
	point2 c; c = a; c /= b; return c;
}
double operator * (point2 a, point2 b) {
	return a.x * b.x + a.y * b.y;
}
double operator % (point2 a, point2 b) {
	return a.x * b.y - a.y * b.x;
}
double dis(point2 a) {
	return sqrt(a.x * a.x + a.y * a.y);
}
double arg(point2 a) {
	return atan2(a.y, a.x);
}
point2 rotate(point2 a, double th) {
	point2 b;
	b.x = a.x * cos(th) - a.y * sin(th);
	b.y = a.x * sin(th) + a.y * cos(th);
	return b;
}
int parallel(point2 a, point2 b) {
	return a * a < eps * eps || b * b < eps * eps || (a % b) * (a % b) / ((a * a) * (b * b)) < eps * eps;
}
int perpend(point2 a, point2 b) {
	return a * a < eps * eps || b * b < eps * eps || (a * b) * (a * b) / ((a * a) * (b * b)) < eps * eps;
}
struct line2 {
	point2 a, s;
};
struct circle2 {
	point2 a;
	double r;
};
double point_line_dis(point2 a, line2 b, point2 *res = NULL) {
	point2 p;
	p = b.a + ((a - b.a) * b.s) / (b.s * b.s) * b.s;
	if (res != NULL) *res = p;
	return dis(a - p);
}
int line_line_cross(line2 a, line2 b, point2 *res) {
	if (parallel(a.s, b.s))
		if (parallel(b.a - a.a, a.s))
			return -1;
		else
			return 0;
	double k1 = (b.a - a.a) % b.s / (a.s % b.s);
	if (res != NULL) *res = a.a + k1 * a.s;
	return 1;
}
int line_circle_cross(line2 a, circle2 b, point2 *res1 = NULL, point2 *res2 = NULL) {
	point2 p;
	double d = point_line_dis(b.a, a, &p);
	if (d / b.r > 1 + eps)
		return 0;
	else if (d / b.r > 1 - eps) {
		if (res1 != NULL) *res1 = p;
		return 1;
	} else {
		d = sqrt(b.r * b.r - d * d) / dis(a.s);
		if (res1 != NULL) *res1 = p + d * a.s;
		if (res2 != NULL) *res2 = p - d * a.s;
		return 2;
	}
}
int circle_circle_cross(circle2 a, circle2 b, point2 *res1 = NULL, point2 *res2 = NULL) {
	double d = dis(a.a - b.a);
	point2 u = (b.a - a.a) / d;
	if (d / (a.r + b.r) > 1 + eps)
		return 0;
	else if (d / (a.r + b.r) > 1 - eps) {
		if (res1 != NULL) *res1 = a.a + u * a.r;
		return 1;
	} else if ((d - fabs(a.r - b.r)) / (a.r + b.r) > eps) {
		double th = acos((a.r * a.r + d * d - b.r * b.r) / (2 * a.r * d));
		if (res1 != NULL) *res1 = a.a + rotate(u * a.r, th);
		if (res2 != NULL) *res2 = a.a + rotate(u * a.r, -th);
		return 2;
	} else if ((d - fabs(a.r - b.r)) / (a.r + b.r) > -eps) {
		if (a.r / b.r < 1 - eps) {
			if (res1 != NULL) *res1 = b.a - u * b.r;
			return 1;
		} else if (a.r / b.r > 1 + eps) {
			if (res1 != NULL) *res1 = a.a + u * a.r;
			return 1;
		} else return -1;
	} else
		return 0;
}
int point_circle_tangent(point2 a, circle2 b, point2 *res1 = NULL, point2 *res2 = NULL) {
	double d = dis(a - b.a);
	point2 u = (a - b.a) / d;
	if (d / b.r > 1 + eps) {
		double th = acos(b.r / d);
		if (res1 != NULL) *res1 = b.a + rotate(u * b.r, th);
		if (res2 != NULL) *res2 = b.a + rotate(u * b.r, -th);
		return 2;
	} else if (d / b.r > 1 - eps) {
		if (res1 != NULL) *res1 = a;
		return 1;
	} else
		return 0;
}
int circle_circle_tangent(circle2 a, circle2 b, line2 *reso1 = NULL, line2 *reso2 = NULL, line2 *resi1 = NULL, line2 *resi2 = NULL) {
	double d = dis(a.a - b.a);
	point2 u = (b.a - a.a) / d;
	int cnt = 0;
	if ((d - fabs(a.r - b.r)) / (a.r + b.r) > eps) {
		double th = acos((a.r - b.r) / d);
		if (reso1 != NULL) {
			reso1->a = a.a + rotate(u * a.r, th);
			reso1->s = b.a + rotate(u * b.r, th) - reso1->a;
		}
		if (reso2 != NULL) {
			reso2->a = a.a + rotate(u * a.r, -th);
			reso2->s = b.a + rotate(u * b.r, -th) - reso2->a;
		}
		cnt += 2;
	} else if ((d - fabs(a.r - b.r)) / (a.r + b.r) > -eps) {
		if (a.r / b.r < 1 - eps) {
			if (reso1 != NULL) {
				reso1->a = b.a - u * b.r;
				reso1->s = rotate(u, pi / 2);
			}
			cnt++;
		} else if (a.r / b.r > 1 + eps) {
			if (reso1 != NULL) {
				reso1->a = a.a + u * a.r;
				reso1->s = rotate(u, pi / 2);
			}
			cnt++;
		} else return -1;
	}
	if (d / (a.r + b.r) > 1 + eps) {
		double th = acos((a.r + b.r) / d);
		if (resi1 != NULL) {
			resi1->a = a.a + rotate(u * a.r, th);
			resi1->s = b.a - rotate(u * b.r, th) - resi1->a;
		}
		if (resi2 != NULL) {
			resi2->a = a.a + rotate(u * a.r, -th);
			resi2->s = b.a - rotate(u * b.r, -th) - resi2->a;
		}
		cnt += 2;
	} else if (d / (a.r + b.r) > 1 - eps) {
		if (resi1 != NULL) {
			resi1->a = a.a + u * a.r;
			resi1->s = rotate(u, pi / 2);
		}
		cnt++;
	}
	return cnt;
}
typedef std::vector<point2> convex2;
double area(const convex2 &a) {
	double s = 0;
	for (int i = 0; i < a.size(); i++)
		s += a[i] % a[(i+1)%a.size()];
	return fabs(s)/2;
}
int point_convex_inside(point2 a, const convex2 &b) {
	double sum = 0;
	for (int i = 0; i < b.size(); i++)
		sum += fabs((b[i] - a) % (b[(i+1)%b.size()] - a));
	return fabs(sum / (2*area(b)) - 1) < eps;
}
int line_convex_cross(line2 a, const convex2 &b, point2 *res1, point2 *res2) {
	int cnt = 0;
	for (int i = 0; i < b.size(); i++) {
		line2 ltmp; point2 ptmp;
		ltmp.a = b[i], ltmp.s = b[(i+1)%b.size()] - b[i];
		int flag = line_line_cross(a, ltmp, &ptmp);
		if (flag == -1) return -1;
		if (flag == 0) continue;
		double k = (ptmp - ltmp.a) * ltmp.s / (ltmp.s * ltmp.s);
		if (k < eps || k > 1+eps) continue;
		if (cnt == 0 && res1 != NULL) *res1 = ptmp;
		else if (cnt == 1 && res2 != NULL) *res2 = ptmp;
		cnt++;
	}
	return cnt;
}
int convex_gen_cmp(point2 a, point2 b) {
	return a.y < b.y - eps || fabs(a.y - b.y) < eps && a.x < b.x - eps;
}
int convex_gen(const convex2 &a, convex2 &b) {
	std::deque<point2> q;
	convex2 t(a);
	std::sort(t.begin(), t.end(), convex_gen_cmp);
	q.push_back(t[0]), q.push_back(t[1]);
	for (int i = 2; i < t.size(); i++) {
		while (q.size() > 1 && ((t[i]-q[q.size()-1]) % (q[q.size()-1]-q[q.size()-2]) > 0 || parallel(t[i]-q[q.size()-1], q[q.size()-1]-q[q.size()-2])))
			q.pop_back();
		q.push_back(t[i]);
	}
	int pretop = q.size();
	for (int i = t.size()-1; i >= 0; i--) {
		while (q.size() > pretop && ((t[i]-q[q.size()-1]) % (q[q.size()-1]-q[q.size()-2]) > 0 || parallel(t[i]-q[q.size()-1], q[q.size()-1]-q[q.size()-2])))
			q.pop_back();
		q.push_back(t[i]);
	}
	q.pop_back();
	if (q.size() < 3) {
		b.clear();
		return 0;
	}
	b.clear();
	for (int i = 0; i < q.size(); i++) b.push_back(q[i]);
}
int halfplane_cross_cmp(line2 a, line2 b) {
	double c1 = arg(a.s), c2 = arg(b.s);
	return c1 < c2-eps || fabs(c1-c2) < eps && b.s % (a.a - b.a) / dis(b.s) > eps;
}
int halfplane_cross(const std::vector<line2> &a, convex2 &b) {
	std::vector<line2> t(a);
	std::sort(t.begin(), t.end(), halfplane_cross_cmp);
	int j = 0;
	for (int i = 0; i < t.size(); i++)
		if (!i || arg(t[i].s) > arg(t[i-1].s) + eps) t[j++] = t[i];
	if (j > 0 && arg(t[j].s) > arg(t[0].s) + 2*pi - eps) j--;
	t.resize(j);
	std::deque<line2> q;
	q.push_back(t[0]), q.push_back(t[1]);
	point2 p;
	for (int i = 2, k = 0; i < t.size(); i++) {
		for (; k < q.size() && t[i].s % q[k].s > 0; k++);
		if (k > 0 && k < q.size() && q[q.size()-1].s % q[0].s > 0 && !parallel(q[q.size()-1].s, q[0].s)) {
			double r1 = (line_line_cross(q[k], q[k-1], &p), t[i].s % (p - t[i].a) / dis(t[i].s));
			double r2 = (line_line_cross(q[0], q[q.size()-1], &p), t[i].s % (p - t[i].a) / dis(t[i].s));
			if (r1 < eps && r2 < eps) {
				b.clear();
				return 0;
			} else if (r1 > -eps && r2 > -eps)
				continue;
		}
		while (q.size() > 1 && (line_line_cross(q[q.size()-1], q[q.size()-2], &p), t[i].s % (p - t[i].a) / dis(t[i].s) < eps)) {
			q.pop_back();
			if (k == q.size()) k--;
		}
		while (q.size() > 1 && (line_line_cross(q[0], q[1], &p), t[i].s % (p - t[i].a) / dis(t[i].s) < eps)) {
			q.pop_front();
			k--; if (k < 0) k = 0;
		}
		q.push_back(t[i]);
	}
	b.clear();
	for (int i = 0; i < q.size(); i++) {
		line_line_cross(q[i], q[(i+1)%q.size()], &p);
		b.push_back(p);
	}
	return 1;
}

struct point3 {
	double x, y, z;
	point3& operator += (point3 a) {
		x += a.x, y += a.y, z += a.z;
		return *this;
	}
	point3& operator -= (point3 a) {
		x -= a.x, y -= a.y, z -= a.z;
		return *this;
	}
	point3& operator *= (double a) {
		x *= a, y *= a, z *= a;
		return *this;
	}
	point3& operator /= (double a) {
		x /= a, y /= a, z /= a;
		return *this;
	}
};
point3 operator + (point3 a, point3 b) {
	point3 c; c = a; c += b; return c;
}
point3 operator - (point3 a, point3 b) {
	point3 c; c = a; c -= b; return c;
}
point3 operator * (point3 a, double b) {
	point3 c; c = a; c *= b; return c;
}
point3 operator * (double a, point3 b) {
	point3 c; c = b; c *= a; return c;
}
point3 operator / (point3 a, double b) {
	point3 c; c = a; c /= b; return c;
}
double operator * (point3 a, point3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
point3 operator % (point3 a, point3 b) {
	point3 c;
	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return c;
}
double dis(point3 a) {
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}
int parallel(point3 a, point3 b) {
	return fabs((a % b) * (a % b) / ((a * a) * (b * b))) < eps;
}
int perpend(point3 a, point3 b) {
	return fabs((a * b) * (a * b) / ((a * a) * (b * b))) < eps;
}
struct line3 {
	point3 a, s;
};
struct face3 {
	point3 a, n;
};
struct circle3 {
	point3 a;
	double r;
};
point2 project(point3 a, face3 b, point3 xs) {
	point3 ys; ys = b.n % xs;
	point2 c; c.x = ((a - b.a) * xs) / dis(xs), c.y = ((a - b.a) * ys) / dis(ys);
	return c;
}
line2 project(line3 a, face3 b, point3 xs) {
	line2 c; c.a = project(a.a, b, xs), c.s = project(a.a + a.s, b, xs) - c.a;
	return c;
}
point3 revproject(point2 a, face3 b, point3 xs) {
	point3 ys; ys = b.n % xs;
	return a.x * xs / dis(xs) + a.y * ys / dis(ys) + b.a;
}
line3 revproject(line2 a, face3 b, point3 xs) {
	line3 c; c.a = revproject(a.a, b, xs), c.s = revproject(a.a + a.s, b, xs) - c.a;
	return c;
}
double point_line_dis(point3 a, line3 b, point3 *res = NULL) {
	point3 p;
	p = b.a + ((a - b.a) * b.s) / (b.s * b.s) * b.s;
	if (res != NULL) *res = p;
	return dis(a - p);
}
double point_face_dis(point3 a, face3 b, point3 *res = NULL) {
	point3 p;
	p = ((a - b.a) * b.n) / (b.n * b.n) * b.n;
	if (res != NULL) *res = a - p;
	return dis(p);
}
double line_line_dis(line3 a, line3 b, point3 *resa = NULL, point3 *resb = NULL) {
	point3 p;
	if (parallel(a.s, b.s)) {
		double d = point_line_dis(a.a, b, &p);
		if (resa != NULL) *resa = a.a;
		if (resb != NULL) *resb = p;
		return d;
	}
	point3 n = a.s % b.s;
	face3 f; f.a = b.a, f.n = n;
	double d = point_face_dis(a.a, f, &p);
	double k1 = ((b.a - p) % b.s) * n / (n * n);
	if (resb != NULL) *resb = p + k1 * a.s;
	if (resa != NULL) *resa = a.a + k1 * a.s;
	return d;
}
int line_face_cross(line3 a, face3 b, point3 *res = NULL) {
	if (perpend(a.s, b.n))
		if (perpend(b.a - a.a, b.n))
			return -1;
		else
			return 0;
	double k = (b.a - a.a) * b.n / (a.s * b.n);
	if (res != NULL) *res = a.a + k * a.s;
	return 1;
}
int face_face_cross(face3 a, face3 b, line3 *res = NULL) {
	if (parallel(a.n, b.n))
		if (perpend(b.a - a.a, a.n))
			return -1;
		else
			return 0;
	point3 s = a.n % b.n;
	point3 p;
	line3 t; t.a = a.a, t.s = a.n % s;
	line_face_cross(t, b, &p);
	if (res != NULL)
		res->a = p, res->s = s;
	return 1;
}
