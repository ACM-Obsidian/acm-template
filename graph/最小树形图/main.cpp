typedef pair<int, int> PII;
PII tmp[MAXN];
int dis[MAXN][MAXN]; int map[MAXN][MAXN];
int vis[MAXN], q[MAXN], inp[MAXN];
int Dfs(int u) {
	vis[u] = true; int ret = 1;
	for (int i = 1; i <= n; i++) if (map[u][i] && !vis[i]) ret += Dfs(i);
	return ret;
}
int Zhuliu(void) {
	memset(map, 0, sizeof map);
	memset(vis, 0, sizeof vis);
	if (Dfs(1) != n) return -1;
	int done = 0;
	while (true) {
		memset(vis, 0, sizeof vis); memset(inp, 0, sizeof inp);
		int Ans = 0;
		for (int i = 1; i <= n; i++) vis[i] = i;
		for (int i = 2; i <= n; i++) {
			tmp[i] = PII(1000000000, 0);
			for (int j = 1; j <= n; j++) if (map[j][i] == 1) tmp[i] = min(tmp[i], PII(dis[j][i], j));
			inp[tmp[i].second]++; if (tmp[i].second) Ans += tmp[i].first;
		}
		int head = 1, tail = 0;
		for (int i = 1; i <= n; i++) if (!inp[i]) q[++tail] = i;
		while (head <= tail) {
			int now = q[head++];
			if (!--inp[tmp[now].second]) q[++tail] = tmp[now].second;
		}
		bool ok = true;
		for (int i = 1, t; i <= n; i++) if (inp[i] > 0) {
			t = i; ok = false;
			do {
				inp[t] = -i;
				t = tmp[t].second;
				vis[t] = i;
			} while (t != i);
		}
		if (ok) return Ans + done;
		for (int i = 1; i <= n; i++) if (inp[i] < 0) {
			done += tmp[i].first;
			for (int j = 1; j <= n; j++) if (vis[j] != vis[i]) {
				if (map[i][j]) {
					map[vis[i]][vis[j]] = 1;
					dis[vis[i]][vis[j]] = min(dis[vis[i]][vis[j]], dis[i][j]);
				}
				if (map[j][i]) {
					dis[vis[j]][vis[i]] = min(dis[vis[j]][vis[i]], dis[j][i] - tmp[i].first);
					map[vis[j]][vis[i]] = 1;
				}
			}
			if (vis[i] != i) for (int j = 1; j <= n; j++) map[i][j] = map[j][i] = 0;
		}
	}
}
