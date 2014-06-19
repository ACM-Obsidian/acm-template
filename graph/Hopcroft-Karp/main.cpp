const int MAXN = 10000;
int match[MAXN];  
int levelx[MAXN], levely[MAXN], link[MAXN]; 
int d[MAXN]; 
inline bool Bfs(void) { 
	int head = 1, tail = 0; 
	memset(levely, 0, sizeof levely); 
	for (int i = 1; i <= n; i++) { 
		if (!match[i]) d[++tail] = i; 
		levelx[i] = 0; 
	} 
	bool ret = false; 
	while (head <= tail) { 
		int now = d[head++]; 
		for (Edge *p = a[now]; p; p = p->next) if (levely[p->y] == 0) { 
			levely[p->y] = levelx[now] + 1; 
			if (link[p->y] == 0) ret = true; 
			else levelx[link[p->y]] = levely[p->y] + 1, d[++tail] = link[p->y]; 
		} 
	} 
	return ret; 
} 
bool Find(int u) { 
	for (Edge *p = a[u]; p; p = p->next) if (levely[p->y] == levelx[u] + 1) { 
		levely[p->y] = 0; 
		if (link[p->y] == 0 || Find(link[p->y])) { 
			match[u] = p->y; link[p->y] = u; 
			return true; 
		} 
	} 
	return false; 
} 
inline void Match(void) { 
	while (Bfs()) 
		for (int i = 1; i <= n; i++) 
			if (!match[i]) Find(i); 
} 
inline void clear(void) {
	memset(match, 0, sizeof match);
	memset(link, 0, sizeof link);
	memset(levelx, 0, sizeof levelx);
	memset(levely, 0, sizeof levely);
}
