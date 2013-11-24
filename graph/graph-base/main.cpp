struct Edge {
	int y; Edge *next, *opt; bool flag, bridge;
	Edge(int y, Edge *next):y(y), next(next){flag = true; bridge = false;}
}*a[MAXN], POOL[MAXM], *data = POOL;

inline void AddEdge(int x, int y, bool t = true) {
        Edge *tmp = a[x];
        a[x] = data++; a[x]->y = y; a[x]->next = tmp; a[x]->flag = true;
        tmp = a[y];
        a[y] = data++; a[y]->y = x; a[y]->next = tmp; a[y]->flag = t;
        a[x]->opt = a[y];
        a[y]->opt = a[x];
}

