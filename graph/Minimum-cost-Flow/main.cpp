struct Edge {
    int y, f, c; Edge *next, *opt;
    Edge(int y, int f, int c, Edge *next):y(y), f(f), c(c), next(next){}
}*a[MAXN];
inline void AddEdge(int x, int y, int f, int c) {
    a[x] = new Edge(y, f, c, a[x]);
    a[y] = new Edge(x, 0, -c, a[y]);
    a[x]->opt = a[y]; a[y]->opt = a[x];
}
int d[MAXN], vis[MAXN], dis[MAXN]; Edge *path[MAXN];
inline pair<int, int> Spfa(void) {
    int Flow = 0, Cost = 0;
    while (true) {
        memset(vis, 0, sizeof vis);
        memset(dis, 0x7f, sizeof dis);
        memset(path, 0, sizeof path);
        int head = 1, tail = 1, sum = 1; d[1] = vs; vis[vs] = true; dis[vs] = 0;
        while (sum) {
            int now = d[head++]; if (head == MAXN) head = 1; sum--;
            for (Edge *p = a[now]; p; p = p->next) if (p->f > 0 && dis[p->y] > dis[now] + p->c) {
                dis[p->y] = dis[now] + p->c;
                path[p->y] = p;
                if (!vis[p->y]) {
                    ++tail; if (tail == MAXN) tail = 1; sum++;
                    d[tail] = p->y;
                    vis[p->y] = true;
                }
            }
            vis[now] = false;
        }
        if (dis[vt] == dis[0]) return make_pair(Flow, Cost);
        int tmp = vt, Min = ~0U>>1;
        while (path[tmp]) {
            Min = min(Min, path[tmp]->f);
            tmp = path[tmp]->opt->y;
        }
        Flow += Min;
        tmp = vt;
        while (path[tmp]) {
            path[tmp]->f -= Min;
            path[tmp]->opt->f += Min;
            Cost += Min * path[tmp]->c;
            tmp = path[tmp]->opt->y;
        }
    }
    return make_pair(Flow, Cost);
}
