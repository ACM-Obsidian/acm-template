class Tree {public:
	//general
	const static int MAXN = 100010;
	const static int MAXP = 17;

	struct Edge {
		int y, z; Edge *next;
	}*a[MAXN], POOL[MAXN << 1], *data;

	inline void AddEdge(int x, int y, int z = 0) {
		Edge *tmp = a[x];
		a[x] = data++; a[x]->y = y; a[x]->z = z; a[x]->next = tmp;
		tmp = a[y];
		a[y] = data++; a[y]->y = x; a[y]->z = z; a[y]->next = tmp;
	}

	int deep[MAXN], father[MAXN], d[MAXN];

	int f[MAXP][MAXN]; //For LCA only
	inline void Bfs(void) {
		int head = 1, tail = 1; d[1] = 1; deep[1] = 0;
		while (head <= tail) {
			int now = d[head++];
			for (int k = 1; (1 << k) <= deep[now]; k++) f[k][now] = f[k - 1][f[k - 1][now]]; //For LCA only
			for (Edge *p = a[now]; p; p = p->next) if (p->y != father[now]) {
				d[++tail] = p->y;
				deep[p->y] = deep[now] + 1;
				f[0][p->y] = father[p->y] = now; //For LCA only
			}
		}
	}

	//LCA
	inline void GoUP(int &y, int d) {
		for (int j = MAXP; j >= 0; j--) if (d & (1 << j)) y = f[j][y];
	}
	inline int LCA(int x, int y) {
		if (deep[x] > deep[y]) swap(x, y);
		GoUP(y, deep[y] - deep[x]);
		if (x == y) return x;
		for (int j = MAXP; j >= 0; j--) if (f[j][x] != f[j][y]) {
			x = f[j][x];
			y = f[j][y];
		}
		return f[0][y];
	}

	//Clear
	inline void clear(void) {
		memset(a, 0, sizeof a); data = POOL; memset(father, 0, sizeof father);
		memset(f, 0, sizeof f); //For LCA only
	}
};

