struct Edge {
	int y, f; Edge *next, *opt;
}*a[MAXN], DATA[MAXM << 1], *data = DATA;
inline void Add(int x, int y, int c) {
	Edge *tmp = data++;
	tmp->y = y; tmp->f = c, tmp->next = a[x]; a[x] = tmp;
	tmp = data++; tmp->y = x; tmp->f = 0; tmp->next = a[y]; a[y] = tmp;
	a[x]->opt = a[y]; a[y]->opt = a[x];
}
int n, m, vs, vt, L;
int level[MAXN], d[MAXN];
inline bool Bfs(void) {
	memset(level, -1, sizeof level);
	d[1] = vs; level[vs] = 0;
	int head = 1, tail = 1;
	while (head <= tail) {
		int now = d[head++];
		e[now] = a[now];
		for (Edge *p = a[now]; p; p = p->next) if (p->f > 0&& level[p->y] == -1)
			level[d[++tail] = p->y] = level[now] + 1;
	}
	return level[vt] != -1;
}
inline int Extend(int u, int sum) {
	if (u == vt) return sum;
	int r = 0, t;
	for (Edge *p = e[u]; p && r < sum; p = p->next) if (level[p->y] == level[u] + 1 && p->f > 0) {
		t = std::min(sum - r, p->f);
		t = Extend(p->y, t);
		p->f -= t, p->opt->f += t, r += t;
		e[u] = p;
	}
	if (!r) level[u] = -1;
	return r;
}
inline int Dinic(void) {
	int r = 0, t;
	while (Bfs()) {
		while ((t = Extend(vs, inf))) r += t;
	}
	return r;
}
