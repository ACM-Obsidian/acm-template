struct Node {
	Edge *begin; int u;
}stack[MAXN]; int top = 0;

int dfs[MAXN], *low, tim = 0, father[MAXN];

inline void Dfs(int uu) {
	top = 1; stack[1].u = uu, stack[1].begin = a[uu];
	while (top) {
		Node &now = stack[top];
		int u = now.u;
		if (now.begin == a[u]) 
			dfs[u] = low[u] = ++tim;
		if (now.begin) {
			while (now.begin) {
				Edge *p = now.begin; now.begin = p->next;
				if (p->y > k && p->flag) {
					if (!dfs[p->y]) {
						p->opt->flag = false;
						stack[++top].u = p->y, stack[top].begin = a[p->y];
						father[p->y] = u;
						break;
					}else low[u] = min(low[u], dfs[p->y]);
				}
			}
		} else {
			if (father[u]) low[father[u]] = min(low[father[u]], low[u]);
			for (Edge *p = a[u]; p; p = p->next) if (p->y > k && p->opt->flag == false && low[p->y] > dfs[u]) {
				p->bridge = p->opt->bridge = true;
				p->opt->flag = true;
			}
			top--;
		}
	}
}
