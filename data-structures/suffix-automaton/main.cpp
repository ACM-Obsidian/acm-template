struct Node {
	Node *next[26], *par; int val, end; // 26 is volatile
}POOL[MAXN << 1], *data, *root, *last; //Note that the size of POOL should be doubled.

inline void Add(int x) {
	Node *p = last, *np = data++;
	np->val = p->val + 1; np->end = true;
	while (p && !p->next[x]) 
		p->next[x] = np, p = p->par;
	if (p == 0) {
		np->par = root;
	} else {
		Node *q = p->next[x];
		if (q->val == p->val + 1) {
			np->par = q;
		} else {
			Node *nq = data++;
			nq->val = p->val + 1;
			memcpy(nq->next, q->next, sizeof q->next);
			nq->par = q->par;
			np->par = q->par = nq;
			while (p && p->next[x] == q)
				p->next[x] = nq, p = p->par;
		}
	}
	last = np;
}

