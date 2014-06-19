const int MAXN = 210;
int nx, ny; // 左边的点标号从1到nx，右边点标号从1到ny
long long inf, cost[MAXN][MAXN], fx[MAXN], fy[MAXN], dist[MAXN]; //权值若为long long的话，只需改动此行即可
int used[MAXN], maty[MAXN], which[MAXN];
inline void AddEdge(int x, int y, int z) {
	cost[x][y] = z;
}
pair<int, long long> KM(void) {
	for (int x = 1; x <= nx; x++) {
		int y0 = 0; maty[0] = x;
		for (int y = 0; y <= ny; y++) { dist[y] = inf + 1; used[y] = false; }
		do {
			used[y0] = true;
			int x0 = maty[y0], y1;
			long long delta = inf + 1;
			for (int y = 1; y <= ny; y++) if (!used[y]) {
				long long curdist = cost[x0][y] - fx[x0] - fy[y];
				if (curdist < dist[y]) {
					dist[y] = curdist;
					which[y] = y0;
				}
				if (dist[y] < delta) {
					delta = dist[y];
					y1 = y;
				}
			}
			for (int y = 0; y <= ny; y++) if (used[y]) {
				fx[maty[y]] += delta;
				fy[y] -= delta;
			} else dist[y] -= delta;
			y0 = y1;
		} while (maty[y0] != 0);
		do {
			int y1 = which[y0];
			maty[y0] = maty[y1];
			y0 = y1;
		} while (y0);
	}
	long long ret = 0;
	int npair = 0;
	for (int y = 1; y <= ny; y++) {
		int x = maty[y];
		if (cost[x][y] < inf) {
			ret += cost[x][y];
			npair++;
		}
	}
	return make_pair(npair, ret);
}
inline void clear(void) {
	memset(fx, 0, sizeof fx);
	memset(fy, 0, sizeof fy);
	memset(cost, 0x3f, sizeof cost);
	memset(maty, 0, sizeof maty);
	inf = cost[0][0];
}
