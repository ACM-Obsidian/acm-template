int dfs[MAXN], low[MAXN], tim = 0;

inline void Dfs(int u) {
	dfs[u] = low[u] = ++tim;
	for (Edge *p = a[u]; p; p = p->next) if (p->flag) {
		if (!dfs[p->y]) {
			p->opt->flag = false;
			Dfs(p->y);
			low[u] = min(low[u], low[p->y]);
		} else low[u] = min(low[u], dfs[p->y]);
	}
	for (Edge *p = a[u]; p; p = p->next) if (p->opt->flag == false && low[p->y] > dfs[u]) {
		p->bridge = p->opt->bridge = true;
	}
}

