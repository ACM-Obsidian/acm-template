#include <iostream>
#include <algorithm>
#include <utility>
#include <set>
#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
using namespace std;
#define FOR(x,y,z) for(int x(y);x<=z;++x)
#define ROF(x,y,z) for(int x(y);x>=z;--x)
#define eps (1e-6)
#define clr(x,y) memset(x,y,sizeof(x))
#define mcp(x,y) memcpy(x,y,sizeof(y))
const int N=10010,M=1010;

double a[M][N];
int db[M],dn[N],next[N],n,m;

void pivot(int l,int e) {
	double t; int p;
	swap(db[l],dn[e]), t=-a[l][e], a[l][e]=-1, p=N-1;
	FOR(j,0,n) if (abs(a[l][j]/=t)>eps) p=next[p]=j; next[p]=N;
	FOR(i,0,m) if (i!=l && abs(t=a[i][e])>eps)
		for (a[i][e]=0,p=next[N-1];p!=N;p=next[p]) a[i][p]+=a[l][p]*t;
}

void solve() {
	double tmax,t; int l,e;
	for (;;) {
		l=e=0, tmax=-1e20;
		for(e=n;e;--e) if (a[0][e]>eps) break; if (e==0) return;
		FOR(i,1,m) if (a[i][e]<-eps && (t=a[i][0]/a[i][e])>tmax) tmax=t, l=i; if (l==0) return;
		pivot(l,e);
	}
}

bool ini() {
	double tmin=1e20; int l=0; 
	mcp(a[m+1],a[0]); ++n;
	FOR(i,1,n) dn[i]=i; FOR(i,1,m) db[i]=n+i;
	FOR(i,1,m) if (a[i][0]<tmin) tmin=a[i][0], l=i;
	if (tmin>eps) return true;
	clr(a[0],0), a[0][n]=-1; FOR(i,1,m) a[i][n]=1; pivot(l,n);
	solve(); if (a[0][0]<-eps) return false; clr(a[0],0);
	FOR(i,1,n) if (dn[i]==n) {
		dn[i]=dn[n];
		FOR(j,1,m) a[j][i]=a[j][n]; --n; break;
	}
	FOR(i,1,n) if (dn[i]<=n) a[0][i]+=a[m+1][dn[i]];
	FOR(i,1,m) if (db[i]<=n) FOR(j,0,n) a[0][j]+=a[i][j]*a[m+1][db[i]];
	return true;
}

int main() {
	freopen("employee.in","r",stdin);
	freopen("employee.out","w",stdout);
	scanf("%d%d",&m,&n);
	FOR(i,1,m) scanf("%lf",&a[i][0]), a[i][0]=-a[i][0];
	FOR(j,1,n) {
		int s,t,c; scanf("%d%d%d",&s,&t,&c);
		FOR(i,s,t) a[i][j]=1;
		a[0][j]=-c;
	}
	ini(); solve();
	printf("%.0f\n",-a[0][0]);
	fclose(stdin); fclose(stdout);
}
