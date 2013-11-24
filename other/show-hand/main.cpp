#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 3000000;

class DYF {public:
	int c[5]; int type;
}a[MAXN]; int N;

inline int getType(const DYF& a) {
	const int *c = a.c;
	if (a.type == 4) return 11;
	if (a.type == 3) return 10;
	if (c[0] == c[3] || c[1] == c[4]) return 9;
	if ((c[0] == c[2] && c[3] == c[4]) || (c[0] == c[1] && c[2] == c[4])) return 8;
	if (a.type == 1) return 7;
	if (c[0] == 1 && c[1] == 10 && c[2] == 11 && c[3] == 12 && c[4] == 13) return 6;
	bool strai = true; for (int j = 1; j <= 4; j++) if (c[j] != c[j - 1] + 1) {strai = false; break;}
	if (strai) return 5;
	for (int i = 2; i <= 4; i++) if (c[i] == c[i - 2]) return 4;
	int pairs = 0;
	for (int i = 1; i <= 4; i++) if (c[i] == c[i - 1]) pairs++;
	return pairs + 1;
}

inline bool V_cmp(const DYF& a, const DYF& b) {
	vector<int> A(a.c, a.c + 5), B(b.c, b.c + 5);
	for (int i = 0; i < (int)A.size(); i++) if (A[i] == 1) A[i] = 14;
	for (int i = 0; i < (int)B.size(); i++) if (B[i] == 1) B[i] = 14;
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());
	A.erase(unique(A.begin(), A.end()), A.end()); reverse(A.begin(), A.end());
	B.erase(unique(B.begin(), B.end()), B.end()); reverse(B.begin(), B.end());
	return A < B;
}

inline bool comp(int a, int b) {
	if (a == 1) a = 14; if (b == 1) b = 14; return a < b;
}

inline bool cmp(DYF a, DYF b) {
	int gA = getType(a), gB = getType(b);
	if (gA != gB) return gA < gB; else {
		if (gA == 1 || gA == 7) {
			return V_cmp(a, b);
		}else
		if (gA == 2 || gA == 4 || gA == 9) {
			int l1, l2; for (int i = 1; i <= 4; i++) {if (a.c[i] == a.c[i - 1]) l1 = i; if (b.c[i] == b.c[i - 1]) l2 = i;}
			if (a.c[l1] != b.c[l2]) return comp(a.c[l1], b.c[l2]); else {
				return V_cmp(a, b);
			}
		} else
		if (gA == 3) {
			int l1 = 0, r1 = 0, l2 = 0, r2 = 0;
			for (int i = 0; i <= 4; i++) {
				if (a.c[i] == 1) a.c[i] = 14;
				if (b.c[i] == 1) b.c[i] = 14;
			}
			sort(a.c, a.c + 5);
			sort(b.c, b.c + 5);
			for (int i = 1; i <= 4; i++) {
				if (a.c[i] == a.c[i - 1]) {if (l1 == 0) l1 = i; else r1 = i;}
				if (b.c[i] == b.c[i - 1]) {if (l2 == 0) l2 = i; else r2 = i;}
			}
			if (a.c[r1] != b.c[r2]) return comp(a.c[r1], b.c[r2]);
			if (a.c[l1] != b.c[l2]) return comp(a.c[l1], b.c[l2]);
			return V_cmp(a, b);
		} else
		if (gA == 6 || gA == 11) {
			return false;
		} else
		if (gA == 8) {
			int l2, l3, r2, r3;
			if (a.c[2] == a.c[0]) l2 = 3, l3 = 0; else l2 = 0, l3 = 3;
			if (b.c[2] == b.c[0]) r2 = 3, r3 = 0; else r2 = 0, r3 = 3;
			if (a.c[l3] != b.c[r3]) return comp(a.c[l3], b.c[r3]); else return comp(a.c[l2], b.c[r2]);
		} else
		if (gA == 5 || gA == 10) {
			if (a.c[0] == 1 && a.c[1] != 2) a.c[0] = 14, sort(a.c, a.c + 1);
			if (b.c[0] == 1 && b.c[1] != 2) b.c[0] = 14, sort(b.c, b.c + 1);
			return a.c[4] < b.c[4];
		} 
		return 0;
	}
}

inline bool eq(int *l1, int *r1, int *l2, int *r2) {
	while (l1 != r1) if (*l1 != *l2) return false; else l1++, l2++;
	return true;
}

int stack[6], top;

inline void Gen(int now, int step){
	if (step > 5 || now > 13) {
		if (step > 5) {
			if (stack[1] == stack[5]) return;
			N++;
			for (int i = 1; i <= 5; i++) a[N].c[i - 1] = stack[i];
		}
		return;
	}
	Gen(now + 1, step);
	register int t = step, back = top;
	for (;t <= 5; t++) {
		stack[++top] = now;
		Gen(now + 1, t + 1);
	}
	top = back;
}

char ch[5][5];
int fim[100], num[5];

int main(void) {
	//freopen("in", "r", stdin);
	//freopen("out", "w", stdout);
	Gen(1, 1);
	int n = N;
	for (int i = 1; i <= N; i++) {
		bool B = false;
		for (int j = 1; j <= 4; j++) if (a[i].c[j] == a[i].c[j - 1]) {B = true; break;}
		if (B) continue;
		memcpy(a[++n].c, a[i].c, sizeof a[i].c);
		a[n].type = 1;
		bool inc = true;
		if (a[n].c[0] == 1 && a[n].c[1] == 10 && a[n].c[2] == 11 && a[n].c[3] == 12 && a[n].c[4] == 13) {
			a[n].type = 4;
		} else {
			for (int j = 1; j <= 4; j++) if (a[n].c[j] != a[n].c[j - 1] + 1) {
				inc = false;
				break;
			}
			if (inc) {
				a[n].type = 3;
			}
		}
	}
	N = n;
	for (int i = 2; i <= 9; i++) fim[i + 48] = i; fim['T'] = 10; fim['A'] = 1; fim['J'] = 11; fim['Q'] = 12; fim['K'] = 13;
	while (scanf("%s %s %s %s %s", ch[0], ch[1], ch[2], ch[3], ch[4]) == 5) {
		bool same = true;
		for (int i = 0; i < 5; i++) num[i] = fim[(int)ch[i][0]];
		sort(num, num + 5);
		for (int i = 1; i < 5; i++) if (ch[i][1] != ch[0][1]) {same = false; break;}
		memcpy(a[N + 1].c, num, sizeof num); a[N + 1].type = 0;
		if (same) {
			n = N + 1;
			a[n].type = 1; bool inc = true;
			if (a[n].c[0] == 1 && a[n].c[1] == 10 && a[n].c[2] == 11 && a[n].c[3] == 12 && a[n].c[4] == 13) {
				a[n].type = 4;
			} else {
				for (int j = 1; j <= 4; j++) if (a[n].c[j] != a[n].c[j - 1] + 1) {
					inc = false;
					break;
				}
				if (inc) {
					a[n].type = 3;
				}
			}
		}
		int cnt = 0;
		for (int i = 1; i <= N; i++) {
			if (cmp(a[i], a[N + 1])) cnt++;
		}
		printf("%d\n", cnt + 1);
	}
	return 0;
}
